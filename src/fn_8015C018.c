// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015C018-0x8015C060 (72B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_802A81AC[];
extern s32 lbl_80305EAC;
s32 fn_80128CB0(CStruct *, void *, void *, s32);
void fn_801A6D80(Unk_93C2DF4D *, s32, s32);
typedef struct { char _0[0x24]; s32 lvl; } G39_t;
void ScriptGetGoal(CStruct *pParams, CScript *pScript) {
    register G39_t *g __asm__("r11");
    s32 sp8;

    fn_80128CB0(pParams, (s32)lbl_802A81AC, &sp8, 1);
    g = (G39_t *)lbl_80305EAC;
    fn_801A6D80(g->lvl, sp8, -1);
}
