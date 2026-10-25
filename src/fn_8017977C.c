// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8017977C-0x8017981C (160B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 CStruct_new(s32);
extern s32 CStruct_ctor(s32);
extern void AddChecksum(CStruct *, s32, s32);
extern void Script_RunScript(s32, s32, s32, s32, s32);
extern void CStruct_delete(CStruct *, s32);
bool fn_8017977C(void **arg0) {
    Unk_6A78CE27 *temp_r30;
    s32 temp_r31;

    temp_r31 = CStruct_ctor(CStruct_new(8));
    temp_r30 = *arg0;
    if (temp_r30->unk0x4 != 0) {
        AddChecksum(temp_r31, QB_ON, 0);
    }
    AddChecksum(temp_r31, QB_CHEAT_FLAG, *(s32 *)temp_r30);
    Script_RunScript(QB_CLIENT_TOGGLE_CHEAT, temp_r31, 0, 0, 0);
    if (temp_r31 != 0) {
        CStruct_delete(temp_r31, 3);
    }
    return true;
}
