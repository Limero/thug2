// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801AF164-0x801AF210 (172B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void Script_GetInteger(s32, s32);
s32 GetInteger(CStruct *, s32, s32 *, s32);
void GetText(CStruct *, void *, void *, s32);
void fn_801AF004(void *, s32, s32, s32);
extern char lbl_802ABC84[];

void fn_801AF164(void *arg0, CStruct *arg1) {
    u8 *spC;
    s32 sp8;

    sp8 = 0;
    GetInteger(arg1, QB_SCORE, &sp8, 0);
    spC = (u8 *)lbl_802ABC84;
    GetText(arg1, QB_TEXT, &spC, 0);
    if ((sp8 != 0) && ((s32) *spC != 0)) {
        fn_801AF004(arg0, spC, 0, sp8);
        return;
    }
    Script_GetInteger(QB_PRINTGAPS, 0);
}
