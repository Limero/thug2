// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801859E8-0x80185A88 (160B). Byte-identical.
#include "types.h"
#include "structs.h"

void *fn_8018B4C0(Unk_C8FEE62D *, s32 *, s32 *);
s32 fn_80184168(Unk_9994C3F5 *);

s32 fn_801859E8(Unk_9994C3F5 *arg0) {
    s32 spC;
    s32 sp8;
    s32 var_r30;
    Unk_C8FEE62D *temp_r3;
    Unk_5BE2D2B7 *temp_r9;

    sp8 = var_r30 = 0;
    while (sp8 < fn_80184168(arg0)) {
        temp_r3 = fn_8018B4C0((char *)arg0 + 4, &sp8, &spC);
        if (*(s32 *)temp_r3->unk0x30 == 0) {
            temp_r9 = *((void * *)&temp_r3->unk0x14);
            if (temp_r9->unk0xAC(
                    (char *)temp_r3 + temp_r9->unk0xA8) != 0) {
                var_r30 += 1;
            }
        }
        sp8 += 1;
    }
    return var_r30;
}
