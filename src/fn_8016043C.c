// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8016043C-0x801604EC (176B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305EE4;
s32 GetInteger(CStruct *, s32, s32 *, s32);
void fn_8019E194(void *);

bool ScriptBindFrontEndToController(CStruct *pParams, CScript *pScript) {
    s32 spC;
    s32 sp8;
    s32 *temp_r9;
    s32 *var_r11;
    s32 var_ctr;
    s32 temp_r3;
    s32 temp_r10;
    s32 *temp_r8;

    GetInteger(pParams, QB_CONTROLLER, &sp8, (s32 *)1);
    GetInteger(pParams, (s32 *)QB_FRONT_END_PAD, &spC, 1);
    temp_r3 = lbl_80305EE4;
    {
        register s32 *pA __asm__("r9");
        register s32 *pB __asm__("r8");

        var_ctr = 4;
        pA = (s32 *)(temp_r3 + 0x38);
        pB = pA;
        __asm__("" : "+r"(pB));
        var_r11 = pB;
        temp_r10 = pA[spC];
        do {
            if (*var_r11 == sp8) {
                *var_r11 = temp_r10;
            }
            var_r11 += 1;
            var_ctr -= 1;
        } while (var_ctr != 0);
        pB[spC] = sp8;
    }
    fn_8019E194(temp_r3);
    return true;
}
