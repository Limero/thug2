// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800153C4-0x80015434 (112B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct W153C4_E {
    u32 f0;
    u32 f4;
    u32 f8;
} W153C4_E;

typedef struct W153C4_N {
    s32 count;
    u32 _4;
    W153C4_E *arr;
} W153C4_N;

extern bool lbl_802FFF68;

W153C4_E *fn_800153C4(s32 arg0, W153C4_N *arg1) {
    W153C4_N *n;
    W153C4_E *e;
    u32 i;

    if (lbl_802FFF68 != 0) {
        return 0;
    }
    n = arg1;
    while (n->count != -1) {
        e = n->arr;
        for (i = 0; i < (u32) n->count; i++) {
            if (e->f8 == (u32) arg0) {
                return e;
            }
            e++;
        }
        n++;
    }
    return 0;
}
