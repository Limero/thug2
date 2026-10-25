#!/usr/bin/env bash
# From-scratch rebuild test: wipe build/, keep compilers, reconfigure, rebuild,
# hash-check, byte-compare. Proves the ngccc rule works on a cold build.
set -e
cd "$(dirname "$0")/.."

echo '=== preserve compilers, wipe build ==='
if [ -d build/compilers ]; then
    mv build/compilers /tmp/compilers_bak
fi
if [ ! -d /tmp/compilers_bak ]; then
    echo 'ERROR: no compilers available (/tmp/compilers_bak missing)'
    exit 1
fi
rm -rf build
mkdir -p build

echo '=== reconfigure (cold) ==='
python3 configure.py --dtk tools/dtk --ninja tools/ninja --compilers /tmp/compilers_bak 2>&1 | tail -3

echo '=== ngccc edge in generated build.ninja ==='
grep -n 'ngccc' build.ninja | head -5

echo '=== build DOL (cold) ==='
tools/ninja build/G2TE52/main.dol 2>&1 | tail -4

echo '=== hash check ==='
tools/ninja build/G2TE52/ok 2>&1 | tail -2

echo '=== byte compare ==='
if cmp -s orig/G2TE52/sys/main.dol build/G2TE52/main.dol; then
    echo 'DOL BYTE-IDENTICAL ✓ (cold rebuild)'
else
    echo 'DOL DIFFERS ✗'
    exit 1
fi

echo '=== objdiff per-function check ==='
bash tools/objdiff_check.sh 2>/dev/null | tail -3 || true

# restore compilers into build and point build.ninja back at them, so the
# working tree isn't left referencing /tmp/compilers_bak
mv /tmp/compilers_bak build/compilers
python3 configure.py --dtk tools/dtk --ninja tools/ninja --compilers build/compilers 2>&1 | tail -1
echo '=== done; compilers restored to build/compilers, build.ninja reconfigured ==='
