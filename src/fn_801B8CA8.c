// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B8CA8-0x801B8DE0 (312B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 fn_801B8678(Unk_0D2D5D83 *, CStruct *, s32);
extern s32 AddChecksum(CStruct *, s32, s32);
extern s32 fn_801B8018(void *, Unk_80577C09 *);
extern s32 GetChecksum_3(Unk_6A70655D *, s32);
extern void AddInteger(CStruct *, s32, s32);
extern f32 fn_8012570C(s32, s32);
extern f32 sqrtf(f32);
extern void fn_801B3220(Unk_C7387A53 *, s32 *, s32 *, Unk_C8FEE62D *);
extern void CStruct_delete(CStruct *, s32);
void fn_801B8CA8(Unk_C7387A53 *arg0, CStruct *arg1, s32 arg2) {
    volatile double _dummy;
    f32 temp_f1;
    f32 temp_f31;
    f32 temp_f13;
    s32 var_r31;

    if (arg2 != 0) {
        arg0->unk0x24 &= ~0x2;
        var_r31 = fn_801B8678(arg0, arg1, arg2);
        AddChecksum(var_r31, 0, 0x1615618);
    } else {
        var_r31 = fn_801B8018(arg0, arg1);
        if (*(s32 *)((char *)GetChecksum_3(arg0->unk0xC, QB_MOTION) + 0x1C) & 0x100) {
            AddInteger(var_r31, QB_IS_JUMPING, 1);
        } else {
            temp_f31 = fn_8012570C(QB_PED_SKATER_JUMP_SPEED, 1);
            temp_f1 = fn_8012570C(QB_PED_SKATER_JUMP_GRAVITY, 1);
            temp_f13 = (temp_f31 * temp_f31) / (temp_f1 * temp_f1);
            temp_f13 = sqrtf(temp_f13);
            temp_f13 = temp_f13 + temp_f13;
            AddInteger(var_r31, QB_JUMPTIME, (s32)temp_f13);
            AddInteger(var_r31, QB_IS_JUMPING, 0);
        }
    }
    fn_801B3220(arg0, QB_STATE_TRICKGRAB, QB_SKATERPED_STATETABLE, var_r31);
    if (var_r31 != 0) {
        CStruct_delete(var_r31, 3);
    }
}
