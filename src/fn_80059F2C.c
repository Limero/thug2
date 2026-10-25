// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80059F2C-0x80059F8C (96B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern f32 lbl_802934C4;
void *Mem_Alloc2(s32);
s32 fn_80057724(void *, s32);
void *fn_80059F2C(char *arg0) {
    s32 x;
    f32 v;
    x = fn_80057724(Mem_Alloc2(0x18), 4);
    v = lbl_802934C4;
    *(s32 *)(arg0 + 0x20) = x;
    *(f32 *)(arg0 + 0x14) = v;
    *(u8 *)(arg0 + 0x1C) = 0x80;
    *(u8 *)(arg0 + 0x1D) = 0x80;
    *(u8 *)(arg0 + 0x1E) = 0x80;
    *(f32 *)(arg0 + 0x10) = v;
    return arg0;
}
