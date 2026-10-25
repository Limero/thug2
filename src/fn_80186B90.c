// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80186B90-0x80186BF8 (104B). Byte-identical.
#include "types.h"
#include "structs.h"

s32 fn_80184168(Unk_9994C3F5 *);
void *fn_8018B4C0(Unk_C8FEE62D *, s32 *, s32 *);
s32 fn_8018FC80(Unk_C7387A53 *);

void fn_80186B90(Unk_9994C3F5 *arg0) {
    s32 spC;
    s32 sp8;
    s32 temp_r31;

    temp_r31 = fn_80184168(arg0);
    sp8 = 0;
    while (sp8 < temp_r31) {
        fn_8018FC80(fn_8018B4C0((char *)arg0 + 4, &sp8, &spC));
        sp8 = sp8 + 1;
    }
}
