#!/usr/bin/env bash
# Per-function objdiff check for the RNG source (fn_800034A0, fn_800034E4)
# NOTE: objdiff-cli is downloaded by ninja; if missing, run:
#   tools/ninja build/tools/objdiff-cli
cd "$(dirname "$0")/.."
OBJDIFF=tools/venv/bin/objdiff-cli
if [ ! -x "$OBJDIFF" ]; then OBJDIFF=build/tools/objdiff-cli; fi
echo "=== using $OBJDIFF ==="
$OBJDIFF report generate -o build/G2TE52/report.json 2>&1 | tail -2
tools/venv/bin/python - <<'EOF'
import json
r = json.load(open('build/G2TE52/report.json'))
def walk(units):
    for u in units:
        if 'units' in u:
            yield from walk(u['units'])
        else:
            yield u
for u in walk(r.get('units', [])):
    name = u.get('name', '')
    if 'rng' in name or 'fn_800034A0' in name or 'fn_800034E4' in name:
        md = u.get('metadata', {})
        fns = md.get('functions', [])
        for f in fns:
            fn = f.get('name', '?')
            fuzzy = f.get('fuzzy_match', f.get('fuzzy', '?'))
            match = f.get('matches', '?')
            sec = f.get('section', '')
            print(f"{fn:28s} section={sec:8s} fuzzy={fuzzy} matches={match}")
EOF
