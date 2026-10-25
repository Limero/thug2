#!/usr/bin/env bash
# Final M3 verification: reconfigure + build + hash + cmp
set -e
cd "$(dirname "$0")/.."

echo '=== reconfigure ==='
python3 configure.py --dtk tools/dtk --ninja tools/ninja 2>&1 | tail -3

echo '=== build DOL ==='
tools/ninja build/G2TE52/main.dol 2>&1 | tail -6

echo '=== hash check (ok target) ==='
tools/ninja build/G2TE52/ok 2>&1 | tail -3

echo '=== byte compare ==='
if cmp -s orig/G2TE52/sys/main.dol build/G2TE52/main.dol; then
    echo 'DOL BYTE-IDENTICAL ✓'
else
    echo 'DOL DIFFERS ✗'
    exit 1
fi
echo '=== QB constants regeneration check (warning-only) ==='
# WARNING-ONLY (NOT exit 1 — this script runs under set -e): the QB
# constants header is generated from the .prg/.qb/dict sources, so it can
# drift whenever tools/gen_qb_constants.py's inputs change or a draft refill
# reverts a name. Both commands need build/G2TE52/report.json (gen_leaves
# import), hence the guard.
if [ -f build/G2TE52/report.json ]; then
    tools/venv/bin/python tools/gen_qb_constants.py --check \
        || echo 'warning: qb_constants.h stale — rerun tools/gen_qb_constants.py'
    tools/venv/bin/python tools/apply_qb_constants.py --dry-run \
        | grep -q 'literals rewritten: 0' \
        || echo 'warning: raw resolvable QB literals remain — rerun tools/apply_qb_constants.py'
else
    echo 'warning: build/G2TE52/report.json missing — skipped QB constant checks'
fi

echo '=== objdiff report ==='
tools/venv/bin/python - <<'EOF'
import json
d = json.load(open('build/G2TE52/objdiff.json')) if False else None
EOF
bash tools/objdiff_check.sh 2>/dev/null | tail -4 || true
