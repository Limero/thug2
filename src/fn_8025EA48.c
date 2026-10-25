// Promoted from src/wip 2026-10-09 (TRK accessor cluster, hand-decompiled).
// range 0x8025EA48-0x8025EA50 (8B). Byte-identical: tools/sda_verify.py LINK-SIM EXACT
// plus full-build `cmp` against the retail DOL.
// TRK state setter (store to lbl_803CAB48; caller is in the skip_cfa gap region).
// The r13-relative global accesses need the per-object -msdata=eabi -G4 override.
// extra_cflags: -msdata=eabi, -G4
#include "types.h"

extern s32 lbl_803CAB48;

void fn_8025EA48(s32 arg0) {
    lbl_803CAB48 = arg0;
}