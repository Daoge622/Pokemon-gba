#!/usr/bin/env bash
set -euo pipefail
cd "$HOME"
mkdir -p tools
if [[ ! -d tools/porymap-6.3.1/.git ]]; then
    git -c http.version=HTTP/1.1 clone --depth 1 --branch 6.3.1 https://github.com/huderlem/porymap.git tools/porymap-6.3.1
fi
cd tools/porymap-6.3.1
test "$(git rev-parse HEAD)" = 139eda92b3b06a5fd675a9825a07ac62e98c1566
qmake6
make -j"${BUILD_JOBS:-4}"
