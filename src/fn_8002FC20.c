// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8002FC20-0x8002FC8C (108B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"
extern f32 lbl_802919A4;
extern f32 lbl_802919A8;
f32 fn_8002F700(void);
void fn_8002FC8C(Unk_A9157FE7 *, s32, s32, s8, s32, f32, f32, f32, f32);
void fn_8002FC20(Unk_A9157FE7 *arg0, s32 arg1, f32 farg0) {
    f32 ret;
    f32 c0;
    f32 c1;

    ret = fn_8002F700();
    c0 = lbl_802919A4;
    c1 = lbl_802919A8;
    fn_8002FC8C(arg0, arg1, 0, 0, 0, c0, ret, farg0, c1);
}
