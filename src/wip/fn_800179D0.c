// WIP DRAFT (non-matching) — C body derived from the disassembly
// family=m2c range=0x800179D0-0x80017C10 size=576B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// PARKED 2026-10-03 (a49): NEAR 52.8% (was DIFF 22.2%). Reproduce:
// LEAF_TMPDIR=<scratch> tools/venv/bin/python tools/test_wip_drafts.py --addr 0x800179D0
//   (DIFF rows print no pct; /tmp cmp harness = gl.compile_fn + masked_pct over 144 words:
//    got 576B = 144 words, 76/144 = 52.8%.)
//
// FIXED vs the m2c draft (all verified against the disassembly):
//  1. inner loop is `lhz` with a 0xC stride (u16* + 6), NOT m2c's
//     `*((s32 *)p)` / `p += 0xC` (which gave `lhz r0,2(r9)` + `addi r9,r9,0x18`).
//  2. the bss flag table base (0x80312434) must be hoisted OUT of the outer
//     loop: assign it to `tbl` BEFORE the do-loop and copy it into the inner
//     pointer inside.  That alone moved 7.6% -> 47.9%: with the assignment
//     inside the loop ngccc split the address (HI16 `lis` in the prologue +
//     LO16 `addi r9,r29,0` in the loop preheader, 1 word short of the want);
//     hoisted, it emits the want's `lis`+`addi` pair and a `mr r9, r29`.
//  3. fn_80131154 (0x80131154) is called with FOUR args (r6 = 0) -- m2c
//     dropped one.  +1 word.
//  4. queue_front (0x800169FC) takes ONE arg (&sp8); m2c invented a 2-arg
//     call that also re-called fn_8001B8D0.
//  5. sprintf is `sprintf(&sp8, lbl_80290CFC /* "ngc_selectPAL%d" */, lbl_80300138)`
//     -- m2c dropped the format arg (spilled a value as the format string).
//  6. Script_RunScript's 1st arg is the plain integer 0x803B17AB, NOT a
//     symbol address: the want emits `ori r3,r3,0x17ab`, and ngccc only uses
//     ori (not addi) when building a 32-bit *literal*.  (QB_NGC_PAL60 in
//     include/qb_constants.h is 0x84BF17AB -- a different build.)
//  7. locals: `char sp8[0x110]` + `s32 sp118` reproduces the want's
//     sp+0x8 / sp+0x118 offsets (m2c's two s32 locals gave 0x0c).
//
// REMAINING DIFF: words 46..101 are shifted 2 words low.  The want's loop-2
// preheader holds FIVE hoisted invariants -- four identical page bases
// (lis r29/r31/r25/r26 = 0x80300000, one per block that touches
// lbl_80300138 / lbl_8030013C / lbl_80300125) plus `li r27, 0` -- and then
// uses them, e.g. `lwz r9,0x13c(r25)` with NO rematerialised `lis`.
// This draft hoists only THREE bases and rematerialises the rest
// (`li r0,0` + `lis r9,0` at the use sites, 2 extra words there).  That is
// exactly the 2-word deficit, and it also costs the frame: 5 callee-saved
// regs -> `stwu -0x138` instead of the want's 7 regs -> `-0x140`
// (so `stw r0,0x13c(r1)`, `lmw r27`, `addi r1,r1,0x138` all miss).
// Also still open: want `or r30,r0,r30` (accumulator as op1, i.e. the
// original source likely read `var_r30 = tmp | var_r30`) vs got
// `or r30,r30,r0`; and r25/r26/r27/r30/r31 register-name selection.
// NEXT IDEA: get those last two invariants (lbl_8030013C's page base and the
// constant 0) into callee-saved registers instead of rematerialised -- that
// supplies the 2 missing preheader words, fixes the frame to 0x140 and
// realigns 46..101.  GCC 2.95 remat preference is what resists this.
// TRIED 2026-10-16 (kept parked body: 52.8% stays best): pointer homes for
// p138/p13C/p125 (+zero, +&sp118) DO fix the frame to stwu -0x140, but land
// at 36.1% — the homes take the wrong names and all five births cluster
// below the loop-2 guard branch, while want splits them across it (andi.
// 0x100; addi r28; lis r29; bne SKIP; lis r31; lis r25; lis r26; li r27).
// Dropping p120 (single-use tail store) gets exactly 7 saved (stmw r25),
// and declaring without initializers + assigning at loop-2 entry keeps
// loop-1's preheader clean, but the andi/bne-interleave (two births hoisted
// above the guard) is scheduler behavior no source placement reproduced —
// assignments before the guard put births too early, inside puts them all
// below. Reopen with a scheduler lever, not another home layout.
extern char lbl_8037B5E8[];
extern char lbl_80290CFC[];
extern u16 lbl_80312434[];
void fn_800173CC(void *);
void fn_80131154(void *, void *, void *, void *);
void fn_80016A88(void *arg0, s32 arg1);
s32 Script_RunScript(s32, s32, s32, s32, s32);
s32 set_blend_mode(void *, void *, void *);
s32 Camera_orthographic(void *, void *, void *, void *, void *);
s32 fn_8001737C(void *);
s32 fn_80018064(s32);
s32 fn_800176B8(void);
s32 sprintf(s32, ...);
s32 OSGetEuRgb60Mode();
void GX_SetZMode(s32, s32, s32);
extern f32 lbl_80290D0C;
extern f32 lbl_80290D10;
extern s32 lbl_80300120;
extern s32 lbl_80300125;
extern s32 lbl_80300138;
extern s32 lbl_8030013C;
extern f32 lbl_8037B76C;
void queue_front(void *);
void fn_80017E20(s32);
void fn_800179D0(void) {
    s32 sp118;
    char sp8[0x110];
    s32 temp_r3;
    s32 temp_r9;
    s32 var_r30;
    s32 var_r31;
    u16 *var_r9;
    u16 *tbl;
    s32 var_ctr;
    *(f32 *)((char *)lbl_8037B5E8 + (s32)0x184) = lbl_80290D0C;
    *(s32 *)((char *)lbl_8037B5E8 + (s32)0x1BC) = 0;
    var_r30 = 0;
    var_r31 = 0;
    tbl = (u16 *)lbl_80312434;
    do {
        fn_80017DA4();
        fn_8001B8D0();
        fn_8001B9C8();
        fn_80017E20(1);
        var_r9 = tbl;
        for (var_ctr = 4; var_ctr != 0; var_ctr--) {
            var_r30 |= *var_r9;
            var_r9 += 6;
        }
        var_r31 += 1;
    } while (var_r31 <= 3);
    lbl_8037B76C = lbl_80290D10;
    if ((var_r30 & 0x200) || (OSGetEuRgb60Mode() != 0)) {
        if (!(var_r30 & 0x100)) {
            do {
                fn_80017DA4();
                fn_8001B8D0();
                queue_front(&sp8);
                Camera_orthographic(&sp8, 0, 0, 0x280, 0x1C0);
                fn_8001B8B0();
                fn_8001737C(&sp8);
                GX_SetZMode(0, 7, 1);
                set_blend_mode(0, 5, 0);
                Script_RunScript(0x803B17AB, 0, 0, 0, 0);
                sp118 = lbl_80300125;
                fn_80018064(&sp118);
                fn_800173CC(&sp8);
                fn_8001B8C0();
                fn_8001B9C8();
                fn_80017E20(1);
                temp_r3 = fn_800176B8();
                if (temp_r3 & 4) {
                    lbl_80300138 += 1;
                }
                if (temp_r3 & 8) {
                    lbl_80300138 -= 1;
                }
                if (lbl_80300138 < 0) {
                    lbl_80300138 = 0;
                }
                temp_r9 = lbl_8030013C;
                if (lbl_80300138 >= temp_r9) {
                    lbl_80300138 = (s32) (temp_r9 - 1);
                }
                fn_80016A88(&sp8, 2);
            } while (!(temp_r3 & 0x100));
        }
        sp118 = 0;
        fn_80018064(&sp118);
        fn_80017DA4();
        fn_80017E20(1);
        fn_80017DA4();
        fn_80017E20(1);
        sprintf(&sp8, (s32)lbl_80290CFC, lbl_80300138);
        fn_80131154(&sp8, 0, 0, 0);
    }
    fn_80018E2C();
    lbl_80300120 = 1;
}
