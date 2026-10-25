// WIP DRAFT (non-matching) — hand-rebuilt from the want disassembly
// 2026-10-08: 78.61% -> **78.9%** (official) from one pin: `temp_r0` ->
// `register u32 temp_r0 __asm__("r0")`.
// family=m2c range=0x80123BE0-0x80124110 size=1328B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// Reproduce with
//   LEAF_TMPDIR=<yourdir> tools/venv/bin/python tools/test_wip_drafts.py --addr 0x80123BE0
// NEAR, masked 78.61%, object .text 1328B == want 1328B (was DIFF 16.27%).
//
// TYPE CORRECTIONS OVER THE m2c BODY (all hand-decoded from the want):
//   * lbl_8039C2AC is an f32 (stfs/fcmpu/fdivs in the want), not s32 — the
//     m2c `*(s32 *)&lbl_8039C2AC` made ngccc emit fctiwz+stfd+lwz+stw round
//     trips at all 3 clamp stores and an extra f30 FPR save.
//   * every int->double cast here is the UNSIGNED 2^52 form (no `xoris`),
//     i.e. the operand is a u32 (`*(s32 *)&lbl_8039BE78` -> `*(u32 *)`).
//     0x8029E3A0/A4/A8/AC = 0.005f/1.0f/0.00125f/32000.0f (all f32).
//   * `+0x146` on the voice struct is an lhz (u16) field.
//   * lbl_8039BE74 is an lbz/stb u8 byte, not a word; the table at
//     lbl_8039BE6C is u32[] (pointer array), so `+0x400` is byte arithmetic.
//   * all callees need prototypes: the want has no `crclr cr1eq` before any
//     bl (recipes item 16 / 4).  memset's size arg must be s32, NOT u32 —
//     `void *memset(void *,s32,u32)` re-introduces a crclr before the call.
//   * 0x8039BEA4 / 0x8039C0A4 are the `lbl_` symbols (want: lis+addi base
//     registers r24/r21 hoisted into the loop preheader), not literals.
//   * frame: want stwu -0x60 / stmw r19,0x24 / stfd f31,0x58, i.e. 13
//     callee-saved GPRs + ONE `volatile double` (int->f64 temp at 0x18).
//   * `off = (i << 5) & 0x1E0` gets strength-reduced by the loop IV pass
//     (addi + rlwinm SH=0); `(i & 0xF) * 0x20` keeps the counter-derived
//     `rlwinm rD,rI,5,23,26` the want uses.  Same rlwinm encoding either way.
//   * `ctx = (char *)lbl_8037B5E8;` must be ASSIGNED INSIDE the loop body:
//     the loop optimizer then hoists the 2-insn lis+addi into the PREHEADER,
//     which is where the want has it (an assignment before the loop stays in
//     the preamble and shifts the whole loop by 2 words).
//   * the 2nd ARQPostRequest's source/length args MUST be computed into
//     locals before the 1st call (see notes below) — that is what makes
//     ngccc emit `addi r29,src,0x400` / `add r31,len,len` before the call.
//
// PARKED 2026-10-03: 78.6% masked, 1328B/1328B size-EXACT.
//   Residual = 71 words, all INSIDE the two ARQPostRequest argument blocks
//   (~38) plus register-number roulette in the first ~30 words (r0 vs r8
//   for the state temp, r19 vs r20 for the hi(0x8039C2B4) base, r21/r22 vs
//   r21/r23 for the second request base) and one GCC reassociation
//   (`a - (b - 0x400)` is canonicalised to `(b + 0x400) - a`).
//   PROVEN BLOCKER: the want computes arg0 (`add r3,off+base`) as the FIRST
//   instruction of each argument block and evaluates the remaining args in
//   reverse-arg order (len2 parts before len1, src1 before arg3's li), which
//   is expand_call's reverse emission; ngccc's scheduler keeps arg0 LAST
//   instead of floating it to the head.  Every attempt to pull it forward
//   from C either (a) did not change the RTL order (hoisting arg0 into a
//   local: the copy is still sunk to the call) or (b) added an extra insn to
//   the loop body (+1 word -> the whole 58-insn loop 1 and 48-insn loop 2
//   lose positional alignment, which is worth far more than the 19 words the
//   reorder would win).  Both loops are already length-exact, so this is a
//   scheduling-order residual, not a structural one.
#include "types.h"

void fn_8011E8D0(void);
void AXSetVoiceState(void *, s32);
void AXSetVoiceSrcRatio(void *, f32);
void DCFlushRange(void *, void *);
void *memset(void *, s32, s32);
void fn_80123A98(s32, s32);
s32 ARQPostRequest(void *, s32, s32, s32, s32, s32, s32, s32);

extern char lbl_8037B5E8[];
extern u32 lbl_8039BE6C[];
extern u32 lbl_8039BE5C;
extern u32 lbl_8039BE60;
extern u32 lbl_8039BE64;
extern u8 lbl_8039BE74;
extern u32 lbl_8039BE78;
extern s32 lbl_8039BE7C;
extern char lbl_8039BE9C[];
extern char lbl_8039BEA4[];
extern u32 lbl_8039C2A4;
extern s32 lbl_8039C2A8;
extern f32 lbl_8039C2AC;
extern u32 lbl_8039C2B0;
extern s32 lbl_8039C2B4;
extern f32 lbl_8029E3A0;
extern f32 lbl_8029E3A4;
extern f32 lbl_8029E3A8;
extern f32 lbl_8029E3AC;

void fn_80123BE0(void) {
    volatile double _dummy;
    register u32 temp_r0 __asm__("r0");   /* 2026-10-08 pin-sweep +0.3 */
    u32 temp_r6;
    u32 temp_r8;
    u32 temp_r9;
    u32 temp_r10;
    u32 temp_r11;
    u32 temp_r25;
    u32 temp_r30;
    u32 temp_r31;
    u32 var_r0;
    u32 var_r27;
    u32 var_r28;
    char *ctx;
    char *req1;
    u32 off;
    u32 src2;
    u32 len2;
    f32 var_f11;
    f32 temp_f0;
    f32 temp_f0b;
    f32 temp_f10;
    f32 temp_f31;

    fn_8011E8D0();
    temp_r0 = lbl_8039C2B4;
    if (temp_r0 == 1) {
        AXSetVoiceState(*(s32 *)&lbl_8039BE9C, 1);
        AXSetVoiceState(*(s32 *)((char *)&lbl_8039BE9C + 4), 1);
        lbl_8039C2B4 = 2;
        goto block_4;
    }
    if ((temp_r0 != 2) || (*(u16 *)(*(s32 *)&lbl_8039BE9C + 0x146) != 0)) {
block_4:
        temp_r8 = lbl_8039C2A4;
        temp_r10 = *(s32 *)(*(s32 *)&lbl_8039BE9C + 0x1B2);
        if (temp_r10 >= temp_r8) {
            lbl_8039C2A8 = lbl_8039C2A8 + (temp_r10 - temp_r8);
        } else {
            lbl_8039C2A8 = lbl_8039C2A8 + (temp_r10 - (temp_r8 - 0x400));
        }
        temp_r9 = lbl_8039C2A8;
        lbl_8039C2A4 = temp_r10;
        if (temp_r9 <= 0x1FFU) {
            return;
        }
        temp_r25 = temp_r9 >> 9;
        if (temp_r25 > 2U) {
            lbl_8039BE7C = 0;
        }
        if (lbl_8039BE7C != 0) {
            temp_r10 = lbl_8039BE60;
            temp_r0 = lbl_8039BE64;
            if (temp_r10 >= temp_r0) {
                var_r0 = temp_r10 - temp_r0;
            } else {
                var_r0 = lbl_8039BE5C - (temp_r0 - temp_r10);
            }
            temp_r31 = var_r0 >> 9;
            if (lbl_8039C2B4 == 2) {
                temp_r6 = lbl_8039C2B0;
                if (temp_r31 < temp_r6) {
                    var_f11 = (f32)(f64)lbl_8039BE78 * (lbl_8029E3A4 - ((f32)(f64)(temp_r6 - temp_r31) * lbl_8029E3A0));
                } else {
                    var_f11 = (f32)(f64)lbl_8039BE78;
                }
                temp_f10 = lbl_8039C2AC;
                if (temp_f10 < var_f11) {
                    temp_f0 = ((f32)(f64)lbl_8039BE78 * lbl_8029E3A8) + temp_f10;
                    lbl_8039C2AC = temp_f0;
                    if (temp_f0 > var_f11) {
                        lbl_8039C2AC = var_f11;
                    }
                } else {
                    temp_f0b = temp_f10 - ((f32)(f64)lbl_8039BE78 * lbl_8029E3A8);
                    lbl_8039C2AC = temp_f0b;
                    if (temp_f0b < var_f11) {
                        lbl_8039C2AC = var_f11;
                    }
                }
                temp_f31 = lbl_8029E3AC;
                AXSetVoiceSrcRatio(*(s32 *)&lbl_8039BE9C, lbl_8039C2AC / temp_f31);
                AXSetVoiceSrcRatio(*(s32 *)((char *)&lbl_8039BE9C + 4), lbl_8039C2AC / temp_f31);
            }
            var_r28 = temp_r31;
            if (var_r28 > temp_r25) {
                var_r28 = temp_r25;
            }
            if (var_r28 != 0) {
                lbl_8039C2A8 = lbl_8039C2A8 - (var_r28 << 9);
                for (var_r27 = 0; var_r27 < var_r28; var_r27++) {
                    ctx = (char *)lbl_8037B5E8;
                    temp_r30 = lbl_8039BE5C - lbl_8039BE64;
                    if (temp_r30 <= 0x1FFU) {
                        fn_80123A98(0U, temp_r30);
                        fn_80123A98(temp_r30, 0x200 - temp_r30);
                    } else {
                        fn_80123A98(0U, 0x200U);
                    }
                    off = (var_r27 & 0xF) * 0x20;
                    DCFlushRange(lbl_8039BE6C[lbl_8039BE74], 0x800);
                    req1 = (char *)&lbl_8039BEA4 + off;
                    temp_r0 = *(u32 *)(ctx + 0x198) >> 1;
                    src2 = lbl_8039BE6C[lbl_8039BE74] + 0x400;
                    len2 = (temp_r0 + ((lbl_8039BE74 << 9) + 0x400)) * 2;
                    ARQPostRequest(req1, 0, 0, 1, lbl_8039BE6C[lbl_8039BE74],
                                   (temp_r0 + (lbl_8039BE74 << 9)) * 2, 0x400, 0);
                    ARQPostRequest((char *)&lbl_8039BEA4 + 0x200 + off, 1, 0, 1, src2, len2, 0x400, 0);
                    lbl_8039BE74 = (u8)((lbl_8039BE74 + 1) & 1);
                }
            } else {
                return;
            }
        } else {
            lbl_8039C2A8 = lbl_8039C2A8 - (temp_r25 << 9);
            for (var_r27 = 0; var_r27 < temp_r25; var_r27++) {
                ctx = (char *)lbl_8037B5E8;
                off = (var_r27 & 0xF) * 0x20;
                memset(lbl_8039BE6C[lbl_8039BE74], 0, 0x800);
                DCFlushRange(lbl_8039BE6C[lbl_8039BE74], 0x800);
                req1 = (char *)&lbl_8039BEA4 + off;
                temp_r0 = *(u32 *)(ctx + 0x198) >> 1;
                src2 = lbl_8039BE6C[lbl_8039BE74] + 0x200;
                len2 = (temp_r0 + ((lbl_8039BE74 << 9) + 0x400)) * 2;
                ARQPostRequest(req1, 0, 0, 1, lbl_8039BE6C[lbl_8039BE74],
                               (temp_r0 + (lbl_8039BE74 << 9)) * 2, 0x400, 0);
                ARQPostRequest((char *)&lbl_8039BEA4 + 0x200 + off, 1, 0, 1, src2, len2, 0x400, 0);
                lbl_8039BE74 = (u8)((lbl_8039BE74 + 1) & 1);
            }
        }
block_37:
        if (lbl_8039C2B4 == 0) {
            lbl_8039C2B4 = 1;
        }
    }
}