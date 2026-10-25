// WIP DRAFT — PARKED (non-matching). Hand-rebuilt from the want; the m2c draft
// had NO case labels on its switch, so all 12 arms folded into one block and it
// compiled to 464 B of 560 B at 37.93%.
// reproduce: LEAF_TMPDIR=<scratch> \
//     tools/venv/bin/python tools/want_got.py 0x80114F40  -> 544B / 120 diffs / 11.76%
//
// family=m2c range=0x80114F40-0x80115170 size=560B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// Progression: 464B/37.93% -> 516B -> 520B -> 524B -> 544B (16 B short).
//
// ------------------------------------------------------------------ decode
// A 12-way dispatch on `*(u8 *)(spC + 2)` after three hash/lookup calls:
//   sp8  = fn_801286D0(0x8F61D602, &sp8, 1)
//   spC  = fn_801285A4(*(arg1+0x18), sp8, &spC, 1)     <- FOUR args
//   fn_80128228(arg0, 0x7F8C98FE)
//   r30  = fn_801272AC(arg0, 0x4B40630D)
//   fn_8012B1C0();  fn_8009F4C4(0x10);  r29 = fn_801252BC();
//   fn_80126808(r30, 0)
// cases 1,2,3,4,5,6,0xA,0xC,0xD ; default -> shared exit
//
// FIVE decode corrections vs the m2c draft:
//  1. The three magic constants are literal 32-bit values, NOT `lis`-fragments:
//     0x8F61D602, 0x7F8C98FE, 0x4B40630D. Decode them by reading the `lis` and
//     `ori` words and OR-ing -- never by eye.
//  2. fn_801285A4 takes FOUR args (value, prev, &out, 1). The draft passed three.
//  3. Case 2's type test is `((v >> 9) & 0x7F) == 2` -- want emits
//     `rlwinm r0,r0,0,9,0x1f` then `cmpw r0,2`. Writing it as a plain mask
//     compare (`(v & 0x7E00) == 0x2000`) loses the shift and folds to a
//     different instruction entirely.
//  4. Case 2's else-branch builds an 8-byte stack PAIR at r1+0x18 (0x43300000
//     in the high word, sign-flipped value in the low), then `lfd f1,0x18(r1)`
//     and `fsub`/`frsp`. It is a `double` local, not a 4-byte union -- the union
//     spelling yields frame -0x28 instead of -0x30.
//  5. The common tail `emit:` stores through a table returned by
//     fn_801291FC(spC) using `stwx r9,r3,r0` (index register), i.e. an
//     INDEXED store, not a pointer bump.
//
// ------------------------------------------------------------------- parked
// Still 16 B short and the prologue differs in register choice: want holds
// arg0/arg1 in r29/r28 (mr r28,r4 / mr r29,r3) while got uses r28/r29 the other
// way round, which cascades into every field access through the wrong base.
// Not recovered. The frame is -0x28 vs want's -0x30 -- one local is still
// missing a dword, most likely a second f64-sized slot that the arms share.
// 2026-10-11: reverse-order arg copies
// (`void *a1=arg1; void *a0=arg0;` + using a0/a1) tried -- GCC coalesces them
// and still homes in arg order (mr r28,r3 first); 544B/120 diffs/11.76%
// unchanged. Reverted. The home swap + missing dword need a recipe.
#include "types.h"

typedef union F2 F2;
union F2 {
    s32 i;
    f32 f;
};

void fn_801286D0(s32, s32 *, s32);
void fn_801285A4(s32, s32, s32 *, s32);
void fn_80128228(void *, s32);
s32 fn_801272AC(void *, s32);
s32 fn_8012B1C0(void);
void *fn_8009F4C4(s32);
void *fn_801252BC(void);
void *fn_80126808(void *, s32);
void fn_80129260(s32, s32);
void fn_80129284(s32, f32);
void fn_801292A8(s32, s32);
void fn_8012935C(s32);
void fn_80125230(void);
void fn_80129504(s32);
void fn_80117CC0(void);
void fn_801294E0(s32);
void fn_80117D74(void);
s32 fn_80129528(s32);
void fn_8012701C(void *, s32);
s32 fn_8012954C(s32);
void fn_80126A30(void);
void fn_80128FB4(void *, s32);
s32 *fn_801291FC(s32);
void fn_80117E28(void *);

s32 fn_80114F40(void *arg0, void *arg1) {
    s32 sp8;
    s32 spC;
    s32 sp10;
    /* 8-byte slot: want does `lfd f1,0x18(r1)` after storing 0x43300000 at 0x18
       and the sign-flipped word at 0x1c, i.e. the pair is built as a DOUBLE and
       then narrowed with frsp. A 4-byte union gives frame -0x28, not -0x30. */
    union {
        f64 d;
        struct { s32 hi; s32 lo; } w;
    } sp18;
    s32 *r29;
    s32 r30;
    void *hold;

    sp8 = 0;
    fn_801286D0(0x8F61D602, &sp8, 1);

    spC = 0;
    fn_801285A4(*(s32 *)((char *)arg1 + 0x18), sp8, &spC, 1);

    sp10 = 0;
    fn_80128228(arg0, 0x7F8C98FE);

    r30 = fn_801272AC(arg0, 0x4B40630D);
    fn_8012B1C0();
    fn_8009F4C4(0x10);
    r29 = (s32 *)fn_801252BC();
    hold = fn_80126808((void *)r30, 0);

    switch (*(u8 *)((char *)spC + 2)) {
    case 1:
        fn_80129260(sp10, *(s32 *)((char *)r29 + 8));
        break;

    case 2:
        if (((*(s32 *)r29 >> 9) & 0x7F) == 2) {
            fn_80129284(sp10, *(f32 *)((char *)r29 + 8));
        } else {
            f32 d;
            sp18.d = *(f64 *)0x8029D1C8;
            sp18.w.hi = 0x43300000;
            sp18.w.lo = *(s32 *)((char *)r29 + 8) ^ 0x80000000;
            d = (f32)sp18.d;
            d = d - (f32)*(f64 *)0x8029D1C8;
            fn_80129284(sp10, d);
        }
        break;

    case 3:
    case 4:
        fn_8012935C(sp10);
        fn_80125230();
        goto emit;

    case 5:
        fn_80129504(sp10);
        fn_80117CC0();
        goto emit;

    case 6:
        fn_801294E0(sp10);
        fn_80117D74();
        goto emit;

    case 0xA:
        if (fn_80129528(sp10) != 0) {
            fn_8012701C(0, 3);
        }
        goto emit;

    case 0xC:
        r30 = fn_8012954C(sp10);
        fn_80126A30();
        if (r30 != 0) {
            fn_80128FB4((void *)r30, 3);
        }
        goto emit;

    case 0xD:
        fn_801292A8(sp10, *(s32 *)((char *)r29 + 8));
        break;

    default:
        break;
    }

emit:
    {
        s32 *tab = fn_801291FC(spC);
        tab[sp10] = *(s32 *)((char *)r29 + 8);
    }

    r29[0] = 0;
    fn_80117E28((void *)r29);
    return 1;
}