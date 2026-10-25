// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80185170-0x80185240 (208B). Byte-identical.
#include "types.h"
#include "structs.h"

extern s32 fn_80184168(Unk_9994C3F5 * arg0);
extern void *fn_8018B4C0(Unk_C8FEE62D * arg0, s32 *arg1, s32 *arg2);
extern s32 fn_8018EC90(Unk_C7387A53 * arg0);
extern s32 fn_8018DC9C(Unk_C7387A53 * arg0);
extern s32 fn_8018DCC8(Unk_C8FEE62D * arg0, s32 arg1, s32 arg2);
extern s32 fn_8018DC98(void *arg0, s32 arg1);

void fn_80185170(s32 arg0, s32 arg1, s32 arg2) {
    s32 spC;
    s32 sp8;
    s32 count;
    Unk_C8FEE62D *temp_r3;
    Unk_89391A04 *temp_r9;

    count = fn_80184168((void *)arg0);
    sp8 = 0;
    while (sp8 < count) {
        temp_r3 = fn_8018B4C0((void *)(arg0 + 4), &sp8, &spC);
        temp_r9 = *((void * *)&temp_r3->unk0x14);
        if ((temp_r9->unk0x24((char *)temp_r3 + temp_r9->unk0x20) != 0) &&
            (fn_8018EC90(temp_r3) == 0)) {
            if (fn_8018DC9C(temp_r3) != 0) {
                fn_8018DCC8(temp_r3, arg1, arg2);
            } else {
                fn_8018DC98(temp_r3, arg1);
            }
        }
        sp8 += 1;
    }
}
