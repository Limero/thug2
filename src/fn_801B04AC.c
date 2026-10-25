// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B04AC-0x801B0544 (152B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_802ABD94[];
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 GetText(CStruct *, void *, void *, s32);
void fn_801B0144(Unk_F96D0DC8 *, Unk_1D62F22E *);
void fn_801B04AC(CStruct *arg0, CStruct *arg1) {
    s32 sp8;
    s32 temp_r3;

    GetInteger(arg1, QB_VALUE, (char *)arg0 + 8, 0);
    temp_r3 = GetInteger(arg1, QB_NUMBER, (char *)arg0 + 0xC, 0);
    if (temp_r3 == 0) {
        arg0->unk0xC = temp_r3;
    }
    sp8 = (s32)lbl_802ABD94;
    GetText(arg1, QB_INITIALS, &sp8, 0);
    fn_801B0144(arg0->unk0x4, sp8);
}
