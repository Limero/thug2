// WIP DRAFT — PARKED (non-matching). This is the body with the CORRECT decoded
// REFRESHED 2026-10-07 (scaffold/flag/volatile re-sweep): 8.6420% -> 12.3457% per-object flags: -fno-rerun-cse-after-loop -> -
// semantics; it compiles to 304 B of the want's 324 B (69 diffs, 9.21%).
// reproduce: LEAF_TMPDIR=<scratch> \
//     tools/venv/bin/python tools/want_got.py 0x80093084   -> 304B / 69 diffs / 9.21%
//
// CAUTION — the size-exact variant is NOT this one. Flipping the flag polarity
// back to `((arg0 & M) == M) || ((arg0 & 1) != 0)` yields a size-exact 324 B /
// 74 diffs / 8.64%, which looks better on every metric, but that polarity is
// what the want's BRANCHES rule out (see "flag polarity" below): it inverts the
// arm-A/arm-B condition. Size-exactness here coincides with being wrong; the
// correct body is kept. See the variant table at the end.
//
// Replaces the m2c husk, which emitted only 96 B of the 324 B function because
// every `0;` placeholder folded away and its two loops were siblings rather
// than nested.  Hand-rebuilt from the want; no inline asm anywhere.
//
// family=m2c range=0x80093084-0x800931C8 size=324B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// ------------------------------------------------------------------ decode
// Frame -0x28.  `mfcr r12` / `stw r12,0xc(r1)` and the epilogue's
// `lwz r12,0xc(r1)` / `mtcrf 0x18,r12`: the function keeps GCC-allocated
// condition-register bits (cr3/cr4) live across the calls it makes, and
// 0x18 restores exactly cr3+cr4.  LR at 0x2c, stmw r26/0x10 = six saved GPRs.
//
//   lbl_803016B0 is SAVED on entry and RESTORED on exit (r26) — a plain
//   save/restore, not a local.  lbl_803017F8 gates a one-shot init.
//   lbl_80301824 is the element count and is RE-READ FROM MEMORY on every loop
//   test (r27 holds its address; r9/r0 get the reload) — it must stay a plain
//   global `s32` so the calls to fn_80093820 can legally clobber it.
//
// The array is `lbl_803795DC` (bss, 0x2004 bytes) and it is an array of
// POINTERS, not of nodes: the want does `lwz r3,0(r31)` then `lwz r0,0x48(r3)`.
// Getting this wrong (as both the m2c draft and the first hand reconstruction
// did) costs ~2 extra frames of register pressure.
// It is reached as `lis r3,0x8038` + `addi r31,r3,-0x6a24`, i.e. a NEGATIVE
// displacement off the page base, not a literal address.
//
// Control flow (the part m2c got wrong — it had the loops as siblings):
//   for (i = 0; i < cnt; i++) {            r29 = i, r31 = walking pointer
//       n = *p++;
//       if (n->unk48 != 0 && ((Owner*)n->unk54)->unk6C > 0)   -> ARM A
//       else                                                  -> ARM B
//   }
//   ARM A: test n->unk58 & arg1, call, `i++`, RELOAD cnt, reload next node,
//          and FALL THROUGH into ARM B's block — so A chains to A.
//   ARM B: an INNER loop that starts at the CURRENT i (not i+1), entered with
//          r31 recomputed as `base + i*4`; when it drains, control leaves the
//          outer loop for good, so the `break` below is required.
//
// The two flag tests are deliberately NOT unifiable — want branches AROUND the
// call when its cr3 bit is set, i.e. the call happens when `(arg0 & M) != M`:
//   ARM A: (arg0 & 1) != 0 || (arg0 & 0x82)  != 0x82
//   ARM B: (arg0 & 1) != 0 || (arg0 & 0x102) != 0x102
// (The m2c draft had both backwards and additionally spelled the bit-1 test as
// `(arg0 & 1) < 0`, which is constant-false for a sign-masked value.)
//
// fn_80093820 takes TWO arguments — `mr r4, r30` before each call, r3 still
// holding the node.  The m2c draft had it as a one-arg call.
//
// `bl 0x80261d40` IS emittable from C: it is a `bl` to an 8-byte stub
// (`sc` ; `blr`) in the unsymbolized CRT region, and declaring the callee as an
// unprototyped extern makes ngccc emit a direct `bl`.  A literal cast-call
// (`((void(*)(void))0x80261d40)()`) does NOT — it goes through
// lis/ori/mtlr/blrl.  This corrects an earlier wrong conclusion that the `sc`
// made the call inexpressible; the `sc` is in the CALLEE.
//
// ------------------------------------------------------------------- parked
// Remaining gap is register pressure and block layout, not semantics:
//   * want: frame -0x28, stmw r26/0x10, callee-saved {r26,r27,r28,r29,r30,r31}.
//     got:  frame -0x30/-0x38, stmw r24 or r22/0x10 — one or two extra values
//     stay live across a call.
//   * want keeps BOTH flag tests in CR bits: `andi. r0,r30,0x82` +
//     `cmpwi cr3,r0,0x82` and `andi. r0,r30,1` + `mcrf cr4,cr0`, i.e. the
//     loop-invariant booleans are setcc values that live in cr3/cr4, and ARM B
//     computes its OWN pair inside the loop body (0x80093150-0x8009316c) rather
//     than reusing ARM A's.  Every formulation tried so far either (a) CSEs the
//     bit-1 test into a GPR (`clrlwi r25,r29,0x1f` + `cmpwi cr4,r25,0`), or
//     (b) promotes the tests to named s32 locals, which costs `xori`/`subfic`/
//     `adde` sequences and one more live register.
//   * want's outer loop is rotated with the increment at the top of the body
//     (`addi r31,r31,4` before the `0x48` load) and the array-indexed reload
//     `lwz r3,0(r31)` in the latch; ngccc picks a different rotation.
// Variants measured (all in a private dir, none promoted):
//   v2 WRONG polarity, size-exact 324B  74 diffs  8.64%  <- best scores, wrong
//   v3 wrong polarity + s32 locals   324B  74 diffs  8.64%
//   v4 CORRECT polarity (= this body) 304B  69 diffs  9.21%  <- semantically right
//   v5 correct + recompute bit-1 in B 316B  72 diffs  8.86%
// The two correct-polarity rows are all 2-5 words short, so none is size-exact.
// The inner loop is now bottom-tested (`do { ... } while (i < lbl_80301824);`):
// retail's arm-B latch is reload-cnt / i++ / cmp / blt back to the load, i.e.
// the guard sits at the bottom and the first iteration is entered untested
// because the outer loop already proved i < cnt.  A top-tested `while` puts an
// extra compare in front of the arm-B body.
//
#include "types.h"

extern s32 lbl_803016B0;
extern bool lbl_803017F8;
extern s32 lbl_80301824;

typedef struct Node93084 Node93084;
struct Node93084 {
    char pad0[0x48];
    s32 unk48;
    void *unk54;
    s32 unk58;
};

typedef struct Owner93084 {
    char pad0[0x6C];
    s32 unk6C;
} Owner93084;

/* node array: 0x2004 bytes = 0x801 POINTERS, not 0x801 nodes. */
extern Node93084 *lbl_803795DC[0x2004 / 4];

void fn_80093820(Node93084 *, s32);
void sc_stub(); /* 0x80261d40: `sc` ; `blr` — unprototyped so ngccc emits `bl` */

void fn_80093084(s32 arg0, s32 arg1) {
    s32 i;
    s32 saved;
    Node93084 **p;

    saved = lbl_803016B0;
    if (lbl_803017F8 == 0) {
        sc_stub();
    }
    p = lbl_803795DC;
    for (i = 0; i < lbl_80301824; i++) {
        Node93084 *n = *p++;
        if (n->unk48 != 0 && ((Owner93084 *)n->unk54)->unk6C > 0) {
            if ((n->unk58 & arg1) != 0 &&
                (((arg0 & 1) != 0) || ((arg0 & 0x82) != 0x82))) {
                fn_80093820(n, arg0);
            }
        } else {
            p = lbl_803795DC + i;
            do {
                Node93084 *m = *p++;
                if ((m->unk58 & arg1) != 0 &&
                    (((arg0 & 1) != 0) || ((arg0 & 0x102) != 0x102))) {
                    fn_80093820(m, arg0);
                }
                i++;
            } while (i < lbl_80301824);
        }
    }
    lbl_803016B0 = saved;
}
