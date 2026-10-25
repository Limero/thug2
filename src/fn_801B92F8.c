// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B92F8-0x801B943C (324B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern void fn_801B90FC(Unk_C7387A53 *);
extern s32 GetChecksum_3(Unk_6A70655D *, s32);
extern s32 fn_801B8018(void *, Unk_80577C09 *);
extern s32 fn_801B8678(Unk_0D2D5D83 *, CStruct *, s32);
extern void fn_80126FF4(Unk_80577C09 *, CStruct *);
extern void CStruct_delete(CStruct *, s32);
extern void AddChecksum(CStruct *, s32, s32);
extern void AddInteger(CStruct *, s32, s32);
extern s32 ContainsFlag(CStruct *, s32);
extern void fn_801B3220(Unk_C7387A53 *, s32 *, s32 *, Unk_C8FEE62D *);
void fn_801B92F8(Unk_C7387A53 *arg0, CStruct *arg1, s32 arg2) {
    Unk_31DE137E *temp_r26;
    s32 var_r29;
    s32 var_r31;

    fn_801B90FC(arg0);
    temp_r26 = GetChecksum_3(arg0->unk0xC, QB_MOTION);
    var_r29 = fn_801B8018(arg0, arg1);
    var_r31 = fn_801B8678(arg0, arg1, arg2);
    fn_80126FF4(var_r29, var_r31);
    if (var_r31 != 0) {
        CStruct_delete(var_r31, 3);
    }
    if (arg2 != 0) {
        arg0->unk0x24 &= ~0x2;
        AddChecksum(var_r29, 0, 0x1615618);
    }
    if (temp_r26->unk0x1C & 0x100) {
        AddInteger(var_r29, QB_IS_JUMPING, 1);
    } else {
        AddInteger(var_r29, QB_IS_JUMPING, 0);
    }
    if (ContainsFlag(arg1, QB_JUMPTONEXTNODE) != 0) {
        arg0->unk0x24 = (arg0->unk0x24 & QB_UNKNOWN_0xFFFFFFFD) | 0x800;
    }
    fn_801B3220(arg0, QB_STATE_TRICKFLIP, QB_SKATERPED_STATETABLE, var_r29);
    if (var_r29 != 0) {
        CStruct_delete(var_r29, 3);
    }
}
