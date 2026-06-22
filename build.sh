#!/usr/bin/env bash

set -euo pipefail

BUILD_DIR="${BUILD_DIR:-build}"
CONFIG="${1:-Release}"

case "$CONFIG" in
  Debug|Release|RelWithDebInfo|MinSizeRel)
    ;;
  *)
    echo "Usage: ./build.sh [Debug|Release|RelWithDebInfo|MinSizeRel]" >&2
    exit 1
    ;;
esac

cmake -S . -B "$BUILD_DIR" -DCMAKE_BUILD_TYPE="$CONFIG"
cmake --build "$BUILD_DIR" --config "$CONFIG"
