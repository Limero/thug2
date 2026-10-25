// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8002BB14-0x8002BBA0 (140B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_80125A3C(void *, s32);
s32 CStruct_new(s32);
s32 CStruct_ctor(s32);
void fn_8012772C(CStruct *, s32, f32);
void Script_RunScript(s32, s32, s32, s32, s32);
void CStruct_delete(CStruct *, s32);
bool fn_8002BB14(Unk_C7387A53 *arg0, Unk_9994C3F5 *arg1) {
    s32 temp_r31;

    fn_80125A3C(QB_MOVIECAM_DEBUG, 0);
    temp_r31 = CStruct_ctor(CStruct_new(8));
    fn_8012772C(temp_r31, 0, *((f32 *)&arg0->unk0xC));
    Script_RunScript(QB_CHANGECAMERAFOV, temp_r31, arg1, 0, 0);
    if (temp_r31 != 0) {
        CStruct_delete(temp_r31, 3);
    }
    return true;
}
