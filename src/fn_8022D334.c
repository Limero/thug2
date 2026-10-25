// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022D334-0x8022D3C0 (140B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_802FFE98[];
void fn_8022D910(s32, s32);
void fn_8022E414(Unk_C7387A53 *, CStruct *);
void fn_8022E5B4(Unk_31DE137E *, CStruct *);
void fn_8000F2F8(Unk_9F352E7C *, s32);
void fn_8000F320(Unk_F12C5E01 *);
s32 fn_800F1034();
void fn_8022D334(Unk_DB0E2BAB *arg0, s32 arg1, s32 arg2) {
    s32 temp_r3;
    Unk_9994C3F5 *temp_r3_2;

    fn_8022D910(arg0, arg2);
    temp_r3 = fn_800F1034();
    fn_8022E414((void *)arg0, (void *)temp_r3);
    if (arg1 == QB_REGULAR_PLAY) {
        temp_r3_2 = *(void * *)&lbl_802FFE98;
        fn_8000F2F8(temp_r3_2, temp_r3_2->unk0x118);
        fn_8022E5B4((void *)arg0, (void *)temp_r3);
        fn_8000F320(*(void * *)&lbl_802FFE98);
        return;
    }
    fn_8022E5B4((void *)arg0, (void *)temp_r3);
}
