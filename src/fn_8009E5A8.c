// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009E5A8-0x8009E63C (148B). Byte-identical.
// extra_cflags: -fno-schedule-insns
#include "types.h"
#include "structs.h"
void fn_80127438(CStruct *, CStruct *);
void fn_80126808(Unk_80577C09 *, Unk_5D1D68CC *, s32);
void fn_8009F4C4(s32);
s32 fn_801288C4(CStruct *, s32);
void GetChecksum_2(CStruct *, s32, s32 *, s32);
bool fn_8009E5A8(Unk_C7387A53 *arg0, CStruct *arg1, CStruct *arg2) {
    s32 sp8;
    s32 temp_r30;
    s32 temp_r3;

    if ((s32) arg0->unk0x24 != 0) {
        GetChecksum_2(arg1, 0, &sp8, 1);
        temp_r3 = fn_801288C4(arg0->unk0x24, sp8);
        if (temp_r3 != 0) {
            fn_8009F4C4(0x10);
            temp_r30 = fn_801252BC();
            fn_80126808(temp_r30, temp_r3, 0);
            fn_80127438(arg2, temp_r30);
            return true;
        }
    }
    return false;
}
