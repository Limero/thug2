// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015C1F0-0x8015C234 (68B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305EAC;
s32 fn_80128C80(CStruct *, void *, void *, s32);
s32 fn_801A70D8(Unk_93C2DF4D *, s32);
typedef struct { char _0[0x24]; s32 lvl; } G39_t;
void ScriptJustGotFlag(CStruct *pParams, CScript *pScript) {
    register G39_t *g __asm__("r9");
    s32 sp8;

    fn_80128C80(pParams, QB_FLAG, &sp8, 1);
    g = (G39_t *)lbl_80305EAC;
    fn_801A70D8(g->lvl, sp8);
}
