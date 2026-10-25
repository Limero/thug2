// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015BEB8-0x8015BF0C (84B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305EAC;
s32 GetInteger(CStruct *, s32, s32 *, s32);
void fn_801A7E14(Unk_93C2DF4D *, s32);
typedef struct { char _0[0x24]; s32 lvl; } G39_t;
bool ScriptSetCurrentChapter(CStruct *pParams, CScript *pScript) {
    register G39_t *g __asm__("r11");
    s32 sp8;
    s32 lvl;

    g = (G39_t *)lbl_80305EAC;
    lvl = g->lvl;
    GetInteger(pParams, QB_CHAPTER, &sp8, 0);
    fn_801A7E14(lvl, sp8);
    return true;
}
