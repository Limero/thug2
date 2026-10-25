// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801159C0-0x80115A28 (104B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetInteger(CStruct *, s32, s32 *, s32);
void * GetScriptString(s32 arg0);
void AddString(CStruct *arg0, s32 arg1, void *arg2);
bool ScriptGetScriptString(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    sp8 = 0;
    GetInteger(pParams, QB_INDEX, &sp8, 0);
    AddString(pScript->unk0x18, QB_STRING, GetScriptString(sp8));
    return true;
}
