// WIP DRAFT (non-matching) — hand-written reconstruction of fn_80125600
// RE-TRIAGED 2026-10-19: sweep still DIFF — ~6% masked; wall stands. Parked as-is.
// family=m2c range=0x80125600-0x8012570C size=268B
// PARKED 2026-10-03 (b38): DIFF ~6% masked (baseline was DIFF 11.9%).
//   tools/venv/bin/python tools/test_wip_drafts.py --addr 0x80125600
//   tools/venv/bin/python tools/want_got.py 0x80125600
// The body below is INSTRUCTION-FOR-INSTRUCTION correct against the want for
// every block except three register-allocation artifacts (see bottom).
// The pct went DOWN vs baseline because the object is now 248B vs the want's
// 268B: the missing words are in the middle of path A, so the positional
// scorer shifts the whole tail.  The m2c baseline scored higher only by
// coincidence of a 240B body (AGENTS.md "masked_pct IS STRICTLY POSITIONAL").
//
// Semantics (from the disassembly):
//   arg == 0            -> counter = 0; h = LIST[0]; if h -> cache/return
//   arg != 0            -> h = arg->field_0x10; if h -> cache/return
//   otherwise           -> i = counter+1; store counter; h = LIST[i];
//                          i > 0xFFF -> cache = 0, counter = 0, return 0
//                          h == 0 -> keep scanning (do/while)
//   success             -> cache = h; return h
// Two copies of the scan loop exist in the want (path A and path B), the
// second one preceded by a peeled first iteration whose test is INVERTED
// (`ble`, fail as fall-through) and its own inlined copy of the fail tail.
//
// Reusable finding (statement order inside a scan loop decides where the
// compare lands): with the source order `i = c+1; if (i > LIM) goto fail;
// h = p[i]; c = i;` ngccc emits `cmplwi; bgt; slwi; lwzx; stw` — the branch
// lands right after the compare and the load/store fall *below* it.  With the
// order `i = c+1; h = p[i]; c = i; if (i > LIM) goto fail;` ngccc hoists the
// `cmplwi` above the load/store and sinks the `bgt` below them, giving the
// want's `slwi; cmplwi; lwzx; stw; bgt`.  That single swap is what made the
// whole 9-word loop body byte-identical (want 0x8012562C-0x8012564C).
// A `while`/`for` loop is still rotated by ngccc (entry test peeled into a
// pre-header + latch); `do {...} while (cond)` is NOT, so the do-while is
// required to keep the entry test out of a peeled block.
//
// What still differs (all reload/local-alloc artifacts, not semantics):
//  1. want 0x80125610 `lwz r9,0x3248(r9)` — the LIST pointer lands in r8 in
//     GOT, so the want's `mr r8,r9` loop preheader (0x80125628) has no
//     counterpart and path A is 2 words short.  Adding a second named pointer
//     (`s32 *p = list;`) is CSE'd away; `&`-punning / volatile / pointer-local
//     variants all made it worse.
//  2. want 0x80125614 `lis r6` — a second, long-lived base register holding
//     the counter address for the two fail tails; GOT re-materialises the
//     `lis` inside each fail block instead (also +1 word per fail block).
//  3. GOT's two identical return tails (retA/out_b) get tail-merged into one
//     block; the want keeps two (0x80125650 and 0x801256FC).
#include "types.h"

extern s32 *lbl_80303248;
extern s32 lbl_80303250;
extern s32 lbl_80303254;

s32 fn_80125600(s32 arg0) {
    s32 h = arg0;
    u32 i;
    s32 *list;

    if (h == 0) {
        list = lbl_80303248;
        lbl_80303250 = h;
        h = list[0];
        if (h != 0) {
            goto out_a;
        }
        do {
            i = (u32)lbl_80303250 + 1;
            h = list[i];
            lbl_80303250 = i;
            if (i > 0xFFFU) {
                goto fail;
            }
        } while (h == 0);
    out_a:
        lbl_80303254 = h;
        return h;
    }

    h = *(s32 *)((char *)arg0 + 0x10);
    if (h != 0) {
        goto out_b;
    }
    list = lbl_80303248;
    i = (u32)lbl_80303250 + 1;
    lbl_80303250 = i;
    h = list[i];
    if (i > 0xFFFU) {
        lbl_80303254 = 0;
        lbl_80303250 = 0;
        return 0;
    }
    if (h == 0) {
        do {
            i = (u32)lbl_80303250 + 1;
            h = list[i];
            lbl_80303250 = i;
            if (i > 0xFFFU) {
                goto fail;
            }
        } while (h == 0);
    }
    goto out_b;
out_b:
    lbl_80303254 = h;
    return h;
fail:
    lbl_80303254 = 0;
    lbl_80303250 = 0;
    return 0;
}