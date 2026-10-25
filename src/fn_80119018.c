// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80119018-0x80119084 (108B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_80303150[];

s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 Tmr_GetTime(void);
void AddInteger(CStruct *, s32, s32);

bool ScriptGetElapsedTime(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 temp_r28;
    s32 temp_r29;

    GetInteger(pParams, QB_STARTTIME, &sp8, 0);
    temp_r29 = sp8;
    temp_r28 = pScript->unk0x18;
    AddInteger(temp_r28, QB_ELAPSEDTIME,
                (*(s32 *)&lbl_80303150 + Tmr_GetTime()) - temp_r29);
    return true;
}