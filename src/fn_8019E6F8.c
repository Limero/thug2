// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8019E6F8-0x8019E770 (120B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 CStruct_new(s32);
s32 CStruct_ctor(void *);
void AddString(CStruct *, s32, void *);
void AddChecksum(CStruct *, s32, s32);
void ScriptReloadSkaterCamAnim(void *, s32);
void CStruct_delete(CStruct *, s32);

bool fn_8019E6F8(void **arg0) {
    Unk_C7387A53 *temp_r30;
    s32 temp_r31;

    temp_r30 = *arg0;
    temp_r31 = CStruct_ctor((void *)CStruct_new(8));
    AddString((void *)temp_r31, 0, temp_r30);
    AddChecksum((void *)temp_r31, 0, temp_r30->unk0x80);
    ScriptReloadSkaterCamAnim((void *)temp_r31, 0);
    if (temp_r31 != 0) {
        CStruct_delete(temp_r31, 3);
    }
    return true;
}
