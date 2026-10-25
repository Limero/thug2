// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80195AAC-0x80195B14 (104B). Byte-identical.
#include "types.h"
#include "structs.h"
// FIXED: fn_8018E24C + fn_80183D68 protos - EXACT, M5.47
void *fn_8018E24C(Unk_C7387A53 *);
void fn_80183D68(Unk_C7387A53 *, void *);
void fn_80195AAC(Unk_C7387A53 *arg0) {
    s32 temp_r30;
    s32 temp_r9;

    if (fn_80195B14() != 0) {
        temp_r9 = arg0->unk0x88 + 1;
        arg0->unk0x88 = temp_r9;
        if (temp_r9 > (s32) arg0->unk0x84) {
            temp_r30 = Game_GetGoalManager();
            fn_80183D68(temp_r30, fn_8018E24C(arg0));
        }
    }
}

