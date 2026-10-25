// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802159C4-0x80215ACC (264B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 lbl_802AF740;
extern f32 lbl_802AF744;
extern void fn_800CC038(void *, s32, s32, s32, f32);
extern s32 ContainsFlag(CStruct *, s32);
extern s32 GetFloat(CStruct *, s32, f32 *, s32);
bool fn_802159C4(Unk_27E58CF3 *arg0, CStruct *arg1) {
    if (ContainsFlag(arg1, QB_OFF) != 0) {
        if ((s32) arg0->unk0x7B8 != 0) {
            arg0->unk0x7B8 = 0;
            fn_800CC038(arg0->unk0x1840, 0, 1, 0, lbl_802AF740);
        }
    } else if (ContainsFlag(arg1, QB_RUN) != 0) {
        arg0->unk0x7B8 = 1;
    } else if (ContainsFlag(arg1, QB_HANGMOVE) != 0) {
        arg0->unk0x7B8 = 2;
    } else if (ContainsFlag(arg1, QB_LADDERMOVE) != 0) {
        arg0->unk0x7B8 = 3;
        arg0->unk0x19CC = lbl_802AF744;
    }
    GetFloat(arg1, QB_STANDARDSPEED, (char *)arg0 + (s32)0x187C, 0);
    return true;
}
