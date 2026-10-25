// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80166B20-0x80166B94 (116B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetStructure_2(CStruct *, s32, s32 *, s32);
s32 Game_GetGoalManager(void);
void fn_801875CC(Unk_526DA6F2 *, s32);
s32 fn_801869E4(Unk_31DE137E *);
void CStruct_dtor(CStruct *);
void fn_80126FF4(Unk_80577C09 *, CStruct *);
void fn_801857D0(Unk_526DA6F2 *);
void s_read_story_info(CStruct *arg0) {
    s32 sp8;
    s32 temp_r29;
    s32 temp_r30;

    sp8 = 0;
    GetStructure_2(arg0, QB_GOALMANAGERPARAMS, &sp8, 0);
    fn_801875CC(temp_r29 = Game_GetGoalManager(), 0);
    CStruct_dtor(temp_r30 = fn_801869E4(temp_r29));
    fn_80126FF4(temp_r30, sp8);
    fn_801857D0(temp_r29);
}
