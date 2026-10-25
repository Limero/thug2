// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007297C-0x80072BE8 (620B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern f32 lbl_8029554C;
extern f32 lbl_80295550;
extern f32 lbl_80295554;
extern f32 lbl_80295560;
extern f64 lbl_80295558; /* see NOTE: unused here, see footer */
void fn_8001E66C(s32, s32 *, s32);
void fn_8001E5DC(s32, s32, s32, s32, s32);
void fn_8001E3CC(s32, s32, s32, s32, s32, s32, s32, s32);
void fn_8001E4E8(s32, s32, s32, s32, s32, s32, s32, s32);
void fn_8001F0A0(s32, s32, s32);
void fn_8001F0F4(void);
void fn_8001F0F8(f32, f32, f32);
void fn_8001F1D4(s32);
void fn_8001F200(f32, f32);
// The want's `slwi + 3x rlwimi` byte build is BITFIELD-INSERT fusion, not a
// bswap: GCC only emits `rlwimi` when the destination is a 4x8-bit field of the
// same word (recipe 110 / §6k). A plain mask/or bswap gives the 7-insn
// rlwinm+or chain instead. This union is load-bearing - do not simplify it.
typedef union { struct { u32 a:8; u32 b:8; u32 c:8; u32 d:8; } f; u32 w; } C4;
void fn_8007297C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 farg0, f32 farg1, f32 farg2) {
    s32 c[21];
    C4 col;
    f32 t13;
    f32 t3;
    s32 t9;
    f32 t1;
    f32 t28;
    f32 t27;
    f32 t26;
    f32 t31;
    f32 t30;
    f32 t27b;
    f32 t30b;
    f32 t31b;

    t13 = lbl_8029554C;
    t3 = farg2 * t13;
    t9 = (s32)t3;
    col.w = (t9 << 0x18) & 0xFF000000;
    col.f.b = t9;
    col.f.c = t9;
    col.f.d = t9;
    c[4] = col.w;
    fn_8001E66C(0, &c[4], arg2);
    fn_8001E5DC(0, 0xC, 0x1C, 0xC, 0x1C);
    c[0] = 1;
    c[1] = 0;
    c[2] = 0;
    c[3] = 0;
    fn_8001E3CC(0, 7, 7, 7, 7, 0, 0, 0);
    if (arg3 != 0) {
        c[0] = 1;
        c[1] = 0;
        fn_8001E4E8(0, 0xF, 0xE, 8, 0xF, 0, 0, 2);
    } else {
        c[0] = 1;
        c[1] = arg3;
        fn_8001E4E8(0, 0xF, 0xE, 8, 0xF, 0, 0, 0);
    }
    fn_8001F0A0(0x80, 0, 4);
    t1 = lbl_80295550;
    fn_8001F0F8(t1, t1, lbl_80295554);
    fn_8001F1D4(-1);
    t28 = lbl_80295550;
    t27 = farg1 + t28;
    t26 = farg0 + t28;
    fn_8001F200(t26, t27);
    t31 = (f32)(f64)arg0;
    fn_8001F0F8(t31, t28, lbl_80295554);
    fn_8001F1D4(-1);
    t30 = lbl_80295560;
    t27b = farg0 + t30;
    fn_8001F200(t27b, t27);
    t30b = farg1 + t30;
    t31b = (f32)(f64)arg1;
    fn_8001F0F8(t31, t31b, lbl_80295554);
    fn_8001F1D4(-1);
    fn_8001F200(t27b, t30b);
    fn_8001F0F8(t28, t31b, lbl_80295554);
    fn_8001F1D4(-1);
    fn_8001F200(t26, t30b);
    fn_8001F0F4();
}
// STATUS 2026-10-03: MATCHES (masked 100.00, size exact 620 == 620B,
// REL14/REL24 + lis/lfs/lfd verified). Reproduce:
//   LEAF_TMPDIR=<private dir> tools/venv/bin/python tools/test_wip_drafts.py --addr 0x8007297C
//
// WHAT THE FIX WAS (baseline was DIFF 16.77%, object 676B):
//  1. SIGNATURE ORDER. m2c emitted (s32,s32,s32, f32,f32,f32, s32) — 3 ints, 3
//     floats, then the 4th int LAST, which puts it in r9 and silently compares
//     the WRONG register (`cmpwi r30` = the 3rd arg). The real order is 4 ints
//     then 3 floats: (r3,r4,r5,r6,f1,f2,f3) — confirmed by the caller
//     src/wip/fn_80072BE8.c:82 `fn_8007297C(0x280,0x1C0,2,a,f1,f2,...)`. With the
//     right order r6->r28 and r5 needs no callee-saved copy (it dies at the
//     first call), which is exactly the want's `mr r31,r3 / mr r27,r4 / mr r28,r6`.
//  2. CALLEE PROTOTYPES. fn_8001E5DC/E3CC/E4E8/F0A0/F0F4/F0F8/F1D4/F200/E66C were
//     unprototyped. Unprototyped float args made ngccc emit int<->float
//     round-trips (fctiwz/lwz/stfd) AND a stray `crset cr1eq` before every bl
//     (+28B). fn_8001F0F8 must be (f32,f32,f32) and fn_8001F200 (f32,f32) — same
//     finding as fn_8007272C.
//  3. fn_8001E66C(0, &c[4], arg2) — 3 int args; the 3rd is the raw r5 pass-through
//     (the callee ignores it: its prologue is `mflr/stmw r29/lwz r30,0(r4)` and
//     uses only r3/r4).
//  4. THE FOUR DEAD STORES at +0x08..+0x17 (`stw r29/r30`) survive ONLY because the
//     word passed by address at +0x18 lives in the SAME object. Five scalars ->
//     gcc dead-store-eliminated all four; one `s32 c[21]` array with the address
//     taken (`&c[4]`) makes them live again, interleaves them 1:1 with the
//     fn_8001E3CC arg `li`s exactly as want does, and puts the fctiwz/cvt temp at
//     +0x68 (c[21] = 84B at +0x08, 12B pad, temp at +0x68, frame 0xc8).
//  5. The `slwi + 3x rlwimi` byte build is NOT a bswap (see the C4 comment).
//
// PROMOTE CAVEAT (recipe 108 / doc-14, checked at sweep time, NOT a match bug):
// `(f32)(f64)arg0` makes ngccc synthesize the int->f64 constant, so the object's
// private `.rodata` holds `4330000080000000` and the `lfd f29` (hoisted into
// f29, used twice) relocates against SECTION .rodata + 0, not against the game's
// `lbl_80295558` (.rodata2:0x80295558) — whose 8 bytes are IDENTICAL. So .text
// is byte-exact and every other relocation names the right game symbol, but the
// link still needs doc-14 pool routing. Writing the conversion as the explicit
// union dance (`union{u32 w[2]; f64 d;}` + `w[1]=arg0^0x8000; w[0]=0x43300000;
// (f32)(d - lbl_80295558)`) DOES name the real symbol but costs the match: the
// union gets its own +8B slot (frame 0xd0), and gcc then keeps lbl_80295558 in
// f30/f31 per site instead of hoisting one copy into f29. Fixing that needs the
// §6j-1 inline-asm dance (banned for this task), not plain C.
