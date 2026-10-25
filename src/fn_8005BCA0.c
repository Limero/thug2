// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005BCA0-0x8005BD04 (100B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// ScriptSetLoadingBarBorder — reads the loading-bar border setting through
// GetInteger under two hash keys, then forwards to fn_8005BA0C (declared
// f32-returning so ngccc drops the crclr cr1eq before its bl, §4p item-27).
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetInteger(CStruct *, void *, s32 *, void *);
extern f32 fn_8005BA0C(s32, s32);
bool ScriptSetLoadingBarBorder(CStruct *pParams, CScript *pScript) {
    s32 spC;
    s32 sp8;

    GetInteger(pParams, QB_WIDTH, &sp8, NULL);
    GetInteger(pParams, (s32 *)QB_HEIGHT, &spC, 0);
    fn_8005BA0C(sp8, spC);
    return true;
}
