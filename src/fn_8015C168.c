// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015C168-0x8015C1F0 (136B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305EAC;
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 fn_80128C80(CStruct *, void *, void *, s32);
s32 fn_801A7094(Unk_93C2DF4D *, s32, s32);
typedef struct { char _0[0x24]; s32 lvl; } G39_t;
void ScriptGetFlag(CStruct *pParams, CScript *pScript) {
    register G39_t *g __asm__("r11");
    register s32 a1 __asm__("r4");
    s32 spC;
    s32 sp8;
    s32 var_r5;
    s32 flags;

    fn_80128C80(pParams, QB_FLAG, &sp8, 1);
    spC = 0;
    GetInteger(pParams, QB_LEVEL, &spC, 0);
    g = (G39_t *)lbl_80305EAC;
    flags = g->lvl;
    var_r5 = spC;
    if (var_r5 == 0) {
        var_r5 = -1;
        a1 = sp8;
        __asm__("" : "+r"(a1));
    } else {
        a1 = sp8;
        __asm__("" : "+r"(a1));
    }
    fn_801A7094(flags, a1, var_r5);
}
