// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8004E734-0x8004E900 (460B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

// The child object the loop inspects: link fields at +4/+8 (see
// CObject_AddRefLink / CObject_RemoveRefLink), script field read at +0x18.
typedef struct No4E734Node {
    char pad0x0[0x18];
    s32 unk0x18;
} No4E734Node;

// arg0: cursor at +0x190, resolved child at +0x194, wrap/clamp flag at
// +0x1BC (an s32 word, NOT a float — want loads it with lwz), scratch index
// at +0x1C0. Matches the layout fn_8004EA60 (src/fn_8004EA60.c) expects.
typedef struct No4E734Self {
    char pad0x0[0x190];
    s32 unk0x190;
    s32 unk0x194;
    char pad0x198[0x24];
    s32 unk0x1BC;
    s32 unk0x1C0;
} No4E734Self;

s32 fn_8003FFC4(No4E734Self *);              // list length  (src/fn_8003FFC4.c)
s32 fn_8003FF64(No4E734Self *, s32);         // nth list entry (src/fn_8003FF64.c)
s32 fn_80042110(void *);                     // hidden-object probe
s32 fn_8009E440(void *, s32);                // ContainsFlag(obj, tag)
s32 fn_8009E3D0(void *, s32, s32 *);         // GetInteger(obj, tag, out)
void fn_8004EA60(No4E734Self *);             // re-publish the tags (src/fn_8004EA60.c)
void CObject_AddRefLink(CStruct *, Unk_9994C3F5 *);
void CObject_RemoveRefLink(CStruct *, CStruct *);

void fn_8004E734(No4E734Self *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 n;
    No4E734Node *sp8;      /* the link cell: {node, prev, next} on the stack */
    No4E734Node *temp;
    s32 padA, padB;

    n = 2 * fn_8003FFC4(arg0);
    if (arg0->unk0x190 < 0) {
        arg0->unk0x190 = 0;
    }
    if (n == 0) {
        goto notfound;
    }
    do {
        /* arg2 != 0 (first pass only) skips the cursor clamp. */
        if (arg2 == 0) {
            arg0->unk0x190 = arg0->unk0x190 + arg1;
            if (arg0->unk0x190 >= fn_8003FFC4(arg0)) {
                if (arg0->unk0x1BC != 0) {
                    arg0->unk0x190 = arg2;      /* pin to 0 */
                } else {
                    arg1 = -arg1;               /* walk back, clamp to last */
                    arg0->unk0x190 = fn_8003FFC4(arg0) - 1;
                }
            } else if (arg0->unk0x190 < 0) {
                if (arg0->unk0x1BC != 0) {
                    arg0->unk0x190 = fn_8003FFC4(arg0) - 1;
                } else {
                    arg0->unk0x190 = arg2;
                    arg1 = -arg1;
                }
            }
        }
        arg2 = 0;
        temp = (No4E734Node *)fn_8003FF64(arg0, arg0->unk0x190);
        ((Unk_59AB5482 *)&sp8)->unk0x4 = NULL;
        ((Unk_59AB5482 *)&sp8)->unk0x8 = NULL;
        sp8 = temp;
        if (sp8 != NULL) {
            CObject_AddRefLink((CStruct *)sp8, &sp8);
        }
        arg0->unk0x194 = sp8->unk0x18;
        if (arg3 != 0) {
            arg0->unk0x1C0 = -1;
            fn_8009E3D0(sp8, QB_TAG_GRID_X, &arg0->unk0x1C0);
        }
        /* Not focusable and not hidden -> stop, keep what we found. */
        if ((fn_8009E440(sp8, QB_TAG_NOT_FOCUSABLE) == 0) &&
            (fn_80042110(sp8) == 0)) {
            if (sp8 != NULL) {
                CObject_RemoveRefLink((CStruct *)sp8, &sp8);
                sp8 = NULL;
            }
            goto done;
        }
        n--;
        if (sp8 != NULL) {
            CObject_RemoveRefLink((CStruct *)sp8, &sp8);
            sp8 = NULL;
        }
    } while (n != 0);
done:
    /* Runs out of candidates -> reset the cursor, publish nothing. */
    if (n == 0) {
        goto notfound;
    }
    fn_8004EA60(arg0);
    return;
notfound:
    arg0->unk0x190 = -1;
    arg0->unk0x194 = 0;
    /* Two address-taken-but-never-written words. The CR-save slot must not be
       shared with the write-only third cell word: forcing these slots keeps the
       local area at 16 bytes, which puts the CR save at 0x18 and the GPR save
       block at 0x1C (frame 0x38) instead of sharing 0x10 (frame 0x30). */
    __asm__("" : : "m"(padA), "m"(padB));
}
