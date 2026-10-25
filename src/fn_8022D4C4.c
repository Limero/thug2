// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022D4C4-0x8022D538 (116B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_802FFE98[];
extern s32 lbl_80305FF4;
void fn_8000F2F8(Unk_9F352E7C *, s32);
void fn_80056B1C(Unk_CFB386B2 *, Unk_C7387A53 *);
void fn_8000F320(Unk_F12C5E01 *);
void fn_8022D4C4(Unk_DB0E2BAB *arg0) {
    Unk_9994C3F5 *temp_r3;

    if (lbl_80305FF4 != 0) {
        temp_r3 = *(void * *)&lbl_802FFE98;
        arg0->unk0x0 = (s32) (arg0->unk0x0 & QB_UNKNOWN_0xFFFFFFBF);
        fn_8000F2F8(temp_r3, temp_r3->unk0x11C);
        fn_80056B1C(arg0->unk0x14, 0);
        fn_8000F320(*(void * *)&lbl_802FFE98);
        arg0->unk0x0 = (s32) (arg0->unk0x0 | 0x10);
    }
}
