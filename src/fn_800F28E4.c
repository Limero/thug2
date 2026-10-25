// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F28E4-0x800F29CC (232B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct VT {
    char pad0x0[0x20];
    s16 off20;
    char pad0x22[0x2];
    s32 (*fn20)(void *, s32);
    char pad0x28[0x10];
    s16 off38;
    char pad0x3A[0x2];
    s32 (*fn38)(void *);
    char pad0x40[0x8];
    s16 off48;
    char pad0x4A[0x2];
    s32 (*fn48)(void *);
    char pad0x50[0x28];
    s16 off78;
    char pad0x7A[0x2];
    s32 (*fn78)(void *);
} VT;

typedef struct NODE {
    char pad0x0[0x4];
    s32 a04;
    char pad0x8[0x48];
    VT *vt;
} NODE;

typedef struct OBJ {
    char pad0x0[0x24];
    s32 a24;
    NODE *headA;
    NODE *headB;
} OBJ;

s32 fn_800F38B8(NODE *);
void fn_800F3930(void *, NODE *);
s32 fn_800F30D4(NODE **, NODE *);
void fn_800F3438(s32, void *);

void fn_800F28E4(OBJ *arg0, NODE *arg1) {
    s32 sp8;
    NODE *t3;
    VT *v;

    sp8 = arg1->a04;
    t3 = fn_800F38B8(arg1);
    if (t3 != NULL) {
        fn_800F3930(t3, arg1);
    }
    v = arg1->vt;
    if (((s32 (*)(void *))v->fn48)((void *)((char *)arg1 + v->off48)) != 0) {
        fn_800F30D4(&arg0->headA, arg1);
    } else {
        v = arg1->vt;
        ((s32 (*)(void *))v->fn78)((void *)((char *)arg1 + v->off78));
        fn_800F30D4(&arg0->headB, arg1);
    }
    v = arg1->vt;
    ((s32 (*)(void *))v->fn38)((void *)((char *)arg1 + v->off38));
    if (arg1 != NULL) {
        v = arg1->vt;
        ((s32 (*)(void *, s32))v->fn20)((void *)((char *)arg1 + v->off20), 3);
    }
    fn_800F3438(arg0->a24, &sp8);
}
