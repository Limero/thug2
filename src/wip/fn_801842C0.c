// PARKED 2026-10-03 (b30): DIFF 48.3% masked, 240B compiled vs 236B want.
// Reproduce: LEAF_TMPDIR=<scratch> tools/venv/bin/python \
//               tools/want_vs_got.py 0x801842C0
//   pct went UP from the 14.3% baseline (m2c body guessed fn_8018B4C0 as a
//   4-arg call and declared neither it nor fn_8018B568/fn_80191DBC; that alone
//   shifted the whole tail).  The body is now semantically exact: every callee
//   declared, correct arities, correct types, correct slots/frame, and
//   instruction-for-instruction identical to the want for the first 0x80 bytes.
//
//   REMAINING DIFF — one root cause, three visible symptoms (loop2 preheader):
//   want keeps the address of the local at sp+0x10 in a callee-saved register
//   for the WHOLE function (r28 = r1+0x10, emitted before loop1) and reload
//   then uses it as the base for both loop2 loads of that slot (at +0x88
//   and +0xa4, loading r3 through 0(r28)):
//   ngccc instead shares that address pseudo with the loop counter, so it
//   dies at the fn_8018B608 call and both loads fold to r1+0x10: the got
//   derives r1+0x10 into r30 at +0x20 (the want keeps that address in r28),
//   and both the +0x88 and +0xa4 loads read r3 through 0x10(r1).
//   and the freed r28 then goes to the loop2 arg2 address, hoisted into the
//   preheader as one EXTRA instruction, which shifts everything after 0x84:
//   at +0x80 the got derives r1+0x14 into r28 where the want zeroes r27.
//   That single extra word is the whole 240-vs-236 length gap.
//
//   RULED OUT (all measured, all keep 240B or make it worse):
//   - `-fno-expensive-optimizations` (the flag the m2c draft carried): kills
//     the while-rotation (`b` no longer lands on the loop test) — worse.
//   - giving the frame pointer's second slot a name only: `sp10` as s32 /
//     `CStruct *` / `*&sp10` / `*&sp10` in both loop2 calls — 100% identical
//     output, so the hoist is not ref-count driven.
//   - `void **sp10` + `*sp10` at the call sites: 252B (needs an extra load).
//   - `register s32 var_r30 __asm__("r30")`: hijacks allocation completely,
//     arg0 lands in r30.
//   - `register ... __asm__("r28")` on &sp10: GCC hands r28 to the *parameter*
//     instead and shifts every frame slot by one.
//   - comma-expression `(sp14 = 0, &sp14)` and moving the `sp14 = 0` into the
//     arg list: no effect on the hoist.
//
//   MOST PROMISING NEXT IDEA: the want's preheader order is
//   `mr r30, r0; li r27, 0; addi r29, r1, 0x18` — the const-0 pseudo outranks
//   BOTH address pseudos, and 6 live values compete for 5 callee-saved regs,
//   so exactly one address (the 1-ref &sp14) must be rematerialised.  Find a
//   source shape that gives `&sp10` a second in-loop use so reload CSEs it
//   with the pre-loop reload pseudo; anything that forces one extra reference
//   to slot 0x10 between the fn_8018B608 call and the loop2 body should flip
//   both symptoms at once.
//
// UPDATE 2026-10-12: three new probes, body unchanged (48.3% stands).
//   - `void **pp10 = &sp10` + loop2 via `*pp10`: 52.54% (+4.2) BUT prologue
//     breaks (stmw r26 vs r27, full recolor cascade). The extra address pseudo
//     costs exactly the callee-saved reg the note says is contested. Direction
//     confirmed (loop2 loads want the (r28) base) but needs a pressure-neutral
//     carrier, not a new local.
//   - merging temp_r0 into var_r30 (with and without pp10): 32.8% / 41.4%,
//     frame shrinks 240B -> 232B. The temp/var split is load-bearing.
//   - `sp10 = NULL` init before loop1: 13.6%, extra store kills the shape.
//   Do not retry extra-locals or slot-init here.
// family=m2c range=0x801842C0-0x801843AC size=236B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "structs.h"

extern s32 fn_80184168(Unk_9994C3F5 *);
extern void *fn_8018B4C0(Unk_C8FEE62D *, s32 *, s32 *);
extern void fn_8018B568(void *, s32 *);
extern void fn_8018B608(void *, void *);
extern void fn_80191DBC(s32);

void fn_801842C0(Unk_C7387A53 *arg0) {
    s32 sp18;
    s32 sp14;
    void *sp10;
    s32 spC;
    s32 sp8;
    s32 temp_r0;
    s32 var_r30;
    void *temp_r31;
    void *temp_r9;

    arg0->unk0x38 = 0;
    sp8 = 0;
    while (sp8 < fn_80184168(arg0)) {
        fn_80191DBC(((Unk_C8FEE62D *)fn_8018B4C0((void *)((char *)arg0 + 4), &sp8, &spC))->unk0x18);
        sp8 += 1;
    }
    fn_8018B608(&sp10, (char *)arg0 + 4);
    temp_r0 = *(s32 *)((char *)sp10 + 4);
    if (temp_r0 > 0) {
        var_r30 = temp_r0;
        do {
            sp14 = 0;
            temp_r31 = fn_8018B4C0(sp10, &sp14, &sp18);
            fn_8018B568(sp10, &sp18);
            if (temp_r31 != NULL) {
                temp_r9 = *(void **)((char *)temp_r31 + 0x14);
                ((void (*)(void *, s32))*(void **)((char *)temp_r9 + 0xC))(
                    (char *)temp_r31 + *(s16 *)((char *)temp_r9 + 8), 3);
            }
            var_r30 -= 1;
        } while (var_r30 != 0);
    }
}