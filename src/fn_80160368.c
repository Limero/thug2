// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80160368-0x801603C0 (88B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_8005583C(void *);
s32 AddString(CStruct *, void *, void *);
s32 GetInteger(CStruct *, void *, s32 *, void *);
bool ScriptGetSoundtrackName(CStruct *pParams, CScript *pScript) {
    s32 temp_r5;
    s32 sp8;

    GetInteger(pParams, 0, &sp8, 1);
    temp_r5 = fn_8005583C(sp8);
    AddString(pScript->unk0x18, QB_SOUNDTRACKNAME,  temp_r5);
    return true;
}
