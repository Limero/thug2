// WIP DRAFT (non-matching) — hand-written from retail disassembly + mwcc iteration.
// family=gxpixel range=0x8028BA08-0x8028BC24 size=540B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// Identity: GXSetFog (dolphin/gx/GXPixel.c) — a Metrowerks-compiled Dolphin SDK
// function. Compiler family = MWCC, evidence in the header note below.
//
// ===== COMPILER FAMILY: MWCC (NOT ProDG) =====
// Evidence from the want bytes (0x8028BA08..0x8028BC20):
//   * prologue `mflr r0` (0x7C0802A6) -> `stw r0,4(r1)` (0x90010004) BEFORE
//     `stwu r1,-0x48(r1)` (0x9421FFB8): the LR slot is ABOVE the new frame,
//     which is mwcc-canonical. ngccc always emits stwu FIRST (see the
//     mwcc-free prologues at e.g. 0x8028BD24's siblings).
//   * two `li r10,0` / `li r11,0` scratch-zero inits before the stwu, and
//     individual `stw r31..r28` saves (0x93E1/93C1/93A1/9381) instead of an
//     `stmw` span.
//   * pop-before-mtlr epilogue: `lwz r31..r28` then `addi r1,r1,0x48` then
//     `mtlr r0` then `blr` (0x8001004C/83E10044/.../38210048/7C0803A6/4E800020).
//   * `-0x6108(r13)`-relative SDA float/double loads (0xC00D9EF8) => small-data
//     on, which ngccc -G0 game objects never emit for a load of a float.
//   * direct MMIO `lis r4,0xCC01` + `stb r0,-0x8000(r4)` = GXFIFO @0xCC008000.
// => Score with tools/mwcc_verify.py, NOT tools/test_wip_drafts.py.
//    The ngccc sweep can only ever report NEAR/DIFF here (AGENTS §6av-205).
//
// ===== ngccc (ProDG) COMPILABILITY SHIM =====
// tools/gen_leaves.compile_fn passes only `-I include`, and this project's
// include/ has no dolphin/gx*.h (they live in libs/dolphin/include, which only
// the mwcc rule puts on the path). That missing-include FAIL is what put this
// draft in the "stratum FAIL" bucket. The `#else` branch below declares just
// enough for ngccc to parse and compile the same body. It is NOT expected to
// match under ngccc — the function is mwcc codegen.
//
// ===== WHERE IT STANDS (mwcc, measured 2026-10-02) =====
// tools/venv/bin/python tools/mwcc_verify.py 0x8028BA08 src/wip/fn_8028BA08.c \
//       -use_lmw_stmw off
//   -> DIFF 99/131 words, 32 matching (24.4%). Object .text 524 B; the true want
//      size is 0x21C = 540 B, so the object is 16 B short and the index-aligned
//      masked % is only meaningful together with the run map (AGENTS 6es).
//      The 32 matching words sit in two CONTIGUOUS runs -- words 31..45 (want
//      0x8028BA84..0x8028BABC: the non-proj branch's compares, the degenerate
//      A/B/C case and the four-term A/B/C division) and words 59..61 -- so the
//      match is structural, not alignment luck.
// Baseline was 122/130 diffs, 8 matching (6.2%). Three wins, all measured:
//  (1) reference the game's real .sdata2 pool symbols instead of C literals.
//      This alone fixed a whole class of r13 SDA21 displacements (want wants
//      -0x6108/-0x6104/-0x6100/-0x60f0/-0x60e0/-0x60d8, and with literals mwcc
//      synthesises a private .sdata2 pool at completely different offsets).
//  (2) hoist `b_s = B_expn + 1;` ABOVE the `1 << b_s` shift. The want computes
//      it once (`addi r28,r3,1` at 0x8028BB08) and reuses r28 for both the
//      shift (0x8028BB18) and the fog2 field (`clrlwi r0,r28,8` at 0x8028BB4C).
//  (3) the two B_mant loop compares are written with DOUBLE literals in the
//      original (`while (B_mant > 1.0)` / `B_mant < 0.5`, i.e. lbl_803CC188 /
//      lbl_803CC198), NOT f32. Evidence: the want carries two DEAD
//      `lfd f0,-0x60f8(r13)` (1.0 as f64) and `lfd f0,-0x60e8(r13)` (0.5 as
//      f64) at 0x8028BAC8/0x8028BAE0 -- constants only a double-typed source
//      expression would materialise. Spelling them as doubles: 18.5% -> 24.4%.
//
// NEGATIVE RESULT worth keeping: the `a = A / (f32)(1 << b_s);` conversion must
// stay PLAIN. It looks like a hand-rolled int->f64 stack pair in the want
// (`xoris r3,r0,0x8000` / `lis r0,0x4330` / `stw`+`stw` / `lfd` / `fsubs`), but
// writing that union out BY HAND makes the `xoris` disappear (18.5% -> 16.8%).
// It is mwcc's own unsigned-int->f64 lowering. Measured, not assumed.
//
// THE REMAINING WALL is mwcc register allocation, not source shape:
//   want  : stwu -0x48, FOUR inline `stw r31,r30,r29,r28`, ZERO FPR saves, plus
//           two `li r10,0` / `li r11,0` scratch inits BEFORE the stwu. Frame
//           slots a@0x2c c@0x28 cvt-pair@0x30/0x34 (only 0x10 of the 0x30-byte
//           locals region is touched).
//   object: stwu -0x58, `addi r11,r1,0x58` + `bl __savegpr_23` (NINE callee-saved
//           GPRs r23..r31), zero FPR saves, no prologue `li`s.
// The surplus regs are the fog0/fog3/fogclr accumulators, which live entirely
// AFTER the function's only call (__cvt_fp2unsigned) and could therefore sit in
// caller-saved regs -- want uses r7/r8/r12/r5/r6/r10/r11 there. Tried and inert:
// no-a_hex/c_hex (read the stack floats at the use site, 0.8%), volatile a/c
// (0.7% -- it reaches the exact 540 B length but only 3/135 words match, so the
// length is a coincidence), -O2/-O3/-O4{,p,s}, -s vs -p. This is the doc-10
// class and is consistent with docs/parkings/20-gxpixel-fog-sched.md ("a pure
// regalloc coin-flip"). That doc's "DOL saves 4 FPRs, mwcc saves 8+" is STALE:
// the want saves ZERO FPRs and the real gap is 4 vs 9 saved GPRs.
//
// FLAG BASIS (`-use_lmw_stmw off`) is DOL-verified, not assumed: scanning every
// mwcc-style prologue in .text (`mflr r0; stw r0,4(r1); stwu r1,-N(r1)`) finds
// 261 sites and ZERO use `stmw` (16 call a `bl __savegpr_*` helper, 6 use
// individual `stw`, 245 save nothing). configure.py's `cflags_dolphin` does NOT
// pass this flag, so any mwcc object that really saves registers will mis-build
// until it is added there (outside this task's edit scope).
//
// PROMOTE NOTE: the object still carries a private 8-byte `.sdata2` holding the
// int->f64 magic (0x43300000 / 0x80000000). The game keeps that pair at
// `lbl_803CC1A8` (.sdata2, data:double, size 0x28), so at promote time this
// object needs its SDA21 pair retargeted there, the mwcc analogue of what
// tools/fix_fp_pool.py does for the ngccc .rodata2 route.
//
// ===== PARKED 2026-10-05: unchanged verdict, THREE new facts =====
// Verdict is still DIFF ~24.2% under mwcc (was 24.4%); the one source change
// kept is a REAL BUG FIX that costs 0.2% (1 word):
//   `c_hex = *(u32 *)&c;` was missing from the non-PROJ branch, so
//   `SET_REG_FIELD(214..217, fog3, ...)` read an uninitialised local whenever
//   GX_FOG_PROJ was clear.  Placement matters: right after `a_hex = ...` costs
//   3.7 words (20.5%), right after the `__cvt_fp2unsigned` call costs 1 (24.2%),
//   which is also where the want stores `c` (stfs f5,0x28(r1) at 0x8028BB24,
//   between the argument setup and the call).  Moved there.
//
// (1) THE PROLOGUE SHAPE IS A FUNCTION OF `-use_lmw_stmw`, AND THIS WANT IS
//     ONLY REACHABLE WITH IT **ON**.  Measured with a synthetic probe (N values
//     live across a call, forced distinct from a `volatile` global):
//       -use_lmw_stmw ON : the saves are ALWAYS inlined -- `stmw rN,off(r1)`
//                          when they are contiguous, individual `stw rN,off(r1)`
//                          when mwcc interleaves them with the first real insns.
//       -use_lmw_stmw OFF: inlined only while <= 4 registers need saving; from 5
//                          up it emits `addi r11,r1,frame; bl __savegpr_N`
//                          (N = lowest register saved: 27, 26, 25, ...).
//     The want does FOUR INTERLEAVED `stw` (r31/r30/r29/r28 at 0x8028BA1C..34,
//     with rlwinm/clrlwi/addi wedged between them) and its epilogue restores
//     exactly those four -- so the original object could not have been built
//     with `off` UNLESS it needed <= 4 saved registers, which is what it has.
//     With `on`, mwcc's ZERO-init of fog1/fog2 also lands before the frame setup
//     (`li r5,0; li r6,0; stw r0,4(r1); stwu...`) which is much closer to the
//     want's `li r10,0; stw r0,4(r1); li r11,0; stwu...`; with `off` those two
//     `li`s sink below the call.  CAUTION: 16 other mwcc prologues in .text DO
//     call `__savegpr_*`, which argues the whole SDK was built `off` -- so this
//     is NOT settled, but `on` is the only setting that can express this want's
//     prologue shape at all.
// (2) `a_hex`/`c_hex` ARE READ IN THE COMMON TAIL, NOT IN THE BRANCHES.  Both
//     branches end in `b 0x8028bb58` and the two `lwz r7,0x2c(r1)` /
//     `lwz r12,0x28(r1)` that feed the fog0/fog3 fields live there.  In the
//     draft (reads inside the proj branch) mwcc instead computes them eagerly
//     and parks them in callee-saved registers, which is what forces
//     `__savegpr_25`.  Moving both reads below the if/else and keeping the same
//     measured length kills 4 instructions and takes the best-SHIFTED match
//     count from 29/131 to 43/131 words (22.1% -> 32.8%): the object gets 4
//     words SHORTER at the front, so the index-aligned number printed by
//     mwcc_verify drops to 3.7% even though the body is much closer.  NOT
//     installed, because the prologue wall (savegpr vs 4x stw) makes the
//     index-aligned score the only number the tooling reports -- but it is the
//     single highest-value next step, together with (1).
// (3) The frame is 0x38 in the want with only 0x28..0x37 unused, i.e. 0x10
//     bytes of slack ABOVE a 4-register save area; the draft's frame is 0x58
//     (9 saved GPRs).  Both the frame size and the save-area OFFSET move with
//     the register count, so (1)+(2) have to land together before any frame
//     experiment is meaningful.
// STILL TRUE: the object carries a private 8-byte `.sdata2` for the int->f64
// magic (the want loads it from the game's pool at `lbl_803CC1A8`, i.e.
// -0x60d8(r13), while the draft gets -0x2280(r13) from its own pool).  That is
// a promote-time retarget, same class as tools/fix_fp_pool.py.
#include "types.h"

#if defined(__MWERKS__)
#include <dolphin/gx.h>
#include <dolphin/os.h>
#include <dolphin/gx/GX.h>
#include <dolphin/gx/GXInit.h>
#else
/* --- ngccc stand-ins (compile only; the function is mwcc codegen) --- */
typedef s32 GXFogType;
typedef struct _GXColor { u8 r, g, b, a; } GXColor;
typedef struct { u8 u8_; u16 u16_; u32 u32_; } PPCWGPipe;
extern volatile PPCWGPipe GXFIFO;
typedef struct { u16 vNumNot; u16 bpSentNot; } GXData;
extern GXData *const gx;
extern u32 __rlwimi(u32, u32, int, int, int);
#define GX_WRITE_U8(ub)     (GXFIFO.u8_ = (u8)(ub))
#define GX_WRITE_U32(ui)    (GXFIFO.u32_ = (u32)(ui))
#define ASSERTMSGLINE(l, c, m) (void)0
#endif

#ifdef SET_REG_FIELD
#undef SET_REG_FIELD
#endif
#define SET_REG_FIELD(line, reg, size, shift, val) \
do { \
    ASSERTMSGLINE(line, ((u32)(val) & ~((1 << (size)) - 1)) == 0, "GX Internal: Register field out of range"); \
    (reg) = ((u32)__rlwimi((u32)(reg), (val), (shift), 32 - (shift) - (size), 31 - (shift))); \
} while (0)

#ifndef OLD_SET_REG_FIELD
#define OLD_SET_REG_FIELD(line, reg, size, shift, val) \
do { \
    ASSERTMSGLINE(line, ((u32)(val) & ~((1 << (size)) - 1)) == 0, "GX Internal: Register field out of range"); \
    (reg) = ((u32)(reg) & ~(((1 << (size)) - 1) << (shift))) | ((u32)(val) << (shift)); \
} while (0)
#endif

#ifndef CHECK_GXBEGIN
#define CHECK_GXBEGIN(line, name) ASSERTMSGLINE(line, !__GXinBegin, "'" name "' is not allowed between GXBegin/GXEnd")
#endif

#ifndef __GXinBegin
extern u8 __GXinBegin;
#endif

#ifndef GX_WRITE_RAS_REG
#define GX_WRITE_RAS_REG(value) \
do { \
    GX_WRITE_U8(0x61); \
    GX_WRITE_U32(value); \
} while (0)
#endif

/* The game's real .sdata2 constant pool for this SDK object (see header). */
extern f32 lbl_803CC178;   /* 0.0f          r13-0x6108 */
extern f32 lbl_803CC17C;   /* 1.0f          r13-0x6104 */
extern f32 lbl_803CC180;   /* 0.5f          r13-0x6100 */
extern f64 lbl_803CC188;   /* 1.0           r13-0x60f8 */
extern f32 lbl_803CC190;   /* 2.0f          r13-0x60f0 */
extern f64 lbl_803CC198;   /* 0.5           r13-0x60e8 */
extern f32 lbl_803CC1A0;   /* 8388638.0f    r13-0x60e0 */
extern f64 lbl_803CC1A8;   /* 0x4330000080000000  r13-0x60d8 */

extern u32 __cvt_fp2unsigned(f32 f);

void GXSetFog(GXFogType type, f32 startz, f32 endz, f32 nearz, f32 farz, GXColor color) {
    u32 fogclr;
    u32 fog0;
    u32 fog1;
    u32 fog2;
    u32 fog3;
    f32 A;
    f32 B;
    f32 B_mant;
    f32 C;
    f32 a;
    f32 c;
    u32 B_expn;
    u32 b_m;
    u32 b_s;
    u32 a_hex;
    u32 c_hex;
    u32 fsel;
    u32 proj;

    fog1 = 0;
    fog2 = 0;

    CHECK_GXBEGIN(138, "GXSetFog");

    fsel = type & 7;
    proj = (type >> 3) & 1;

    if (proj) {
        if (farz == nearz || endz == startz) {
            a = lbl_803CC178;
            c = lbl_803CC178;
        } else {
            A = lbl_803CC17C / (endz - startz);
            a = A * (farz - nearz);
            c = A * (startz - nearz);
        }
        a_hex = *(u32 *)&a;
        c_hex = *(u32 *)&c;
    } else {
        if (farz == nearz || endz == startz) {
            A = lbl_803CC178;
            B = lbl_803CC180;
            C = lbl_803CC178;
        } else {
            A = (farz * nearz) / ((farz - nearz) * (endz - startz));
            B = farz / (farz - nearz);
            C = startz / (endz - startz);
        }

        B_mant = B;
        B_expn = 0;
        while (B_mant > lbl_803CC188) {
            B_mant *= lbl_803CC180;
            B_expn++;
        }
        while (B_mant > lbl_803CC178 && B_mant < lbl_803CC198) {
            B_mant *= lbl_803CC190;
            B_expn--;
        }

        c = C;
        /* NOTE (measured, 2026-10-02): the plain `(f32)(1 << b_s)` cast below is
         * CORRECT and must NOT be hand-written as a union. Want 0x8028BB08..BB38
         * computes b_s once and reuses it for both the shift and the fog2 field
         * (recomputed into r28 at 0x8028BB4C from the same value): it scales the
         * 8388638.0f constant by the mantissa, shifts 1 by b_s, flips the 0x8000
         * sign bit, stages the result with the 0x4330 bias high half in the
         * 0x30/0x34 stack slots, reloads the pair as a double, and subtracts the
         * bias double from its SDA slot (-0x60d8(r13)) — but that IS mwcc's own
         * unsigned-int->f64 lowering for the plain cast: with the union spelled out
         * by hand the sign-flip DISAPPEARS and the score drops 18.5% -> 16.8%.
         * Left as the plain cast deliberately. */
        b_s = B_expn + 1;
        a = A / (f32)(1 << b_s);
        a_hex = *(u32 *)&a;
        b_m = __cvt_fp2unsigned(lbl_803CC1A0 * B_mant);
        c_hex = *(u32 *)&c;

        OLD_SET_REG_FIELD(198, fog1, 24, 0, b_m);
        OLD_SET_REG_FIELD(199, fog1, 8, 24, 0xEF);

        OLD_SET_REG_FIELD(201, fog2, 5, 0, b_s);
        OLD_SET_REG_FIELD(202, fog2, 8, 24, 0xF0);
    }

    SET_REG_FIELD(209, fog0, 11, 0, (a_hex >> 12) & 0x7FF);
    SET_REG_FIELD(210, fog0, 8, 11, (a_hex >> 23) & 0xFF);
    SET_REG_FIELD(211, fog0, 1, 19, (a_hex >> 31));
    OLD_SET_REG_FIELD(212, fog0, 8, 24, 0xEE);
    GX_WRITE_RAS_REG(fog0);

    GX_WRITE_RAS_REG(fog1);
    GX_WRITE_RAS_REG(fog2);

    SET_REG_FIELD(214, fog3, 11, 0, (c_hex >> 12) & 0x7FF);
    SET_REG_FIELD(215, fog3, 8, 11, (c_hex >> 23) & 0xFF);
    SET_REG_FIELD(216, fog3, 1, 19, (c_hex >> 31));
    SET_REG_FIELD(217, fog3, 1, 20, proj);
    OLD_SET_REG_FIELD(218, fog3, 3, 21, fsel);
    OLD_SET_REG_FIELD(219, fog3, 8, 24, 0xF1);
    GX_WRITE_RAS_REG(fog3);

    SET_REG_FIELD(222, fogclr, 8, 16, color.r);
    SET_REG_FIELD(223, fogclr, 8, 8, color.g);
    SET_REG_FIELD(224, fogclr, 8, 0, color.b);
    OLD_SET_REG_FIELD(225, fogclr, 8, 24, 0xF2);
    GX_WRITE_RAS_REG(fogclr);

    gx->bpSentNot = 0;
}