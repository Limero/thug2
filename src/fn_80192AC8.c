// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80192AC8-0x80192B2C (100B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305F9C;
extern s32 ContainsFlag(CStruct *, s32);
extern void fn_8022048C(Unk_C7387A53 *);
extern void fn_8018C054(Unk_C7387A53 *, s32);
extern void fn_8018D080(Unk_C8FEE62D *);
void fn_80192AC8(Unk_C8FEE62D * arg0) {
    s32 temp_r30;
    s32 temp_r3;

    temp_r30 = lbl_80305F9C;
    temp_r3 = arg0->unk0x20;
    if (ContainsFlag(temp_r3, QB_GAME_CONTINUES_AFTER_EXPIRATION) != 1) {
        fn_8022048C((void *)temp_r30);
    }
    fn_8018C054(arg0, 0);
    fn_8018D080(arg0);
}
