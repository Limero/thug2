// PARKED 2026-10-03 (a41): NEAR 60.3% at the exact 716B size (was DIFF 24.6% /
// REFRESHED 2026-10-07 (scaffold/flag/volatile re-sweep): 60.3352% -> 63.1285% per-object flags: -mps-float -Os -> -mps-float
// 712B). Reproduce:
// LEAF_TMPDIR=<scratch> tools/venv/bin/python \
//     tools/test_wip_drafts.py --addr 0x80110B84
//   -> "NEAR  m2c  0x80110B84 (716B) 60.3%"   (flags -mps-float -Os)
// Body is honest C: no inline asm, no opcode transcription, no relocation
// pinning beyond `register ... __asm__("frN")` FPR register pins.
// INERT: not registered in splits.txt/configure.py. family=m2c
// range=0x80110B84-0x80110E50 size=716B — activate via tools/wip.py.
//
// WHAT THIS ROUND FIXED (24.6% -> 60.3%), in order of value:
//  1. SEMANTIC BUG: the QB_HEIGHT clamp read s.extent[7] (0x4C) but stored
//     s.extent[6] (0x48) — retail stores 0x4C. One wrong destination word.
//  2. FPR register pins restore the retail min/max pre-copy that 3.9.3
//     coalesces away. WANT keeps `fmr f13,f0` + `fmr f13,f11` for the max
//     clamp; unpinned GCC drops the copy entirely, which made the object ONE
//     WORD SHORT and shifted every later block (clamps 2/3, GetVector, the
//     whole PS tail, the QB_TEXTURE fallback and the epilogue) out of
//     positional alignment. `register f32 var_f13 __asm__("fr13")` forces the
//     copy. temp_f13/var_f13/var_f12/fb pin fr13/fr13/fr12/fr11.
//     NOTE the pin on temp_f13 IS load-bearing for the *existence* of the
//     fmr (unpinning it drops the score back to 20.8%), but it costs the
//     `fmuls f13,f13,f0` operand order in clamps 2/3 (see residual).
//  3. PS tail: hoisting the two loop-invariant pair loads into named
//     `__ps_t off` / `__ps_t zlo` locals stops GCC re-reading them after each
//     aliasing psq_st, taking the object from 724B to exactly 716B and
//     re-aligning the whole tail. 24.6 -> 49.2 (with 1+2) -> 60.3 (with 3).
//
// REMAINING 71 masked-word diffs, all regalloc/scheduler tie-breaks:
//  (a) 22 words — the whole paired-single tail (0x80110DA8..0x80110DFC).
//      Same 22-instruction count and same 8 loads/8 stores as WANT; only the
//      pair-register homes (f11/f9/f12/f10 vs f11/f13/f12/f0) and the
//      load/store interleave differ. See "RULED OUT" for the reload shape.
//  (b) 11+11 words — clamps 2 and 3 (0x80110CAC.., 0x80110D24..). Clamp 1
//      (0x80110C34..) is now byte-exact. Clamps 2/3 lose 6 words each to the
//      commutative `fmuls` operand order: because temp_f13 is pinned to fr13,
//      GCC loads the *constant* into f13 and the *parameter* into f0, giving
//      `fmuls f13,f0,f13` / `lis r9`+`lfs f0,0x60` where WANT has
//      `fmuls f13,f13,f0` / `lis r11`+`lfs f13,0x60`. Clamp 1 wins this coin
//      flip, 2 and 3 lose it. Source-order swap of the multiply operands
//      untried (would likely just move which clamp wins).
//  (c) 6 words — one per clamp: WANT compares against f0 (the fresh temp),
//      GCC's reload1 if_convert rewrites the condition onto the destination
//      register (`fcmpu cr0,f11,f12` / `fcmpu cr0,f11,f13`). This is
//      doc-74's GCC-2.95 float-select expansion; no source spelling reaches
//      it.
//
// RULED OUT (do not re-run):
//  * Hoisting the computed corner pairs into `__ps_t t0`/`t1` locals so both
//    stores share one register. GCC forwards EVERY reload away (716B ->
//    708B / 700B, 50.3%). WANT's reload asymmetry — no reload for the
//    pairs[1]/pairs[2] store-back but a reload of 0x48/0x50 for corner[2]/
//    corner[3] — is therefore unreachable: the memory-read form reloads
//    0x08/0x10 instead, and the register form reloads nothing. Forwarding is
//    all-or-nothing here (doc-06 M5.0n stale-register wall, confirmed).
//  * Pinning `pp` (the lo/hi temp) to fr0. Does not change the fcmpu operand
//    and re-flips the fmuls operand order.
//  * Unpinning temp_f13 from fr13 (20.8% — the fmr is required).
//  * The 12-store init block (0x80110BCC..0x80110C20) now matches positionally
//    as a side effect of the FPR pins; no longer a blocker. Do not spend
//    more time on store-order permutations for it.
// INERT: see above.
#include "types.h"
extern f32 lbl_8029CF74;
extern f32 lbl_8029CF78;
extern f32 lbl_8029CF7C;
extern f32 lbl_8029CF80;
#include "qb_constants.h"
#include "structs.h"
// FLAG: -mps-float
void fn_800071D4(void *);
s32 GetStructure_2(CStruct *, s32, CStruct **, s32);
s32 GetFloat(CStruct *, s32, f32 *, s32);
s32 GetVector(CStruct *, s32, f32 *, s32);
void fn_80005BD4(f32 *);
void fn_8006C694(void *);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
void fn_8006C780(s32);
void fn_8006C610(void);
typedef struct { f32 x, y, z, w; } Vec4;
typedef struct fn_80110B84_ctx {
    Vec4 corner[2];
    f32 offset[2];
    f32 extent[10];
    CStruct *texture;
    f32 parameter[3];
    s32 textureHandle;
} fn_80110B84_ctx;
bool ScriptKillAllTextureSplats(CStruct *arg0) {
    fn_80110B84_ctx s;
    register f32 temp_f13 __asm__("fr13");
    register f32 var_f12 __asm__("fr12");
    register f32 var_f13 __asm__("fr13");
    register f32 fb __asm__("fr11");
    register f32 pp;
    f32 *p1;
    f32 *p2;
    __ps_t *corner;
    __ps_t *pairs;
    __ps_t *offset_pair;
    __ps_t off;
    __ps_t zlo;
    f32 *offset;

    fn_800071D4(&s);
    s.texture = 0;
    s.textureHandle = 0;
    if (GetStructure_2(arg0, QB_BOX, &s.texture, 0) != 0) {
        p1 = &s.extent[2];
        p2 = &s.extent[6];
        p2[1] = lbl_8029CF74;
        p2[2] = lbl_8029CF74;
        p2[3] = lbl_8029CF78;
        s.extent[6] = lbl_8029CF74;
        p1[2] = lbl_8029CF74;
        p1[1] = lbl_8029CF74;
        p1[3] = lbl_8029CF78;
        s.extent[2] = lbl_8029CF74;
        s.extent[1] = lbl_8029CF74;
        s.parameter[0] = lbl_8029CF74;
        s.parameter[2] = lbl_8029CF74;
        s.parameter[1] = lbl_8029CF74;
        if (GetFloat(s.texture, QB_HEIGHT, &s.parameter[0], 1) != 0) {
            temp_f13 = s.parameter[0] * lbl_8029CF7C;
            fb = s.extent[3];
            s.parameter[0] = temp_f13;
            pp = (-temp_f13) * lbl_8029CF80;
            var_f12 = pp;
            if (fb < pp) {
                var_f12 = fb;
            }
            s.extent[3] = var_f12;
            fb = s.extent[7];
            pp = temp_f13 * lbl_8029CF80;
            var_f13 = pp;
            if (fb > pp) {
                var_f13 = fb;
            }
            s.extent[7] = var_f13;
        }
        if (GetFloat(s.texture, QB_DIST, &s.parameter[1], 1) != 0) {
            temp_f13 = s.parameter[1] * lbl_8029CF7C;
            fb = s.extent[4];
            s.parameter[1] = temp_f13;
            pp = (-temp_f13) * lbl_8029CF80;
            var_f12 = pp;
            if (fb < pp) {
                var_f12 = fb;
            }
            s.extent[4] = var_f12;
            fb = s.extent[8];
            pp = temp_f13 * lbl_8029CF80;
            var_f13 = pp;
            if (fb > pp) {
                var_f13 = fb;
            }
            s.extent[8] = var_f13;
        }
        if (GetFloat(s.texture, QB_WIDTH, &s.parameter[2], 1) != 0) {
            temp_f13 = s.parameter[2] * lbl_8029CF7C;
            fb = s.extent[2];
            s.parameter[2] = temp_f13;
            pp = (-temp_f13) * lbl_8029CF80;
            var_f12 = pp;
            if (fb < pp) {
                var_f12 = fb;
            }
            s.extent[2] = var_f12;
            fb = s.extent[6];
            pp = temp_f13 * lbl_8029CF80;
            var_f13 = pp;
            if (fb > pp) {
                var_f13 = fb;
            }
            s.extent[6] = var_f13;
        }
        offset = s.offset;
        if (GetVector(s.texture, QB_OFFSET, offset, 1) != 0) {
            fn_80005BD4(offset);
        }
        corner = (__ps_t *)&s.corner[0];
        pairs = (__ps_t *)&s.extent[0];
        offset_pair = (__ps_t *)&s.offset[0];
        off = offset_pair[0];
        zlo = pairs[0];
        corner[0] = pairs[1] + off;
        corner[1] = pairs[2] + zlo;
        pairs[3] += off;
        pairs[4] += zlo;
        pairs[1] = corner[0];
        pairs[2] = corner[1];
        corner[2] = pairs[3];
        corner[3] = pairs[4];
        fn_8006C694(s.corner);
    } else if (GetChecksum_2(arg0, QB_TEXTURE, &s.textureHandle, 0) != 0) {
        fn_8006C780(s.textureHandle);
    } else {
        fn_8006C610();
    }
    return true;
}
