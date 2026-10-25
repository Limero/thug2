// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015BD7C-0x8015BDD4 (88B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_80305EAC;
typedef struct { char _0[0x24]; s32 lvl; } G39_t;
s32 GetInteger(CStruct *, s32, s32 *, s32);
void fn_801A7E0C(Unk_B0DD7FE7 *, s32);
bool ScriptSetClassicTotalGoals(CStruct *pParams, CScript *pScript) {
    register G39_t *g __asm__("r11");
    s32 sp8;
    s32 goals;

    g = (G39_t *)lbl_80305EAC;
    goals = g->lvl;
    sp8 = 0;
    GetInteger(pParams, 0, &sp8, 1);
    fn_801A7E0C(goals, sp8);
    return true;
}
