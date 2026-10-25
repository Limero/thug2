// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801CDCD0-0x801CDD4C (124B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 lbl_802AD2EC;
extern f32 fn_801DA814(f32, f32, f32);
extern s32 fn_8012772C(CStruct *, s32, f32);
bool fn_801CDCD0(s32 arg0, s32 arg1, CScript *arg2) {
    register f32 res __asm__("fr0");
    register f32 mn __asm__("fr13");
    register f32 fa __asm__("fr1");
    register f32 fc __asm__("fr3");
    register f32 a2 __asm__("fr2");
    f32 fb;
    register f32 temp_f1 __asm__("fr1");
    register s32 p __asm__("r9");
    register s32 temp_r10 __asm__("r10");
    register s32 temp_r11 __asm__("r11");
    s32 temp_r31;

    p = arg0;
    temp_r31 = arg2->unk0x18;
    __asm__("" : "+r"(temp_r31));
    temp_r10 = ((Unk_71062261 *)p)->unk0xC;
    temp_r11 = ((Unk_71062261 *)p)->unk0x15BC;
    fa = *((f32 *)&((Unk_31DE137E *)temp_r10)->unk0x5C);
    fb = *((f32 *)&((Unk_31DE137E *)temp_r11)->unk0x18C);
    fc = *((f32 *)&((Unk_31DE137E *)temp_r10)->unk0xBC);
    a2 = fa;
    temp_f1 = fn_801DA814(fa - fb, a2, fc);
    res = temp_f1;
    __asm__("" : "+f"(temp_f1));
    mn = lbl_802AD2EC;
    if (temp_f1 < mn) {
        res = mn;
    }
    fn_8012772C(temp_r31, QB_AIRTIMELEFT, res);
    return true;
}
