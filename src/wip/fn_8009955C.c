// WIP DRAFT (non-matching) — best measured body: 608B (EXACT size), masked
// match 41.45% (63/152 words), verdict DIFF.  Previous best was 24.34%.
// family=m2c range=0x8009955C-0x800997BC size=608B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// PARKED 2026-10-04 (2nd pass).  Every block now emits want's block ORDER and
// word COUNT (all four search phases + the compaction loop); the residue is
// register allocation plus two ngccc loop-optimiser artifacts in the
// compaction loop.
//
// WHAT IS NOW BYTE-STRUCTURAL (word count AND per-block order match want):
//   * prologue/epilogue: 0x38 frame, `stmw r20,8(r1)`, `stw r0,0x3c(r1)`,
//     `vals` in r20 — all four words exact.
//   * outer preheader: 17 instructions, same multiset/order as want up to
//     registers (entry guard `cmpw i,nvals` + the three hoisted `slwi`
//     c0*4/e1*4/e2*4 that buy r21-r23 and hence the 0x38 frame).
//   * phase-1 search loop: the plain `for (j=0;j<c0;j++) items[j]` form gives
//     want's top-tested shape (`b TEST` / LATCH / TEST / BODY / FOUND).
//   * phases 2-4: goto state machine gives want's top-tested shape with the
//     latch ABOVE the test (20 words each) and a `li rX,0` in each preheader.
//   * compaction loop: `n=count; k=0; if (k<n) {o=0; do{...}while(k<(u16)n);}`
//     gives want's entry-guard + bottom-test shape with `clrlwi` for (u16)n.
//
// NEW LEVERS FOUND THIS PASS (the old note's "blockers" are all resolved):
//   1. ANTI-ROTATION.  ngccc-2.95 loopify rotates every `for`/`while` whose
//      latch increments a 2nd IV, AND duplicates the body when it does.
//      Neither `for`, `while`, `if(c) do{}while(c)` nor `goto`-out-of-`for`
//      avoids it.  The form that DOES is an explicit goto state machine with
//      the latch label placed BEFORE the test label:
//          j = c0; o = o1; goto testN;
//        latchN:  j++; o += 4;
//        testN:   if (j < end) goto bodyN;  goto doneN;
//        bodyN:   if (slot != v) goto latchN;
//                 slot = 0; found = 1; hN++; cntN--; goto doneN;
//        doneN: ;
//      → emits [preheader … b TEST][LATCH][TEST][BODY][FOUND] = want exactly
//      (recipes §6cw-2 / §6an "goto-into-for" family, anti-rotation sibling).
//      Side effect: goto-form loops are NOT seen by loopify, so the three
//      `slwi` no longer hoist by themselves — keep the explicit o1/o2/o3.
//   2. PER-PHASE STORE-ZERO.  want materialises the constant 0 FOUR times
//      (r24 / r6 / r6 / r7) instead of once.  Writing ONE named local `z`,
//      re-assigned `z = 0;` in each phase preheader and stored (`slot = z`),
//      reproduces 4 materialisations (hoisted for phase 1, `li r8,0` for
//      phases 2-4).  Three SEPARATE temps (z1,z2,z3) also work but cost a
//      13th saved register → frame 0x40, wrong.  A redundant `found = 0`
//      instead of `z = 0` is dead-code-eliminated (no `li`).
//   3. UNPROTOTYPED-BOUND CASTS.  Declare the compaction bound `s32 n` (not
//      u16) and keep the `(u16)` cast ONLY in `lim = (u16)n - 1` and in the
//      latch `while (k < (u16)n)`; the entry guard stays `if (k < n)`.  The
//      two different spellings stop ngccc from folding/CSE-ing the guard into
//      the latch, which is exactly want's un-merged guard+latch pair.
//   4. INLINE THE RUN TOTAL.  `for (i = 0; i < h0+h1+h2+h3; i++)` (no
//      `total` local) frees a register — without it the frame is 0x40 and
//      the score collapses to 35%; want has no total local either (the sum
//      lands directly in r29, reusing c0's dead register).
//   5. MEMCPY ARG SPELLING.  `memcpy(&items[k], &items[k+1], len)` (typed
//      index) is the only spelling that lands on 608B; `memcpy(q,(char*)q+4)`
//      and `memcpy(q,q+1,…)` are 1 word short (want's `addi r4,r3,4` in the
//      found path needs 2 strength-reduced address IVs to hit the count).
//
// REMAINING BLOCKER (register allocation + one loop-optimiser artifact):
//   * every phase's `lwzx r0, r11, r9` (want) vs `lwzx r0, r9, r11` (got):
//     same semantics, base/index swapped in the encoding.  want's counter map
//     is c0=r29,e1=r30,e2=r3,e3=r28,h0=r27,h1=r12,h2=r5,h3=r4,i=r9/i+1=r26,
//     o1..o3=r21..r23,zeros=r24/r6/r7,v=r8,j=r10,o=r11,found=r7,nvals=r25;
//     got puts c0/e1/e2 in volatile regs and h1/h2/h3 in saved regs instead,
//     and hoists `mr r20,r5`/`mr r29,r4` to the top of the preheader (the old
//     24% body scheduled them in want's order — a real allocator coin-flip).
//   * compaction loop: want keeps a 2nd copy of the count (`mr r8,r11` in the
//     preheader, `mr r11,r8` in the latch) and re-derives `(u16)n` twice
//     (clrlwi in the found path AND in the latch); loopify instead hoists one
//     clrlwi to the loop head and strength-reduces the memcpy source into a
//     3rd induction variable (`addi r4,r9,4` / `addi r4,r4,4`).  The net word
//     count matches only thanks to lever 5.
//
// Negative results recorded: -fno-schedule-insns2 (15.8%), -fno-gcse (636B),
//   -fno-crossjumping/-fno-loop-optimize (rejected by ngccc); declaring
//   memcpy (loses `crclr cr1eq`); `(char*)` cursor instead of a byte offset
//   (materialises the pointer: `add r9,r0,r21`, 624B); `u32 n` / a 2nd copy
//   `n2` for the latch bound (CSE folds them away, identical output);
//   goto-form loops with typed-index addressing (no strength reduction →
//   `slwi` form, 548B); `for`/`while` spellings of phases 2-4 (rotate+duplicate
//   or guard+bottom-test, never want's top-tested layout).
//
// NOTE: `o1/o2/o3` are ordinary statements *inside* the outer loop only to
// make ngccc hoist the three `slwi` into the loop preheader; that hoist is
// what allocates r20-r23 and hence the 0x38 frame.  Do not "clean them up".
// Also note structs.h's shared Unk_13E912CF types 0x60/0x64 as s32 — for
// this function all five fields are u16; a promotion needs a real struct here,
// not the shared one.
#include "types.h"
#include "structs.h"

typedef struct {
    char pad0x00[0x58];
    s32 *items;
    char pad0x5C[2];
    u16 count;
    u16 cnt0;
    u16 cnt1;
    u16 cnt2;
    u16 cnt3;
} Unk_9955C;

void fn_8009955C(Unk_9955C *self, s32 nvals, s32 *vals) {
    s32 c0 = self->cnt0;
    s32 c1 = self->cnt1;
    s32 c2 = self->cnt2;
    s32 c3 = self->cnt3;
    s32 e1 = c0 + c1;
    s32 e2 = e1 + c2;
    s32 e3 = e2 + c3;
    s32 h0 = 0, h1 = 0, h2 = 0, h3 = 0;
    s32 i, j, o, v, found, o1, o2, o3, z;
    s32 k, lim;
    s32 n;
    s32 *q;

    for (i = 0; i < nvals; i++) {
        found = 0;
        v = vals[i];
        o1 = c0 * 4;
        o2 = e1 * 4;
        o3 = e2 * 4;
        for (j = 0; j < c0; j++) {
            if (self->items[j] == v) {
                self->items[j] = 0;
                found = 1;
                h0++;
                self->cnt0--;
                break;
            }
        }
        /* phases 2-4: goto state machine = ngccc anti-rotation (see note) */
        if (!found) {
            j = c0;
            o = o1;
            z = 0;
            goto test1;
        latch1:
            j++;
            o += 4;
        test1:
            if (j < e1) {
                goto body1;
            }
            goto done1;
        body1:
            if (*(s32 *)((char *)self->items + o) != v) {
                goto latch1;
            }
            *(s32 *)((char *)self->items + o) = z;
            found = 1;
            h1++;
            self->cnt1--;
            goto done1;
        done1: ;
        }
        if (!found) {
            j = e1;
            o = o2;
            z = 0;
            goto test2;
        latch2:
            j++;
            o += 4;
        test2:
            if (j < e2) {
                goto body2;
            }
            goto done2;
        body2:
            if (*(s32 *)((char *)self->items + o) != v) {
                goto latch2;
            }
            *(s32 *)((char *)self->items + o) = z;
            found = 1;
            h2++;
            self->cnt2--;
            goto done2;
        done2: ;
        }
        if (!found) {
            j = e2;
            o = o3;
            z = 0;
            goto test3;
        latch3:
            j++;
            o += 4;
        test3:
            if (j < e3) {
                goto body3;
            }
            goto done3;
        body3:
            if (*(s32 *)((char *)self->items + o) != v) {
                goto latch3;
            }
            *(s32 *)((char *)self->items + o) = z;
            h3++;
            self->cnt3--;
            goto done3;
        done3: ;
        }
    }

    /* run total is NOT a local: the sum reuses c0's dead register (r29) */
    for (i = 0; i < h0 + h1 + h2 + h3; i++) {
        n = self->count;
        k = 0;
        if (k < n) {
            o = 0;
            do {
                q = (s32 *)((char *)self->items + o);
                if (*q == 0) {
                    lim = (u16)n - 1;
                    if (k < lim) {
                        memcpy(&self->items[k], &self->items[k + 1],
                               (lim - k) * 4);
                    }
                    self->count = self->count - 1;
                    break;
                }
                k++;
                o += 4;
            } while (k < (u16)n);
        }
    }
}