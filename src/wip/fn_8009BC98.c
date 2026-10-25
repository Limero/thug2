// PARKED 2026-10-30 (a11): NEAR 86.8% (was NEAR 58.7%).
// 2026-10-08: reload_pin_sweep WIN — pin `p44` -> `register ... p44 __asm__("r9")` => official 88.4% (sweep base 86.83%). ONE pin only; pins are not additive.
// reproduce: LEAF_TMPDIR=<scratch> tools/venv/bin/python \
//              tools/test_wip_drafts.py --addr 0x8009BC98
//   object .text = 0x700 = 1792 B = want exactly (448 words each, 0x700 both).
//   sections: .text + .rela.text only — no .rodata/.data/.bss, so a future
//   masked-EXACT is also promote-clean (no doc-14 pool caveat).
//   0 emitted inline instructions except the two `register ... __asm__("rN")`
//   DECLARATION attributes (0 insns) — far inside the §4g 30% budget.
//
// WHAT THE 28-POINT JUMP WAS (both are "one value must be ONE web", §6bt):
//
//  A. The shift operands `1 << p44->bN` were LITERALS while the stack-arg
//     slots used the pinned `one`. That is TWO const-1 pseudos; because r30
//     is hard-pinned to `one` (§6bq) local_alloc had to give the shift one a
//     second callee-saved colour (r28) => 9 saved regs (r23..r31) and a
//     -0x70 frame. Writing `(u16)(one << p44->bN)` collapses them to one web:
//     `stwu -0x68 / stmw r24,0x48 / stw r0,0x6c` — want's prologue exactly.
//     MEASURED ALONE this is 45.98% (0x6F8, 8 B short) — load-bearing but NOT
//     sufficient; the rule is "every use of the constant", not just the stores.
//
//  B. The `else` arm must use LITERALS (1/0) for its four stack-arg slots, NOT
//     the named `one`/`zero`. want really does re-materialise the pair inside
//     the else arm — `li r30,1` at 0x8009C054 and `li r29,0` at 0x8009C05C,
//     between the `li r7,0` of fn_8001EEE0 and its `bl`, and `li r29,0` just
//     after it — even though the pre-if block already born them at 0x8009BDD0 /
//     0x8009BDD8. That proves the else arm's const pseudos are BLOCK-LOCAL and
//     local_alloc recycled the (then-dead) r30/r29 into them. Reusing `one`/
//     `zero` there suppressed both `li`s and left .text 8 B short. Converting
//     ONLY the else arm to literals: 45.98% -> 86.83%, .text -> 0x700 exact.
//     (Symmetrically the THEN arm reuses the pre-if web and must NOT get its
//     own literals — `one`/`zero` there is correct. Do not "unify" this.)
//
// REMAINING RESIDUAL (~59 of 448 words) is ONE local_alloc colour permutation
// plus its scheduling cascade:
//  * var_r28 / lbl_80297734-address are SWAPPED. want: var_r28=r28 and the
//    hoisted symbol address=r26 (`lis r26` 0x8009BD78 / 0x8009BD9C, consumed by
//    `lfs f1,0x7734(r26)` at 0x8009BE44, i.e. across the `bl fn_8001EA14`).
//    GOT: var_r28=r26 and the address=r28. want's r26 must have been handed out
//    by local_alloc (3rd allocno, lowest free callee-saved), because r26..r29
//    are ALL occupied when the else arm's const-1 is allocated and it still
//    lands in r30 — GOT, with r28 free, takes r28.
//  * Downstream of that swap: else arm `li r28,1` (want `li r30,1`) + two
//    `stw r28,8(r1)` (want `stw r30`), and the `p44->b6/b7` reloads can no
//    longer coalesce with their `slw` destination (want `lbz r4,6(r11)` +
//    `slw r4,r30,r4`; got `lbz r0,6(r11)` + `slw r4,r30,r0`), which in turn
//    reorders `li r7,0` past `fmr f2,f1`.
//  * REJECTED: `register s32 var_r28 __asm__("r28")` (recipes §6cb lever 2 /
//    §6bq hard pin). It does free r28, but local_alloc then hands r26 to
//    var_r27 and the address pseudo to r27 => a 4-way permutation: 85.27%.
//  * Most promising next idea: make the symbol address a real local_alloc
//    allocno rather than a reload-allocated one, so local_alloc (not reload)
//    picks its colour and lands on r26. §6cb lever 1 wants exactly this
//    ("a `lis` with a `bl` between it and its consumer is a VARIABLE in the
//    original"), but the obvious `f32 *pf = &lbl_80297734; ... = *pf;` adds an
//    `addi` that want does not have — want keeps the 0x7734 inside the `lfs`.
//    A spelling that gives cc1 a live-across-call address pseudo WITHOUT the
//    extra `addi` is the thing to hunt for next.
//
// MEASURED INERT / REJECTED THIS ROUND (so nobody repeats them):
//  * `fmr f3,f2` (want) vs `fmr f3,f1` (got), x2: giving the 3rd float arg its
//    own name chained from the 2nd (`temp_f2 = temp_f1; temp_f3 = temp_f2;`)
//    is BYTE-IDENTICAL — cc1's flow/CSE collapses the chain back to the fan-out.
//    The chained-copy family (§6fe) is not reachable from C spelling here.
//  * Merging `temp_f0` (the eight lbl_80297734 defaults) into `temp_f1` (the
//    three fn_8001EA14 args): 84.82%. The two names must stay distinct.
//  * `T98.h48` typed `s32` instead of `void *` (dropping the pointer->int cast):
//    byte-identical. KEPT because it is the honest type — the field is handed
//    straight to `fn_8001F1D4(s32)`. (The remaining compile warning is the
//    `s32 *p30` vs `f32 *v30` pun, not this.)
//  * The `one`/`zero` hard pins stay load-bearing (recipe log item 6 below).
//
// SMALL UNTOUCHED ITEMS (2-4 words each, all after the colour fix would land):
//  * `set_blend_mode(0,5,0)`: want emits `li r3,0 / li r5,0 / li r4,5`, got
//    `li r3,0 / li r4,5 / li r5,0` (arg-list `li` order, §6dl-1).
//  * the 2nd/3rd/4th `lwz 0x44(r31)` all pick r11; want alternates r9/r11,
//    with the matching `andi. r11,r0,2` vs `andi. r9,r0,2`.
//
// EARLIER RECIPE LOG (kept for provenance; items 1-5 still hold, item 6's
// diagnosis has been SUPERSEDED by A+B above — the extra register was not a
// broken pin, it was a second const-1 web for the shifts):
// family=m2c range=0x8009BC98-0x8009C398 size=1792B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"

extern f32 lbl_80297734;

void fn_8001EA14(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32,
                s32, f32, f32, f32);
void fn_8001EEE0(s32, s32, s32, s32, s32);
void fn_8001FA54(s32, s32, s32, s32, s32);
void fn_8001EDE0(s32, s32, s32, s32);
void fn_8001E6F0(s32, s32, s32, s32, s32);
void fn_8001FAA4(s32, s32, s32, s32, s32);
void fn_8001E2FC(s32, s32, s32, s32, s32, s32, s32);
void fn_8001E3CC(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
void fn_8001E4E8(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
void fn_8001F2D8(s32, ...);
void fn_8001E248(s32, s32, s32, s32, s32, s32, s32);
void set_blend_mode(s32, u32, s32);
s32 fn_8001EFBC(s32, s32 *);
void fn_8001F0A0(s32, s32, s32);
void fn_8001F0F8(f32, f32, f32);
void fn_8001F1D4(s32);
void fn_8001F200(f32, f32);
void fn_8001F0F4(void);

/* the per-vertex attribute block hanging off arg0+0x44 */
typedef struct {
    char _p[6];
    u8  b6;
    u8  b7;
    u8  b8;
    u8  b9;
    u16 hA;
    char _pC[4];
    s32  w10;
    s32  w14;
} LT_t;

/* arg0: 0x28 = f32[12], 0x30 = s32[4], 0x34 = f32[8], 0x3C = kind,
 *       0x44 = LT_t *, 0x48 = handle */
typedef struct {
    char  _p00[0x28];
    f32  *v28;
    char  _p2C[4];
    f32  *v30;
    f32  *v34;
    char  _p38[4];
    s32   kind;
    char  _p40[4];
    LT_t *lt;
    s32 h48;
} T98;

void fn_8009BC98(T98 *arg0) {
    s32 sp40;
    volatile f32 sp20;
    volatile f32 sp24;
    volatile f32 sp28;
    volatile f32 sp2C;
    volatile f32 sp30;
    volatile f32 sp34;
    volatile f32 sp38;
    volatile f32 sp3C;
    s32 sp18;
    s32 sp14;
    s32 sp10;
    s32 spC;
    s32 sp8;
    f32 temp_f0;
    f32 temp_f1;
    s32 temp_r0;
    s32 temp_r0_2;
    s32 var_r0;
    s32 var_r24;
    s32 var_r25;
    s32 var_r27;
    s32 var_r28;
    s32 *p30;
    volatile f32 *p34;
    f32 *v28;
    register LT_t *p44 __asm__("r9");
    f32 var_f1;
    f32 var_f2;
    register s32 one __asm__("r30");
    register s32 zero __asm__("r29");

    temp_r0 = arg0->kind;
    switch (temp_r0) {
    case 0:
        var_r0 = 2;
        goto block_9;
    case 2:
        var_r0 = 3;
        goto block_9;
    case 4:
        var_r0 = 4;
    block_9:
        p30 = arg0->v30;
        var_r24 = 0;
        var_r25 = 0;
        if (p30 != NULL) {
            var_r27 = p30[0];
            var_r28 = p30[1];
            if (var_r0 > 2) {
                var_r24 = p30[2];
            }
            if (var_r0 > 3) {
                var_r25 = p30[3];
            }
        } else {
            var_r28 = arg0->h48;
            var_r25 = var_r28;
            var_r27 = var_r28;
            var_r24 = var_r25;
        }
        p34 = arg0->v34;
        if (p34 != NULL) {
            sp20 = p34[0];
            sp30 = p34[1];
            sp24 = p34[2];
            sp34 = p34[3];
            if (var_r0 > 2) {
                sp28 = p34[4];
                sp38 = p34[5];
            }
            if (var_r0 > 3) {
                p34 = *(f32 * volatile *)&arg0->v34;
                sp2C = p34[6];
                sp3C = p34[7];
            }
        } else {
            temp_f0 = lbl_80297734;
            sp20 = temp_f0;
            sp3C = temp_f0;
            sp2C = temp_f0;
            sp38 = temp_f0;
            sp28 = temp_f0;
            sp34 = temp_f0;
            sp24 = temp_f0;
            sp30 = temp_f0;
        }
        one = 1;
        zero = 0;
        sp8 = one;
        spC = zero;
        sp10 = zero;
        sp14 = zero;
        sp18 = zero;
        p44 = arg0->lt;
        temp_f1 = lbl_80297734;
        fn_8001EA14(p44->w10, (u16) (one << p44->b6), (u16) (one << p44->b7),
                    p44->b9, 0, 0, 0, 1, sp8, spC, sp10, sp14, sp18, temp_f1,
                    temp_f1, temp_f1);
        p44 = arg0->lt;
        if ((p44->hA & 2) && (p44->w14 != 0)) {
            sp8 = one;
            spC = zero;
            sp10 = zero;
            sp14 = zero;
            sp18 = one;
            temp_f1 = lbl_80297734;
            fn_8001EA14(p44->w14, (u16) (one << p44->b6), (u16) (one << p44->b7),
                        p44->b9, 0, 0, 0, 1, sp8, spC, sp10, sp14, sp18,
                        temp_f1, temp_f1, temp_f1);
            fn_8001EEE0(2, 1, 2, 0, 0);
            fn_8001FA54(4, 0, 0, 4, 0);
            p44 = arg0->lt;
            fn_8001EDE0(0, 1, (u16) (one << p44->b6), (u16) (one << p44->b7));
            p44 = arg0->lt;
            fn_8001EDE0(1, 1, (u16) (one << p44->b7), (u16) (one << p44->b6));
            fn_8001E6F0(0, 1, 4, 0, 0x7D);
            fn_8001E6F0(1, 1, 4, 0, 0x7D);
            fn_8001FAA4(0, 0x3C, 0x3C, 0x3C, 0x3C);
            fn_8001E2FC(0, 0, 0, 4, 1, 1, 4);
            sp8 = one;
            spC = one;
            sp10 = zero;
            sp14 = zero;
            fn_8001E3CC(0, 7, 4, 5, 7, 0, 0, 1, sp8, spC, sp10, sp14);
            sp8 = one;
            spC = one;
            fn_8001E4E8(0, 0xF, 0xA, 8, 0xF, 0, 0, 1, sp8, spC);
            sp8 = one;
            spC = zero;
            sp10 = zero;
            sp14 = one;
            fn_8001E3CC(1, 7, 4, 5, 7, 0, 0, 1, sp8, spC, sp10, sp14);
            sp8 = one;
            spC = zero;
            fn_8001E4E8(1, 0xF, 0xF, 0xF, 2, 0, 0, 0, sp8, spC);
        } else {
            fn_8001EEE0(1, 1, 1, 0, 0);
            fn_8001FA54(4, 0, 0, 4, 0);
            p44 = arg0->lt;
            fn_8001EDE0(0, 1, (u16) (one << p44->b6), (u16) (one << p44->b7));
            fn_8001E6F0(0, 1, 4, 0, 0x7D);
            fn_8001FAA4(0, 0x3C, 0x3C, 0x3C, 0x3C);
            fn_8001E2FC(0, 0, 0, 4, 0, 0xFF, 0xFF);
            sp8 = 1;
            spC = 0;
            sp10 = 0;
            sp14 = 0;
            fn_8001E3CC(0, 7, 4, 5, 7, 0, 0, 1, sp8, spC, sp10, sp14);
            sp8 = 1;
            spC = 0;
            fn_8001E4E8(0, 0xF, 0xA, 8, 0xF, 0, 0, 1, sp8, spC);
        }
        fn_8001F2D8(3, 9, 1, 0xD, 1, 0xB, 1);
        fn_8001E248(4, 1, 1, 0, 0, 0, 2);
        set_blend_mode(0, 5, 0);
        sp40 = -1;
        fn_8001EFBC(4, &sp40);
        temp_r0_2 = arg0->kind;
        switch (temp_r0_2) {
        case 0:
            fn_8001F0A0(0xA8, 0, 2);
            v28 = arg0->v28;
            fn_8001F0F8(v28[0], v28[1], v28[2]);
            fn_8001F1D4(var_r27);
            fn_8001F200(sp20, sp30);
            v28 = arg0->v28;
            fn_8001F0F8(v28[3], v28[4], v28[5]);
            fn_8001F1D4(var_r28);
            var_f1 = sp24;
            var_f2 = sp34;
            goto block_33;
        case 2:
            fn_8001F0A0(0x90, 0, 3);
            v28 = arg0->v28;
            fn_8001F0F8(v28[0], v28[1], v28[2]);
            fn_8001F1D4(var_r27);
            fn_8001F200(sp20, sp30);
            v28 = arg0->v28;
            fn_8001F0F8(v28[3], v28[4], v28[5]);
            fn_8001F1D4(var_r28);
            fn_8001F200(sp24, sp34);
            v28 = arg0->v28;
            fn_8001F0F8(v28[6], v28[7], v28[8]);
            fn_8001F1D4(var_r24);
            var_f1 = sp28;
            var_f2 = sp38;
        block_33:
            fn_8001F200(var_f1, var_f2);
            fn_8001F0F4();
            return;
        case 4:
            fn_8001F0A0(0x80, 0, 4);
            v28 = arg0->v28;
            fn_8001F0F8(v28[0], v28[1], v28[2]);
            fn_8001F1D4(var_r27);
            fn_8001F200(sp20, sp30);
            v28 = arg0->v28;
            fn_8001F0F8(v28[3], v28[4], v28[5]);
            fn_8001F1D4(var_r28);
            fn_8001F200(sp24, sp34);
            v28 = arg0->v28;
            fn_8001F0F8(v28[6], v28[7], v28[8]);
            fn_8001F1D4(var_r24);
            fn_8001F200(sp28, sp38);
            v28 = arg0->v28;
            fn_8001F0F8(v28[9], v28[10], v28[11]);
            fn_8001F1D4(var_r25);
            fn_8001F200(sp2C, sp3C);
            fn_8001F0F4();
            return;
        }
        break;
    }
}
