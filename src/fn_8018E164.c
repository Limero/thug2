// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018E164-0x8018E1E8 (132B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 CStruct_new(s32);
void CStruct_delete(CStruct *, s32);
void Script_RunScript(s32, s32, s32, s32, s32);
void AddChecksum(CStruct *, s32, s32);
s32 CStruct_ctor(s32);
s32 fn_8018E24C(Unk_C7387A53 *);
void fn_8018E164(Unk_C7387A53 *arg0) {
    s32 temp_r31;


temp_r31 = CStruct_ctor(CStruct_new(8));
    AddChecksum(temp_r31, QB_GOAL_ID, fn_8018E24C(arg0));
    Script_RunScript(QB_GOAL_NO_VALID_KEY_COMBOS, temp_r31, 0, 0, 0);
    if (temp_r31 != 0) {
        CStruct_delete(temp_r31, 3);
    }
}
