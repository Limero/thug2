// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F54EC-0x801F559C (176B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 CStruct_new(s32);
void fn_801F559C(Unk_F0C166E4 *);
void CStruct_delete(CStruct *, s32);
void AddInteger(CStruct *, s32, s32);
s32 CStruct_ctor(s32);
void Script_RunScript(s32, s32, s32, s32, s32);
void fn_801F54EC(Unk_F0C166E4 * arg0, s32 arg1) {
    s32 temp_r31;
    void *temp_r10;
    Unk_4E705049 *temp_r9;

    if (arg1 != 0) {
        Script_RunScript(QB_GOAL_EDITOR_DESTROY_CURSOR, 0, 0, 0, 0);
        return;
    }
    temp_r31 = CStruct_ctor(CStruct_new(8));
    AddInteger(temp_r31, QB_PLAYER, 0);
    temp_r10 = arg0->unk0xAC04;
    temp_r9 = ((CScript *)temp_r10)->unk0x18;
    ((s32 (*)(void *, void *))temp_r9->unk0x1C)(temp_r10 + temp_r9->unk0x18, temp_r31);
    if (temp_r31 != 0) {
        CStruct_delete(temp_r31, 3);
    }
    fn_801F559C(arg0);
}
