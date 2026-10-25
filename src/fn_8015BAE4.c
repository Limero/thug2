// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015BAE4-0x8015BB2C (72B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305EAC;
s32 fn_80128C80(CStruct *, void *, void *, s32);
void fn_801A6C4C(Unk_93C2DF4D *, s32);
typedef struct { char _0[0x24]; s32 lvl; } G39_t;
bool ScriptCareerStartLevel(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    register G39_t *g __asm__("r9");

    fn_80128C80(pParams, QB_LEVEL, &sp8, 1);
    g = (G39_t *)lbl_80305EAC;
    fn_801A6C4C(g->lvl, sp8);
    return true;
}
