// PARKED 2026-10-03: DIFF (baseline was FAIL — did not compile).
//
// Reproduce:  LEAF_TMPDIR=<private dir> tools/venv/bin/python tools/test_wip_drafts.py --addr 0x8005A7E8
//
// WHAT THIS IS: spot/point-light accumulation over an array of packed RGBA
// words. Semantics are now fully decoded (see notes at the bottom); the body
// below is instruction-shape-correct in both PS blobs and in the byte-clamp
// tail. It is NOT a masked-EXACT, and the pct is low (my own masked estimate
// ~5%; the official scorer reports only the DIFF bucket). It went DOWN from a
// naive draft only because the body is now the right LENGTH — the remaining
// gap is the frame size, and masked_pct is strictly positional, so a 16-byte
// frame miss shifts every word and flattens the score.
//
// REMAINING DIFF (the single blocker): the stack frame.
//   The want build reserves 0xf8 bytes of frame with the GPR save area based
//   at 0x84 covering 17 callee-saved registers and six callee-saved FPRs
//   covering 0xc8 through 0xf0, leaving 132 bytes of locals (0x00..0x83).
//   The current build reserves 0xd8 bytes with the GPR save area based at
//   0x74 covering 15 registers plus an r12 condition-register save and seven
//   FPRs covering 0xb0 through 0xe0, leaving 116 bytes of locals (0x00..0x73).
// .text is 976 B vs 992 B (3 words short) purely because of this.
//
// The want's local area has two 8-byte PS slots at 0x18 and 0x20 that this
// draft does not have, and the want emits dead paired-single stores of the f13
// value to stack offset 24 and the f9 value to stack offset 32 in the first
// loop body, and of f13 to offset 24 plus f12 to offset 32 in the second loop
// body — the SAME two slots in both loops, with
// f13 = the arg2-minus-light .xy pair and f9/f12 = the .zw pair. So `vx` and
// `vz` have home frame slots in the original and ngccc stores them at their
// definition but folds the PS-op uses to the register (never reloads 0x18 /
// 0x20). ngccc only gives an `SN_PS_type` a memory slot when its scalar half
// is read — `dot` (0x30) and `d2` (0x38) get slots because they are read back
// with `lfs`; `vx`/`vz` never are, so this draft keeps them in registers.
// (The other 76 B of the want's local area is unexplained padding/holes:
// 0x00-07, 0x14-17, 0x2C-2F, 0x40-77 (56 B), 0x80-83.)
//
// RULED OUT (all measured, don't repeat):
//  * Adding unused locals to grow the frame: 8 unused `__ps_t` / `SN_PS_type`
//    / `double` / `f32` locals -> frame UNCHANGED (0xd8). ngccc gives dead
//    locals no slot at all (confirms the house note in BRIEF.md).
//  * `volatile SN_PS_type vx, vz;` -> forces both slots and both dead stores
//    (frame 0xd8->0xe8) but ngccc then also RELOADS them: .text 1016 B
//    (>992) and frame still 0x10 short. Worse.
//  * `__ps_t vx, vz;` instead of `SN_PS_type` -> byte-identical output, no
//    slots, frame unchanged.
//  * Aggregating `out` as `struct { s32 w; u8 b[4]; }` -> frame unchanged
//    (0xd8), .text 976->980. +0.4% masked, kept the simpler form.
//
// MOST PROMISING NEXT IDEA: the want carries a dead loop-invariant
// `addi r19,r28,0x10` (= arg2+0x10) hoisted into loop 2's top block with
// `mr r19,r28` restored at the latch, and r19 is never read inside loop 2.
// That means the ORIGINAL source referenced `arg2 + 0x10` in an expression
// that ngccc's loop-invariant motion kept before dead-code elimination. A
// source shape that (a) references arg2+0x10 in loop 2 and (b) keeps two more
// PS values simultaneously live (so ngccc's PS allocator assigns them frame
// slots 0x18/0x20 and spills without reloading) should recover both the frame
// and the 4 missing instructions at once.
//
// ---------------------------------------------------------------------------
// SEMANTIC DECODE (all of this is verified against the want):
//  * args: r3=src (u32*), r4=dst (s32*), r5=arg2 (Vec4* — deref'd with
//    `psq_l` at +0 and +8), r6=arg3 (Vec4*, may be NULL), r7=n.
//  * lbl_8030089C = light count. lbl_80364CC8 = 150 lights of 0x28 B,
//    stride-indexed; fields used: +0x00 xy, +0x08 zw, +0x10 f10 (gain),
//    +0x14 f14 (radius^2), +0x1C/+0x1D/+0x1E = three u8 colour bytes.
//  * lbl_80293458 = PS-format {0.0f,0.0f} in .rodata2 — the `ps_merge00`
//    filler in BOTH dot products, i.e. both dots are written with a literal
//    4th term of 0.0f.  lbl_802934EC = 0.0f, lbl_802934F8 = 255.0f,
//    lbl_802934F0 = double 2^52 (the u32->double bias constant).
//  * loop 1 (select): per light, `dot = (arg2-L) . arg3 + 0.0f` via
//    ps_sub/ps_mul/ps_merge00/ps_madd/ps_sum0, stored to 0x30; `vis` is
//    1 when arg3 == NULL, else `(dot <= 0.0f)` (the `cror cr0eq,cr0lt` +
//    `bns` pair is the `a<=b` boolean). Then
//    `L->f10 > 0.0f && fn_8005A114(L, arg2) != 0 && vis` collects the index;
//    at most 3 (cmpwi cnt,2 / bgt). fn_8005A114 takes TWO args.
//  * if nothing was collected: `memcpy(dst, src, n*4)` and return.
//  * loop 2 (accumulate): per element, acc_r/acc_g/acc_b init to 0.0f; inner
//    loop over the collected lights computes `d2 = (arg2-L).(arg2-L) + 0.0f`
//    into 0x38, and if `d2 < L->f14 * L->f14` then
//    `k = L->f10 * ((L->f14 - sqrtf(d2)) / L->f14)` and
//    `acc += k * (f32)(f64)L->cN`.  The u8->float conversions go through the
//    2^52 double trick at 0x78/0x7c, shared with the clamp code.
//  * tail: `out = *src`, then per byte, `u = <the byte>`, `t = (f32)(f64)u +
//    acc`, clamp: `t > 255.0f ? 255 : (s32)t`, storing back into bytes 0,1,2
//    of the same word (byte 0 takes input byte 3 via `srwi r,r0,24`), then
//    `*dst = out`.
//
// m2c draft bugs that had to be fixed to get this far:
//  * `fn_8005A114(arg2)` — it is `fn_8005A114(Light*, Vec4*)`, 2 args.
//  * `sqrtf()` result unused in m2c; in fact `sqrtf` (0x80270CA4) returns its
//    value in BOTH f0 and f1 (`fmr f1,f0` right before `blr`), so the want's
//    post-call `fsubs f1,f0,f1` is `f14 - sqrtf(d2)`, NOT `f14 - d2`.
//  * `>> 0x18U` must stay unsigned: want is `srwi`, a signed shift gives
//    `srawi` + `xoris` and breaks the u32->double path.
//  * loop 2 walks src/dst as pointers (`lwz r0,0(r24)` / `stw r0,0(r23)`),
//    not `arg0[i]` (index arithmetic gives `slwi`/`lwzx`/`stwx`).
//  * `vis` must be materialised as 0/1 (`vis=0; if (dot<=0.0f) vis=1;`).
//    Assigning the boolean directly makes ngccc keep it in CR and emit
//    `mfcr` + `clrlwi r,r,31`.
//  * the PS sub/mul temps must be computed INSIDE `if (arg3 != 0)`; hoisting
//    them out lets ngccc sink them above the branch and changes block shape.
//  * inner-loop guard is `hit < cnt` (`cmpw r25,r21`), outer guard is
//    `cnt < n` (`cmpw r21,r0`) — not `n > 0` / `cnt > 0`.
// family=m2c range=0x8005A7E8-0x8005ABC8 size=992B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"

typedef struct {
    __ps_t xy;
    __ps_t zw;
} Vec4;

typedef struct {
    __ps_t xy;
    __ps_t zw;
    f32 f10;
    f32 f14;
    f32 f18;
    u8 c0;
    u8 c1;
    u8 c2;
    u8 c3;
    f32 f20;
    f32 f24;
} Light;

extern Light lbl_80364CC8[];
extern __ps_t lbl_80293458;
extern s32 lbl_8030089C;

s32 fn_8005A114(Light *arg0, Vec4 *arg1);
void *memcpy(void *, const void *, u32);
f32 sqrtf(f32);

void fn_8005A7E8(u32 *arg0, s32 *arg1, Vec4 *arg2, Vec4 *arg3, u32 arg4) {
    SN_PS_type vx;
    SN_PS_type vz;
    SN_PS_type dot;
    SN_PS_type d2;
    __ps_t t2;
    s32 list[3];
    Light *L;
    u32 i;
    s32 cnt;
    s32 vis;
    s32 hit;
    s32 j;
    s32 out;
    u8 *bp;
    u32 *sp;
    s32 *dp;
    f32 acc1;
    f32 acc0;
    f32 acc2;
    f32 t;
    f32 s;

    cnt = 0;
    if (cnt < lbl_8030089C) {
        for (i = 0; i < (u32)lbl_8030089C; i++) {
            vis = 1;
            if (arg3 != 0) {
                vz.ps = __builtin_ps_sub(arg2->zw, lbl_80364CC8[i].zw);
                vx.ps = __builtin_ps_sub(arg2->xy, lbl_80364CC8[i].xy);
                t2 = __builtin_ps_mul(arg3->zw, vz.ps);
                t2 = __builtin_ps_merge00(t2, lbl_80293458);
                dot.ps = __builtin_ps_madd(arg3->xy, vx.ps, t2);
                dot.ps = __builtin_ps_sum0(dot.ps, dot.ps, dot.ps);
                vis = 0;
                if (dot.flt.hi <= 0.0f) {
                    vis = 1;
                }
            }
            L = &lbl_80364CC8[i];
            if (L->f10 > 0.0f && fn_8005A114(L, arg2) != 0 && vis != 0) {
                list[cnt] = i;
                cnt++;
                if (cnt > 2) {
                    break;
                }
            }
        }
    }
    if (cnt == 0) {
        memcpy(arg1, (void *)arg0, arg4 * 4);
        return;
    }
    if (cnt > 0) {
        sp = arg0;
        dp = arg1;
        for (i = 0; i < arg4; i++) {
            acc1 = 0.0f;
            acc0 = acc1;
            acc2 = acc1;
            hit = 0;
            if (hit < cnt) {
                for (j = 0; j < cnt; j++) {
                    L = &lbl_80364CC8[list[j]];
                    vx.ps = __builtin_ps_sub(arg2->xy, L->xy);
                    vz.ps = __builtin_ps_sub(arg2->zw, L->zw);
                    t2 = __builtin_ps_mul(vz.ps, vz.ps);
                    t2 = __builtin_ps_merge00(t2, lbl_80293458);
                    d2.ps = __builtin_ps_madd(vx.ps, vx.ps, t2);
                    d2.ps = __builtin_ps_sum0(d2.ps, d2.ps, d2.ps);
                    if (d2.flt.hi < L->f14 * L->f14) {
                        s = sqrtf(d2.flt.hi);
                        hit = 1;
                        t = L->f10 * ((L->f14 - s) / L->f14);
                        acc2 += t * (f32)(f64)L->c2;
                        acc0 += t * (f32)(f64)L->c0;
                        acc1 += t * (f32)(f64)L->c1;
                    }
                }
            }
            if (hit != 0) {
                out = *sp;
                bp = (u8 *)&out;
                t = (f32)(f64)((u32)out >> 24) + acc0;
                bp[0] = t > 255.0f ? 255 : (s32)t;
                t = (f32)(f64)bp[1] + acc1;
                bp[1] = t > 255.0f ? 255 : (s32)t;
                t = (f32)(f64)bp[2] + acc2;
                bp[2] = t > 255.0f ? 255 : (s32)t;
                *dp = out;
                sp++;
                dp++;
            }
        }
    }
}
