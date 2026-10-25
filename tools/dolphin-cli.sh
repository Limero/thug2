#!/usr/bin/env bash
# Run Dolphin's CLI tools from the host's flatpak installation without
# bubblewrap (which can't run inside this nested sandbox).
#
# Usage: tools/dolphin-cli.sh <tool> [args...]
#   tools: dolphin-tool | dolphin-emu-nogui | dolphin-emu
#
# Finds the flatpak app + KDE runtime under /var/lib/flatpak and runs the
# binary through the runtime's own dynamic loader with all of the runtime's
# library dirs on the search path (avoids host/runtime glibc mixing).

set -euo pipefail

APP=/var/lib/flatpak/app/org.DolphinEmu.dolphin-emu/current/active/files
KDE_ROOT=/var/lib/flatpak/runtime/org.kde.Platform/x86_64

if [ ! -d "$APP" ]; then
    echo "error: Dolphin flatpak not mounted at /var/lib/flatpak" >&2
    exit 1
fi

# Pick the newest KDE Platform runtime branch (branch/commit/files)
KDE=$(find "$KDE_ROOT" -maxdepth 3 -type d -name files 2>/dev/null | sort -V | tail -1)

TOOL="$1"; shift || true
BIN="$APP/bin/$TOOL"
LOADER="$KDE/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2"

[ -x "$BIN" ] || { echo "error: $TOOL not found in flatpak app" >&2; exit 1; }
[ -e "$LOADER" ] || { echo "error: runtime loader not found" >&2; exit 1; }

# All directories under the runtime + app that contain shared libraries
LIBS=$(find "$KDE/lib" "$APP/lib" -type f \( -name '*.so' -o -name '*.so.*' \) \
       -printf '%h\n' 2>/dev/null | sort -u | paste -sd: -)

exec "$LOADER" --library-path "$LIBS" "$BIN" "$@"
