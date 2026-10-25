// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80055B9C-0x80055CB0 (276B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct {
    char pad0x0[8];
    s16 off;
    char pad0xA[2];
    s32 (*fn)(void *, s32);
} VT_t;
typedef struct {
    char pad0x0[0x14];
    VT_t *vt;
} NodeA_t;
typedef struct {
    char pad0x0[0x18];
    VT_t *vt;
} NodeB_t;
typedef struct {
    char pad0x0[0xD0];
    void *d0;
    char pad0xD4[0xB0];
    char pad0x184[0x60];
    s32 f1e4;
    char pad0x1E8[0x94];
    NodeA_t *n27c;
    NodeA_t *n280;
    s32 unk284;
} Obj_t;

void fn_8005D734(s32);
void fn_8005840C(NodeB_t *, s32);
void fn_800577A0(void *);
void *fn_800577B4(void *, s32);
void fn_8005790C(void *, s32);
void fn_8005656C(void *);
void Mem_Free(void *);
extern char lbl_802932A8[];

void fn_80055B9C(Obj_t *arg0, s32 arg1) {
    NodeB_t *node;
    NodeA_t *n;
    VT_t *vt;

    arg0->unk284 = (s32)lbl_802932A8;
    if (arg0->d0 != NULL) {
        fn_800577A0(arg0->d0);
        goto loop_test;
loop_body:
        fn_8005840C(node, 0x40);
        vt = node->vt;
        vt->fn((char *)node + vt->off, 3);
loop_test:
        node = (NodeB_t *)fn_800577B4(arg0->d0, 0);
        if (node != NULL) {
            goto loop_body;
        }
        if (arg0->d0 != NULL) {
            fn_8005790C(arg0->d0, 3);
        }
    }
    fn_8005656C(arg0);
    n = arg0->n27c;
    if (n != NULL) {
        vt = n->vt;
        vt->fn((char *)n + vt->off, 3);
    }
    n = arg0->n280;
    if (n != NULL) {
        vt = n->vt;
        vt->fn((char *)n + vt->off, 3);
    }
    if (arg0->f1e4 != 0) {
        fn_8005D734(arg0->f1e4);
    }
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
