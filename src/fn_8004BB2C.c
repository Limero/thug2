// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8004BB2C-0x8004BCC0 (404B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

// 16-byte CObject link node: list head lives at obj+4.
typedef struct Unk_Link {
    void *unk0x0; /* payload (the linked object) — written by the caller */
    void *unk0x4; /* next link */
    void *unk0x8; /* prev link */
    void *unk0xC; /* padding — never touched by Add/RemoveRefLink */
} Unk_Link;

// 16-byte "pending candidate" node walked via arg0->unk0x10.
typedef struct Unk_Node {
    void *unk0x0;
    void *unk0x4;  /* candidate object; (void *)-1 == end-of-chain */
    void *unk0x8;
    struct Unk_Node *unk0xC; /* next node */
} Unk_Node;

typedef struct Unk_Self {
    char pad0x0[0x10];
    Unk_Node *unk0x10; /* head of the pending-candidate chain */
    char pad0x14[0x38];
    void *unk0x4C; /* currently held object */
} Unk_Self;

void CObject_AddRefLink(void *obj, Unk_Link *link);
void CObject_RemoveRefLink(void *obj, Unk_Link *link);
void fn_800A33E4(Unk_Self *self, void *other);

void fn_8004BB2C(Unk_Self *arg0, void *arg1) {
    s32 z1 = 0;
    Unk_Link sp8;  /* the temporary link holding arg1 — r1+0x08 */
    Unk_Link sp18; /* the per-candidate scratch link — r1+0x18 */
    Unk_Link *pA;
    Unk_Link *pB;
    void **pCur;
    Unk_Node *walker;
    /* Hard-register VARIABLES — these emit ZERO instructions; they only tell
       cc1 which register a value lives in (see levers 2 and 5 in the header). */
    register s32 head9 __asm__("r9");
    register s32 link24 __asm__("r24");
    void *nxt;
    void *o;
    void *o2;

    pA = &sp8;
    pA->unk0x4 = z1;
    pA->unk0x8 = z1;
    sp8.unk0x0 = arg1;
    link24 = (s32)&sp8;
    if (arg1 != 0) {
        CObject_AddRefLink(arg1, (Unk_Link *)link24);
    }

    if (sp8.unk0x0 != 0) {
        /* The second clear and the whole walk are INSIDE the equality test:
           retail's `bne` at 0x8004BB88 leaves the block entirely. */
        pCur = &arg0->unk0x4C;
        if (arg0->unk0x4C == sp8.unk0x0) {
            /* If we are already holding arg1, drop it, then clear unconditionally:
               the release idiom writes the NULL twice and retail keeps both. */
            if (sp8.unk0x0 != 0) {
                CObject_RemoveRefLink(arg0->unk0x4C, pCur);
                arg0->unk0x4C = z1;
            }
            arg0->unk0x4C = z1;

            /* Walk the pending chain for the first candidate that is unused and
               is not arg1 itself.  `head9` is the scratch the next pointer is
               born in; `walker` is the loop variable's home. */
            head9 = (s32)arg0->unk0x10;
            if (*(void **)((char *)head9 + 4) == (void *)-1) {
                head9 = 0;
            }
            walker = (Unk_Node *)head9;
            if (walker != 0) {
                do {
                    pB = &sp18;
                    o = walker->unk0x4;
                    pB->unk0x4 = 0;
                    pB->unk0x8 = 0;
                    sp18.unk0x0 = o;
                    if (o != 0) {
                        CObject_AddRefLink(o, pB);
                    }
                    nxt = *(void **)((char *)sp18.unk0x0 + 0x58);
                    if (nxt == 0 && sp18.unk0x0 != sp8.unk0x0) {
                        if (arg0->unk0x4C != 0) {
                            CObject_RemoveRefLink(arg0->unk0x4C, pCur);
                            arg0->unk0x4C = 0;
                        }
                        arg0->unk0x4C = sp18.unk0x0;
                        if (arg0->unk0x4C != 0) {
                            CObject_AddRefLink(arg0->unk0x4C, pCur);
                        }
                        if (sp18.unk0x0 != 0) {
                            CObject_RemoveRefLink(sp18.unk0x0, &sp18);
                            sp18.unk0x0 = 0;
                        }
                        break;
                    }
                    head9 = (s32)walker->unk0xC;
                    o2 = *(void **)((char *)head9 + 4);
                    walker = (Unk_Node *)head9;
                    if (o2 == (void *)-1) {
                        walker = 0;
                    }
                    if (sp18.unk0x0 != 0) {
                        CObject_RemoveRefLink(sp18.unk0x0, &sp18);
                        sp18.unk0x0 = 0;
                    }
                } while (walker != 0);
            }
        }
    }

    fn_800A33E4(arg0, arg1);
    if (sp8.unk0x0 != 0) {
        CObject_RemoveRefLink(sp8.unk0x0, (Unk_Link *)link24);
        sp8.unk0x0 = 0;
    }
}
