// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80185BB8-0x80185C48 (144B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_80184168(void *);
void *fn_8018B4C0(void *, s32 *, s32 *);
s32 fn_8018EC64(void *);
s32 fn_8018D924(void *);
void fn_8018D97C(void *);
void fn_80185BB8(void *arg0) {
    s32 sp8;
    s32 spC;
    void *r;

    ((Unk_C7387A53 *)arg0)->unk0x50 = 1;
    for (sp8 = 0; sp8 < fn_80184168(arg0); sp8++) {
        r = fn_8018B4C0((char *)arg0 + 4, &sp8, &spC);
        if (fn_8018EC64(r) != 0 && fn_8018D924(r) != 0) {
            fn_8018D97C(r);
        }
    }
}
