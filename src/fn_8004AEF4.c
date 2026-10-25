// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8004AEF4-0x8004B03C (328B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

void CObject_AddRefLink(void *, void *);
void CObject_RemoveRefLink(void *, void *);
void fn_8004C110(void *, void *, s32, s32);
void fn_80041564(s32 *, s32 **, s32);

/* The stack ref-link node, from the promoted callees' own type
   (`Unk_9994C3F5` has prev at +4 and next at +8).  Typed locally: the
   corpus-merged class types those members `s32` and the shared header is not
   to be edited for one function (M6.89d-note in AGENTS.md). */
typedef struct Ref_4AEF4 {
    void *saved;   /* +0: the node this function must unref on the way out */
    void *prev;    /* +4: CObject_AddRefLink / RemoveRefLink link field */
    void *next;    /* +8: ditto */
} Ref_4AEF4;

/* The list node: self->unk0x4C is the ref-link head (a node of the same type),
   self->unk0x58 the next node in that chain.  Typed locally because the
   corpus-wide Unk_C7387A53 class votes unk0x4C/unk0x58 as s32 (see the
   M6.89d-note in AGENTS.md: a merged class member type can be wrong for the
   function you are matching, and this function's own file is the right place
   for the true layout). */
typedef struct Obj_4AEF4 {
    char pad0x00[0x4C];
    struct Obj_4AEF4 *link;   /* +0x4C: ref-link head (AddRefLink writes here) */
    char pad0x50[0x08];
    struct Obj_4AEF4 *next;   /* +0x58: chain link */
} Obj_4AEF4;

void fn_8004AEF4(void *arg0, s32 **arg1, void **arg2, s32 arg3) {
    Obj_4AEF4 *self;
    Obj_4AEF4 *node;
    Obj_4AEF4 *old;
    Obj_4AEF4 *cur;
    char *linkp;
    Ref_4AEF4 ref;
    Ref_4AEF4 *rp;
    Ref_4AEF4 *rq;
    s32 t;
    register s32 a3 __asm__("r25");

    a3 = arg3;
    rp = &ref;
    rp->prev = 0;
    rp->next = 0;
    rq = rp;
    __asm__("" : "+r"(rp));
    t = *(s32 *)((char *)(*(s32 **)arg2) + 0x58);
    ref.saved = (void *)t;
    if (t != 0) {
        CObject_AddRefLink((void *)t, rq);
    }
    node = *(Obj_4AEF4 **)arg1;
    if (node != NULL) {
        self = (Obj_4AEF4 *)arg0;
        linkp = (char *)&self->link;
        old = self->link;
        if ((old == (Obj_4AEF4 *)(*(s32 **)arg2)) || (old == NULL)) {
            if (old != NULL) {
                CObject_RemoveRefLink(old, linkp);
                self->link = NULL;
            }
            self->link = node;
            CObject_AddRefLink(node, linkp);
            if (self->link->next != NULL) {
                do {
                    node = self->link;
                    if (node != NULL) {
                        CObject_RemoveRefLink(node, linkp);
                        self->link = NULL;
                    }
                    cur = node->next;
                    self->link = cur;
                    if (cur != NULL) {
                        CObject_AddRefLink(cur, linkp);
                    }
                } while (self->link->next != NULL);
            }
        }
    }
    fn_8004C110(arg0, arg2, 0, 0);
    fn_80041564((s32 *) *(s32 **)arg2, arg1, a3);
    t = (s32)ref.saved;
    if (t != 0) {
        CObject_RemoveRefLink((void *)t, rq);
        ref.saved = 0;
    }
}
