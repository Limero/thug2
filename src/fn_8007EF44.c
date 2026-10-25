// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007EF44-0x8007EFB4 (112B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct W7EF44_Ent {
    u8 _p0[4];
    u16 flags;
} W7EF44_Ent;

typedef struct W7EF44_Ent2 {
    u8 _p0[0x50];
    u16 f50;
} W7EF44_Ent2;

typedef struct W7EF44_Root {
    u8 _p0[0x20];
    W7EF44_Ent **list;
    u32 count;
    u8 _p2[4];
    s32 v2C;
    W7EF44_Ent2 *child;
} W7EF44_Root;

void fn_8007EF44(W7EF44_Root *arg0, s16 arg1) {
    W7EF44_Ent2 *p;
    u32 i;

    p = arg0->child;
    if (p != NULL) {
        p->f50 = (u16) arg1;
        return;
    }
    arg0->v2C = arg1;
    if (arg0->list != NULL) {
        for (i = 0; i < arg0->count; i++) {
            W7EF44_Ent *e = arg0->list[i];
            u32 v = e->flags;
            v &= ~2;
            if (arg1 != 0) {
                v |= 2;
            }
            e->flags = (u16) v;
        }
    }
}
