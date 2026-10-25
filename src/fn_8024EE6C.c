// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8024EE6C-0x8024EEC0 (84B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -msdata=eabi -G4
// MSL heap free path: releases the block pointed to by arg0 via the free fn
// pointer (lbl_803CA348), and also arg0 itself when arg1's bit 0 is set
// (counterpart of the fn_8024EE00 allocator).
// Suggested rename: fn_8024EE6C_heap_free.
#include "types.h"

extern s32 lbl_803CA348;

void fn_8024EE6C(s32 arg0, s32 arg1) {
    ((s32 (*)(s32))lbl_803CA348)(*(s32 *)arg0);
    if (arg1 & 1) {
        ((s32 (*)(s32))lbl_803CA348)(arg0);
    }
}
