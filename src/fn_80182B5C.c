// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80182B5C-0x80182B88 (44B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void *fn_80182F98(s32, s32);
// fn_80182F98 is a 2-arg array-index helper: (arrayBase, idx) -> element ptr
// (see src/fn_80182F98.c); arg0 is the array base, arg1 the index, and arg0
// itself arrives pre-offset by 0x54 in the caller's source (`arr + 0x54`).
s32 fn_80182B5C(s32 arg0, s32 arg1) {
    return (*(s32 *)((char *)fn_80182F98(arg0 + 0x54, arg1) + 0x18) >> 4) & 1;
}