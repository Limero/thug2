// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80128DA0-0x80128E04 (100B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern f32 lbl_8029E604;
void fn_80128470(s32, s32, f32 *, f32 *, s32);
typedef struct { u8 _0[4]; f32 f4; f32 f8; } T;
void GetPair(s32 arg0, s32 arg1, T *arg2, s32 arg3) {
    f32 sp8; f32 spC;
    s32 var_r7; f32 f0; f32 *p8; f32 *pC;
    register f32 t4 __asm__("fr13");
    f0 = lbl_8029E604;
    p8 = &sp8;
    pC = &spC;
    sp8 = f0;
    var_r7 = 0;
    spC = f0;
    if (arg3 != 0) var_r7 = 1;
    fn_80128470(arg0, arg1, p8, pC, var_r7);
    t4 = sp8;
    arg2->f4 = t4;
    arg2->f8 = spC;
}
