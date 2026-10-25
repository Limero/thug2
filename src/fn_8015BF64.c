// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015BF64-0x8015BFCC (104B). Byte-identical.
#include "types.h"
extern char lbl_802A81AC[];
extern s32 lbl_80305EC0;
extern s32 lbl_80305EAC;
#include "qb_constants.h"
#include "structs.h"
s32 fn_80128CB0(CStruct *, void *, void *, s32);
s32 IsTrue(s32, void *);
void fn_801A6CF8(Unk_93C2DF4D *, s32, s32);
typedef struct { char _0[0x24]; s32 lvl; } G39_t;
bool ScriptSetGoal(CStruct *pParams, CScript *pScript) {
    register G39_t *g __asm__("r11");
    s32 sp8;

    fn_80128CB0(pParams, (s32)lbl_802A81AC, &sp8, 1);
    if (IsTrue(lbl_80305EC0, QB_IS_CAREER) != 0) {
        g = (G39_t *)lbl_80305EAC;
        fn_801A6CF8(g->lvl, sp8, -1);
    }
    return true;
}
