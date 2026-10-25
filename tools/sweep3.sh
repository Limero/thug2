#!/bin/bash
# Run 8 parallel test_wip_drafts slices and summarize.
cd "$(dirname "$0")/.." || exit 1
for i in 0 1 2 3 4 5 6 7; do
  tools/venv/bin/python tools/test_wip_drafts.py --slice $i/8 > /tmp/sweep3_$i.log 2>&1 &
done
wait
echo "=== per-slice results ==="
for i in 0 1 2 3 4 5 6 7; do
  echo "--- slice $i ---"
  grep '=== results' /tmp/sweep3_$i.log || tail -2 /tmp/sweep3_$i.log
done
echo "=== totals ==="
grep -h '  EXACT ' /tmp/sweep3_*.log | grep -o '0x[0-9A-F]*' | sort -u | wc -l
