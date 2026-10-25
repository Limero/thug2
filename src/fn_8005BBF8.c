// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005BBF8-0x8005BCA0 (168B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetInteger(CStruct *, void *, s32 *, void *);
void fn_8005B9E0(s32 *arg0);
bool ScriptSetLoadingBarEndColor(CStruct *pParams, CScript *pScript) {
    struct {
        s32 sp8;
        s32 outs[3];
    } S;
    s8 clr[4];
    s32 g;
    s32 b;

    s32 *p = &S.outs[0];
    GetInteger(pParams, (void *)QB_R, p, 0);
    GetInteger(pParams, (void *)QB_G, &S.outs[1], 0);
    GetInteger(pParams, (void *)QB_B, &S.outs[2], 0);
    g = S.outs[1];
    b = S.outs[2];
    clr[0] = ((u8 *)p)[3];
    clr[1] = g;
    clr[2] = b;
    clr[3] = -0x80;
    S.sp8 = *(s32 *)clr;
    fn_8005B9E0(&S.sp8);
    return true;
}
