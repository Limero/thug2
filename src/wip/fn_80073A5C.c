// PARKED 2026-10-05 (w_80073A5C): best measured 14.29% masked (object 7680B
// vs symbol 7672B, +8B / +2 words), up from the 7.04% m2c baseline.
//
// WHAT WAS FIXED (all semantics, no casts):
//  1. CALLEE PROTOTYPES. m2c left ~30 of the 36 callees unprototyped. That
//     alone emitted 153 spurious `crclr cr1eq` words; the draft now declares
//     every one with a real arity/return type, leaving 7 crclr (retail has 6,
//     all before the genuinely-variadic fn_8001F2D8) — verified in the .o.
//  2. ARITY. fn_80016E18 is (s32,s32,s32,s32,s32): m2c passed 5/6/7 args at
//     three sites. fn_8001E3CC takes 12 args (8 GPR + 4 stack) and
//     fn_8001E4E8 takes 10 (8 GPR + 2 stack) — the draft only passed 8, so the
//     stack-arg block (r1+0x8..0x14) was never materialised.
//  3. THE 0x110-BYTE LOCAL AT r1+0x18. queue_front / Camera_orthographic /
//     fn_8001737C / fn_80016A88 all take this object; m2c typed it `s32 sp18`,
//     so ngccc sized the frame 0x68 instead of 0x180. A real `VObj` (0x110B)
//     local fixed the frame.
//  4. ARG1 FIELD TYPES. Unk_DB0E2BAB types 0x8/0xC/0x14/0x18/0x1C as s32, but
//     retail loads every one of them with `lfs`, never `lwz`. A local `A1`
//     struct with f32 at those offsets removed a whole int->float round-trip
//     cluster (+13 words) around the fn_8001F03C call. temp_r25 (the global
//     at 0x803016D8) is a DIFFERENT object whose fields ARE all s32 — typing
//     it as the same struct was a second, separate bug.
//  5. queue_front's 2nd arg is arg1, not arg0 (retail leaves r4 = the
//     incoming r4 untouched across the call).
//  6. The int->double idiom: m2c modelled r1+0x140 as two independent s32
//     (sp140/sp144). It is one 8-byte union{u32 w[2]; f64 d;}. Writing it as
//     a union removed the last spurious `lfd f31` hoist-to-callee-saved.
//
// RESIDUAL (why it is not closed):
//  * +2 words over the symbol, so the score is length-clamped.
//  * The prologue still differs: want `stwu r1,-0x180 / stmw r19,0x14c` with
//    NO callee-saved FPR; got has `stwu -0x178 / stfd f31 / stmw r18`.
//    One extra callee-saved GPR (r18 vs r19) and one callee-saved FPR push
//    every frame offset and every later register choice.
//  * The `*(f64*)0x80295610` constant is hoisted ONCE into f31 by ngccc;
//    retail re-loads it at each use (`lfd f8,0x5610(r9)` / `lfd f11,...`).
//    That single hoist is what forces the f31 save, the +8B frame, the extra
//    GPR, and the whole downstream register-assignment skew.
//  * Block structure now matches well (see the bl-aligned segment map: the
//    running delta is within +-10 words of zero from 0x800741e8 onward), but
//    individual blocks still pick different callee-saved registers: e.g. at
//    0x800740F4 want stores `r28` into 0x8(r1)/0xc(r1) where got stores
//    `r31`/`r29` — same 13-word shape, different register homes.
//  * fn_80073828 at 0x80074828 is 14 words vs want's 6 (the *(s32*)0x80301690
//    4th arg plus two float loads); not yet diagnosed.
//
// RULED OUT (measured, not guessed):
//  * `temp_f1 = *(s32*)0x802955F8` vs `*(f32*)`: the s32 read is LOAD-BEARING.
//    Changing it to f32 collapses the score 14.29% -> 2.73% (the compiler then
//    CSEs the two `fmr f2,f1` uses away). Same for `var_f7`. Kept as-is.
//  * The 7 copy-filter bytes as one `struct{s8 a..g}` instead of seven scalars:
//    10.27% (worse than 14.29%). Reversed source order of the seven scalar
//    stores: identical 14.29%, i.e. that block is not order-sensitive yet.
//  * Splitting temp_r25 out into its own all-s32 struct dropped the score to
//    9.19% while fixing the size, so it was kept only together with the union
//    fix (v6), not alone.
//
// NEXT LEVER: the f31 hoist. Retail reloading `lbl_80295610` per use means the
// source value is not loop-invariant in the original; a `volatile f64 *`
// load or splitting the two subtraction sites into separately-read temporaries
// is the obvious next experiment. NOT attempted — it risks the load-bearing
// f32/s32 pattern above and would need per-site re-measurement.
// family=m2c range=0x80073A5C-0x80075854 size=7672B
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

/* The 0x110-byte object at r1+0x18 that is handed to queue_front /
   Camera_orthographic / fn_8001737C / fn_80016A88.  Declared as its own
   struct so the compiler sizes the frame slot (0x18..0x127) correctly. */
typedef struct VObj {
    char pad0[0x110];
} VObj;

/* --- real prototypes: every callee below is PROTOTYPED.  m2c left ~30 of
   them implicit, which makes ngccc emit `crclr cr1eq` before each bl
   (153 spurious words) and guess the arg widths. --- */
void queue_front(VObj *, void *);
void Camera_orthographic(VObj *, s32, s32, s32, s32);
void fn_8001737C(VObj *);
void fn_80016A88(VObj *, s32);
void fn_80016B50(s32, s32, s32, s32, s32);
void fn_80016C70(void);
void fn_80016E18(s32, s32, s32, s32, s32);
s32 fn_80016EAC(s32);
s32 fn_80016EC4(s32);
void fn_8001E1D4(s32, s32, s32);
void fn_8001E248(s32, s32, s32, s32, s32, s32, s32);
void fn_8001E2FC(s32, s32, s32, s32, s32, s32, s32);
void fn_8001E3CC(s32, s32, s32, s32, s32, s32, s32, s32, u8, s32, s32, s32);
void fn_8001E4E8(s32, s32, s32, s32, s32, s32, s32, s32, u8, s32);
void fn_8001E5DC(u32, s32, s32, s32, s32);
void fn_8001E66C(s32, u32 *);
void fn_8001E6F0(s32, s32, s32, s32, s32);
void fn_8001E968(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
void fn_8001EDE0(s32, s32, s32, s32);
void fn_8001EEE0(s32, s32, s32, s32, s32);
void fn_8001EF84(s32, s32 *);
void fn_8001EFBC(s32, s32 *);
void fn_8001F03C(s32, void *, f32, f32, f32, f32);
void fn_8001F298(s32, s32, s32);
void fn_8001F2D8(s32, ...);
void fn_8001FA54(s32, s32, s32, s32, s32);
void fn_8001FAA4(s32, s32, s32, s32, s32);
void SetTevSwapModeTable(u32, s32, s32, s32, s32);
void GX_SetCopyFilter(s32, s32, s32, void *);
void GX_InvalidateTexAll(void);
void fn_8006EC34(void);
void fn_8007272C(s32);
void fn_80073828(s32, s32, s32, s32, f32, f32);
void fn_80073880(s32, s32, s32, s32);
void set_blend_mode(s32, s32, s32);

/* arg1's fields at 0x8/0xC/0x14/0x18/0x1C are FLOAT in the retail binary
   (they are loaded with `lfs`, never `lwz`), so the shared Unk_DB0E2BAB
   (all-s32) makes ngccc emit int->float round-trips at every use site. */
typedef struct A1 {
    s32 unk0x0;
    s32 unk0x4;
    f32 unk0x8;
    f32 unk0xC;
    s32 unk0x10;
    f32 unk0x14;
    f32 unk0x18;
    f32 unk0x1C;
    s32 unk0x20;
    s32 unk0x24;
    s32 unk0x28;
} A1;
/* The global at 0x803016D8 (temp_r25) is a table of s32 tex handles; all of
   its fields are loaded with `lwz`, so it must NOT be the same struct as arg1. */
typedef struct Tbl {
    s32 unk0x0;
    char pad0x4[0xC];
    s32 unk0x10;
    s32 unk0x14;
    s32 unk0x18;
    s32 unk0x1C;
    char pad0x20[0x4];
    s32 unk0x24;
    s32 unk0x28;
} Tbl;
void fn_80073A5C(CStruct *arg0, A1 *arg1) {
    VObj sp18;
    s32 sp128;
    s8 sp136;
    s8 sp135;
    s8 sp134;
    s8 sp133;
    s8 sp132;
    s8 sp131;
    s8 sp130;
    /* retail keeps an 8-byte int/double union slot at r1+0x140 */
    union { u32 w[2]; f64 d; } sp140;
    s32 sp8;
    s32 spC;
    s32 sp10;
    s32 sp14;
    f32 temp_f10;
    f32 temp_f10_2;
    f32 temp_f13;
    f32 temp_f13_2;
    f32 temp_f1;
    f32 temp_f6;
    f32 var_f7;
    s16 *var_r10;
    s16 *var_r10_2;
    s16 *var_r9;
    s32 temp_r11;
    s32 temp_r11_2;
    s32 temp_r11_3;
    s32 temp_r6;
    s32 temp_r7;
    s32 var_ctr;
    s32 var_ctr_2;
    s32 var_ctr_3;
    s32 var_ctr_4;
    u16 temp_r30_2;
    u16 temp_r30_3;
    u16 temp_r5;
    u8 temp_r29;
    u8 temp_r30;
    Tbl *temp_r25;

    queue_front(&sp18, arg1);
    Camera_orthographic(&sp18, 0, 0, 0x280, 0x1C0);
    fn_8001737C(&sp18);
    fn_80016B50(7, -1, -1, -1, -1);
    fn_8001F298(0, 7, 0);
    fn_8001EEE0(1, 1, 1, 0, 0);
    fn_8001FA54(7, 0, 0, 7, 0);
    fn_8001E6F0(0, 1, 4, 0, 0x7D);
    fn_8001E6F0(1, 1, 4, 0, 0x7D);
    fn_8001E6F0(2, 1, 4, 0, 0x7D);
    fn_8001E6F0(3, 1, 4, 0, 0x7D);
    fn_8001E6F0(4, 1, 4, 0, 0x7D);
    fn_8001FAA4(0, 0x3C, 0x3C, 0x3C, 0x3C);
    fn_8001E2FC(0, 0, 0, 4, 0, 0, 4);
    fn_8001E2FC(1, 0, 0, 4, 0, 0, 4);
    fn_8001E2FC(2, 0, 0, 4, 0, 0, 4);
    fn_8001E2FC(3, 0, 0, 4, 0, 0, 4);
    fn_8001E2FC(4, 0, 0, 4, 0, 0, 4);
    sp128 = -1;
    fn_8001EFBC(4, &sp128);
    fn_8001F2D8(3, 9, 1, 0xD, 1, 0xB, 1);
    fn_8001E248(4, 1, 0, 0, 0, 0, 2);
    sp128 = -1;
    fn_8001EF84(4, &sp128);
    sp130 = 0x10;
    sp131 = 0;
    sp132 = 0;
    sp133 = 0x1F;
    sp134 = 0;
    sp135 = 0;
    sp136 = 0x10;
    GX_SetCopyFilter(0, 0, 0, &sp130);
    temp_r25 = (Tbl *)0x803016D8;
    fn_80016E18(temp_r25->unk0x0, 0, 4, 1, 1);
    GX_SetCopyFilter(0, 0, 0, NULL);
    fn_80016B50(7, -1, -1, -1, -1);
    fn_80073880(0, 0, 0, 0);
    fn_80073828(0, 0, 5, 0, *(f32 *)0x802955F8, *(f32 *)0x802955FC);
    fn_80016E18(temp_r25->unk0x1C, 7, 4, 1, 0);
    GX_InvalidateTexAll();
    fn_80073880(7, 0, 0, 0);
    fn_80073828(7, 7, 6, 0, *(f32 *)0x802955F8, *(f32 *)0x802955FC);
    fn_80016E18(temp_r25->unk0x1C, 7, 4, 1, 0);
    GX_InvalidateTexAll();
    fn_80073880(7, 0, 0, 0);
    fn_8001F298(0, 7, 0);
    fn_8001EEE0(1, 1, 1, 0, 0);
    fn_8001FA54(7, 0, 0, 7, 0);
    fn_8001E6F0(0, 1, 4, 0, 0x7D);
    fn_8001E6F0(1, 1, 4, 0, 0x7D);
    fn_8001E6F0(2, 1, 4, 0, 0x7D);
    fn_8001E6F0(3, 1, 4, 0, 0x7D);
    fn_8001E6F0(4, 1, 4, 0, 0x7D);
    fn_8001FAA4(0, 0x3C, 0x3C, 0x3C, 0x3C);
    fn_8001E2FC(0, 0, 0, 4, 0, 0, 4);
    fn_8001E2FC(1, 0, 0, 4, 0, 0, 4);
    fn_8001E2FC(2, 0, 0, 4, 0, 0, 4);
    fn_8001E2FC(3, 0, 0, 4, 0, 0, 4);
    fn_8001E2FC(4, 0, 0, 4, 0, 0, 4);
    sp128 = -1;
    fn_8001EFBC(4, &sp128);
    fn_8001F2D8(3, 9, 1, 0xD, 1, 0xB, 1);
    fn_8001E248(4, 1, 0, 0, 0, 0, 2);
    sp128 = -1;
    fn_8001EF84(4, &sp128);
    fn_80016B50(6, -1, -1, -1, -1);
    fn_8001E5DC(0, 0xC, 0x1C, 0xC, 0x1C);
    fn_8001E5DC(1, 0xC, 0x1C, 0xC, 0x1C);
    fn_8001E5DC(2, 0xC, 0x1C, 0xC, 0x1C);
    fn_8001E5DC(4, 0xD, 0x1D, 0xD, 0x1D);
    sp128 = arg0->unk0x4;
    fn_8001E66C(0, &sp128);
    sp128 = -1;
    fn_8001E66C(1, &sp128);
    fn_8001EEE0(1, 1, 5, 0, 0);
    SetTevSwapModeTable(3, 1, 0, 0, 0);
    sp8 = 1;
    spC = 1;
    sp10 = 0;
    sp14 = 0;
    fn_8001E3CC(0, 7, 4, 5, 7, 0, 0, 0, 1, 1, 0, 0);
    sp8 = 1;
    spC = 1;
    fn_8001E4E8(0, 8, 0xE, 0xD, 0xF, 8, 0, 0, 1, 1);
    sp8 = 1;
    sp10 = 3;
    spC = 1;
    sp14 = 0;
    fn_8001E3CC(1, 7, 4, 5, 7, 0, 0, 0, 1, 1, 3, 0);
    sp8 = 1;
    spC = 1;
    fn_8001E4E8(1, 8, 0xE, 0xD, 2, 8, 0, 0, 1, 1);
    sp8 = 1;
    sp10 = 2;
    spC = 1;
    sp14 = 0;
    fn_8001E3CC(2, 7, 4, 5, 7, 0, 0, 0, 1, 1, 2, 0);
    sp8 = 1;
    spC = 1;
    fn_8001E4E8(2, 8, 0xE, 0xD, 2, 8, 0, 0, 1, 1);
    sp8 = 1;
    sp10 = 0;
    spC = 1;
    sp14 = 0;
    fn_8001E3CC(3, 7, 4, 5, 7, 0, 0, 0, 1, 1, 0, 0);
    sp8 = 1;
    spC = 1;
    fn_8001E4E8(3, 0xF, 8, 2, 0xF, 0, 0, 0, 1, 1);
    sp8 = 1;
    spC = 0;
    sp10 = 0;
    sp14 = 0;
    fn_8001E3CC(4, 7, 4, 5, 7, 0, 0, 0, 1, 0, 0, 0);
    sp8 = 1;
    spC = 0;
    fn_8001E4E8(4, 0xF, 0xE, 2, 0xF, 0, 0, 0, 1, 0);
    fn_8007272C(0);
    SetTevSwapModeTable(3, 0, 0, 0, 0);
    fn_8001EEE0(1, 1, 1, 0, 0);
    if ((s32) *(s32 *)0x8030167C != 0) {
        sp8 = 1;
        spC = 0;
        sp10 = 0;
        sp14 = 0;
        fn_8001E3CC(0, 7, 4, 5, 7, 0, 0, 0, 1, 0, 0, 0);
        sp8 = 1;
        spC = 0;
        fn_8001E4E8(0, 0xF, 0xC, 0xF, 0xF, 0, 0, 0, 1, 0);
        fn_8007272C(0);
        sp8 = 1;
        spC = 0;
        sp10 = 0;
        sp14 = 0;
        fn_8001E3CC(0, 7, 4, 5, 7, 0, 0, 0, 1, 0, 0, 0);
        sp8 = 1;
        spC = 0;
        fn_8001E4E8(0, 0xF, 0xC, 0xD, 0xF, 0, 0, 0, 1, 0);
        fn_8007272C(4);
    }
    fn_80016E18(temp_r25->unk0x14, 6, 4, 1, 0);
    GX_InvalidateTexAll();
    fn_80073880(5, 0, 0, 0);
    if ((s32) *(s32 *)0x80301680 == 4) {
        fn_80016B50(0, -1, -1, -1, -1);
        sp8 = 1;
        spC = 0;
        sp10 = 0;
        sp14 = 0;
        fn_8001E3CC(0, 7, 4, 5, 7, 0, 0, 0, 1, 0, 0, 0);
        sp8 = 1;
        spC = 0;
        fn_8001E4E8(0, 0xF, 0xC, 8, 0xF, 0, 0, 0, 1, 0);
        fn_8007272C(1);
    }
    fn_80016B50(5, -1, -1, -1, -1);
    fn_80073828(5, 5, 5, 0, *(f32 *)0x80301684, *(f32 *)0x802955FC);
    if ((s32) *(s32 *)0x80301678 != 0) {
        fn_80016E18(temp_r25->unk0x14, 5, 4, 1, 0);
        GX_InvalidateTexAll();
        fn_80073880(5, 0, 0, 0);
        fn_80073828(5, 5, 6, 0, *(f32 *)0x802955F8, *(f32 *)0x802955FC);
    }
    fn_80016E18(temp_r25->unk0x14, 5, 4, 1, 0);
    GX_InvalidateTexAll();
    fn_80073880(5, 0, 0, 0);
    fn_80073828(5, 5, 6, 0, *(f32 *)0x802955F8, *(f32 *)0x802955FC);
    fn_80016E18(temp_r25->unk0x14, 5, 4, 1, 0);
    GX_InvalidateTexAll();
    fn_80073880(5, 0, 0, 0);
    fn_80073828(5, 5, 5, 0, *(f32 *)0x802955F8, *(f32 *)0x802955FC);
    fn_80016E18(temp_r25->unk0x14, 5, 4, 1, 0);
    fn_8001F298(0, 7, 0);
    fn_8001EEE0(1, 1, 1, 0, 0);
    fn_8001FA54(7, 0, 0, 7, 0);
    fn_8001E6F0(0, 1, 4, 0, 0x7D);
    fn_8001E6F0(1, 1, 4, 0, 0x7D);
    fn_8001E6F0(2, 1, 4, 0, 0x7D);
    fn_8001E6F0(3, 1, 4, 0, 0x7D);
    fn_8001E6F0(4, 1, 4, 0, 0x7D);
    fn_8001FAA4(0, 0x3C, 0x3C, 0x3C, 0x3C);
    fn_8001E2FC(0, 0, 0, 4, 0, 0, 4);
    fn_8001E2FC(1, 0, 0, 4, 0, 0, 4);
    fn_8001E2FC(2, 0, 0, 4, 0, 0, 4);
    fn_8001E2FC(3, 0, 0, 4, 0, 0, 4);
    fn_8001E2FC(4, 0, 0, 4, 0, 0, 4);
    sp128 = -1;
    fn_8001EFBC(4, &sp128);
    fn_8001F2D8(3, 9, 1, 0xD, 1, 0xB, 1);
    fn_8001E248(4, 1, 0, 0, 0, 0, 2);
    sp128 = -1;
    fn_8001EF84(4, &sp128);
    fn_80016B50(4, -1, -1, -1, -1);
    fn_80073880(5, 0, 0, 0);
    sp8 = 1;
    spC = 0;
    sp10 = 0;
    sp14 = 0;
    fn_8001E3CC(0, 7, 4, 5, 7, 0, 0, 0, 1, 0, 0, 0);
    sp8 = 1;
    spC = 0;
    fn_8001E4E8(0, 0xF, 0xF, 0xF, 0xF, 0, 0, 0, 1, 0);
    fn_8007272C(0);
    temp_f1 = *(s32 *)0x802955F8;
    fn_80073828(4, 4, 5, 0, temp_f1, temp_f1);
    if ((s32) *(s32 *)0x80301678 != 0) {
        fn_80016E18(temp_r25->unk0x10, 4, 4, 1, 0);
        GX_InvalidateTexAll();
        fn_80073880(4, 0, 0, 0);
        fn_80073828(4, 4, 6, 0, *(f32 *)0x802955F8, *(f32 *)0x802955FC);
    }
    fn_80016E18(temp_r25->unk0x10, 4, 4, 1, 0);
    fn_8001F298(0, 7, 0);
    fn_8001EEE0(1, 1, 1, 0, 0);
    fn_8001FA54(7, 0, 0, 7, 0);
    fn_8001E6F0(0, 1, 4, 0, 0x7D);
    fn_8001E6F0(1, 1, 4, 0, 0x7D);
    fn_8001E6F0(2, 1, 4, 0, 0x7D);
    fn_8001E6F0(3, 1, 4, 0, 0x7D);
    fn_8001E6F0(4, 1, 4, 0, 0x7D);
    fn_8001FAA4(0, 0x3C, 0x3C, 0x3C, 0x3C);
    fn_8001E2FC(0, 0, 0, 4, 0, 0, 4);
    fn_8001E2FC(1, 0, 0, 4, 0, 0, 4);
    fn_8001E2FC(2, 0, 0, 4, 0, 0, 4);
    fn_8001E2FC(3, 0, 0, 4, 0, 0, 4);
    fn_8001E2FC(4, 0, 0, 4, 0, 0, 4);
    sp128 = QB_UNKNOWN_0xFF000000 | 0xFF0000 | 0xFF00 | 0xFF;
    fn_8001EFBC(4, &sp128);
    fn_8001F2D8(3, 9, 1, 0xD, 1, 0xB, 1);
    fn_8001E248(4, 1, 0, 0, 0, 0, 2);
    sp128 = QB_UNKNOWN_0xFF000000 | 0xFF0000 | 0xFF00 | 0xFF;
    fn_8001EF84(4, &sp128);
    sp8 = 1;
    spC = 0;
    sp10 = 0;
    sp14 = 0;
    fn_8001E3CC(0, 7, 4, 5, 7, 0, 0, 0, 1, 0, 0, 0);
    sp8 = 1;
    spC = 0;
    fn_8001E4E8(0, 0xF, 0xE, 8, 0xF, 0, 0, 0, 1, 0);
    fn_8001E5DC(0, 0xC, 0x1C, 0xC, 0x1C);
    temp_r30 = arg0->unk0xC;
    temp_r29 = *(s32 *)((char *)arg0 + (s32)0xD);
    fn_80016B50(5, -1, -1, -1, -1);
    set_blend_mode(0, 0, 0);
    sp128 = 0xFF;
    fn_8001E66C(0, &sp128);
    fn_8007272C(0);
    set_blend_mode(0, 1, 0);
    sp128 = ((((temp_r30 << 0x18) & ~0xFF0000) | ((temp_r30 << 0x10) & 0xFF0000)) & ~0xFF00) | ((temp_r30 << 8) & 0xFF00) | 0xFF;
    fn_8001E66C(0, &sp128);
    fn_80073880(5, 0, 0, 0);
    fn_8007272C(0);
    sp128 = ((((temp_r29 << 0x18) & ~0xFF0000) | ((temp_r29 << 0x10) & 0xFF0000)) & ~0xFF00) | ((temp_r29 << 8) & 0xFF00) | 0xFF;
    fn_8001E66C(0, &sp128);
    fn_80073880(4, 0, 0, 0);
    fn_8007272C(0);
    fn_80016E18(temp_r25->unk0x14, 5, 4, 1, 0);
    GX_InvalidateTexAll();
    fn_80016B50(0, -1, -1, -1, -1);
    if ((s32) *(s32 *)0x80301680 == 3) {
        set_blend_mode(0, 0, 0);
        sp128 = 0xFF;
        fn_8001E66C(0, &sp128);
        fn_8007272C(0);
        set_blend_mode(0, 1, 0);
    }
    sp128 = arg0->unk0x8;
    fn_8001E66C(0, &sp128);
    fn_80073880(5, 0, 0, 0);
    fn_8007272C(0);
    if ((s32) arg1->unk0x0 != 0) {
        fn_80016B50(7, -1, -1, -1, -1);
        fn_8007272C(0);
        sp128 = QB_UNKNOWN_0xFF000000 | 0xFF0000 | 0xFF00;
        fn_8001F03C(2, &sp128, arg1->unk0x18, arg1->unk0x1C, *(f32 *)0x80295600, *(f32 *)0x80295604);
        fn_8001F298(0, 7, 0);
        set_blend_mode(0, 0, 0);
        fn_8001FEC0(0);
        fn_8001FA54(7, 0, 0, 7, 0);
        fn_8001E2FC(0, 0, 0, 0xFF, 0, 0, 0xFF);
        fn_8001EEE0(1, 0, 1, 0, 0);
        fn_8001E5DC(0, 0xC, 0x1C, 0xD, 0x1D);
        sp128 = 0xFF0000 | 0xFF;
        fn_8001E66C(0, &sp128);
        sp8 = 1;
        spC = 0;
        fn_8001E4E8(0, 0xF, 0xF, 0xF, 0xE, 0, 0, 0, 1, 0);
        sp8 = 1;
        sp14 = 0;
        spC = 0;
        sp10 = 0;
        fn_8001E3CC(0, 7, 7, 7, 7, 0, 0, 0, 1, 0, 0, 0);
        fn_8001E1D4(2, *(s32 *)0x80301670, 0);
        fn_80016B50(8, -1, -1, -1, -1);
        fn_80016E18(temp_r25->unk0x24, 9, *(s32 *)0x80301674, 1, 1);
        GX_InvalidateTexAll();
        fn_80073880(9, 2, 0, 0);
        fn_8007272C(5);
        fn_80016E18(temp_r25->unk0x28, 0xA, *(s32 *)0x80301674, 1, 1);
        GX_InvalidateTexAll();
        fn_80073880(0xA, 2, 0, 0);
        fn_8007272C(6);
        fn_8001F298(0, 7, 0);
        fn_8001EEE0(1, 1, 1, 0, 0);
        fn_8001FA54(7, 0, 0, 7, 0);
        fn_8001E6F0(0, 1, 4, 0, 0x7D);
        fn_8001E6F0(1, 1, 4, 0, 0x7D);
        fn_8001E6F0(2, 1, 4, 0, 0x7D);
        fn_8001E6F0(3, 1, 4, 0, 0x7D);
        fn_8001E6F0(4, 1, 4, 0, 0x7D);
        fn_8001FAA4(0, 0x3C, 0x3C, 0x3C, 0x3C);
        fn_8001E2FC(0, 0, 0, 4, 0, 0, 4);
        fn_8001E2FC(1, 0, 0, 4, 0, 0, 4);
        fn_8001E2FC(2, 0, 0, 4, 0, 0, 4);
        fn_8001E2FC(3, 0, 0, 4, 0, 0, 4);
        fn_8001E2FC(4, 0, 0, 4, 0, 0, 4);
        sp128 = QB_UNKNOWN_0xFF000000 | 0xFF0000 | 0xFF00 | 0xFF;
        fn_8001EFBC(4, &sp128);
        fn_8001F2D8(3, 9, 1, 0xD, 1, 0xB, 1);
        fn_8001E248(4, 1, 0, 0, 0, 0, 2);
        sp128 = QB_UNKNOWN_0xFF000000 | 0xFF0000 | 0xFF00 | 0xFF;
        fn_8001EF84(4, &sp128);
        fn_8001E1D4(0, *(s32 *)0x80301670, 0);
        fn_8006EC34();
        temp_f6 = arg1->unk0x1C - arg1->unk0x18;
        if ((s32) arg1->unk0x4 != 0) {
            temp_f10 = *(f32 *)0x80295608;
            var_ctr = 0;
            var_f7 = *(s32 *)0x802955F8;
            temp_r7 = (s32) ((arg1->unk0x8 * temp_f10) / temp_f6);
            temp_r6 = (s32) ((arg1->unk0xC * temp_f10) / temp_f6);
            temp_f10_2 = var_f7 / (f32) (f64) temp_r6;
            if (temp_r7 > 0) {
                var_ctr_2 = temp_r7;
                var_r10 = (s16 *)0x80377420;
                do {
                    sp140.w[1] = arg1->unk0x10 ^ 0x80000000;
                    sp140.w[0] = QB_INT_TO_DOUBLE_BIAS;
                    temp_f13 = var_f7 * (f32) (sp140.d - *(f64 *)0x80295610);
                    var_f7 += *(f32 *)0x80295618 / (f32) (f64) temp_r7;
                    temp_r11 = (s32) temp_f13;
                    *((s32 *)var_r10) = (((u16) temp_r11 << 8) & 0xFF00) | (u16) temp_r11;
                    var_r10 += 2;
                    var_ctr_2 -= 1;
                } while (var_ctr_2 != 0);
                var_ctr = temp_r7;
            }
            temp_r11_2 = 0x100 - temp_r6;
            if (var_ctr < temp_r11_2) {
                var_r9 = (var_ctr * 2) + 0x80377420;
                var_ctr_3 = temp_r11_2 - var_ctr;
                do {
                    *((s32 *)var_r9) = 0;
                    var_r9 += 2;
                    var_ctr_3 -= 1;
                } while (var_ctr_3 != 0);
                var_ctr = temp_r11_2;
            }
            if (var_ctr <= 0xFF) {
                var_ctr_4 = 0x100 - var_ctr;
                var_r10_2 = (var_ctr * 2) + 0x80377420;
                do {
                    sp140.w[1] = arg1->unk0x10 ^ 0x80000000;
                    sp140.w[0] = QB_INT_TO_DOUBLE_BIAS;
                    temp_f13_2 = var_f7 * (f32) (sp140.d - *(f64 *)0x80295610);
                    var_f7 += temp_f10_2;
                    temp_r11_3 = (s32) temp_f13_2;
                    *((s32 *)var_r10_2) = (((u16) temp_r11_3 << 8) & 0xFF00) | (u16) temp_r11_3;
                    var_r10_2 += 2;
                    var_ctr_4 -= 1;
                } while (var_ctr_4 != 0);
            }
            arg1->unk0x4 = 0;
        }
        fn_80016E18(temp_r25->unk0x14, 8, 0x28, 1, 0);
        fn_80016E18(temp_r25->unk0x1C, 7, 4, 1, 0);
        GX_InvalidateTexAll();
        fn_80016B50(8, -1, -1, -1, -1);
        fn_8001EEE0(1, 0, 1, 0, 0);
        fn_8001E2FC(0, 0, 0, 4, 0, 1, 4);
        set_blend_mode(0, 0, 0);
        temp_r30_2 = fn_80016EAC(5);
        fn_8001EDE0(0, 1, temp_r30_2, fn_80016EC4(5));
        temp_r30_3 = fn_80016EAC(5);
        temp_r5 = fn_80016EC4(5);
        sp8 = 0x100;
        spC = 0;
        sp10 = 0;
        fn_8001E968(*(s32 *)((char *)0x803016D8 + (s32)0x14), temp_r30_3, temp_r5, 9, 0, 0, 0, 0x100, 0, 0);
        sp8 = 1;
        spC = 0;
        sp10 = 0;
        sp14 = 0;
        fn_8001E3CC(0, 7, 7, 7, 7, 0, 0, 0, 1, 0, 0, 0);
        sp8 = 1;
        spC = 0;
        fn_8001E4E8(0, 0xF, 0xF, 0xF, 8, 0, 0, 0, 1, 0);
        fn_8007272C(0);
        if ((s32) *(s32 *)0x80301688 != 0) {
            fn_80016E18(temp_r25->unk0x14, 8, 4, 1, 0);
            GX_InvalidateTexAll();
            fn_80073880(5, 0, 0, 0);
            fn_80073828(5, 5, 5, *(s32 *)0x80301690, *(f32 *)0x8030168C, *(f32 *)0x802955FC);
            if ((s32) *(s32 *)0x80301678 != 0) {
                fn_80016E18(*(s32 *)((char *)0x803016D8 + (s32)0x14), 8, 4, 1, 0);
                GX_InvalidateTexAll();
                fn_80073880(5, 0, 0, 0);
                fn_80073828(5, 5, 6, *(s32 *)0x80301690, *(f32 *)0x802955F8, *(f32 *)0x802955FC);
            }
        }
        fn_8001F298(0, 7, 0);
        fn_8001EEE0(1, 1, 1, 0, 0);
        fn_8001FA54(7, 0, 0, 7, 0);
        fn_8001E6F0(0, 1, 4, 0, 0x7D);
        fn_8001E6F0(1, 1, 4, 0, 0x7D);
        fn_8001E6F0(2, 1, 4, 0, 0x7D);
        fn_8001E6F0(3, 1, 4, 0, 0x7D);
        fn_8001E6F0(4, 1, 4, 0, 0x7D);
        fn_8001FAA4(0, 0x3C, 0x3C, 0x3C, 0x3C);
        fn_8001E2FC(0, 0, 0, 4, 0, 0, 4);
        fn_8001E2FC(1, 0, 0, 4, 0, 0, 4);
        fn_8001E2FC(2, 0, 0, 4, 0, 0, 4);
        fn_8001E2FC(3, 0, 0, 4, 0, 0, 4);
        fn_8001E2FC(4, 0, 0, 4, 0, 0, 4);
        sp128 = -1;
        fn_8001EFBC(4, &sp128);
        fn_8001F2D8(arg0, 3, 9, 1, 0xD, 1, 0xB, 1);
        fn_8001E248(4, 1, 0, 0, 0, 0, 2);
        sp128 = -1;
        fn_8001EF84(4, &sp128);
        fn_80016B50(0, -1, -1, -1, -1);
        fn_80016E18(*(s32 *)0x803016EC, 8, 0x28, 1, 0);
        GX_InvalidateTexAll();
        fn_8001E2FC(0, 0, 0, 4, 0, 1, 4);
        set_blend_mode(0, 5, 0);
        fn_8001EEE0(1, 0, 2, 0, 0);
        fn_80073880(7, 0, 0, 0);
        fn_80073880(5, 1, 1, 0);
        sp8 = 1;
        spC = 1;
        sp10 = 0;
        sp14 = 0;
        fn_8001E3CC(0, 7, 7, 7, 7, 0, 0, 0, 1, 1, 0, 0);
        sp8 = 1;
        spC = 1;
        fn_8001E4E8(0, 0xF, 0xF, 0xF, 8, 0, 0, 0, 1, 1);
        sp8 = 1;
        spC = 0;
        fn_8001E4E8(1, 0xF, 0xF, 0xF, 2, 0, 0, 0, 1, 0);
        sp8 = 1;
        sp10 = 3;
        sp14 = 0;
        spC = 0;
        fn_8001E3CC(1, 7, 7, 7, 4, 0, 0, 0, 1, 0, 3, 0);
        fn_8007272C(0);
        fn_80016C70();
        fn_8006EC34();
    }
    fn_80016A88(&sp18, 2);
}
