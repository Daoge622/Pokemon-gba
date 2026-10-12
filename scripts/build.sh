#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")/.."
workspace='/mnt/d/Pokemon gba'
mkdir -p "$workspace/logs" "$workspace/artifacts/current"
jobs="${BUILD_JOBS:-$(nproc)}"
target=()
rom=pokeemerald.gba
for option in "$@"; do
    case "$option" in
        --release) target=(release); rom=pokeemerald-release.gba ;;
        --run) echo "GUI launching is disabled. Build only; test manually later." >&2; exit 2 ;;
        *) echo "Unknown option: $option" >&2; exit 2 ;;
    esac
done
# pipefail preserves the compiler exit code. Never run a stale ROM on failure.
make -j"$jobs" "${target[@]}" 2>&1 | tee "$workspace/logs/build-latest.log"
# Checks compile native helpers and scripts only; never execute a GBA ROM.
python3 scripts/tests/check-immediate-scripts.py | tee "$workspace/logs/immediate-script-checks.log"
python3 scripts/tests/check-playtest-20261010.py | tee "$workspace/logs/playtest-20261010-checks.log"
python3 scripts/tests/check-playability.py | tee "$workspace/logs/playability-checks.log"
python3 scripts/tests/check-part7.py | tee "$workspace/logs/part7-engine-checks.log"
python3 scripts/tests/check-part6.py | tee "$workspace/logs/part6-static-checks.log"
python3 scripts/tests/check-part55.py | tee "$workspace/logs/part55-static-checks.log"
python3 scripts/tests/check-part55-core.py | tee "$workspace/logs/part55-native-checks.log"
python3 scripts/tests/check-part5.py | tee "$workspace/logs/part5-static-checks.log"
python3 scripts/tests/check-part4.py | tee "$workspace/logs/part4-static-checks.log"
python3 scripts/tests/check-part4-core.py | tee "$workspace/logs/part4-native-checks.log"
python3 scripts/tests/check-chinese.py | tee "$workspace/logs/chinese-checks.log"
python3 scripts/tests/test-opening.py | tee "$workspace/logs/opening-checks.log"
python3 scripts/tests/check-route102-petalburg.py | tee "$workspace/logs/route102-petalburg-checks.log"
python3 scripts/tests/check-part1.py | tee "$workspace/logs/part1-checks.log"
python3 scripts/tests/check-part2.py | tee "$workspace/logs/part2-checks.log"
python3 scripts/tests/check-part3-west.py | tee "$workspace/logs/part3-west-checks.log"
python3 scripts/tests/check-part3-northwest.py | tee "$workspace/logs/part3-northwest-checks.log"
python3 scripts/tests/check-part3-volcano.py | tee "$workspace/logs/part3-volcano-checks.log"
python3 scripts/tests/check-part3-core.py | tee "$workspace/logs/part3-core-checks.log"
python3 scripts/tests/check-part3-data.py | tee "$workspace/logs/part3-data-checks.log"
test -s "$rom"
if [[ "$rom" == pokeemerald.gba ]]; then
    cp "$rom" "$workspace/artifacts/current/pokeemerald.gba"
    cp pokeemerald.elf "$workspace/artifacts/current/pokeemerald.elf"
else
    cp "$rom" "$workspace/artifacts/current/$rom"
fi
sha256sum "$workspace/artifacts/current/$rom" | tee "$workspace/logs/rom-sha256.txt"
