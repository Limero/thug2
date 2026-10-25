// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800DFD2C-0x800DFDFC (208B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef void *Obj;

extern f32 lbl_8029A4C0;

void *fn_800AA84C(void *arg0);
s32 fn_800145AC(void);
void fn_800AA0B4(Obj o, f32 v);
void fn_800A9F70(Obj o, s32 arg1);
void fn_800AA068(Obj o);
void fn_800AA074(Obj o);

void fn_800DFD2C(s32 arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1) {
    volatile double _dummy;
    Obj temp_r31;
    f32 v;

    temp_r31 = fn_800AA84C((u8 *)arg0 + 0x24);
    v = farg0;
    v = v * lbl_8029A4C0 + (f32)(f64)(u32)fn_800145AC();
    fn_800AA0B4(temp_r31, (f32)(s32)v);
    if (arg2 != 0) {
        fn_800A9F70(temp_r31, 0);
        fn_800AA068(temp_r31);
        fn_800AA074(temp_r31);
    }
}
