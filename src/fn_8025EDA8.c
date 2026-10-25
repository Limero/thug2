// Promoted from src/wip 2026-10-09 (TRK accessor cluster, hand-decompiled).
// range 0x8025EDA8-0x8025EDB0 (8B). Byte-identical: tools/sda_verify.py LINK-SIM EXACT
// plus full-build `cmp` against the retail DOL.
// TRK state getter (lbl_803CA368 +0xC).
// The r13-relative global accesses need the per-object -msdata=eabi -G4 override.
// extra_cflags: -msdata=eabi, -G4
#include "types.h"

extern s32 lbl_803CA368;

s32 fn_8025EDA8(void) {
    return ((s32 *)&lbl_803CA368)[3];
}