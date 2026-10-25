// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800AB990-0x800ABAB0 (288B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_8012543C(s32);
void Script_RunScript(s32, s32, s32, s32, s32);
s32 GetChecksum_3(Unk_6A70655D *, s32);
void AddChecksum(CStruct *, s32, s32);
s32 CStruct_new(s32);
s32 Script_GetInteger(s32, s32);
s32 CStruct_ctor(s32);
s32 fn_801745B4(s32);
void CStruct_delete(CStruct *, s32);
extern s32 lbl_80305EAC;
void fn_800AB990(Unk_0771A7B9 *arg0) {
    s32 temp_r28;
    s32 temp_r31;
    s32 temp_r3;
    s32 var_r29;

    if ((arg0->unk0x34B8 != 0) && (Script_GetInteger(QB_TODMANAGER_TEMP_TOD_CHANGED, 1) != 0)) {
        var_r29 = 0;
        temp_r28 = CStruct_ctor(CStruct_new(8));
        AddChecksum((CStruct *)temp_r28, 0, QB_ISBLOCKING);
        while (var_r29 < arg0->unk0x2054) {
            temp_r31 = *(s32 *)((char *)arg0 + 0x68 + var_r29 * 0x20);
            if (GetChecksum_3((Unk_6A70655D *)temp_r31, QB_MODEL) != 0) {
                Script_RunScript(QB_CUTSCENEOBJ_INIT_MODEL, temp_r28, temp_r31, 0, 0);
            }
            var_r29 += 1;
        }
        temp_r3 = fn_801745B4(lbl_80305EAC);
        if (temp_r3 != 0) {
            Script_RunScript(QB_CUTSCENEOBJ_INIT_MODEL, temp_r28, temp_r3, 0, 0);
        }
        if (temp_r28 != 0) {
            CStruct_delete((CStruct *)temp_r28, 3);
        }
        *(s32 *)((char *)fn_8012543C(QB_TODMANAGER_TEMP_TOD_CHANGED) + 0xC) = 0;
    }
}
