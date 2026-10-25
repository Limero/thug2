// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8024D558-0x8024D5C4 (108B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_802B1510[];
extern s32 fn_80250E24(CStruct *, s32);
extern void fn_80250E6C(CStruct *, unsigned);
s32 fn_8024D558(Unk_C7387A53 *arg0) {
    u32 temp_r30;
    s32 temp_r3;

    goto check;
body:
    fn_80250E6C(*((void * *)&arg0->unk0x44), 9);
check:
    temp_r3 = fn_80250E24(*((void * *)&arg0->unk0x44), 9);
    if (temp_r3 == 1) {
        goto body;
    }
    temp_r30 = *(s32 *)((char *)lbl_802B1510 + (((u32)temp_r3 >> 1U) & QB_UNKNOWN_0x7FFFFFFC));
    fn_80250E6C(*((void * *)&arg0->unk0x44), temp_r30 >> 0x11U);
    return temp_r30 & 0x1FFFF;
}
