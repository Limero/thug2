#!/bin/bash
cd "$(dirname "$0")/.."
set -e
echo '=== 1. register generated leaves ==='
tools/venv/bin/python tools/add_gen_leaves.py 2>&1 | tail -2
echo '=== 2. reconfigure ==='
python3 configure.py --dtk tools/dtk --ninja tools/ninja --compilers build/compilers 2>&1 | tail -1
echo '=== 3. re-split ==='
rm -f build/G2TE52/config.json
tools/ninja build/G2TE52/config.json 2>&1 | tail -2
echo '=== 4. build DOL ==='
rm -f build/G2TE52/main.elf build/G2TE52/main.dol
tools/ninja build/G2TE52/main.dol 2>&1 | tail -5
echo '=== 5. verify ==='
if cmp -s orig/G2TE52/sys/main.dol build/G2TE52/main.dol; then
    echo '>>> DOL BYTE-IDENTICAL <<<'
else
    echo '>>> DOL DIFFERS - checking for dropped functions <<<'
    tools/venv/bin/python tools/dbg_allleaves.py 2>&1 | head -20
fi
