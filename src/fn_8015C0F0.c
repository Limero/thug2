// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015C0F0-0x8015C168 (120B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305EAC;
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 fn_80128C80(CStruct *, void *, void *, s32);
void fn_801A7048(Unk_93C2DF4D *, s32, s32);
typedef struct { char _0[0x24]; s32 lvl; } G39_t;
bool ScriptUnSetFlag(CStruct *pParams, CScript *pScript) {
    register G39_t *g __asm__("r11");
    s32 spC;
    s32 sp8;

    fn_80128C80(pParams, QB_FLAG, &sp8, 1);
    spC = -1;
    GetInteger(pParams, QB_LEVEL, &spC, 0);
    g = (G39_t *)lbl_80305EAC;
    fn_801A7048(g->lvl, sp8, spC);
    return true;
}
