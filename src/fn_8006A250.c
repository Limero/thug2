// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8006A250-0x8006A3E0 (400B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
#include "mem.h"

extern char lbl_80294A10[];

typedef struct A250_NODE {
    void *unk0x0;
    struct A250_NODE *unk0x4;
    struct A250_NODE *unk0x8;
} A250_NODE;

typedef struct A250_HDR {
    A250_NODE *unk0x0;
    s32 unk0x4;
    char pad0x8[0x10];
    void *unk0x18;
} A250_HDR;

void fn_8006A250(A250_HDR *arg0, s32 arg1) {
    A250_NODE *sp[16];
    A250_NODE *head1;
    A250_NODE *node1;
    A250_NODE *n1;
    A250_NODE *head2;
    A250_NODE *node2;
    A250_NODE *n2;

    head1 = arg0->unk0x0;
    arg0->unk0x18 = lbl_80294A10;
    node1 = head1 != 0 ? head1->unk0x4 : 0;
    sp[2] = node1;
    sp[4] = head1;
    if (node1 != head1) {
        do {
            n1 = sp[2];
            sp[10] = n1;
            sp[2] = n1->unk0x4;
            sp[8] = n1;
            sp[14] = n1;
            sp[8] = n1->unk0x4;
            sp[12] = n1;
            if (n1 != arg0->unk0x0) {
                n1->unk0x8->unk0x4 = n1->unk0x4;
                n1->unk0x4->unk0x8 = n1->unk0x8;
                Mem_Free(n1);
                arg0->unk0x4 = arg0->unk0x4 - 1;
            }
            sp[6] = sp[8];
        } while (sp[2] != sp[4]);
    }

    head2 = arg0->unk0x0;
    node2 = NULL;
    sp[0] = sp[2];
    if (head2 != 0) node2 = head2->unk0x4;
    sp[2] = node2;
    sp[4] = head2;
    if (node2 != head2) {
        do {
            n2 = sp[2];
            sp[10] = n2;
            sp[2] = n2->unk0x4;
            sp[8] = n2;
            sp[14] = n2;
            sp[8] = n2->unk0x4;
            sp[12] = n2;
            if (n2 != arg0->unk0x0) {
                n2->unk0x8->unk0x4 = n2->unk0x4;
                n2->unk0x4->unk0x8 = n2->unk0x8;
                Mem_Free(n2);
                arg0->unk0x4 = arg0->unk0x4 - 1;
            }
            sp[6] = sp[8];
        } while (sp[2] != sp[4]);
    }

    sp[0] = sp[2];
    Mem_Free(arg0->unk0x0);
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
