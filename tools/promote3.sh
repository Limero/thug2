#!/bin/bash
# Promote EXACTs from sweep3, verify DOL, regenerate report+progress.
cd "$(dirname "$0")/.." || exit 1
grep -h '  EXACT ' /tmp/sweep3_*.log | grep -o '0x[0-9A-F]*' | sort -u > /tmp/exact4.txt
echo "EXACT addresses: $(cat /tmp/exact4.txt | tr '\n' ' ')"
tools/venv/bin/python tools/promote_wip.py $(cat /tmp/exact4.txt) 2>&1 | grep -iE 'byte-identical|DIFF|promot|refus|skip' | head -10
echo "=== verify ==="
cmp orig/G2TE52/sys/main.dol build/G2TE52/main.dol && echo 'DOL BYTE-IDENTICAL'
echo "=== regenerate report + progress ==="
rm -f build/G2TE52/report.json
build/tools/objdiff-cli report generate -o build/G2TE52/report.json 2>&1 | tail -1
tools/venv/bin/python tools/gen_progress.py 2>&1 | tail -1
grep -E 'Functions matched' PROGRESS.md | head -1
