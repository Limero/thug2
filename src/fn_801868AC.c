// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801868AC-0x8018694C (160B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_8018ECBC(Unk_C7387A53 * arg0);
void *fn_8018B4C0(Unk_C8FEE62D * arg0, s32 *arg1, s32 *arg2);
s32 fn_80184168(Unk_9994C3F5 * arg0);

void *fn_801868AC(s32 arg0) {
    s32 spC;
    s32 sp8;
    Unk_C8FEE62D *temp_r31;
    Unk_89391A04 *temp_r9;

    sp8 = 0;
    while (sp8 < fn_80184168(arg0)) {
        temp_r31 = fn_8018B4C0(arg0 + 4, &sp8, &spC);
        if (fn_8018ECBC(temp_r31) != 0) {
            temp_r9 = *((void * *)&temp_r31->unk0x14);
            if (((s32 (*)(void *))*((void * *)&temp_r9->unk0x24))((char *)temp_r31 + temp_r9->unk0x20) != 0) {
                return temp_r31;
            }
        }
        sp8 += 1;
    }
    return NULL;
}
