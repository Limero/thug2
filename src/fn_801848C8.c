// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801848C8-0x80184930 (104B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void fn_8018E6D4(void *);
void *fn_8018B4C0(s32, s32 *, s32 *);
s32 fn_80184168(s32);
void fn_801848C8(s32 arg0) {
    s32 spC;
    s32 sp8;

    sp8 = 0;
    while (sp8 < fn_80184168(arg0)) {
        fn_8018E6D4(fn_8018B4C0(arg0 + 4, &sp8, &spC));
        sp8 += 1;
    }
}