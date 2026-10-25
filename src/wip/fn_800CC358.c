// WIP DRAFT (non-matching until promoted) — updated by 2026-08-23 park-sweep session
// PARKED 94.1% (2026-08-31): doc-15 test/materialize coin-flip at the tail
// (want `cmpwi r9,0; li r3,0; beq; addi r3,r9,-4` vs got li/cmpwi swapped).
// NOTE (2026-08-31 session): the constant-arm variant of this coin-flip was
// CRACKED in fn_8009ED14 via the not_if lever (`if (!cond) var=F; else
// var=T;` emits [test; T; branch; F]). It does NOT transfer here: the arms
// are non-constant (0 vs node-4), and every branchy form (if/else both
// polarities, ternary, node pin r9 + sel pin r3) coalesces node into r3 or
// duplicates the tail (measured 50.0/38.2/79.4/91.2%). Best form stays
// init-if + sel r3 pin at 94.1%.
// family=m2c range=0x800CC358-0x800CC3E0 size=136B
// IMPROVED 91.2% -> 94.1% (2026-08-23): tail-only register asm("r3") pin forces the select into
// the return reg. Residual 2 words = doc-15 test/materialize coin-flip (cmpwi vs li order).
// PARKED 2026-10-03: NEAR 94.1% (32/34 words), SIZE-EXACT 136B. Reproduce:
//   export LEAF_TMPDIR=<private dir>
//   tools/venv/bin/python tools/test_wip_drafts.py --addr 0x800CC358
//   tools/venv/bin/python tools/want_got.py 0x800CC358
//
// REMAINING BLOCKER (2 words, 0x800CC3C0..0x800CC3C4) — a pure load/compare
// emission-order swap inside ONE basic block, no register or opcode change:
// want tests r9 first and then zeroes r3, while got zeroes r3 first and then
// tests r9. This is the doc-15 "load-order coin-flip" family (AGENTS.md 4p.51).
//
// CORRECTION 2026-10-04 (supersedes the "SELF-CONTRADICTION" claim below):
// **there is no self-contradiction — want is CONSISTENT.** Both want blocks
// use the SAME test-then-zero order at 0x39C (against r11 into r0) and at
// 0x3C0 (against r9 into r3).
// It is *ngccc* that is inconsistent: test-then-zero for the `p` block,
// zero-then-test for the `sel` block. So this is NOT provably unreachable
// from source; the earlier "no statement order produces both" proof was a
// misreading of the want. Do not cite it again.
//
// TRIED 2026-10-04 (all WORSE than 94.1%, none flip the 2 words):
//   * sel spelled EXACTLY like the working p select (NULL-first ternary, as
//     both s32 and void*): 50.0% — instructively, the pin makes ngccc home
//     the NODE in r3 instead of r9, so the whole prologue shifts
//     (`lwz r3,0x38(r3)`). The ternary's shape is right but pinning sel to
//     r3 and then branching on it collapses node->sel.
//   * `p = NULL; if (n2) p = n2-4;` (make BOTH selects init-if): 88.2% —
//     moves the p block to zero-then-test too, i.e. ngccc picks ONE order
//     for both selects and init-if means zero-first everywhere. Want needs
//     test-first for both, and test-first is only reachable via the ternary,
//     which the r3 pin breaks. That is the real wall: pin-vs-shape.
//   * p/sel statement order swapped (sel first): 33.3% (object 120B).
//   * not_if form for sel (the fn_8009ED14 lever): 50.0%.
//   * no pin at all: 31.3% (object 128B) — pin IS load-bearing.
//   * return shaped through a helper `Unk_1D62F22E_2 *q` local: 31.3%.
//
// TRIED 2026-08-31 (all measured, all WORSE than 94.1%):
//   * `sel = node;` then `if (node == NULL) return 0;` (test before zeroing
//     the pinned reg) ................................. 31.3% (object 128B)
//   * if/else instead of the conditional assign ......... 50.0%
//   * ternary select `sel = node ? ... : 0` ............. 50.0%
//   * hoisting `sel = 0` above the `if (b)` guards ...... 68.8% (object 128B)
//   * dropping the `register s32 sel asm("r3")` pin entirely ... 32.3% (124B)
//   The pin IS load-bearing: without it ngccc picks a different register for
//   the NULL-poisoned load base and the whole tail restructures.
//
// FLAGS: -fno-sched-spec / -fno-schedule-insns2 -> 94.1% no-op;
// -fno-schedule-insns -> 82.4% (worse).
//
// 2026-10-18: filled the pin-matrix gap (node-pin-r9 + ternary, sel
// unpinned: 88.2% with sel in r11; both pins + ternary: 77.1% restructured).
// Node-pin restores the r9 base but sel will not stay in r3. Reverted.
// CLASSIFICATION: doc-15 scheduler tie. Parking is correct; this is not a
// missing recipe, it is a coin-flip the original compiler lost differently.
// Real blocker, restated: with the r3 pin ngccc will not emit test-first for
// the sel block; without the pin it will not emit the wanted r3 base.
#include "types.h"
#include "structs.h"
s32 fn_800CC358(Unk_C7387A53 *arg0) {
    Unk_DB0E2BAB *node;
    s32 b;
    void *n2;
    void *p;
    {
        register s32 sel asm("r3");
        node = *((void * *)&arg0->unk0x38);
        if (node->unk0x4 == -1) {
            node = NULL;
        }
        if (node == NULL) {
            goto ret0;
        }
        node = *((void * *)&node->unk0x24);
        b = (node->unk0x4 == -1);
        n2 = node;
        if (b) {
            n2 = NULL;
        }
        p = (n2 == NULL) ? NULL : (char *)n2 - 4;
        if (p == NULL) {
            return 0;
        }
        if (b) {
            node = NULL;
        }
        sel = 0;
        if (node != NULL) {
            sel = (s32)(char *)node - 4;
        }
        return ((Unk_1D62F22E_2 *)sel)->unk0x38;
    }
ret0:
    return 0;
}
