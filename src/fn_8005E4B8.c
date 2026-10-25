// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005E4B8-0x8005E55C (164B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
void fn_8005E2F4(float v);
void fn_8005E2E8(float v);
#include "qb_constants.h"
#include "structs.h"
void fn_8005E2DC(float v);
s32 GetFloat(CStruct *, s32, f32 *, void *);
bool ScriptSet2DIn3DSpaceParams(CStruct *pParams, CScript *pScript) {
    f32 spC;
    f32 sp8;

    if (GetFloat(pParams, QB_NOSCALE_DISTANCE, &sp8, NULL) != 0) {
        fn_8005E2DC(sp8);
    }
    if (GetFloat(pParams, QB_MAX_SCALE, &spC, 0) != 0) {
        fn_8005E2E8(spC);
    }
    if (GetFloat(pParams, QB_MIN_SCALE, &spC, 0) != 0) {
        fn_8005E2F4(spC);
    }
    return true;
}
