// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018483C-0x801848C8 (140B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

extern s32 fn_80184168(s32 arg0);
extern void *fn_8018B4C0(void *arg0, s32 *arg1, s32 *arg2);
extern s32 fn_8018E3B8(void *arg0);

void fn_8018483C(s32 arg0) {
    s32 spC;
    s32 sp8;
    void *temp_r31;
    s32 temp_r9;

    sp8 = 0;
    while (sp8 < fn_80184168(arg0)) {
        temp_r31 = fn_8018B4C0((char *)arg0 + 4, &sp8, &spC);
        if (fn_8018E3B8(temp_r31) != 0) {
            temp_r9 = *(s32 *)((char *)temp_r31 + 0x14);
            ((s32 (*)(void *))*(s32 *)((char *)temp_r9 + 0x64))(
                (char *)temp_r31 + *(s16 *)((char *)temp_r9 + 0x60));
        }
        sp8 = sp8 + 1;
    }
}
