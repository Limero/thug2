// Promoted from src/wip 2026-10-09 (TRK accessor cluster, hand-decompiled).
// range 0x8025EA58-0x8025EA60 (8B). Byte-identical: tools/sda_verify.py LINK-SIM EXACT
// plus full-build `cmp` against the retail DOL.
// TRK state getter (lbl_803CAB40); unreferenced by wired objects -> force_active.
// The r13-relative global accesses need the per-object -msdata=eabi -G4 override.
// extra_cflags: -msdata=eabi, -G4
#include "types.h"

extern s32 lbl_803CAB40;

s32 fn_8025EA58(void) {
    return lbl_803CAB40;
}