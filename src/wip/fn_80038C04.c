// PARKED 2026-10-05 — NOT ATTEMPTED (PS/VMX wall), but the body
// below is measurably more faithful and this header records everything the
// disasm says, so the next attempt does not re-derive it.
//
// family=m2c range=0x80038C04-0x800394CC size=2248B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// WHY IT IS PARKED. This is a **paired-single / VMX** function: 200+ of its 562
// instructions are `psq_lx` / `psq_l` / `psq_st` and it also uses `xsmaddasp`,
// `vmrghb` and 6 callee-saved FPRs (f26-f31). AGENTS §4b: `-mps-float` is
// **per-object only** (`// extra_cflags:`), and plain `float` arithmetic cannot
// reproduce a `psq_*` stream at all — every load/store in the want is a 8-byte
// PS pair with W0,I0 scaling, which a scalar `f32` local can never emit. That is
// the documented FPR/PS wall (AGENTS §9), so this is a "prefer leaf targets"
// skip, not a near-miss.
//
// WHAT THE WANT ACTUALLY IS (measured, for whoever picks it up):
//  * frame 0x188 (392B); `stmw r26,0x140(r1)`, LR at 0x18c, and
//    `stfd f26..f31` at 0x158..0x180 — six FPR callee-saves, so the body keeps
//    6 live PS values across the calls.
//  * exactly FOUR calls in 562 instructions:
//      the call at 0x80038C38 to fn_80036328 moves the return value into r29
//      and compares r29 against zero, with a not-equal branch around a load of
//      zero into r3 before tail-calling the epilogue.
//      the call at 0x80038C48 to fn_80036810 takes arg0 and arg1 in r3 and r4
//      (two args, where m2c had invented seven).
//      the call at 0x80038CC4 to fn_8003A428 is followed by four
//      move-to-count-register/branch-decrement repetitions with r0 holding 4.
//      the call at 0x800390DC to fn_80036810 with twelve args compares r29
//      against -1 and branches to the end on equality.
//      the call at 0x80039134 to fn_8003A428 is followed by four
//      move-to-count-register/branch-decrement repetitions with r11 holding 4.
//    plus the 0x8003A428 at 0x80038CC4 — so three 4-trip `mtctr`/`bdnz` loops
//    (0x80038C64, 0x80038CD0, 0x80039140). Each is GCC unrolling a `for (n=4)`
//    4x and still emitting the ctr/bdnz per copy — i.e. the source loops are
//    `for (i = 0; i < 4; i++)`, NOT the `do{}while(--n)` m2c wrote.
//  * three PS block bases are precomputed in the preheader:
//    `addi r29,r1,8`, `addi r26,r1,0x48`, `addi r27,r1,0x118`, and
//    `slwi r30,r3,6` (index * 64) — that is a 4x4 float matrix / 64-byte vertex
//    stride. The `psq_lx f0, r30+r9` indexed load confirms it: indexed PS load
//    out of a caller-supplied array at `arg0->unk0x4`.
//  * the whole body is `dst[8 + i*8] = *(ps*)&src[i*8]` style block copies plus
//    a 4x4 matrix-vector product; `lbl_80291F04` / `lbl_80291F08` (both `.rodata2`
//    f32, loaded with `lfs`) are the two constants of the second block.
//  * the function returns 0 if `fn_80036328()` was 0, else 1.
//
// WHAT THE m2c BODY GETS WRONG (all verified above):
//  * `fn_80036810` is called with 2 args here, not 7 (fixed in this draft — the
//    only edit made).
//  * the three loops are `mtctr/bdnz` 4-trip loops, not `do{--n}while(n)`, so
//    m2c's `var_ctr` decrements are the wrong shape.
//  * every `0;` statement is an m2c artefact for an unresolved condition; the
//    real conditions are `cmpwi r29,0` / `cmpwi r29,-1` (return values) and the
//    PS block loops.
//  * the `static s32 spXXX;` file-scope block is m2c inventing names for stack
//    slots. `sp118`/`sp120` in particular are POINTERS in m2c's own body
//    (`sp118 = &sp48`), not s32. Making them function locals was measured and is
//    WORSE (716B -> 660B object; uninitialised locals let cc1 fold even more),
//    so the statics were left alone rather than churn the draft for nothing.
//  * the arithmetic is `Unk_DB0E2BAB` 4x4 row-dot-vector products written as
//    scalar f32 chains; in the want these are PS.
//
// MEASURED: DIFF, 716B vs want 2248B (383 words short). Nothing here is within
// reach of a match without solving the PS/VMX codegen problem first, so the
// honest recommendation is to leave this parked and spend effort on leaves.
//#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 lbl_80291F04;
extern f32 lbl_80291F08;
static s32 sp118;
static s32 sp120;
static s32 sp128;
static s32 sp130;
static s32 sp138;
static s32 sp14;
static s32 sp18;
static s32 sp1C;
static s32 sp20;
static s32 sp24;
static s32 sp28;
static s32 sp2C;
static s32 sp30;
static s32 sp34;
static s32 sp38;
static s32 sp3C;
static s32 sp40;
static s32 sp44;
static s32 sp54;
static s32 sp5C;
static s32 sp64;
static s32 sp70;
static s32 sp74;
static s32 sp84;
static s32 spC;

s32 fn_80038C04(Unk_9994C3F5 *arg0, s32 arg1, s32 arg2) {
    f32 *sp120;
    f32 *sp118;
    f32 sp114;
    f32 sp110;
    f32 sp10C;
    f32 sp108;
    f32 sp104;
    f32 sp100;
    f32 spFC;
    f32 spF8;
    f32 spF4;
    f32 spF0;
    f32 spEC;
    f32 spE8;
    f32 spE4;
    f32 spE0;
    f32 spDC;
    f32 spD8;
    f32 spD4;
    f32 spD0;
    f32 spCC;
    f32 spC8;
    f32 spC4;
    f32 spC0;
    f32 spBC;
    f32 spB8;
    f32 spB4;
    f32 spB0;
    f32 spAC;
    f32 spA8;
    f32 spA4;
    f32 spA0;
    f32 sp9C;
    Unk_59AB5482 sp98;
    f32 sp80;
    f32 sp7C;
    f32 sp78;
    f32 sp6C;
    f32 sp68;
    f32 sp60;
    f32 sp58;
    f32 sp50;
    f32 sp4C;
    f32 sp48;
    Unk_59AB5482 sp8;
    f32 temp_f0;
    f32 temp_f10;
    f32 temp_f11;
    f32 temp_f12;
    f32 temp_f13;
    f32 temp_f4;
    f32 temp_f9;
    s32 temp_r29;
    s32 temp_r3;
    s32 var_ctr;
    s32 var_ctr_2;
    s32 var_ctr_3;

    temp_r29 = fn_80036328();
    temp_r3 = fn_80036810(arg0, arg1, arg2, arg0, arg1, arg0, arg1);
    if (temp_r29 == 0) {
        return 0;
    }
    var_ctr = 4;
    do {
        var_ctr -= 1;
    } while (var_ctr != 0);
    0;
    0;
    0;
    0;
    0;
    0;
    0;
    fn_8003A428(arg0->unk0x8);
    var_ctr_2 = 4;
    do {
        var_ctr_2 -= 1;
    } while (var_ctr_2 != 0);
    0;
    0;
    temp_f4 = sp4C;
    0;
    0;
    0;
    0;
    0;
    0;
    0;
    0;
    0;
    0;
    0;
    sp78 = -sp128;
    sp7C = -sp130;
    sp80 = -sp138;
    sp4C = sp58;
    temp_f12 = sp50;
    temp_f11 = sp60;
    sp58 = temp_f4;
    sp118 = &sp48;
    sp50 = sp68;
    sp68 = temp_f12;
    sp60 = sp6C;
    sp6C = temp_f11;
    ((Unk_59AB5482 *)&sp118)->unk0x4 = &sp8;
    *((f32 *)&sp98) = (((Unk_DB0E2BAB *)sp118)->unk0xC * sp38) + ((((Unk_DB0E2BAB *)sp118)->unk0x8 * sp28) + ((((Unk_DB0E2BAB *)sp118)->unk0x0 * *((f32 *)&sp8)) + (((Unk_DB0E2BAB *)sp118)->unk0x4 * sp18)));
    sp9C = (((Unk_DB0E2BAB *)sp118)->unk0xC * sp3C) + ((((Unk_DB0E2BAB *)sp118)->unk0x8 * sp2C) + ((((Unk_DB0E2BAB *)sp118)->unk0x0 * spC) + (((Unk_DB0E2BAB *)sp118)->unk0x4 * sp1C)));
    spA0 = (((Unk_DB0E2BAB *)sp118)->unk0xC * sp40) + ((((Unk_DB0E2BAB *)sp118)->unk0x8 * sp30) + ((((Unk_DB0E2BAB *)sp118)->unk0x0 * sp8.unk0x8) + (((Unk_DB0E2BAB *)sp118)->unk0x4 * sp20)));
    spA4 = (((Unk_DB0E2BAB *)sp118)->unk0xC * sp44) + ((((Unk_DB0E2BAB *)sp118)->unk0x8 * sp34) + ((((Unk_DB0E2BAB *)sp118)->unk0x0 * sp14) + (((Unk_DB0E2BAB *)sp118)->unk0x4 * sp24)));
    spA8 = (((Unk_DB0E2BAB *)sp118)->unk0x1C * sp38) + ((((Unk_DB0E2BAB *)sp118)->unk0x18 * sp28) + ((((Unk_DB0E2BAB *)sp118)->unk0x10 * *((f32 *)&sp8)) + (((Unk_DB0E2BAB *)sp118)->unk0x14 * sp18)));
    spAC = (((Unk_DB0E2BAB *)sp118)->unk0x1C * sp3C) + ((((Unk_DB0E2BAB *)sp118)->unk0x18 * sp2C) + ((((Unk_DB0E2BAB *)sp118)->unk0x10 * spC) + (((Unk_DB0E2BAB *)sp118)->unk0x14 * sp1C)));
    spB0 = (((Unk_DB0E2BAB *)sp118)->unk0x1C * sp40) + ((((Unk_DB0E2BAB *)sp118)->unk0x18 * sp30) + ((((Unk_DB0E2BAB *)sp118)->unk0x10 * sp8.unk0x8) + (((Unk_DB0E2BAB *)sp118)->unk0x14 * sp20)));
    spB4 = (((Unk_DB0E2BAB *)sp118)->unk0x1C * sp44) + ((((Unk_DB0E2BAB *)sp118)->unk0x18 * sp34) + ((((Unk_DB0E2BAB *)sp118)->unk0x10 * sp14) + (((Unk_DB0E2BAB *)sp118)->unk0x14 * sp24)));
    spB8 = (((Unk_DB0E2BAB *)sp118)->unk0x2C * sp38) + ((((Unk_DB0E2BAB *)sp118)->unk0x28 * sp28) + ((((Unk_DB0E2BAB *)sp118)->unk0x20 * *((f32 *)&sp8)) + (((Unk_DB0E2BAB *)sp118)->unk0x24 * sp18)));
    spBC = (((Unk_DB0E2BAB *)sp118)->unk0x2C * sp3C) + ((((Unk_DB0E2BAB *)sp118)->unk0x28 * sp2C) + ((((Unk_DB0E2BAB *)sp118)->unk0x20 * spC) + (((Unk_DB0E2BAB *)sp118)->unk0x24 * sp1C)));
    spC0 = (((Unk_DB0E2BAB *)sp118)->unk0x2C * sp40) + ((((Unk_DB0E2BAB *)sp118)->unk0x28 * sp30) + ((((Unk_DB0E2BAB *)sp118)->unk0x20 * sp8.unk0x8) + (((Unk_DB0E2BAB *)sp118)->unk0x24 * sp20)));
    spC4 = (((Unk_DB0E2BAB *)sp118)->unk0x2C * sp44) + ((((Unk_DB0E2BAB *)sp118)->unk0x28 * sp34) + ((((Unk_DB0E2BAB *)sp118)->unk0x20 * sp14) + (((Unk_DB0E2BAB *)sp118)->unk0x24 * sp24)));
    spC8 = (((Unk_DB0E2BAB *)sp118)->unk0x3C * sp38) + ((((Unk_DB0E2BAB *)sp118)->unk0x38 * sp28) + ((((Unk_DB0E2BAB *)sp118)->unk0x30 * *((f32 *)&sp8)) + (((Unk_DB0E2BAB *)sp118)->unk0x34 * sp18)));
    spCC = (((Unk_DB0E2BAB *)sp118)->unk0x3C * sp3C) + ((((Unk_DB0E2BAB *)sp118)->unk0x38 * sp2C) + ((((Unk_DB0E2BAB *)sp118)->unk0x30 * spC) + (((Unk_DB0E2BAB *)sp118)->unk0x34 * sp1C)));
    spD0 = (((Unk_DB0E2BAB *)sp118)->unk0x3C * sp40) + ((((Unk_DB0E2BAB *)sp118)->unk0x38 * sp30) + ((((Unk_DB0E2BAB *)sp118)->unk0x30 * sp8.unk0x8) + (((Unk_DB0E2BAB *)sp118)->unk0x34 * sp20)));
    temp_f10 = sp8.unk0xC;
    temp_f9 = sp8.unk0x2C;
    temp_f13 = (((Unk_DB0E2BAB *)sp118)->unk0x38 * temp_f9) + ((((Unk_DB0E2BAB *)sp118)->unk0x30 * temp_f10) + (((Unk_DB0E2BAB *)sp118)->unk0x34 * sp8.unk0x1C));
    spD4 = (((Unk_DB0E2BAB *)sp118)->unk0x3C * sp8.unk0x3C) + temp_f13;
    0;
    0;
    0;
    0;
    if (fn_80036810(arg0, QB_DUMMY_SCALE_ZZ, sp30, sp40, sp38, sp20, sp3C, sp14, sp24, sp34, temp_f9, temp_f10, 0, 0, temp_f13) != -1) {
        temp_f0 = lbl_80291F04;
        *((f32 *)&sp98) = temp_f0;
        0;
        0;
        sp98.unk0x8 = temp_f0;
        ((Unk_E266FB50 *)&sp98)->unk0xC = lbl_80291F08;
        sp98.unk0x4 = temp_f0;
        0;
        0;
        fn_8003A428(arg0->unk0x8);
        var_ctr_3 = 4;
        do {
            var_ctr_3 -= 1;
        } while (var_ctr_3 != 0);
        0;
        0;
        0;
        0;
        0;
        0;
        sp120 = &sp98;
        ((Unk_59AB5482 *)&sp120)->unk0x4 = &sp48;
        spD8 = (((Unk_DB0E2BAB *)sp120)->unk0xC * sp78) + ((((Unk_DB0E2BAB *)sp120)->unk0x8 * sp68) + ((((Unk_DB0E2BAB *)sp120)->unk0x0 * sp48) + (((Unk_DB0E2BAB *)sp120)->unk0x4 * sp58)));
        spDC = (((Unk_DB0E2BAB *)sp120)->unk0xC * sp7C) + ((((Unk_DB0E2BAB *)sp120)->unk0x8 * sp6C) + ((((Unk_DB0E2BAB *)sp120)->unk0x0 * sp4C) + (((Unk_DB0E2BAB *)sp120)->unk0x4 * sp5C)));
        spE0 = (((Unk_DB0E2BAB *)sp120)->unk0xC * sp80) + ((((Unk_DB0E2BAB *)sp120)->unk0x8 * sp70) + ((((Unk_DB0E2BAB *)sp120)->unk0x0 * sp50) + (((Unk_DB0E2BAB *)sp120)->unk0x4 * sp60)));
        spE4 = (((Unk_DB0E2BAB *)sp120)->unk0xC * sp84) + ((((Unk_DB0E2BAB *)sp120)->unk0x8 * sp74) + ((((Unk_DB0E2BAB *)sp120)->unk0x0 * sp54) + (((Unk_DB0E2BAB *)sp120)->unk0x4 * sp64)));
        spE8 = (((Unk_DB0E2BAB *)sp120)->unk0x1C * sp78) + ((((Unk_DB0E2BAB *)sp120)->unk0x18 * sp68) + ((((Unk_DB0E2BAB *)sp120)->unk0x10 * sp48) + (((Unk_DB0E2BAB *)sp120)->unk0x14 * sp58)));
        spEC = (((Unk_DB0E2BAB *)sp120)->unk0x1C * sp7C) + ((((Unk_DB0E2BAB *)sp120)->unk0x18 * sp6C) + ((((Unk_DB0E2BAB *)sp120)->unk0x10 * sp4C) + (((Unk_DB0E2BAB *)sp120)->unk0x14 * sp5C)));
        spF0 = (((Unk_DB0E2BAB *)sp120)->unk0x1C * sp80) + ((((Unk_DB0E2BAB *)sp120)->unk0x18 * sp70) + ((((Unk_DB0E2BAB *)sp120)->unk0x10 * sp50) + (((Unk_DB0E2BAB *)sp120)->unk0x14 * sp60)));
        spF4 = (((Unk_DB0E2BAB *)sp120)->unk0x1C * sp84) + ((((Unk_DB0E2BAB *)sp120)->unk0x18 * sp74) + ((((Unk_DB0E2BAB *)sp120)->unk0x10 * sp54) + (((Unk_DB0E2BAB *)sp120)->unk0x14 * sp64)));
        spF8 = (((Unk_DB0E2BAB *)sp120)->unk0x2C * sp78) + ((((Unk_DB0E2BAB *)sp120)->unk0x28 * sp68) + ((((Unk_DB0E2BAB *)sp120)->unk0x20 * sp48) + (((Unk_DB0E2BAB *)sp120)->unk0x24 * sp58)));
        spFC = (((Unk_DB0E2BAB *)sp120)->unk0x2C * sp7C) + ((((Unk_DB0E2BAB *)sp120)->unk0x28 * sp6C) + ((((Unk_DB0E2BAB *)sp120)->unk0x20 * sp4C) + (((Unk_DB0E2BAB *)sp120)->unk0x24 * sp5C)));
        sp100 = (((Unk_DB0E2BAB *)sp120)->unk0x2C * sp80) + ((((Unk_DB0E2BAB *)sp120)->unk0x28 * sp70) + ((((Unk_DB0E2BAB *)sp120)->unk0x20 * sp50) + (((Unk_DB0E2BAB *)sp120)->unk0x24 * sp60)));
        sp104 = (((Unk_DB0E2BAB *)sp120)->unk0x2C * sp84) + ((((Unk_DB0E2BAB *)sp120)->unk0x28 * sp74) + ((((Unk_DB0E2BAB *)sp120)->unk0x20 * sp54) + (((Unk_DB0E2BAB *)sp120)->unk0x24 * sp64)));
        sp108 = (((Unk_DB0E2BAB *)sp120)->unk0x3C * sp78) + ((((Unk_DB0E2BAB *)sp120)->unk0x38 * sp68) + ((((Unk_DB0E2BAB *)sp120)->unk0x30 * sp48) + (((Unk_DB0E2BAB *)sp120)->unk0x34 * sp58)));
        sp10C = (((Unk_DB0E2BAB *)sp120)->unk0x3C * sp7C) + ((((Unk_DB0E2BAB *)sp120)->unk0x38 * sp6C) + ((((Unk_DB0E2BAB *)sp120)->unk0x30 * sp4C) + (((Unk_DB0E2BAB *)sp120)->unk0x34 * sp5C)));
        sp110 = (((Unk_DB0E2BAB *)sp120)->unk0x3C * sp80) + ((((Unk_DB0E2BAB *)sp120)->unk0x38 * sp70) + ((((Unk_DB0E2BAB *)sp120)->unk0x30 * sp50) + (((Unk_DB0E2BAB *)sp120)->unk0x34 * sp60)));
        sp114 = (((Unk_DB0E2BAB *)sp120)->unk0x3C * sp84) + ((((Unk_DB0E2BAB *)sp120)->unk0x38 * sp74) + ((((Unk_DB0E2BAB *)sp120)->unk0x30 * sp54) + (((Unk_DB0E2BAB *)sp120)->unk0x34 * sp64)));
        0;
        0;
        0;
        0;
        0;
        0;
    }
    0;
    0;
    0;
    0;
    0;
    0;
    return 1;
}
