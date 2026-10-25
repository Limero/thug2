// range 0x8000A1FC-0x8000A288 (0x8C). Byte-identical.
// Identification: container constructor in the node family (between the
// A13C/A37C constructors). Initializes two embedded node objects at self+0xc
// and self+0x24 that share the vtable lbl_8028FFA0 (.rodata2): each node gets
// id=-1 at +4, zero at +8, is wired as a doubly-linked self-loop (+0xc/+0x10
// point to itself), vtable at +0x14. Zeroes self+0x44/0x48, calls
// fn_8000A37C(self) to attach its child, then copies the child (self+0x3c)
// into self+0x40 and clears self+0x44/0x48. Returns self.
//
// Matching key (recipe 244): the per-node store orders are NOT the same for
// the two nodes — n1 wants source [u4, u8, next, prev, vt], n2 wants
// [u4, vt, next, prev, u8] — and the tail three stores want source
// [0x40, 0x44, 0x48] (rotate-right emit gives want's [0x48, 0x40, 0x44]).
// Writing both nodes' stores interleaved by field (n1->X; n2->X;) tops out at
// 26/35; writing all of n1's stores then all of n2's and permuting each
// 5-store block separately is what hits 35/35.
#include "types.h"
#include "structs.h"
typedef struct {
    s32 u0;
    s32 u4;
    s32 u8;
    void *next;
    void *prev;
    void *vt;
} A1Node;
extern char lbl_8028FFA0[];
extern void fn_8000A37C(Unk_C7387A53 *);
void *fn_8000A1FC(Unk_C8FEE62D *self) {
    A1Node *n1 = (A1Node *)((char *)self + 0xc);
    A1Node *n2 = (A1Node *)((char *)self + 0x24);
    self->unk0x4 = 0;
    n1->u4 = -1;
    n1->u8 = 0;
    n1->next = n1;
    n1->prev = n1;
    n1->vt = lbl_8028FFA0;
    n2->u4 = -1;
    n2->vt = lbl_8028FFA0;
    n2->next = n2;
    n2->prev = n2;
    n2->u8 = 0;
    self->unk0x44 = 0;
    self->unk0x48 = 0;
    fn_8000A37C(self);
    *((void * *)&self->unk0x40) = *((void * *)&self->unk0x3C);
    self->unk0x44 = 0;
    self->unk0x48 = 0;
    return self;
}