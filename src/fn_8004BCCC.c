// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8004BCCC-0x8004BEB0 (484B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

void CScreenElement_SetChildLockState(void *, s32);
void CObject_AddRefLink(void *, void *);
void CObject_RemoveRefLink(void *, void *);
void fn_8012F5E4(void *, void *);
void fn_8004AEF4(void *, s32 **, void **, s32);

/* The stack ref-link node, exactly as the promoted sibling src/fn_8004AEF4.c
   spells it: CObject_AddRefLink / RemoveRefLink link at +4 / +8. */
typedef struct Ref_BCCC { void *saved; void *prev; void *next; } Ref_BCCC;

/* The object the recursion walks: +0x64 is the field the first AddRefLink
   takes, +0x70 the one the loop re-reads off the new head, +0x08 the vtable
   used by the trailing vcall. */
typedef struct Node_BCCC {
    char pad00[0x8];
    void *vt;      /* +0x08 */
    char pad0C[0x58];
    void *unk64;   /* +0x64 */
    char pad68[0x8];
    void *unk70;   /* +0x70 */
} Node_BCCC;

typedef struct Vt1_BCCC {
    char pad00[0x18];
    s16 off;                   /* +0x18 : lha */
    char pad1A[2];
    void *(*fn)(void *, void *); /* +0x1C */
} Vt1_BCCC;

typedef struct Vt2_BCCC {
    char pad00[0x08];
    s16 off;                   /* +0x08 : lha */
    char pad0A[2];
    void *(*fn)(void *, s32);  /* +0x0C */
} Vt2_BCCC;

typedef struct Self_BCCC {
    char pad00[0x2C];
    Vt1_BCCC *vt;              /* +0x2C */
} Self_BCCC;

void fn_8004BCCC(void *arg0, s32 arg1, void **arg2, s32 arg3) {
    Ref_BCCC sp8;
    Ref_BCCC sp18;
    register s32 p8 __asm__("r27");
    Ref_BCCC *b8;
    void *t0;
    Ref_BCCC *p18;
    Ref_BCCC *q18;
    Node_BCCC *t2;
    Vt1_BCCC *vt;
    Vt2_BCCC *vt2;
    void *t1;

    CScreenElement_SetChildLockState(*arg2, 0);
    t0 = ((Node_BCCC *)*arg2)->unk64;
    b8 = &sp8;
    b8->prev = 0;
    b8->next = 0;
    __asm__("" : "+r"(b8));
    p8 = (s32)b8;
    sp8.saved = t0;
    if (t0 != 0) {
        CObject_AddRefLink(t0, (Ref_BCCC *)p8);
    }
    if (sp8.saved != 0) {
        p18 = &sp18;
        do {
            t1 = ((Node_BCCC *)sp8.saved)->unk70;
            p18->prev = 0;
            p18->next = 0;
            sp18.saved = t1;
            if (sp18.saved != 0) {
                CObject_AddRefLink(sp18.saved, p18);
            }
            fn_8004BCCC(arg0, 0, (Ref_BCCC *)p8, arg3);
            if (sp8.saved != 0) {
                CObject_RemoveRefLink(sp8.saved, (Ref_BCCC *)p8);
                sp8.saved = 0;
            }
            sp8.saved = sp18.saved;
            if (sp8.saved != 0) {
                CObject_AddRefLink(sp8.saved, (Ref_BCCC *)p8);
            }
            if (sp18.saved != 0) {
                CObject_RemoveRefLink(sp18.saved, p18);
                sp18.saved = 0;
            }
        } while (sp8.saved != 0);
    }
    if (arg1 == 0) {
        if ((arg3 != 0) && (*arg2 != 0)) {
            fn_8012F5E4(arg3, *arg2);
        }
        q18 = &sp18;
        q18->prev = 0;
        q18->next = 0;
        sp18.saved = 0;
        fn_8004AEF4(arg0, q18, arg2, 1);
        if (sp18.saved != 0) {
            CObject_RemoveRefLink(sp18.saved, q18);
            sp18.saved = 0;
        }
        vt = ((Self_BCCC *)arg0)->vt;
        vt->fn((char *)arg0 + vt->off, *arg2);
        t2 = (Node_BCCC *)*arg2;
        if (t2 != 0) {
            vt2 = (Vt2_BCCC *)t2->vt;
            vt2->fn((char *)t2 + vt2->off, 3);
        }
    }
    if (sp8.saved != 0) {
        CObject_RemoveRefLink(sp8.saved, (Ref_BCCC *)p8);
        sp8.saved = 0;
    }
}
