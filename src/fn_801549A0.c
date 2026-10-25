// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801549A0-0x80154A24 (132B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_80305F9C[];
extern char lbl_802A7F24[];
extern s32 GetText(CStruct *, void *, void *, s32);
extern s32 strlen(void *);
extern s32 strcasecmp(void *, void *);
void fn_80220060(Unk_C7387A53 *, u8 *);
s32 ScriptSendChatMessage(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    register s32 var_r3 __asm__("r3");

    sp8 = 0;
    GetText(pParams, QB_STRING, &sp8, 0);
    var_r3 = 0;
    if (sp8 != 0) {
        if ((strlen(sp8) != 0) && (strcasecmp(sp8, lbl_802A7F24) != 0)) {
            fn_80220060(*(s32 *)&lbl_80305F9C, sp8);
        }
        var_r3 = 1;
    }
    return var_r3;
}
