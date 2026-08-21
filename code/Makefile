#---------------------------------------------------------------------------------
.SUFFIXES:
#---------------------------------------------------------------------------------

ifeq ($(strip $(DEVKITARM)),)
$(error "Please set DEVKITARM in your environment. export DEVKITARM=<path to>devkitARM")
endif

TOPDIR ?= $(CURDIR)
include $(DEVKITARM)/3ds_rules

#---------------------------------------------------------------------------------
# TARGET is the name of the output
# BUILD is the directory where object files & intermediate files will be placed
# SOURCES is a list of directories containing source code
# DATA is a list of directories containing data files
# INCLUDES is a list of directories containing header files
# GRAPHICS is a list of directories containing graphics files
# GFXBUILD is the directory where converted graphics files will be placed
#   If set to $(BUILD), it will statically link in the converted
#   files as if they were data files.
#
# NO_SMDH: if set to anything, no SMDH file is generated.
# ROMFS is the directory which contains the RomFS, relative to the Makefile (Optional)
# APP_TITLE is the name of the app stored in the SMDH file (Optional)
# APP_DESCRIPTION is the description of the app stored in the SMDH file (Optional)
# APP_AUTHOR is the author of the app stored in the SMDH file (Optional)
# ICON is the filename of the icon (.png), relative to the project folder.
#   If not set, it attempts to use one of the following (in this order):
#     - <Project name>.png
#     - icon.png
#     - <libctru folder>/default_icon.png
#---------------------------------------------------------------------------------
TARGET		:=	$(notdir $(CURDIR))
BUILD		:=	build
SOURCES		:=	source source/asm source/lib source/common source/game source/game/ui/screens source/msys source/msys/3ds
DATA		:=	data
INCLUDES	:=	include source
GRAPHICS	:=	gfx
GFXBUILD	:=	$(BUILD)
#ROMFS		:=	romfs
#GFXBUILD	:=	$(ROMFS)/gfx

#---------------------------------------------------------------------------------
# options for code generation
#---------------------------------------------------------------------------------
MM3D	 	:= MM3D
MM3DJ 		:= MM3DJ
Z3D			:= MM3D
VERFLAGS := -D MM3D=$(MM3D) -D MM3DJ=$(MM3DJ) -D Z3D=$(Z3D)

# Build for USA 1.1 instead of USA 1.0:  make usa11=1
#
# This has to live in VERFLAGS and nowhere else. VERFLAGS is the only variable
# that reaches all three consumers of include/game/addresses.h -- the C++, the
# preprocessed assembly, and the cpp pass that turns mm.ld.in into the linker
# script. Setting it on only some of them yields a build whose hooks are
# assembled for one version and linked against the other's patch sites, which
# links cleanly and then branches into the middle of unrelated code.
usa11 ?= 0
ifneq ($(usa11), 0)
  VERFLAGS += -D Z3D_USA_11
  OUTPUT_IPS := basecode1.1.ips
  VANILLA_EXHEADER := ../bin/exheader1.1.bin
else
  OUTPUT_IPS := basecode.ips
  VANILLA_EXHEADER := ../bin/exheader1.0.bin
endif

# Generated from mm.ld.in so its addresses come from the same table the C++ and
# the assembly use.
LD_TEMPLATE	:= mm.ld.in
LINK_SCRIPT	:= $(BUILD)/mm.ld

ifeq ($(MM3D), $(Z3D))
  ASFLAGS += -D _USA_=1 -D _JP_=0
else
ifeq ($(MM3DJ), $(Z3D))
  ASFLAGS += -D _USA_=0 -D _JP_=1
endif
endif
ARCH	:=	-march=armv6k -mtune=mpcore -mfloat-abi=hard -mtp=soft -mfpu=vfpv2

CFLAGS	:=	-g -Wall -O2 -mword-relocations -D DEBUG \
			-ffunction-sections -fomit-frame-pointer \
			$(ARCH)

CFLAGS	+=	$(INCLUDE) -D__3DS__ $(VERFLAGS)

CXXFLAGS	:= $(CFLAGS) -fno-rtti -fno-exceptions -std=gnu++17 -Wno-invalid-offsetof \
							-Wno-array-bounds

ASFLAGS	+=	-g $(ARCH) $(INCLUDE) $(VERFLAGS)
LDFLAGS	=	 -g $(ARCH) -Wl,-Map,$(notdir $*.map) -T $(TOPDIR)/$(LINK_SCRIPT)

LIBS	:= -lctru -lm

# Debug-specific flags
debug ?= 0
ifneq ($(debug), 0)
	CFLAGS += -g -DENABLE_DEBUG
	CXXFLAGS += -g -DENABLE_DEBUG
endif

debug_print ?= 0
ifneq ($(debug_print), 0)
	CFLAGS += -g -DDEBUG_PRINT
	CXXFLAGS += -g -DDEBUG_PRINT
endif

ifeq ($(copyto),)
	export COPYTO=${citraPath}
else
	export COPYTO=$(copyto)
endif


#---------------------------------------------------------------------------------
# list of directories containing libraries, this must be the top level containing
# include and lib
#---------------------------------------------------------------------------------
LIBDIRS	:= $(CTRULIB)


#---------------------------------------------------------------------------------
# no real need to edit anything past this point unless you need to add additional
# rules for different file extensions
#---------------------------------------------------------------------------------
ifneq ($(BUILD),$(notdir $(CURDIR)))
#---------------------------------------------------------------------------------

export OUTPUT	:=	$(CURDIR)/$(TARGET)
export TOPDIR	:=	$(CURDIR)

export VPATH	:=	$(foreach dir,$(SOURCES),$(CURDIR)/$(dir)) \
			$(foreach dir,$(GRAPHICS),$(CURDIR)/$(dir)) \
			$(foreach dir,$(DATA),$(CURDIR)/$(dir))

export DEPSDIR	:=	$(CURDIR)/$(BUILD)

CFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
CPPFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.cpp)))
SFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.S)))
PICAFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.v.pica)))
SHLISTFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.shlist)))
GFXFILES	:=	$(foreach dir,$(GRAPHICS),$(notdir $(wildcard $(dir)/*.t3s)))
BINFILES	:=	$(foreach dir,$(DATA),$(notdir $(wildcard $(dir)/*.*)))

#---------------------------------------------------------------------------------
# use CXX for linking C++ projects, CC for standard C
#---------------------------------------------------------------------------------
ifeq ($(strip $(CPPFILES)),)
#---------------------------------------------------------------------------------
	export LD	:=	$(CC)
#---------------------------------------------------------------------------------
else
#---------------------------------------------------------------------------------
	export LD	:=	$(CXX)
#---------------------------------------------------------------------------------
endif
#---------------------------------------------------------------------------------

#---------------------------------------------------------------------------------
ifeq ($(GFXBUILD),$(BUILD))
#---------------------------------------------------------------------------------
export T3XFILES :=  $(GFXFILES:.t3s=.t3x)
#---------------------------------------------------------------------------------
else
#---------------------------------------------------------------------------------
export ROMFS_T3XFILES	:=	$(patsubst %.t3s, $(GFXBUILD)/%.t3x, $(GFXFILES))
export T3XHFILES		:=	$(patsubst %.t3s, $(BUILD)/%.h, $(GFXFILES))
#---------------------------------------------------------------------------------
endif
#---------------------------------------------------------------------------------

export OFILES_SOURCES 	:=	$(CPPFILES:.cpp=.o) $(CFILES:.c=.o) $(SFILES:.S=.o)

export OFILES_BIN	:=	$(addsuffix .o,$(BINFILES)) \
			$(PICAFILES:.v.pica=.shbin.o) $(SHLISTFILES:.shlist=.shbin.o) \
			$(addsuffix .o,$(T3XFILES))

export OFILES := $(OFILES_BIN) $(OFILES_SOURCES)

export HFILES	:=	$(PICAFILES:.v.pica=_shbin.h) $(SHLISTFILES:.shlist=_shbin.h) \
			$(addsuffix .h,$(subst .,_,$(BINFILES))) \
			$(GFXFILES:.t3s=.h)

export INCLUDE	:=	$(foreach dir,$(INCLUDES),-I$(CURDIR)/$(dir)) \
			$(foreach dir,$(LIBDIRS),-I$(dir)/include) \
			-I$(CURDIR)/$(BUILD)

export LIBPATHS	:=	$(foreach dir,$(LIBDIRS),-L$(dir)/lib)

export _3DSXDEPS	:=	$(if $(NO_SMDH),,$(OUTPUT).smdh)

ifeq ($(strip $(ICON)),)
	icons := $(wildcard *.png)
	ifneq (,$(findstring $(TARGET).png,$(icons)))
		export APP_ICON := $(TOPDIR)/$(TARGET).png
	else
		ifneq (,$(findstring icon.png,$(icons)))
			export APP_ICON := $(TOPDIR)/icon.png
		endif
	endif
else
	export APP_ICON := $(TOPDIR)/$(ICON)
endif

ifeq ($(strip $(NO_SMDH)),)
	export _3DSXFLAGS += --smdh=$(CURDIR)/$(TARGET).smdh
endif

ifneq ($(ROMFS),)
	export _3DSXFLAGS += --romfs=$(CURDIR)/$(ROMFS)
endif

.PHONY: all clean $(BUILD)

#---------------------------------------------------------------------------------
all: $(BUILD)

$(BUILD): check-addrs
	@[ -d $@ ] || mkdir -p $@
	@python3 ../tools/genaddrs.py >/dev/null
	@$(DEVKITARM)/bin/arm-none-eabi-cpp -P -I include $(VERFLAGS) $(LD_TEMPLATE) -o $(LINK_SCRIPT)
	@$(MAKE) --no-print-directory -C $(BUILD) -f $(CURDIR)/Makefile
	@python3 patch.py $(OUTPUT).elf -o $(OUTPUT_IPS) --ld $(LINK_SCRIPT)
	@$(MAKE) --no-print-directory exheaders

# The exheader differs per game version (USA 1.1's .rodata is larger) and per
# target (console grows .data to reach the new code region, Emulator grows .bss),
# so this produces both variants for whichever version is being built.
.PHONY: exheaders
exheaders:
	@if [ -f $(VANILLA_EXHEADER) ]; then \
		mkdir -p $(BUILD); \
		python3 ../tools/mkexheader.py --vanilla $(VANILLA_EXHEADER) \
			--out $(BUILD)/exheader.bin; \
		python3 ../tools/mkexheader.py --vanilla $(VANILLA_EXHEADER) \
			--out $(BUILD)/exheader_emulator.bin --emulator; \
	else \
		echo "warning: $(VANILLA_EXHEADER) missing, not generating an exheader"; \
	fi

# Re-verify every address against both game images. A stale or wrong 1.1 address
# should be a build failure, not a wild branch discovered months later. Skipped
# with a warning when the images are absent, so a contributor without dumps can
# still build for 1.0.
.PHONY: check-addrs
check-addrs:
	@if [ -f ../bin/code1.0.bin ] && [ -f ../bin/code1.1.bin ]; then \
		python3 ../tools/mapaddr.py --check; \
	else \
		echo "warning: ../bin/code1.0.bin or code1.1.bin missing, skipping address check"; \
	fi
# ifneq ($(strip $(COPYTO)),)
# 	@echo "Copying $(OUTPUT_IPS) to ${COPYTO}."
# 	@cp $(OUTPUT_IPS) $(COPYTO)
# endif
ifneq ($(GFXBUILD),$(BUILD))
$(GFXBUILD):
	@mkdir -p $@
endif

ifneq ($(DEPSDIR),$(BUILD))
$(DEPSDIR):
	@mkdir -p $@
endif

#---------------------------------------------------------------------------------

clean:
	@echo clean ...
	@rm -fr $(BUILD)  $(TARGET).elf basecode.ips basecode1.1.ips $(TARGET).smdh code.elf

#---------------------------------------------------------------------------------
$(GFXBUILD)/%.t3x	$(BUILD)/%.h	:	%.t3s
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	@tex3ds -i $< -H $(BUILD)/$*.h -d $(DEPSDIR)/$*.d -o $(GFXBUILD)/$*.t3x

#---------------------------------------------------------------------------------
else

#---------------------------------------------------------------------------------
# main targets
#---------------------------------------------------------------------------------
$(OUTPUT).elf	:	$(OFILES) $(TOPDIR)/$(LINK_SCRIPT)
#$(OUTPUT).3dsx	:	$(OUTPUT).elf $(_3DSXDEPS)

#$(OFILES_SOURCES) : $(HFILES)



#---------------------------------------------------------------------------------
# you need a rule like this for each extension you use as binary data
#---------------------------------------------------------------------------------
%.bin.o	%_bin.h :	%.bin
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	@$(bin2o)

#---------------------------------------------------------------------------------
%.der.o	%_der.h :	%.der
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	@$(bin2o)

#---------------------------------------------------------------------------------
.PRECIOUS	:	%.t3x
#---------------------------------------------------------------------------------
%.t3x.o	%_t3x.h :	%.t3x
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	@$(bin2o)

#---------------------------------------------------------------------------------
# rules for assembling GPU shaders
#---------------------------------------------------------------------------------
define shader-as
	$(eval CURBIN := $*.shbin)
	$(eval DEPSFILE := $(DEPSDIR)/$*.shbin.d)
	echo "$(CURBIN).o: $< $1" > $(DEPSFILE)
	echo "extern const u8" `(echo $(CURBIN) | sed -e 's/^\([0-9]\)/_\1/' | tr . _)`"_end[];" > `(echo $(CURBIN) | tr . _)`.h
	echo "extern const u8" `(echo $(CURBIN) | sed -e 's/^\([0-9]\)/_\1/' | tr . _)`"[];" >> `(echo $(CURBIN) | tr . _)`.h
	echo "extern const u32" `(echo $(CURBIN) | sed -e 's/^\([0-9]\)/_\1/' | tr . _)`_size";" >> `(echo $(CURBIN) | tr . _)`.h
	picasso -o $(CURBIN) $1
	bin2s $(CURBIN) | $(AS) -o $*.shbin.o
endef

%.shbin.o %_shbin.h : %.v.pica %.g.pica
	@echo $(notdir $^)
	@$(call shader-as,$^)

%.shbin.o %_shbin.h : %.v.pica
	@echo $(notdir $<)
	@$(call shader-as,$<)

%.shbin.o %_shbin.h : %.shlist
	@echo $(notdir $<)
	@$(call shader-as,$(foreach file,$(shell cat $<),$(dir $<)$(file)))

#---------------------------------------------------------------------------------
%.t3x	%.h	:	%.t3s
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	@tex3ds -i $< -H $*.h -d $*.d -o $*.t3x

-include $(DEPSDIR)/*.d

#---------------------------------------------------------------------------------------
endif
#---------------------------------------------------------------------------------------
