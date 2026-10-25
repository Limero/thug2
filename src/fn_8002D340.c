// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8002D340-0x8002D3A4 (100B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_802FFE98[];
void fn_8000F320(Unk_F12C5E01 *);
s32 fn_8000F16C(Unk_4897C6F8 *);
void fn_8000F2F8(Unk_9F352E7C *, s32);
s32 fn_80010400(s32, s32, s32);
s32 fn_8002D340(void) {
    s32 temp_r30;
    s32 temp_r30_2;

    temp_r30_2 = *(s32 *)&lbl_802FFE98;
    fn_8000F2F8(temp_r30_2, fn_80010400(temp_r30_2, QB_ANIMHEAP, 1));
    temp_r30 = fn_8000F16C(*(s32 *)&lbl_802FFE98);
    fn_8000F320(*(s32 *)&lbl_802FFE98);
    return temp_r30;
}
