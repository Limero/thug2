// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800C9970-0x800C9A38 (200B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 lbl_80299320;
extern f32 lbl_80299324;

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
} Sp8;

s32 GetChecksum_2(CStruct * arg0, s32 arg1, s32 * arg2, s32 arg3);
s32 fn_800CA01C(Unk_31DE137E * arg0, s32 arg1, CStruct * arg2);
void fn_8012772C(CStruct * arg0, s32 arg1, f32 arg2);

s32 fn_800C9970(Unk_31DE137E *arg0, CStruct *arg1, CScript *arg2) {
    Sp8 sp8;
    s32 sp18;
    Sp8 *psp;
    f32 temp_f0;
    f32 temp_f13;
    s32 temp_r28;
    s32 var_r3;

    psp = &sp8;
    temp_f0 = lbl_80299320;
    temp_f13 = lbl_80299324;
    psp->unk0 = temp_f0;
    psp->unk4 = temp_f0;
    psp->unk8 = temp_f0;
    psp->unkC = temp_f13;
    GetChecksum_2(arg1, QB_BONE, &sp18, 1);
    temp_r28 = fn_800CA01C(arg0, sp18, psp);
    fn_8012772C(arg2->unk0x18, QB_X, psp->unk0);
    fn_8012772C(arg2->unk0x18, QB_Y, sp8.unk4);
    fn_8012772C(arg2->unk0x18, QB_Z, psp->unk8);
    var_r3 = 0;
    if (temp_r28 != 0) {
        var_r3 = 1;
    }
    return var_r3;
}
