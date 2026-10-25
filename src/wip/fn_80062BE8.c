// WIP DRAFT (non-matching) — fn_80062BE8, 348 B, leaf float-initializer (no frame,
// no calls). INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// family=m2c range=0x80062BE8-0x80062D44 size=348B
//
// Score 2026-10-01: NEAR 47.1%, object .text = 0x15C = 348 B = want size.
// Score command: tools/venv/bin/python tools/test_wip_drafts.py --addr 0x80062BE8
// NOTE: the previously inherited `// FLAG: -Os` was REMOVED — on the fixed body it
// costs 7 points (47.1% flagless vs 40.2% with -Os).
//
// What is load-bearing in this body (all measured):
//  * The file-local Unk_80062BE8 type map. m2c's `Unk_FFAD6788`/`CStruct` are all-s32,
//    so every `f32` store became `stw` with an `fctiwz`/`stfd` int-conversion dance
//    and a 40-byte FPR frame: 392 B object vs 348 B want, 2.3%. Correct member
//    widths (f32 at every `stfs` offset, s32 at every `stw`, `u8` at 0x12C for the
//    single `stb`) make the frame disappear and the size exact.
//  * The three float temps (temp_f0/f12/f13). Using `lbl_802940xx` directly at every
//    store site makes GCC emit one `lfs` per site (28 loads, +40 B, frame reappears);
//    the temps give exactly the 8 `lfs` want has. Load-bearing, do not inline them.
//  * `volatile s32 i_128`. want does TWO read-modify-writes of 0x128 (2 lwz, 2 stw).
//    Plain C lets GCC forward the first store into the second load and collapse them
//    to 1 lwz / 1 stw (2 words short). Marking just that member volatile forces both
//    pairs and reproduces the 87-word length.
//  * `& 0xFFFFFFFE` on the FIRST RMW (not 0x7FFFFFFF). Verified against ngccc:
//    `x & 0x7FFFFFFF` emits `clrlwi r0,r0,1` (word 0x5400007e) whereas want's
//    0x5400003c is what `x & 0xFFFFFFFE` emits. m2c's QB_UNKNOWN_0xFFFFFFFE was right.
//  * Source store order == want's emitted order, verified store-by-store.
//    The 3-store pointer groups are written `+4, +8, +0xC` in source because that is
//    what makes GCC emit them `0xC, +4, +8`; the other two orders measured worse.
//  * `register char *temp_r8 __asm__("r8")` / `temp_r10 __asm__("r10")`: want holds
//    those sub-object bases in r8/r10 (+6 words, 40.2% -> 47.1%).
//
// === PARKED (2026-10-01) — NEAR 47.1%, size-exact, 46 diffs ===
// Stuck below the front end; both residual classes are GCC reload / list-scheduler
// decisions, not reachable from C:
//  (1) HI16 anchor colour + constant registers (~32 words). want allocates the
//      8 rodata anchors to {r9,r10,r8,r7,r9,r10,r7,r6} and materialises the zero
//      constant in r11 and the one constant in r9; this body allocates
//      {r9,r11,r10,r8,r7,r6,r7,r6} with zero in r9 / one in r11. Everything follows
//      from that single cascade: want's window is {7..10} and r11 is already taken by
//      the zero constant, ours is {8..11}. `cc1 -dr` shows the reload pseudos are
//      numbered in source order either way (v17 hoisted all four `= 0` stores above
//      the float reads and the reload pseudo numbers DID change — 88..91 for the
//      constants ahead of 92.. for the anchors — yet the output was byte-identical),
//      so `choose_reload_regs` is doing a multi-pass, order-insensitive assignment.
//  (2) Float-tail store positions (~7 words). want emits f_F0, [RMW], f_B4, f_9C,
//      f_B0 ... f_E8, f_EC, f_98, f_F4; we emit f_9C, [RMW], f_B4, f_EC, f_F0,
//      f_B0 ... f_E8, f_98, f_F4 — f_9C is pulled across the volatile store and f_EC
//      is pulled forward to slot 4. Single-variable source moves of f_F0 / f_9C / f_EC
//      (v18/v19) leave it unchanged: a sched2 priority tie, not a statement-order issue.
// UNTRIED: forcing the zero/one constants into r11/r9 from C (a `register s32 z
// __asm__("r11")` is folded back to a literal by ngccc, so a pin cannot reach them);
// no lever found for the reload cascade. Also untried: nested-struct members instead
// of the raw `*(f32 *)(temp_rX + k)` group writes, which might change the base-register
// pressure enough to move the anchor window down by one.
#include "types.h"
typedef struct {
    char pad0x00[0x28];
    f32 f_28; f32 f_2C; f32 f_30; f32 f_34; f32 f_38;
    f32 f_3C; f32 f_40; f32 f_44;
    char pad0x48[0x20];
    f32 f_68; f32 f_6C; f32 f_70; f32 f_74; f32 f_78; f32 f_7C;
    s32 i_80; s32 i_84;
    s32 i_88; f32 f_8C; f32 f_90; f32 f_94;
    f32 f_98; f32 f_9C; f32 f_A0; f32 f_A4; f32 f_A8; f32 f_AC;
    f32 f_B0; f32 f_B4; f32 f_B8; f32 f_BC; f32 f_C0; f32 f_C4; f32 f_C8;
    f32 f_CC; f32 f_D0; f32 f_D4; f32 f_D8; f32 f_DC; f32 f_E0;
    s32 i_E4;
    f32 f_E8; f32 f_EC; f32 f_F0; f32 f_F4;
    char pad0xF8[0xC];
    s32 i_104; s32 i_108; s32 i_10C;
    char pad0x110[0x18];
    volatile s32 i_128;
    u8 b_12C;
    s32 i_130; s32 i_134; s32 i_138; s32 i_13C;
    s32 i_140; s32 i_144; s32 i_148; s32 i_14C; s32 i_150; s32 i_154;
    s32 i_158; s32 i_15C; s32 i_160; s32 i_164; s32 i_168;
} Unk_80062BE8;

extern f32 lbl_80294024;
extern f32 lbl_80294028;
extern f32 lbl_8029402C;
extern f32 lbl_80294030;
extern f32 lbl_80294034;
extern f32 lbl_80294038;
extern f32 lbl_8029403C;
extern f32 lbl_80294040;
void fn_80062BE8(Unk_80062BE8 *arg0) {
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f13;
    register char *temp_r8 __asm__("r8");
    register char *temp_r10 __asm__("r10");

    temp_f0 = lbl_80294024;
    temp_r8 = (char *)arg0 + 0x38;
    temp_f13 = lbl_80294034;
    temp_f12 = lbl_80294038;
    arg0->f_28 = lbl_80294028;
    temp_r10 = (char *)arg0 + 0x68;
    arg0->f_2C = lbl_8029402C;
    arg0->f_30 = lbl_80294030;
    arg0->i_104 = 0;
    arg0->i_108 = 0;
    arg0->i_10C = 0;
    arg0->i_E4 = 0;
    arg0->f_78 = temp_f0;
    arg0->f_7C = temp_f0;
    arg0->i_88 = 0;
    arg0->f_8C = temp_f0;
    arg0->f_90 = temp_f0;
    arg0->f_34 = temp_f0;
    arg0->f_38 = temp_f0;
    *(f32 *)(temp_r8 + 4) = temp_f0;
    *(f32 *)(temp_r8 + 8) = temp_f0;
    *(f32 *)(temp_r8 + 0xC) = temp_f0;
    arg0->f_BC = temp_f13;
    arg0->f_C0 = temp_f13;
    arg0->f_C4 = temp_f13;
    arg0->f_C8 = temp_f13;
    arg0->f_CC = temp_f12;
    arg0->f_D0 = temp_f13;
    arg0->f_D4 = temp_f13;
    arg0->f_A0 = temp_f12;
    arg0->f_A4 = temp_f12;
    arg0->f_A8 = temp_f0;
    arg0->f_AC = lbl_8029403C;
    arg0->f_F0 = temp_f0;
    arg0->i_128 = (s32) (arg0->i_128 & 0xFFFFFFFE);
    arg0->f_B4 = lbl_80294040;
    arg0->f_9C = temp_f13;
    arg0->f_B0 = temp_f0;
    arg0->f_B8 = temp_f0;
    arg0->f_D8 = temp_f0;
    arg0->f_DC = temp_f12;
    arg0->f_E0 = temp_f0;
    arg0->f_E8 = temp_f0;
    arg0->f_EC = temp_f0;
    arg0->f_98 = temp_f12;
    arg0->f_F4 = temp_f12;
    arg0->b_12C = 0;
    arg0->f_68 = temp_f12;
    *(f32 *)(temp_r10 + 4) = temp_f12;
    *(f32 *)(temp_r10 + 8) = temp_f12;
    *(f32 *)(temp_r10 + 0xC) = temp_f12;
    arg0->i_14C = 0;
    arg0->i_150 = 0;
    arg0->i_128 = (s32) ((arg0->i_128 & 0xFFFFFFEE) | 0x100);
    arg0->i_158 = 1;
    arg0->i_13C = 0;
    arg0->i_140 = 1;
    arg0->i_138 = 0;
    arg0->i_130 = 0;
    arg0->i_160 = 0;
    arg0->i_134 = 0;
    arg0->i_164 = 0;
    arg0->i_15C = 1;
    arg0->i_168 = 1;
    arg0->i_80 = 0;
}
