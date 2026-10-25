// Promoted from src/wip 2026-10-09 (TRK accessor cluster, hand-decompiled).
// range 0x8025EDB8-0x8025EDC0 (8B). Byte-identical: tools/sda_verify.py LINK-SIM EXACT
// plus full-build `cmp` against the retail DOL.
// TRK state setter (lbl_803CA368 +0x8).
// The r13-relative global accesses need the per-object -msdata=eabi -G4 override.
// extra_cflags: -msdata=eabi, -G4
#include "types.h"

extern s32 lbl_803CA368;

void fn_8025EDB8(s32 arg0) {
    ((s32 *)&lbl_803CA368)[2] = arg0;
}