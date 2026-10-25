// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80117C18-0x80117CC0 (168B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
extern s32 lbl_803032D8;
bool ScriptSetScriptWarningLevel(CStruct *pParams, CScript *pScript) {
    u32 sp8;
    sp8 = QB_NONE;
    GetChecksum_2(pParams, QB_LEVEL, (s32 *)&sp8, 0);
    switch (sp8) {
    case QB_NONE: lbl_803032D8 = 0; break;
    case QB_WARN: lbl_803032D8 = 1; break;
    case QB_ASSERT: lbl_803032D8 = 2; break;
    }
    return true;
}
