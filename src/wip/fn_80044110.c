// WIP DRAFT (non-matching) — hand-rewritten from the want disassembly.
// family=hand range=0x80044110-0x800445E8 size=1240B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// PARKED 2026-10-04: 91.3% is the C ceiling; re-proved this round.
//
// BEST MEASURED: NEAR 91.3%, object size EXACT (1240 B == want).
// (inherited m2c body was DIFF 5.1%; previous hand body NEAR 67.4%.)
//
// ---------------------------------------------------------------------------
// NEW MEASUREMENT THIS ROUND — THE 1240 B CEILING IS FORCED BY ngccc's
// `cmpwi`+`beq` FUSION, NOT BY THE STORE ORDER, so stop re-running store-order
// permutations.  The want's opening block computes the link address into r9
// from r1 plus 8, zeroes r0, copies the address into callee-saved r22 and
// stores the zero to 8(r9), then tests r3 against zero with a standalone
// compare separated from its forward branch by two stores (a zero to 4(r9)
// and r3 itself to 8(r1)) before the branch and the copy of r22 to the
// fourth argument register ahead of the call.
// i.e. the null test on `r3` is a STANDALONE `cmpwi` separated from its `beq`
// by two stores, and the obj store consumes `r3` directly (NO reload).  Two
// C spellings exist and they are 1 word apart in OPPOSITE directions:
//   (a) test through memory — `if (p1->obj != NULL)` — gives cmpwi+beq but
//       costs an extra `lwz r3,8(r1)` reload  => 1240 B, 27 diffs, 91.3%.
//   (b) test the register — `if (arg0->unk64 != NULL)` — removes the reload
//       (object 1236 B is then 1 word SHORT) BUT cc1 folds the whole compare
//       into the branch, emitting `beq` alone: -1 word, 1236 B, 299 diffs.
// Measured all 12 combinations of {store order: obj/prev/next} x {(a) mem,
// (b) direct}: every `_mem` variant is 1240 B / 91.29% regardless of order,
// every `_direct` variant is 1236 B / 2.9-3.2%.  Store order is a free
// parameter here; the compare/branch fusion is the whole wall.
// This is the SAME ngccc behaviour as residual (C) below (`cmpwi r28,0` twice
// vs one `mtcrf`) and is the C-side twin of docs/parkings/72: when nothing
// between a compare and its branch touches CR, GCC 2.95 emits the compare
// INSIDE the branch (RTL `if (x != 0)`), and there is no C spelling that
// keeps the flag alive across the two stores.
// ---------------------------------------------------------------------------
//
// Frame layout is now EXACT (stwu -0x70 / stmw r22,0x48 / stw r0,0x74, 10
// saved GPRs, locals 0x8..0x47) and the instruction SEQUENCE is 1:1 with the
// want (310 == 310 words; tools/align-by-mnemonic opcode diff is empty except
// for one `cmpwi`/`mtcrf` swap).  27/310 words still differ.
//
// WHAT CLOSED THE GAP (all measured; the three levers are the C *shape*, not
// flags — no flags beat the default -O2 -G0 -mcpu=750 -fno-common, see below):
//  1. `p2 = &ref2` must be assigned INSIDE the walk loop body.  With it before
//     the loop, the &ref2 pseudo is live across the whole walk, cc1 gives it a
//     dedicated callee-saved register (an extra `mr r21,r30`), the frame grows
//     to -0x80/stmw r21,0x54 and the object needs an extra 4-byte spill:
//     11 saved GPRs + spill = 1240 B but frame wrong (that was the 67.4% body).
//     Moving the assignment into the loop body makes cc1 rematerialise &ref2 in
//     the second loop (`addi r28,r1,0x18` inside the loop) instead of carrying
//     it: 10 GPRs, no spill, frame exact.
//  2. The walk loop's condition must read the local's FIELD, not through the
//     pointer: `while (ref.obj != NULL)` instead of `while (p1->obj != NULL)`.
//     That single change moves the invariant-flag save pair into loop 1's
//     PREHEADER, exactly like the want:
//        want  cmpwi r28,0 / lwz r0,8(r1) / mfcr r27 / cmpwi r0,0 / beq
//     With `p1->obj` cc1 puts `cmpwi <arg2>,0 / mfcr` AFTER the walk instead,
//     and everything below the epilogue shifts.
//  3. Store order of the three initial writes to the ref node: `obj` first
//     (`p1->obj = ...; p1->prev = 0; p1->next = 0;`).  obj-first is what makes
//     the object exactly 1240 B (the obj store is the only one that must be
//     frame-relative); prev,next,obj gives 1236 B.
//  4. The second loop's `pB = &ref3;` must sit AFTER the first
//     `CObject_AddRefLink(arg0, pA)` call, not at the top of the loop body —
//     otherwise cc1 hoists `&ref3` into the loop preamble and the body is one
//     word longer than the want's.
//
// WHAT IS STILL MISSING (27 words, one root cause + 3 small ones):
//  A. cc1 folds `p1 = &ref` so that p1 and `&ref` are ONE pseudo.  Consequences:
//     the `addi` for &ref is hoisted into the PROLOGUE (before the `bl` at
//     0x80044138) because the merged pseudo is live across that call, and the
//     want instead has, right after the call, the link address built into
//     short-lived r9, a zero materialised, the address copied to long-lived
//     r22, a zero stored to 8(r9), the compare of r3 against zero, and then
//     the remaining zero and r3 stores to 4(r9) and 8(r1).
//     i.e. TWO pseudos (short-lived address in the caller-saved r9 for the two
//     zero stores, long-lived p1 in callee-saved r22 for the four call args).
//     Because the store order needed for (3) puts the obj store first, cc1
//     then also reloads `lwz r3,8(r1)` for the `if` test, which the want does
//     not have — so the 310-word budget is spent on the wrong instruction.
//     (With prev,next,obj order there is no reload but the object is 1236 B.)
//     Not reachable from plain C so far: `register`, a second pointer variable
//     (q), `Ref44110 refs[3]` + indexing, assigning p1 before the n() call, and
//     -fno-gcse / -fno-cse-follow-jumps / -fno-thread-jumps / -fno-expensive-
//     optimizations / -fno-cse-skip-blocks / -fstrength-reduce all leave it
//     merged.
//  B. Callee-saved numbering: cc1 gives p1 r23 and the loop-2 `lis 0x8030_0000`
//     base r22; the want has p1 r22 and the base r23.  Everything else already
//     matches (r24=g, r25=arg1/i, r26=idx, r27=saved-CR, r28=arg2/pA, r29,
//     r30=&ref2/pB, r31=arg0), so this is a single swap of two allocations and
//     it is downstream of (A): with &ref/p1 split, p1's live range no longer
//     spans the call and the allocator's order changes.
//  C. 0x800442CC: want re-executes `cmpwi r28,0` for the `arg2 > 0` test and
//     uses the saved CR only for the later `arg2 != 0` test; cc1 CSEs the two
//     identical compares and emits `mtcrf 0x80,r27` for both.
//  D. Loop-1 scheduling: want emits the `ref.obj -> ->unk70` loads BEFORE the
//     two `p2->prev/next = 0` stores and the obj store AFTER the `cmpwi`.
//     Reordering the three `p2` initialisers in C moves the instruction count
//     instead (obj-first there = 311 B), so this one is scheduler-bound.
//
// MEASURED AND REJECTED (real measurements, no theory):
//  * four ref objects (a second Ref pair for the second loop, declared in the
//    loop body or in an enclosing block): 10 GPRs as wanted but the locals do
//    NOT share slots — ngccc 2.95 does not share stack slots between
//    block-scoped automatics — so the frame goes to -0x80/stmw r22,0x58 and the
//    object is 1236 B (7.1%).
//  * one shared pointer variable for both loops (`wsharep2`): 1232 B, 3.6%.
//  * `while (p1->obj != NULL)` (i.e. reverting (2)): 1236 B, 2.9%.
//  * flags on the 91.3% body: -fno-schedule-insns2 76.5%, -fno-cse-follow-jumps
//    54.2%, -fno-gcse 4.2% (1232 B), -fno-cse-skip-blocks 90.0%,
//    -fno-thread-jumps / -fno-sched-interblock / -fno-delayed-branch /
//    -fno-expensive-optimizations / -fstrength-reduce = 91.3% (tie).
//    Default -O2 -G0 -mcpu=750 -fno-common is the best.  -Os and -fno-gcse were
//    already hopeless on the old body; -fno-gcse is here too.
//
// TWO EARLIER FINDINGS WORTH KEEPING (see the report / AGENTS-recipes.md):
//  1. The `.rodata2` double at 0x80292510 = 0x4330000080000000 is ngccc's
//     *s32->f32 bias constant*, not a game literal: a plain `f32 v =
//     (s32)field;` compiles to xoris/stw/lis 0x4330/stw + `lfd` + ONE `fsub`
//     + `frsp`.  Any `(f64)a - <extern double>` in ngccc emits TWO fsubs
//     (bias + user) — verified with 4 probe TUs — which is what first
//     suggested the want was doing a user-level double subtraction.  It is
//     not: the whole expression is `v = arg0->unk198;`.
//  2. The 0x78/0xB40 allocation's per-entry pointer fill is
//     `for (i = 1; i < 0x1E; i++) tbl[i] = tbl[0] + 0x60 * i;` — the index
//     starts at 1 so cc1 strength-reduces to two IVs (0x60 stride from
//     0x60, index stride from 4) and keeps the indexed `stwx r0,r11,r9`;
//     writing `0x60 * (i-1)` collapses to a pointer add + `stw` instead.
//  3. ngccc's PPC frame convention: `stwu r1,-N(r1)` where N = (locals size,
//     rounded to 8, starting at 0x8 for the outgoing-arg area) + 4 per saved
//     GPR, and the LR is stored at `N+4` — i.e. ONE WORD ABOVE the allocated
//     frame (verified on 5 probe TUs plus this function).  So "frame is 8 too
//     big" can be either an extra saved GPR or an extra local; both were live
//     here simultaneously and fixing only one gives the 1236 B / wrong-frame
//     dead ends above.
//
// PROMOTION NOTE: the object carries a PRIVATE 8-byte .rodata
// (0x4330000080000000, finding 1).  It must be routed to the already
// registered `lbl_80292510` (src/r2d_8029250C.c holds exactly those bytes)
// with tools/fix_fp_pool.py, or the DOL layout shifts (AGENTS doc-14 pool
// caveat).  Every call-site symbol in the object is already correct: the
// five AddRefLink / five RemoveRefLink / two `n`(0x8003FE18) / two
// fn_8000F2F8 / two fn_80044960 counts all match the want.
//
#include "types.h"

typedef struct ScriptCtx44110 {
    char pad0[0x124];
    s32 unk124;
} ScriptCtx44110;

extern const f32 lbl_8029250C;
extern char lbl_80292508[];
extern ScriptCtx44110 *lbl_802FFE98;
extern void *lbl_80300434;

/* 2026-10-18: prologue cascade decoded — got's extra `addi r23,r1,8` is p1=&ref
   born at prologue-top into r23, while want births it post-n()-call into r22
   (`addi r9,r1,8; mr r22,r9`). Same strategy, homes shifted by one saved reg
   across the whole body (~27-word cascade from ONE live-range). Decl-init of
   g tried (inert, reverted). Fix = find the extra live variable shifting
   allocation (compare full saved-reg homes), not statement order. Parked. */
/* the stack ref-link node: +0 object, +4 prev, +8 next */
typedef struct Ref44110 {
    void *obj;
    void *prev;
    void *next;
} Ref44110;

typedef struct Node44110 {
    char pad0[0x18];
    s32 unk18;
    char pad1[0x54];
    void *unk70;
} Node44110;

typedef struct Obj44110 {
    char pad0[0xC];
    s32 unk0C;
    char pad10[0x54];
    Node44110 *unk64;
    char pad68[0x114];
    f32 unk17C;
    char pad180[0x10];
    s32 unk190;
    s32 *unk194;
    s32 unk198;
    s32 unk19C;
    s32 unk1A0;
    f32 unk1A4;
    s32 unk1A8;
    char pad1AC[8];
    f32 unk1B4;
    f32 unk1B8;
    f32 unk1BC;
    s32 unk1C0;
    char pad1C4[8];
    s32 unk1CC;
} Obj44110;

typedef struct Vt44110 {
    char pad0[0x10];
    s16 off;
    char pad12[2];
    void (*fn)(void *, void *);
} Vt44110;

typedef struct Sub44110 {
    char pad0[0x17C];
    f32 unk17C;
} Sub44110;

void n(void *, s32);
void CObject_AddRefLink(void *, void *);
void CObject_RemoveRefLink(void *, void *);
void fn_8000F2F8(ScriptCtx44110 *, s32);
void fn_8000F320(void *);
void *Mem_Alloc(s32);
void Mem_Free(void *);
void *Mem_NewZero(s32);
s32 fn_80053790(s32);
void fn_800586CC(s32, char *, s32 *, f32 *);
void fn_8004ADC8(void *, s32, s32, s32, s32);
void fn_8004AEF4(void *, Ref44110 *, Ref44110 *, s32);
s32 fn_80044960(void *, char *);
void *fn_800422E8(void *);
void fn_80042768(void *, s32);
void fn_800427AC(void *, char *);
void CScreenElement_SetScale(void *, s32, s32, f32, f32);

void fn_80044110(Obj44110 *arg0, s32 *arg1, s32 arg2) {
    Ref44110 ref;
    Ref44110 ref2;
    Ref44110 ref3;
    s32 sp38;
    f32 sp3C;
    Ref44110 *p1;
    Ref44110 *p2;
    Ref44110 *pA;
    Ref44110 *pB;
    void *g;
    s32 idx;
    s32 i;
    s32 cnt;
    s32 *p;
    s32 *tbl;
    Vt44110 *vt;
    void *obj;
    f32 scale;
    f32 v;

    g = lbl_80300434;
    n(arg0, 0);
    p1 = &ref;

    p1->obj = arg0->unk64;
    p1->prev = 0;
    p1->next = 0;
    if (p1->obj != NULL) {
        CObject_AddRefLink(p1->obj, p1);
    }
    while (ref.obj != NULL) {
        p2 = &ref2;
        p2->prev = 0;
        p2->next = 0;
        p2->obj = ((Node44110 *)ref.obj)->unk70;
        if (ref2.obj != NULL) {
            CObject_AddRefLink(ref2.obj, p2);
        }
        fn_8004ADC8(g, ((Node44110 *)ref.obj)->unk18, 1, 0, 0);
        if (ref.obj != NULL) {
            CObject_RemoveRefLink(ref.obj, p1);
            ref.obj = NULL;
        }
        ref.obj = ref2.obj;
        if (ref.obj != NULL) {
            CObject_AddRefLink(ref.obj, p1);
        }
        if (ref2.obj != NULL) {
            CObject_RemoveRefLink(ref2.obj, p2);
            ref2.obj = NULL;
        }
    }

    fn_8000F2F8(lbl_802FFE98, lbl_802FFE98->unk124);
    tbl = Mem_Alloc(0x78);
    arg0->unk194 = tbl;
    tbl[0] = (s32)Mem_Alloc(0xB40);
    fn_8000F320(lbl_802FFE98);

    for (i = 1; i < 0x1E; i++) {
        arg0->unk194[i] = arg0->unk194[0] + 0x60 * i;
    }
    for (i = 0; i < 0x1E; i++) {
        *(u8 *)arg0->unk194[i] = 0;
    }

    arg0->unk1A0 = 0;
    arg0->unk198 = 0;
    arg0->unk19C = 0;
    arg0->unk1A4 = lbl_8029250C;
    if (arg0->unk1CC != 0) {
        arg0->unk17C = lbl_8029250C;
        arg0->unk1A8 = 0;
    }

    if (arg2 > 0) {
        p = arg1;
        cnt = arg2;
        do {
            fn_80044960(arg0, (char *)*p);
            p++;
        } while (--cnt != 0);
    }
    if (arg2 != 0) {
        arg0->unk198++;
        arg0->unk19C++;
    }

    arg0->unk1C0 = arg0->unk19C;
    idx = 0;
    if (arg0->unk198 >= arg0->unk1A8) {
        if (arg0->unk1CC != 0) {
            fn_800586CC(fn_80053790(arg0->unk190), lbl_80292508, &sp38, &sp3C);
            scale = sp3C * arg0->unk1B4 * arg0->unk1B8;
            v = arg0->unk198;
            arg0->unk1A0 = 0;
            arg0->unk1A4 = lbl_8029250C;
            v = v * scale;
            arg0->unk198 = 0;
            arg0->unk17C = v;
            arg0->unk19C = 0;
            arg0->unk1A8 = (s32)v / (s32)scale;
            if (idx < arg2) {
                p = arg1;
                cnt = arg2;
                do {
                    fn_80044960(arg0, (char *)*p);
                    p++;
                } while (--cnt != 0);
            }
            arg0->unk1C0 = arg0->unk1A8;
        } else {
            arg0->unk1C0 = arg0->unk1A8;
            idx = arg0->unk198 % arg0->unk1A8;
        }
    }

    arg0->unk1BC = lbl_8029250C;
    for (i = 0; i < arg0->unk1C0; i++) {
        pA = &ref2;
        fn_8000F2F8(lbl_802FFE98, lbl_802FFE98->unk124);
        obj = fn_800422E8(Mem_NewZero(0x1D0));
        fn_8000F320(lbl_802FFE98);
        vt = *(Vt44110 **)((char *)g + 0x2C);
        vt->fn((char *)g + vt->off, obj);
        pA->prev = 0;
        pA->next = 0;
        pA->obj = arg0;
        if (arg0 != NULL) {
            CObject_AddRefLink(arg0, pA);
        }
        pB = &ref3;
        pB->prev = 0;
        pB->next = 0;
        pB->obj = obj;
        if (obj != NULL) {
            CObject_AddRefLink(obj, pB);
        }
        fn_8004AEF4(g, pA, pB, 1);
        if (pB->obj != NULL) {
            CObject_RemoveRefLink(pB->obj, pB);
            pB->obj = NULL;
        }
        if (pA->obj != NULL) {
            CObject_RemoveRefLink(pA->obj, pA);
            pA->obj = NULL;
        }
        fn_80042768(obj, arg0->unk190);
        fn_800427AC(obj, (char *)arg0->unk194[idx]);
        idx++;
        CScreenElement_SetScale(obj, 0, 0, arg0->unk1B4, arg0->unk1B4);
        arg0->unk1BC = ((Sub44110 *)obj)->unk17C * arg0->unk1B4 * arg0->unk1B8 + arg0->unk1BC;
        if (idx >= arg0->unk1A8) {
            idx = 0;
        }
    }

    Mem_Free((void *)arg0->unk194[0]);
    Mem_Free(arg0->unk194);
    n(arg0, 1);
    arg0->unk0C = arg0->unk0C | 0x1000;
    if (ref.obj != NULL) {
        CObject_RemoveRefLink(ref.obj, p1);
        ref.obj = NULL;
    }
}