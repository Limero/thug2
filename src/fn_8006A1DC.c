// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8006A1DC-0x8006A250 (116B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

/* 12-byte circular list node owned by the object at +0.  fn_8006A250 (the
   method table's slot-3 entry) unlinks it through +4 (next) / +8 (prev). */
typedef struct ListNode {
    void *unk0x0;
    struct ListNode *next;
    struct ListNode *prev;
} ListNode_t;

/* Constructor target: node, s32 state, 4-float vector, method table. */
typedef struct Obj {
    ListNode_t *node;
    s32 state;
    f32 v0;
    f32 v1;
    f32 v2;
    f32 v3;
    void (*vtbl[10])(void);
} Obj_t;

extern char lbl_80294A10[];
extern f32 lbl_80294A0C[];
void *Mem_Alloc2(s32);

void *fn_8006A1DC(Obj_t *self) {
    ListNode_t *node;
    register f32 *vp __asm__("r10");
    register f32 *pg __asm__("r11");
    register s32 rv __asm__("r3");
    f32 c;

    self->vtbl[0] = (void (*)(void))lbl_80294A10;
    self->state = 0;
    node = (ListNode_t *)Mem_Alloc2(0xC);
    pg = &lbl_80294A0C;
    vp = &self->v0;
    self->node = node;
    c = pg[0];
    __asm__ __volatile__("mr %0,%1" : "=r"(rv) : "r"(self));
    node->prev = node;
    node->next = node;
    self->v0 = c;
    vp[1] = c;
    vp[2] = c;
    vp[3] = c;
    return (Obj_t *)rv;
}
