// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800AAA08-0x800AAA34 (44B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern f32 lbl_80301AC4[];
f32 fn_800AAA08(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    arg0 = arg0 + arg1 * 2 + arg2 * 4 + arg3 * 8;
    return lbl_80301AC4[arg0];
}
