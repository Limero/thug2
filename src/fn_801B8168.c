// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B8168-0x801B826C (260B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern void fn_801B90FC(Unk_C7387A53 *);
extern s32 fn_801B8678(Unk_0D2D5D83 *, CStruct *, s32);
extern s32 ContainsFlag(CStruct *, s32);
extern s32 fn_801B8018(void *, Unk_80577C09 *);
extern void fn_801B3220(Unk_C7387A53 *, s32 *, s32 *, Unk_C8FEE62D *);
extern void CStruct_delete(CStruct *, s32);

void fn_801B8168(Unk_C7387A53 *arg0, CStruct *arg1, s32 arg2) {
    s32 var_r30;

    fn_801B90FC(arg0);
    if (arg2 != 0) {
        arg0->unk0x24 = (arg0->unk0x24 & QB_UNKNOWN_0xFFFFFFFD);
        var_r30 = fn_801B8678(arg0, arg1, arg2);
        fn_801B3220(arg0, QB_STATE_JUMPVERT, QB_SKATERPED_STATETABLE, var_r30);
    } else {
        if (ContainsFlag(arg1, QB_JUMPTONEXTNODE) != 0) {
            arg0->unk0x24 = (arg0->unk0x24 & QB_UNKNOWN_0xFFFFFFFD);
            var_r30 = fn_801B8678(arg0, arg1, 0);
            arg0->unk0x24 = (arg0->unk0x24 | 0x800);
        } else {
            var_r30 = fn_801B8018(arg0, arg1);
        }
        fn_801B3220(arg0, QB_STATE_JUMP, QB_SKATERPED_STATETABLE, var_r30);
    }
    if (var_r30 != 0) {
        CStruct_delete(var_r30, 3);
    }
}
