// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015BB2C-0x8015BB78 (76B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_80305EAC;
s32 fn_80128C80(CStruct *, void *, void *, s32);
s32 fn_801A6CCC(Unk_93C2DF4D *);
bool ScriptCareerLevelIs(CStruct *pParams, CScript *pScript) {
    Unk_975100B4 *g;
    s32 sp8;

    fn_80128C80(pParams, 0, &sp8, 1);
    g = (char *)lbl_80305EAC;
    __asm__("" : "+r"(g));
    return (fn_801A6CCC((void *)g->unk0x24) ^ sp8) == 0;
}
