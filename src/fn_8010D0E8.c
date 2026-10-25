// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8010D0E8-0x8010D1C0 (216B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

s32 fn_80128E34(CStruct *, void *, void *, s32);
s32 GetStructure_2(CStruct *, s32, s32 *, s32);
void fn_801270B4(CStruct *, s32);
s32 fn_8009F498(s32);
void CObject_AddRefLink(CStruct *, Unk_9994C3F5 *);
s32 fn_8009F3D0(Unk_C8FEE62D *, s32, CStruct *);

bool ScriptRunScriptOnObject(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 spC;
    s32 sp10;
    Unk_C8FEE62D *temp_r30;
    void *temp_r9;
    char *temp_r4;

    fn_80128E34(pParams, QB_ID, &sp8, 1);
    fn_80128E34(pParams, 0, &spC, 1);
    sp10 = 0;
    GetStructure_2(pParams, QB_PARAMS, &sp10, 0);
    fn_801270B4(pScript->unk0x18, QB_UNIQUEID);
    temp_r30 = fn_8009F498(sp8);
    if (temp_r30 != 0) {
        temp_r9 = *((void * *)&temp_r30->unk0x14);
        if ((temp_r9 != NULL) && (*(void **)(temp_r4 = (char *)temp_r9 + (s32)0xBC) == NULL)) {
            *(void **)temp_r4 = (void *)temp_r30;
            CObject_AddRefLink((void *)temp_r30, temp_r4);
        }
        fn_8009F3D0((void *)temp_r30, spC, sp10);
        return true;
    }
    return false;
}
