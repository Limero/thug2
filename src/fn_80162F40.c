// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80162F40-0x80162FE4 (164B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern CStruct * lbl_80366478;
s32 GetText(CStruct *, void *, void *, s32);
s32 ContainsFlag(CStruct *, s32);
s32 fn_8005CFC0(s32);
s32 fn_8005CA70(CStruct *, void *, s32, s32, s32);

s32 ScriptLoadParticleTexture(CStruct *pParams, CScript *pScript) {
    void *sp8;
    s32 temp_r7;
    s32 var_r31;

    GetText(pParams, 0, &sp8, 0);
    {
        register u8 *chk __asm__("r4");
        chk = (u8 *)sp8;
        if (*chk == 0) {
            return 0;
        }
    }
    var_r31 = fn_8005CFC0(lbl_80366478);
    temp_r7 = ContainsFlag(pParams, QB_PERM);
    if (var_r31 == 0) {
        var_r31 = fn_8005CA70(lbl_80366478, sp8, 1, 1, temp_r7);
    }
    return var_r31 ? 1 : 0;
}
