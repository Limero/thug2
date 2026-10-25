// PARKED 2026-09-27 (ag19): best 80.4% (was 80.4%). Residual = ONE root
// cause, 10 words: the two loop-carried callee-saved webs are register-
// SWAPPED — want p (vcall base) = r30 / countdown i = r31, got p = r31 /
// i = r30 (words 0x8002FA1C li, FA24 addi, FA30 mr, FA34 lwz, FA38 addi,
// FA48 add, FA50 lwz, FA68 li, FA70 addi, FA74 addic.). Every other word
// is identical and all branch targets match (verified with a relocation-
// resolving want|got diff — the masked sweep cannot see branch targets).
// ALSO FIXED this round: the in-loop next-load read offset 0x10 (a pad
// field) instead of 0xC — word FA50 now differs only in the register.
// Tried (17 distinct attempts): decl order (i before p); if/else vs ternary
// NULL-coalesce at both sites and both polarities; struct-pointer arithmetic
// spelling; p/q two-variable split; for/while/do-while loop forms; `i > 0`
// condition; hdr elimination via direct arg0+0x1C; vt via char* cast;
// `[0].next` spelling; adj temp; separate `cur` loop-node var; this-add
// temp; full 24-flag sweep on the fixed body (no strict improvement); 3
// register-pin configs as last resort (DISCLOSED): p->r30 s32-alias (the
// walk's elem cascades into r30), p->r30 + elem->r9 (registers DO match,
// but the pre-loop coalesce block restructures and the frame grows
// 0x10 -> 0x18), i->r31 (allocation collapses to 42.9%). No real source
// shape reaches the swap; the pin escape is a sculpture, not a shape.
// Family: doc-15 callee-saved role-rotation (r30/r31 swap), cf. §6y-126 /
// doc-32 walker-role-rotation. Do not re-grind flags or decl orders.
// WIP DRAFT (non-matching) — C body reconstructed by hand from the DOL
// family=m2c range=0x8002F9C4-0x8002FA90 size=204B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// MEASURED 2026-09-26: NEAR 80.4% (41/51 words), size-exact 204B.
// Improved from the previous 64.7% (33/51) body.  STILL PARKED — the only
// residual is a two-register role rotation, see "REMAINING BLOCKER" below.
//
// WHAT THIS FUNCTION IS (decode, verified against the raw words):
//   count a sentinel-terminated singly-linked list, then virtual-call a
//   release/destructor on every node in order.  arg0+0x18 is the list head
//   cell; its +0x0C field is the first node.  A node carries
//     +0x04  s32    terminator flag (-1 == end of list)
//     +0x0C  node*  next link
//     +0x14  vtbl*  vtable of the base sub-object
//   and the vtable itself is the standard THUG shape: +0x18 s16 this-adjust,
//   +0x1C the method (so the call is `fn(node + s16(vtbl+0x18))`).
//   The two `addi r30,±4` are a BASE-SUB-OBJECT adjustment: the vcall base
//   pointer is `node - 4` and the `this` handed to the method is that base
//   plus the vtable's s16, so the two offsets must be written as BYTE
//   arithmetic through two distinct struct views (below) or GCC folds them.
//
// RE-SOLVED THIS ROUND (were the 18 word-diffs of the old body):
//   * the walker is ONE web in the retail code (r9 for all three list
//     segments: the counting walk, the post-walk re-read, and the per-
//     iteration next load).  m2c had split it into `var_r9` / `var_r9_2` /
//     `var_r9_3`, which let ngccc colour the post-walk copy r3 and the
//     in-loop copy r11.  Using one variable for all three fixes 8 diffs.
//   * the vcall base is a separate loop-carried web (r30), updated IN PLACE
//     at the loop head (`p = p + 4`) and recomputed at the latch; the
//     `this` value is that same web, so only one callee-saved register is
//     needed and the node pointer can stay in the scratch r9.  Giving the
//     "this" value its own C variable (as m2c did) makes TWO webs live
//     across the blrl and pushes the walker into r31 — 51%.
//   * the vtable field is the SHARED `Unk_4E705049` (unk0x18 s16, unk0x1C
//     s32) rather than m2c's `CStruct` pair, which is what emits the
//     `lha r3,0x18(r9)` + `lwz r0,0x1c(r9)` this-adjust/method pair.
//   * the element and the vcall base are two 4-byte-offset views of one
//     object (F9C4_Node at node, F9C4_VObj at node-4).  Modelling them as
//     ONE struct makes GCC fold the -4/+4 pair away, which the retail code
//     does not do.
//
// REMAINING BLOCKER (10 words, all one cause):
//   r30 and r31 are SWAPPED between the two loop-carried values:
//     want  p (vcall base, live across the blrl) = r30, countdown i = r31
//     got   p = r31, countdown i = r30
//   Every other word is identical, and after applying the object's
//   R_PPC_REL14/REL24 relocations all nine branch targets match the retail
//   CFG exactly (verified with a relocation-resolving want|got diff — the
//   masked sweep cannot see branch targets, so this was checked separately).
//   ngccc insists on the opposite assignment.  Exhausted without a win:
//     3 loop forms (for / do-while / while, plus `i = i - 1`, `--i`,
//     `i--` in the increment); ternary vs if/else for the NULL coalesce,
//     at the pre-loop site and inside the loop, independently; 6 local
//     declaration orders; `p` typed as struct pointer, `char *` and `s32`
//     with byte casts; counter `s32`/`u32`; hoisting `i = count` above the
//     `count > 0` guard; a named `tail` temp; the full 24-flag sweep
//     (tools/flag_sweep.py: no strict improvement); and 6 hard-register pin
//     configurations (pin p->r30, i->r31, count->r11, elem->r9, both, and
//     pin-a-copy forms) — every pin collapses the allocation (41-55%) or
//     pulls the walker into the pinned register.  This is the AGENTS.md
//     doc-15 / §6y-126 callee-saved role-rotation class; do not re-grind the
//     pins or the flag space for this draft.
#include "types.h"
#include "structs.h"

typedef struct F9C4_Node F9C4_Node;
typedef struct F9C4_Hdr F9C4_Hdr;
typedef struct F9C4_VObj F9C4_VObj;

/* list element, as reached through the walker pointer */
struct F9C4_Node {
    char pad0x0[4];
    s32 flag;               /* +0x04 : -1 terminates the list */
    char pad0x8[4];
    F9C4_Node *next;        /* +0x0C */
    char pad0x10[8];
};

/* the list head cell lives at arg0 + 0x18 */
struct F9C4_Hdr {
    char pad0x0[0x0C];
    F9C4_Node *head;        /* +0x0C */
};

/* vcall view: this base is 4 bytes BELOW the walker, so the vtable pointer
   is at +0x18 (= F9C4_Node + 0x14) and the next link at +0x10. */
struct F9C4_VObj {
    char pad0x0[0x10];
    F9C4_Node *next;        /* +0x10 */
    char pad0x14[4];
    Unk_4E705049 *vtbl;     /* +0x18 */
};

void fn_8002F9C4(void *arg0) {
    F9C4_Hdr *hdr;
    F9C4_Node *elem;
    F9C4_VObj *p;
    Unk_4E705049 *vt;
    s32 count;
    s32 i;

    hdr = (F9C4_Hdr *)((char *)arg0 + 0x18);
    count = 0;
    elem = hdr->head;
    goto test;
advance:
    elem = elem->next;
    count = count + 1;
test:
    if (elem->flag == -1) {
        elem = NULL;
    }
    if (elem != NULL) {
        goto advance;
    }

    /* re-read the head: the walk above left the walker NULL */
    elem = hdr->head;
    if (elem->flag == -1) {
        elem = NULL;
    }
    p = (elem != NULL) ? (F9C4_VObj *)((char *)elem - 4) : NULL;
    if (count > 0) {
        for (i = count; i != 0; i--) {
            vt = p->vtbl;
            p = (F9C4_VObj *)((char *)p + 4);
            ((void (*)(void *))vt->unk0x1C)((char *)p + vt->unk0x18);
            elem = ((F9C4_Node *)p)->next;
            if (elem->flag == -1) {
                elem = NULL;
            }
            p = (elem != NULL) ? (F9C4_VObj *)((char *)elem - 4) : NULL;
        }
    }
}
