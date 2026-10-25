// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8006A780-0x8006A8C0 (320B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
#include "mem.h"

typedef struct A780_VT {
    char _00[8];
    s16 off8;
    char _0A[2];
    s32 (*fn0C)(void *, s32);
} A780_VT;

typedef struct A780_OBJ {
    char pad0x0[0x1B8];
    A780_VT *unk0x1B8;
} A780_OBJ;

typedef struct A780_NODE {
    A780_OBJ *unk0x0;
    struct A780_NODE *unk0x4;
    struct A780_NODE *unk0x8;
} A780_NODE;

typedef struct A780_HDR {
    A780_NODE *unk0x0;
    s32 unk0x4;
} A780_HDR;

void fn_800698E0(void *);

void fn_8006A780(A780_HDR *arg0) {
    A780_NODE *sp[19];
    A780_NODE *n;
    A780_OBJ *obj;
    A780_VT *vt;

    sp[0] = arg0->unk0x0 != 0 ? arg0->unk0x0->unk0x4 : 0;
    sp[2] = arg0->unk0x0;
    if (sp[0] != arg0->unk0x0) {
        do {
            fn_800698E0(sp[0]->unk0x0);
            obj = sp[0]->unk0x0;
            if (obj != 0) {
                vt = obj->unk0x1B8;
                vt->fn0C((char *)obj + vt->off8, 3);
            }
            sp[0] = sp[0]->unk0x4;
            sp[2] = arg0->unk0x0;
        } while (sp[0] != sp[2]);
    }
    sp[6] = arg0->unk0x0 != 0 ? arg0->unk0x0->unk0x4 : 0;
    sp[8] = arg0->unk0x0;
    if (sp[6] != arg0->unk0x0) {
        do {
            n = sp[6];
            sp[14] = n;
            sp[6] = n->unk0x4;
            sp[12] = n;
            sp[18] = n;
            sp[12] = n->unk0x4;
            sp[16] = n;
            if (n != arg0->unk0x0) {
                n->unk0x8->unk0x4 = n->unk0x4;
                n->unk0x4->unk0x8 = n->unk0x8;
                Mem_Free(n);
                arg0->unk0x4 = arg0->unk0x4 - 1;
            }
            sp[10] = sp[12];
        } while (sp[6] != sp[8]);
    }
    sp[4] = sp[6];
}
