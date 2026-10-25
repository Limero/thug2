// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800CC268-0x800CC2D4 (108B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct Node {
    s32 unk0x0;
    s32 unk0x4;              /* -1 == end-of-list sentinel */
    s32 unk0x8;
    struct Node *unk0xC;     /* ->next */
    char _pad0[0x28];
    struct Node *unk0x38;    /* list head */
    char _pad1[0x28];
    s32 unk0x64;             /* bit 29 tested below */
} Node;

/* AND-folds bit 29 of every node's +0x64 (short-circuited by the running
   accumulator) over the list at arg0->unk0x38; returns 1 if the list is empty. */
s32 fn_800CC268(Node *arg0) {
    Node *a, *b, *c;
    s32 acc, t1, t2, bit;

    a = arg0->unk0x38;
    acc = 1;
    if (a->unk0x4 == -1) {
        a = 0;
    }
    b = a;
    if (b != 0) {
        do {
            bit = (s32) (((u32) b->unk0x64 >> 0x1D) & 1);
            t1 = 1;
            if (acc == 0) {
                t1 = 0;
            }
            t2 = 1;
            if (bit == 0) {
                t2 = 0;
            }
            c = b->unk0xC;
            acc = t1 & t2;
            if (c->unk0x4 == -1) {
                c = 0;
            }
            b = c;
        } while (b != 0);
    }
    return acc;
}
