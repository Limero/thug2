// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F2F98-0x800F3090 (248B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct VT {
    char pad0x0[0x48];
    s16 off48;
    char pad0x4A[0x2];
    s32 (*fn48)(void *);
    char pad0x50[0x18];
    s16 off68;
    char pad0x6A[0x2];
    s32 (*fn6C)(void *);
} VT;

typedef struct NODE {
    char pad0x0[0x14];
    s32 (*cb)(void *, void *, void *, void *);
    void *a18;
    void *a1C;
    char pad0x20[0x8];
    void *a28;
    char pad0x2C[0x4];
    struct NODE *next;      /* 0x30 */
    struct NODE *sub;       /* 0x34 */
    char pad0x38[0x18];
    VT *vt;                 /* 0x50 */
} NODE;

typedef struct OBJ {
    char pad0x0[0x28];
    NODE *headA;            /* 0x28 */
    NODE *headB;            /* 0x2C */
} OBJ;

s32 fn_800F39CC(s32);
NODE *fn_800F38B8(s32);
s32 fn_800F30D4(NODE **, NODE *);
s32 fn_800F3090(NODE **, NODE *);

void fn_800F2F98(OBJ *arg0) {
    NODE *n;
    NODE *nxt;
    NODE *t;
    VT *v;

    n = arg0->headB;
    if (n != NULL) {
        do {
            nxt = n->next;
            switch (fn_800F39CC((s32)n)) {
            case 0: break;                        /* phantom: steers the pivot */
            case 1: break;                        /* phantom: steers the pivot */
            case 2:
                t = fn_800F38B8((s32)n);
                if (t != NULL) {
                    t = fn_800F38B8((s32)n);
                    v = t->vt;
                    if (((s32 (*)(void *))v->fn48)((void *)((char *)t + v->off48)) == 0) {
                        break;
                    }
                }
                /* fallthrough */
            case 3:
                v = n->vt;
                if (((s32 (*)(void *))v->fn6C)((void *)((char *)n + v->off68)) == 0) {
                    break;
                }
                if (n->cb != NULL) {
                    n->cb((void *)n, n->a28, n->a18, n->a1C);
                }
                /* fallthrough */
            case 4:
                fn_800F30D4(&arg0->headB, n);
                fn_800F3090(&arg0->headA, n);
                break;
            case 5: break;                        /* phantom: steers the pivot */
            }
            n = nxt;
        } while (n != NULL);
    }
}
