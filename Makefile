# Top-level convenience targets. The real build lives in code/Makefile.
#
#   make                 build USA 1.0
#   make usa11           build USA 1.1
#   make exheaders       generate the exheaders for both versions and targets
#   make release         build everything and lay out release/ for upload
#   make check           re-verify the address table and both patches
#   make clean

TITLE_ID    := 0004000000125500
RELEASE_DIR := release
VERSION     := $(shell git describe --tags --always --dirty 2>/dev/null || echo dev)

# Each package is named for the game version and the target it is for, and the
# exheader inside is always called exheader.bin -- that is the name both Luma
# and Emu look for, so there is nothing for the user to rename or pick.
PACKAGES := usa1.0-console usa1.0-emulator usa1.1-console usa1.1-emulator

# Copy the generated exheaders into a version's two packages, if they exist.
# They will not when building without the game's own exheader to derive from --
# CI can still publish the patches, and `make exheaders` fills the gap locally.
define stage_exheader
if [ -f code/build/exheader.bin ]; then \
	cp code/build/exheader.bin $(RELEASE_DIR)/$(1)-console/exheader.bin; \
	cp code/build/exheader_emulator.bin $(RELEASE_DIR)/$(1)-emulator/exheader.bin; \
else \
	echo "note: no exheader for $(1); packaging the patch only"; \
fi
endef

.PHONY: all usa10 usa11 exheaders release check clean

all: usa10

usa10:
	@$(MAKE) -C code

usa11:
	@$(MAKE) -C code usa11=1

exheaders:
	@$(MAKE) -C code exheaders
	@$(MAKE) -C code exheaders usa11=1

check:
	@python3 tools/mapaddr.py --check
	@python3 tools/mapaddr.py --regcheck
	@for v in 0 1; do \
		$(MAKE) --no-print-directory -C code clean >/dev/null; \
		$(MAKE) --no-print-directory -C code usa11=$$v >/dev/null || exit 1; \
		if [ $$v = 0 ]; then ips=basecode.ips; bin=code1.0.bin; \
		else ips=basecode1.1.ips; bin=code1.1.bin; fi; \
		printf 'usa11=%s  ' $$v; \
		python3 tools/verify_ips.py code/$$ips bin/$$bin \
			--elf code/code.elf --exheader code/build/exheader.bin | tail -1 || exit 1; \
	done

release:
	@rm -rf $(RELEASE_DIR)
	@for p in $(PACKAGES); do mkdir -p $(RELEASE_DIR)/$$p; done
	@$(MAKE) --no-print-directory -C code clean >/dev/null
	@$(MAKE) --no-print-directory -C code >/dev/null
	@cp code/basecode.ips $(RELEASE_DIR)/usa1.0-console/code.ips
	@cp code/basecode.ips $(RELEASE_DIR)/usa1.0-emulator/code.ips
	@$(call stage_exheader,usa1.0)
	@$(MAKE) --no-print-directory -C code clean >/dev/null
	@$(MAKE) --no-print-directory -C code usa11=1 >/dev/null
	@cp code/basecode1.1.ips $(RELEASE_DIR)/usa1.1-console/code.ips
	@cp code/basecode1.1.ips $(RELEASE_DIR)/usa1.1-emulator/code.ips
	@$(call stage_exheader,usa1.1)
	@for p in $(PACKAGES); do \
		sed -e 's/@VERSION@/$(VERSION)/g' -e 's/@PACKAGE@/'$$p'/g' \
		    -e 's/@TITLE_ID@/$(TITLE_ID)/g' \
		    docs/install-template.md > $(RELEASE_DIR)/$$p/INSTALL.md; \
		( cd $(RELEASE_DIR) && python3 -m zipfile -c mm3d-practice-$(VERSION)-$$p.zip $$p ); \
	done
	@echo "$(RELEASE_DIR)/ ($(VERSION)):"
	@ls -1 $(RELEASE_DIR)/*.zip | sed 's/^/  /'

clean:
	@$(MAKE) -C code clean
	@rm -rf $(RELEASE_DIR)
