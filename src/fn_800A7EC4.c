// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A7EC4-0x800A7F38 (116B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct A7EC4_E {
    s32 f0;
    u8 _p[8];
} A7EC4_E;

typedef struct A7EC4_O {
    A7EC4_E *arr;
    s32 count;
} A7EC4_O;

extern void CObject_AddRefLink(void *arg0, A7EC4_E *elem);

void fn_800A7EC4(A7EC4_O *arg0, s32 arg1) {
    s32 i;

    for (i = 0; i < arg0->count; i++) {
        A7EC4_E *e = (A7EC4_E *)(i * 12 + (s32) arg0->arr);
        if (e->f0 == 0) {
            e->f0 = arg1;
            if (arg1 != 0) {
                CObject_AddRefLink((void *) arg1, e);
            }
            return;
        }
    }
}
