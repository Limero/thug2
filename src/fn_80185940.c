// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80185940-0x801859E8 (168B). Byte-identical.
#include "types.h"
#include "structs.h"

extern s32 fn_80184168(Unk_9994C3F5 * arg0);
extern void *fn_8018B4C0(Unk_C8FEE62D * arg0, s32 *arg1, s32 *arg2);

s32 fn_80185940(Unk_9994C3F5 *arg0, s32 arg1) {
    s32 sp8;
    s32 spC;
    s32 var_r30;
    Unk_C8FEE62D *temp_r3;
    Unk_8415B424 *temp_r9;

    var_r30 = 0;
    sp8 = 0;
    while (sp8 < fn_80184168(arg0)) {
        temp_r3 = fn_8018B4C0((char *)arg0 + 4, &sp8, &spC);
        if (*(s32 *)*((void * *)&temp_r3->unk0x30) == 0) {
            temp_r9 = *((void * *)&temp_r3->unk0x14);
            if (temp_r9->unk0xBC(
                    (char *)temp_r3 + temp_r9->unk0xB8, arg1) != 0) {
                var_r30 += 1;
            }
        }
        sp8 += 1;
    }
    return var_r30;
}
