// WIP DRAFT (non-matching) — hand-reconstructed from the DOL (2026-09-26).
// 2026-10-08: reload_pin_sweep WIN — pin `tmp` -> `register ... tmp __asm__("r0")` => official 56.5% (sweep base 8.54%). ONE pin only; pins are not additive.
//
// PARKED 2026-10-03: DIFF 8.24% (baseline DIFF 8.24% — unchanged; the
// pct did not move because the scorer is strictly positional and this body
// is still 3 words short, so every diff is still a shifted diff).
// reproduce: LEAF_TMPDIR=<scratch> tools/venv/bin/python \
//               tools/test_wip_drafts.py --addr 0x8000B934
// Body is now 328B vs want 340B (82 vs 85 instructions).  Structurally the
// body is RIGHT: frame 0x30, `stmw r27,0x1c`, LR@0x34, both vcall shapes
// (lha/lwz/add/mtlr/blrl), the unlink tail, the `or.`-fused loop latch and
// the CR-liveness across blrl all match.  Exactly THREE words are missing
// and five word-groups differ; nothing is semantically unknown any more.
//
// === WHAT IS STILL MISSING (3 words, 0xB950-0xB970 + 0xB990 + 0xB9A4) ===
//
// (1) REGISTER-HOME SWAP (arg0 <-> &sp).  want: r27=arg1 r28=&sp r29=arg0
//     r30=node r31=nxt, loop var in the VOLATILE r10.  ngccc: r27=arg1
//     r28=arg0 r29=&sp r30=node r31=nxt, loop var in r11.  Because the swap
//     is a single transposition the whole rest of the body shifts with it.
//     *** THE PIN IS THE ONLY LEVER THAT HAS EVER MOVED THIS. ***
//     One pin, `register Lst *p __asm__("r28") = &sp;`, reproduces the
//     ENTIRE callee-saved map (r27=arg1 r28=&sp r29=arg0 r30=node r31=nxt,
//     loop var back in a volatile reg) and takes 8.24% -> 10.59% with the
//     frame unchanged (still 0x30 / stmw r27).  It was measured and then
//     REMOVED again, because with the pin in place the block is still NOT
//     byte-identical (4 further word-groups differ, below) and the brief
//     only sanctions a pin once the rest is exact.  One-line repro:
//       sed 's/    Lst \*p = &sp;/    register Lst *p __asm__("r28") = \&sp;/'
//       on this file, then re-run the command above.
//     Still unknown: why retail's allocator puts the PARM arg0 in r29 and
//     the local &sp in r28 while ngccc does the reverse.  35 decl/stmt
//     permutations and 12 flags (previous agent) are all no-ops; the pin
//     says the ONLY thing that matters is which of the two gets the lower
//     colour, i.e. it is the parm-vs-local priority in global_alloc's
//     reg_alloc_order, not any source-order/birth effect.
//
// (2) PROLOGUE SCRATCH-WEB IDIOM (2 words) — issue 32 Flavor B.
//     The want builds the address in r11 from r1 plus 8, builds r8 from r29
//     plus 4, bumps r10 by 0x1d8, stores r10 to 8(r11), copies r11 into the
//     r28 home, and stores r8 to 4(r11); this build instead builds r30 from
//     r29 plus 4, builds r28 from r1 plus 8, bumps r11 by 0x1d8, stores r11
//     to 8(r28), emits a copy of r4 into r27, and stores r30 to 4(r28).
//     Two separate losses: (a) no `mr` of the &sp scratch into its home —
//     ngccc materialises `&sp` straight into the home register, so no copy
//     web exists (docs/parkings/32-walker-role-rotation.md Flavor B: this
//     shape is documented as un-reproducible); (b) `base` (arg0+4, r8) and
//     `node` (arg0+4, r30) are the SAME rtx in the source and get CSEd into
//     ONE addi, while retail keeps two (one short-lived r8 in the prologue,
//     one loop-invariant r30 sunk into the loop preheader at 0xB9A4).
//     Because both spellings are literally `addi rX,arg0,4`, no cast,
//     offset or type spelling can split them — this needs either a
//     rematerialisation policy difference or a `-fno-cse`-class flag.
//
// (3) PRE-LOOP TERNARY BLOCK LAYOUT (1 word) — the last structural diff.
//     The want compares r9 against 0, branches to the load arm on nonzero,
//     falls through a load-immediate of 0 into r9, branches to the merge,
//     and at the load arm loads r9 from 4(r9) before merging into a record-form
//     OR of r10 with itself; this build compares r9 against 0, loads
//     immediate 0 into r0, branches to the merge on equal, loads r0 from
//     4(r9) on the fall-through, and merges into a record-form OR of r11
//     with r0 twice.
//     GCC 2.95's `expand_cond` provably EMITS the want form first (branch
//     if nonzero to the load arm, constant arm inline, `b` to the merge
//     point); flow.c `reorder_basic_blocks` then swaps the two arms and
//     inverts the branch, deleting the `b`.  Retail kept the pre-swap form,
//     so retail's CFG must have been non-reorderable (a 2nd predecessor on
//     the load arm is the obvious candidate).  The IDENTICAL expression
//     inside the loop DOES come out as `beq` form in both, i.e. the loop's
//     ternary was reordered in retail too — only the pre-loop one was not.
//
// === RULED OUT THIS ROUND — do not repeat ===
//  * Splitting the pre-loop temp from the loop variable (the change that IS
//    in the body now: want's r9 = sentinel-normalised node, r10 = loop
//    variable, so they are two distinct source variables, and the old draft
//    had them as one).  Semantically correct, and it does move `tmp` into
//    r9 as retail has it, but it scores exactly the same 8.24% — GCC still
//    routes the ternary through an r0 temp.  The in-place `lwz r9,4(r9)`
//    that retail has is only expressible if the load's destination pseudo
//    is NOT the pseudo being tested, and no spelling of a self-assign
//    gives that (GCC always emits the load into a fresh reg because the
//    base and the destination would be the same pseudo).
//  * `nxt = tmp ? tmp->unk0x4 : NULL; while ((cur = nxt) != 0)` (i.e. folding
//    the copy into the while condition): 332B, still the `beq` arm order,
//    and it WORSENS the register map (arg0=r28, &sp=r30, node=r31).
//  * A dedicated destination variable used only by the pre-loop ternary:
//    identical 8.24%, GCC gives the dest its own reg (r11) instead of
//    coalescing it onto the dead temp.
//  * `Elem *np = &tmp->unk0x4; np = tmp ? np : NULL;` — DROPS the load
//    entirely (GCC folds the address into the select and never emits it),
//    i.e. semantically wrong; do not use.
//  * Two full `list_head` struct typedefs for the head vs the list
//    elements: byte-identical output (same offsets, same code).
//
// === NEXT IDEA (most promising) ===
// Attack (3) by giving the pre-loop ternary's load arm a second
// predecessor, e.g. by writing the pre-loop advance as the SAME block the
// loop latch would jump to (a `goto`-shaped `for(;;)` whose latch is the
// pre-loop `cmp/load`).  If `reorder_basic_blocks` then bails, the missing
// `b` appears and the body reaches 85 instructions, which finally makes
// masked_pct positional-honest for the first time.  Do (3) before touching
// (1) again — (1) is worth only 2.35 points on a shifted body, whereas (3)
// is worth the whole tail of the function.
//
// Original header notes (kept for the record):
// IDENTITY: fn_8000B934 is slot 3 of the 0x18-byte rodata2 vtable at
// lbl_802901F0, i.e. the teardown method of the composite CScript object
// built by the (matched) ctor src/fn_8000B838.c.  Sibling vtables in the
// same table: lbl_802901D8 (method 0x8000BDDC), lbl_802901F0 (0x8000B934 =
// this fn), lbl_80290208 (0x8000BE64), lbl_80290220 (0x8000BE10, the
// list-head dtor), lbl_80290238 (method 0x8000BEB8).
//
// OBJECT LAYOUT (derived from fn_8000B838 + this body):
//   arg0+0x04  doubly-linked list head node: +0x04 = next (-1 == end
//              sentinel), +0x0C = first, +0x10 = last, +0x14 = marker vt.
//   arg0+0x1C  0x24-byte child (fn_8000B838's Mem_NewZero(0x24) object),
//              class descriptor at +0x18.
//   arg0+0x20  this object's vtable pointer.
//   list element: class descriptor at +0xEC.
// The `next == -1 -> NULL` normalisation is the sentinel check: the head
// node's own +0x4 is -1, so an empty list walks to the head and stops.
//
// The `p->cur = (s32)base` store below is DEAD in C (overwritten two
// statements later by `p->cur = (s32)cur`) but MUST be kept: two loads sit
// between the two stores, so CSE cannot dead-store-eliminate it, and the
// retail bytes contain it.  Do not "clean it up".
//
// The `Lst *p = &sp` pointer local is load-bearing: it is what makes ngccc
// keep &sp in a callee-saved register (want r28) instead of folding the
// field accesses to r1 displacements.  It is what produces the 0x30 frame
// and the 5-register `stmw r27, 0x1c(r1)` (16-byte local + 4-byte local +
// 5 saved GPRs = 8+16+4+20 = 0x30, save area at r1+0x1c, LR at r1+0x34).
//
// CURRENT SCORE: 8.24% masked (68 of 82 words differ) — was 5.88% on the
// m2c draft, whose frame was 0x60 / `stmw r26` (wrong local type) and whose
// vtable offsets were s32 (`lwz` instead of want's `lha`).  Frame, save
// area, epilogue, both vcall shapes and the whole unlink tail now match.
// The old draft's `// FLAG: -fno-rerun-cse-after-loop` was REMOVED: it was
// stale (worth +1.2% on the m2c body, -2.3% on this one), and promote_wip
// re-verifies under whatever flags a header still carries.
//
// REMAINING BLOCKERS (all allocator/scheduler, no source form found):
//  1. REGISTER HOME SWAP: want homes arg0->r29 and &sp->r28; ngccc gives
//     arg0->r28 and &sp->r29.  Everything else (node r30, nxt r31,
//     arg1 r27) already matches.  Invariant across ~35 source
//     permutations (declaration order, decl-init vs assignment birth of
//     &sp, Lst*/char*/void*/array pointer forms, merged vs split temps,
//     inline vs staged `arg1 & 1`, own/node/vt variable reuse) and 12
//     flags (-fno-schedule-insns/-insns2/-sched-spec/-thread-jumps/
//     -branch-count-reg/-strength-reduce/-expensive-optimizations/
//     -rerun-cse-after-loop/-gcse, ...).  This is the doc-10 /
//     docs/parkings/10-pure-regalloc-coin-flip.md class: it needs a
//     hard-register pin (`register ... __asm__("r28")`), deliberately not
//     used here.
//  2. PROLOGUE 9-WORD WINDOW (0x8000B950-0x8000B970): want splits the &sp
//     web — `addi r11,r1,8` / `stw vt,8(r11)` / `mr r28,r11` /
//     `stw base,4(r11)` — and interleaves the lbl_802901D8 lis/addi pair
//     around `addi r8,r29,4`.  ngccc keeps one &sp web, emits the dead
//     p->cur store first, and hoists `addi r30,arg0,4` above the lis.
//  3. PRE-LOOP TERNARY BLOCK LAYOUT: want is
//     `cmpwi / bne L / li 0 / b M / L: lwz / M: or.` (true arm out of
//     line).  Every guarded spelling tried (ternary, if/else, both
//     polarities, temp-then-assign, goto) emits either the load hoisted
//     above the test or the loop's `li/beq/lwz` form.  NOTE: the
//     IDENTICAL expression inside the loop DOES match with the plain
//     ternary, so this is a one-site block-ordering artifact.
//     The unguarded spelling `nxt = cur->unk0x4; if (cur == NULL) nxt =
//     NULL;` scores 2 words better (73 diffs / 11.0%) because ngccc
//     hoists the load, but it dereferences before the null test and is
//     not a faithful decompilation — rejected.
//  4. Tail store order of the two self-link stores is right in both.
// family=m2c range=0x8000B934-0x8000BA88 size=340B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern char lbl_802901D8[];
extern char lbl_802901F0[];
extern char lbl_80290220[];
/* Class-descriptor shape for the list elements: s16 instance offset at
   +8, method pointer at +C (the `lha`/`lwz`/`add`/`mtlr`/`blrl` shape). */
typedef struct { char pad0x0[8]; s16 unk0x8; char pad0xA[2]; s32 unk0xC; } DispA;
/* Same shape, 0x20-byte descriptor: offset at +0x18, method at +0x1C. */
typedef struct { char pad0x0[0x18]; s16 unk0x18; char pad0x1A[2]; s32 unk0x1C; } DispB;
/* List element / list head node. */
typedef struct {
    char pad0x0[4];
    s32 unk0x4;
    s32 unk0x8;
    s32 unk0xC;
    s32 unk0x10;
    s32 unk0x14;
    char pad0x18[0xD4];
    s32 unk0xEC;
} Elem;
/* The 0x24-byte child hung off arg0+0x1C. */
typedef struct { char pad0x0[0x18]; s32 unk0x18; s32 unk0x1C; s32 unk0x20; s32 unk0x24; } Owner;
/* 16-byte stack local walked by the list loop. */
typedef struct { s32 unk0x0; s32 cur; s32 cls; s32 unk0xC; } Lst;
void fn_8000B934(CScript *arg0, s32 arg1) {
    Lst sp;
    Lst *p = &sp;
    Elem *base;
    register Elem *tmp __asm__("r0");
    Elem *cur;
    Elem *nxt;
    Owner *own;
    Unk_C8FEE62D *node;
    s32 flag;
    DispA *vta;
    DispB *vtb;

    arg0->unk0x20 = (s32)lbl_802901F0;
    base = (Elem *)((char *)arg0 + 4);
    p->cur = (s32)base;
    p->cls = (s32)lbl_802901D8;
    tmp = (Elem *)base->unk0xC;
    if (tmp->unk0x4 == -1) {
        tmp = NULL;
    }
    p->cur = (s32)tmp;
    tmp = (tmp != NULL) ? (Elem *)tmp->unk0x4 : NULL;
    cur = tmp;
    node = (Unk_C8FEE62D *)((char *)arg0 + 4);
    while (cur != NULL) {
        tmp = (Elem *)p->cur;
        nxt = (Elem *)tmp->unk0xC;
        if (nxt->unk0x4 == -1) {
            nxt = NULL;
        }
        p->cur = (s32)nxt;
        nxt = (nxt != NULL) ? (Elem *)nxt->unk0x4 : NULL;
        if (cur != NULL) {
            vta = (DispA *)cur->unk0xEC;
            ((s32 (*)(void *, s32))vta->unk0xC)((char *)cur + vta->unk0x8, 3);
        }
        cur = nxt;
    }
    own = *(Owner **)((char *)arg0 + 0x1C);
    if (own != NULL) {
        vtb = (DispB *)own->unk0x18;
        ((s32 (*)(void *, s32))vtb->unk0x1C)((char *)own + vtb->unk0x18, 3);
    }
    p->cls = (s32)lbl_802901D8;
    node->unk0x14 = (s32)lbl_80290220;
    *(s32 *)(node->unk0x10 + 0xC) = node->unk0xC;
    *(s32 *)(node->unk0xC + 0x10) = node->unk0x10;
    node->unk0xC = (s32)node;
    node->unk0x10 = (s32)node;
    flag = arg1 & 1;
    if (flag != 0) {
        Mem_Free(arg0);
    }
}
