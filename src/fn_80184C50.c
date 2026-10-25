// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80184C50-0x80184CB8 (104B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

s32 fn_80184168(void *);
s32 fn_8018B4C0(void *, s32 *, s32 *);
s32 fn_8018D108(s32);

void fn_80184C50(void *arg0) {
    s32 spC;
    s32 sp8;

    sp8 = 0;
    while (sp8 < fn_80184168(arg0)) {
        fn_8018D108(fn_8018B4C0((char *)arg0 + 4, &sp8, &spC));
        sp8++;
    }
}
