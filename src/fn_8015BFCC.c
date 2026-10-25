// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015BFCC-0x8015C018 (76B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_802A81AC[];
extern s32 lbl_80305EAC;
typedef struct { char _0[0x24]; s32 lvl; } G39_t;
s32 fn_80128CB0(CStruct *, void *, void *, s32);
void fn_801A6D34(Unk_93C2DF4D *, s32, s32);
bool ScriptUnSetGoal(CStruct *pParams, CScript *pScript) {
    register G39_t *g __asm__("r11");
    s32 sp8;

    fn_80128CB0(pParams, (s32)lbl_802A81AC, &sp8, 1);
    g = (G39_t *)lbl_80305EAC;
    fn_801A6D34(g->lvl, sp8, -1);
    return true;
}
