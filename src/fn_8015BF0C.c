// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015BF0C-0x8015BF64 (88B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_80305EAC;
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
void fn_801A6B38(Unk_93C2DF4D *, s32);
typedef struct { char _0[0x24]; s32 lvl; } G39_t;
bool ScriptCareerReset(CStruct *pParams, CScript *pScript) {
    register G39_t *g __asm__("r11");
    s32 sp8;
    s32 lvl;

    g = (G39_t *)lbl_80305EAC;
    lvl = g->lvl;
    sp8 = 0;
    GetChecksum_2(pParams, 0, &sp8, 0);
    fn_801A6B38(lvl, sp8);
    return true;
}
