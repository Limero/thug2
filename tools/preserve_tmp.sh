#!/usr/bin/env bash
# Preserve /tmp work artifacts inside the repo (tools/reference/) so they are
# not lost when the sandbox tmpfs is cleared. Run from the project root.
set -e
cd "$(dirname "$0")/.."
REF=tools/reference
mkdir -p "$REF/dtk-template-docs" "$REF/compiler-sweeps/objects" \
    "$REF/rng-match" "$REF/bootlogs" "$REF/depfile-test"

# dtk-template docs fetched from upstream (workflow reference)
mv -f /tmp/dtktpl_readme.md /tmp/gs.md /tmp/splits.md "$REF/dtk-template-docs/" 2>/dev/null || true

# Compiler-sweep experiment sources + objects from the M3 discovery
# (all *_src.c, mx_*.c, oh_*.c, sh_*.c, pd_test.c, rg_src.c, sd_src.c, etc.)
for f in /tmp/*.c; do
    [ -e "$f" ] && mv -f "$f" "$REF/compiler-sweeps/"
done
for f in /tmp/*.o; do
    [ -e "$f" ] && mv -f "$f" "$REF/compiler-sweeps/objects/"
done

# RNG match exploration (M4): the 6 source-shape variants (sources only —
# original machine-code bytes are never preserved into the repo)
mv -f /tmp/rngtest/*.c "$REF/rng-match/" 2>/dev/null || true
mv -f /tmp/rngtest/*.o "$REF/compiler-sweeps/objects/" 2>/dev/null || true
rmdir /tmp/rngtest 2>/dev/null || true

# Dolphin boot-test evidence logs
mv -f /tmp/nogui_*.log /tmp/final_boot.log "$REF/bootlogs/" 2>/dev/null || true

# -MD depfile behavior test
mv -f /tmp/depbuild/* "$REF/depfile-test/" 2>/dev/null || true
rmdir /tmp/depbuild 2>/dev/null || true

echo '=== tools/reference tree ==='
find "$REF" -type f | sort | head -40
echo
echo "files moved: $(find "$REF" -type f | wc -l)"
echo '=== .o objects (gitignored) ==='
find "$REF" -name '*.o' | wc -l
