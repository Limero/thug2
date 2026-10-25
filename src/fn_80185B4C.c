// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80185B4C-0x80185BB8 (108B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

s32 fn_80184168(void *);
void *fn_8018B4C0(void *, s32 *, s32 *);
void fn_8018E584(void *);

/* file-local layout: only the 0x50 flag word is touched here. */
typedef struct { char _pad[0x50]; s32 unk50; } T_85B4C;

void fn_80185B4C(void *arg0) {
    s32 spC;
    s32 sp8;

    ((T_85B4C *)arg0)->unk50 = 1;
    sp8 = 0;
    while (sp8 < fn_80184168(arg0)) {
        fn_8018E584(fn_8018B4C0((char *)arg0 + 4, &sp8, &spC));
        sp8 = sp8 + 1;
    }
}
