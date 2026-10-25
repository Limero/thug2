// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8010F078-0x8010F130 (184B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern s32 lbl_80383100[];
extern void GetString(CStruct *, s32 *, s32 *, s32);
extern s32 ContainsFlag(CStruct *, s32);
extern s32 fn_8000A778(s32);
extern void fn_8016A67C(s32, s32);

bool ScriptLoadQB(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 var_r11;

    sp8 = 0;
    GetString(pParams, 0, &sp8, 0);
    if (ContainsFlag(pParams, QB_LEVELSPECIFIC) != 0) {
        var_r11 = 0;
        while (var_r11 <= 0xE) {
            if (lbl_80383100[var_r11] == 0) {
                lbl_80383100[var_r11] = fn_8000A778(sp8);
                break;
            }
            var_r11++;
        }
        fn_8016A67C(sp8, 1);
    } else {
        fn_8016A67C(sp8, 0);
    }
    return true;
}
