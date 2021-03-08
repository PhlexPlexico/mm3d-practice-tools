#!/bin/bash

set -eu

RST_ROOT=$(dirname "$0")
RELEASE_DIR=$RST_ROOT/release
VERSION=$(git describe --tags --dirty --always --long --match '*')

print_status () {
  MSG=$1
  BLUE='\033[0;34m'
  NC='\033[0m'
  echo -e "${BLUE}${MSG}${NC}"
}

# Clean up the release directory
rm -r $RELEASE_DIR || true
mkdir $RELEASE_DIR

build () {
  TARGET_VERSION=$1

  print_status "Building MM3D Practice Patch..."

  # Copy the version-specific build files
  cp $RST_ROOT/$TARGET_VERSION/*.bin $RST_ROOT/

  # Touch main.cpp to get an up-to-date build time
  touch $RST_ROOT/source/rst/main.cpp

  # Run the patcher
  Magikoopa --build --workdir $RST_ROOT/

  # Copy build output
  mkdir $RELEASE_DIR/$TARGET_VERSION
  flips -i $RST_ROOT/bak/code.bin $RST_ROOT/code.bin $RELEASE_DIR/$TARGET_VERSION/code.ips
  if [ -z ${RST_DEV+x} ]; then
    flips -b $RST_ROOT/bak/code.bin $RST_ROOT/code.bin $RELEASE_DIR/$TARGET_VERSION/code.bps
  fi
  cp $RST_ROOT/code.bin $RST_ROOT/source/build/patched_code.bin
  cp $RST_ROOT/source/build/patched_code.bin $RST_ROOT/source/build/patched_code_faster_aim.bin
  cp $RST_ROOT/exheader*.bin $RELEASE_DIR/$TARGET_VERSION/

  # Clean up
  rm -r $RST_ROOT/loader/*.bin $RST_ROOT/loader/*.sym || true
  rm -r $RST_ROOT/*.bin $RST_ROOT/*.sym || true
  rm -r $RST_ROOT/bak || true
}

git submodule update --init
build v100

if [ -z ${RST_DEV+x} ]; then

  print_status "packing"

  mv $RELEASE_DIR/v100/exheader.bin $RELEASE_DIR/v100/exheader_citra.bin
  mv $RELEASE_DIR/v100/exheader_legacy.bin $RELEASE_DIR/v100/exheader.bin
  pushd $RELEASE_DIR
  7z a mm3d_project_restoration_${VERSION}.7z .
  popd
fi
