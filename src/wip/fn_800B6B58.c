// WIP DRAFT (non-matching) — HAND-REBUILT 2026-09-27 from the retail
// 0x800B6B58..0x800B6CA4 instruction stream. The old m2c body was a statics
// husk (8x `0;`, its object was far smaller than retail and every opcode-4
// word had collapsed into a single `fmsubs`); it is gone.
//
// family=m2c range=0x800B6B58-0x800B6CA4 size=332B
// extra_cflags: -mps-float
// FLAG: -fno-schedule-insns
//
// PARKED 2026-10-06: re-audited against the
// retail stream; verdict unchanged (DIFF). Object 304B vs want 332B (7 words
// short), and the residual is exactly the register-web-split copies this header
// already lists: +0x04 `mr r9,r3` (a's address web split r9 reads / r3 writes),
// +0x10 `addi r11,r1,8` (&w0 materialised once), the four ps_mr value-home
// copies (+0x48 f11<-f0, +0x78 f10<-f13, +0xEC f13<-f0, +0x138 fmr f0<-f13) and
// the second fmr f13,f4 for the stfs 0x80, plus the uniform f0..f12 vs f4..f13
// FPR colouring. Each is a load/store whose operand sits in a different register
// than the value's home; an empty-asm barrier or "+r"/"+f" wedge cannot force
// one, and emitting them literally needs an asm template (banned for a draft).
// No new semantic/type lever found (arg quads are 16-byte {x,y,z,w} f32, the
// two rodata operand forms lbl_80298828/lbl_80298994 are correct, the frame is
// the 18-slot 0x98 map). Body left unchanged as the current best (31/83 words
// in-order with the header flags); needs the original C statement shape.
//
// INERT: not registered in splits.txt/configure.py — never compiled by the
// real build, not counted in objdiff progress. activate via tools/wip.py.
//
// ---------------------------------------------------------------- WHAT IT IS
// A paired-single "quaternion-shaped" product. Signature is
// fn(Quat *a, Quat *b): BOTH args are 16-byte {x,y,z,w} f32 quads, and *a is
// read in full before any store, so it is a genuine in/out. Retail copies the
// 0x98 frame of 9 two-pair work quaternions, and the recovered arithmetic is
//
//   a.x = a.w*b.x + a.x*b.w + (a.y*b.z - a.z*b.y)
//   a.y = a.w*b.y + a.y*b.w + (a.z*b.x - a.x*b.z)
//   a.z = a.w*b.z + a.z*b.w + (a.y*b.z - a.z*b.y)      <-- see note (3)
//   a.w = a.w*b.w - 2*(a.x*b.x + a.z*b.z)
//
// i.e. the vector part of a Hamilton product a (x) b, but the scalar is NOT
// a.w*b.w - (a.x*b.x + a.y*b.y + a.z*b.z): the a.y*b.y product is never
// subtracted, and the a.z*b.z term is negated by a memory operand. See the
// two notes below — both are real retail behaviour, not transcription slips.
// Callers: only fn_800B6A88 @0x800B6B20 and @0x800B6B2C, which build two
// quads on its own frame (sp+0x08 and sp+0x18, out = sp+0x28) and call this
// twice with the same out pointer.
//
// ------------------------------------------------------- THE THREE FIXES
// (1) SIt IS PAIRED-SINGLE CODE, all of it. The m2c draft read it as scalar
//     f32 because m2c has no Gekko PS support. Every opcode-4 word in the
//     range was hand-decoded (raw words dumped; psq_l/st fields are
//     fD=r bits 6-10 / rA 11-15 / W 16 / I 17-19 / d 20-31, and A-form is
//     D 6-10 / A 11-15 / B 16-20 / C 21-25 / XO5 26-30):
//       ps_muls0 = A*C[+0] broadcast      ps_mul  = A*C
//       ps_madd  = A*C + B (A/B/C = 11-15/16-20/21-25 — NOT the A*B+C that
//                  the Gekko docs' operand listing suggests; verified against
//                  the 0x6C80 site, which only comes out right as A*C+B)
//       ps_sum0  = {A[+0]+B[+0], C[+4]}   ps_merge00 = {A[+0], B[+0]}
//       ps_merge10 = {A[+4], B[+0]}       ps_mr    = X-form xo10=72
//     All of it is emittable from C with `-mps-float` + `__builtin_ps_*`
//     (__ps_t is a cc1 builtin mode(PS) type; no SN_PS.h include needed
//     because the sweep strips includes).
// (2) THE FRAME IS 18 PS SLOTS, NOT A HANDFUL OF TEMPORARIES. 9 work
//     quaternions x 2 pairs = 0x90 bytes, plus GCC 2.95's 8-byte floor pad
//     = 0x98, which is retail's `stwu r1,-0x98(r1)` EXACTLY. Declaring them
//     as one local `struct { volatile __ps_t p0, p1; }` reproduces the
//     declaration-order slot assignment byte for byte:
//        w0 = 0x08/0x10  w1 = 0x18/0x20  w2 = 0x28/0x30  w3 = 0x38/0x40
//        w4 = 0x48/0x50  w5 = 0x58/0x60  w6 = 0x68/0x70  w7 = 0x78/0x80
//        w8 = 0x88/0x90
//     and all 20 store / 9 load displacements match retail (verified by
//     histogram: st 8,16,24,32,40,48,56,64,72,80,88,96,104,112,136,144
//     + stfs 0x78,0x80,0x8c ; ld 8,16(x4),0x28,0x2c,0x30,0x78,0x80,0x88,0x90).
//     The `volatile` on the members is load-BEARING and is the only way found
//     to reproduce retail's memory traffic: it makes each member read a real
//     psq_l (w0.p1 is read THREE times from 0x10, w0.p0 once from 0x08)
//     instead of a forwarded value, it makes single-lane writes a 4-byte
//     `stfs` into the pair (`((volatile f32 *)&w7.p0)[0] = a->w`), and —
//     because GCC 2.95 does no DSE — it preserves the ELEVEN write-only work
//     quaternions (w1,w3,w4,w5,w6 and the second halves) whose only effect
//     in retail is a dead psq_st. The w3/w4/w5/w6 values are therefore
//     written to their slot AND kept in a register, which is exactly what
//     retail does (it never reloads 0x38/0x40/0x48/0x50/0x58/0x60/0x68/0x70).
//     Non-volatile members let GCC forward the arg loads and drop the
//     multi-lane write-only stores, and the whole frame collapses.
// (3) TWO REAL QUIRKS, both reproduced rather than "fixed":
//     (a) 0x8c — the `lbl_80298994` (1.0f) store lands in the HI LANE of the
//         w8.p0 pair, i.e. it OVERWRITES the pair's upper half between the
//         `psq_st` (0x800B6C18) and the reload (0x800B6C38). The reload
//         therefore yields (d.lo, 1.0f) and only the low lane is used, so
//         the store is semantically dead. C: `((volatile f32 *)&w8.p0)[1]`.
//     (b) the final `madd` is fed by `merge00(a.z*b.z, a.z*b.z) - lbl_80298828`
//         — the pair AT lbl_80298828 (.rodata2, size 0x3C, all zeros in this
//         DOL) is the memory operand that negates the a.z*b.z term, and the
//         a.y*b.y product lands in the dead hi lane with it. So
//         a.w = a.w*b.w - 2*(a.x*b.x + a.z*b.z) - 2*0.0f, i.e. the a.y*b.y
//         product is genuinely dropped. Do not "fix" this into a textbook
//         quaternion product.
//     Also note w2.p0[+0]/[+4] and w2.p1[+0] are read back with three `lfs`
//     (0x28/0x2c/0x30) and stored to a->x/y/z, and the tail is
//     `fmsubs f5,f5,f4,f0` = a->w * b->w - w8.p1[+0].
//
// --------------------------------------------------------- REPRODUCTION NOTES
// * `awc`/`bwc` plus an empty `"+f"` asm barrier: the ONLY way found to make
//   ngccc emit retail's `fmr f13,f5` / `fmr f13,f4` before the two 0x78/0x80
//   stfs (a->w and b->w must sit in two webs, not one). The barriers contain
//   no instructions, only a constraint reference — no asm templates anywhere
//   in this file.
// * `-fno-schedule-insns` (§4r / recipe 48 family) roughly doubles the
//   in-order match (16 -> 31 of 83) and is size-neutral. Without it ngccc's
//   scheduler interleaves the dead store-run differently.
// * retail reaches its operands through `r9` (= arg0, split from r3) and
//   through `r11` (= r1+8, the &w0 base); this build keeps everything on r3
//   and r1+disp. Not reachable from C here (see RESIDUAL).
//
// ------------------------------------------------------------------ VERDICT
// NOT EXACT.  76 words / 304B compiled vs retail 83 words / 332B (size
// MINUS 28B).  Frame, prologue, epilogue, the 0x98 slot map, all 20 stores,
// all 9 loads, the lbl_80298994 / lbl_80298828 address forms and the whole
// opcode-4 stream are present and in the right order; 31/83 retail words
// match in-order (LCS) and only 2/83 match positionally, because the two
// streams are offset by the 7 missing words below.
//   tools/test_wip_drafts.py --addr 0x800B6B58  -> DIFF, 2/83 masked
//     (that tool ignores the FLAG line, so it scores the flagless build; the
//      flag changes instruction ORDER only, not size or opcode content)
//   with the header's -fno-schedule-insns: 31/83 in-order, 76 words
//
// RESIDUAL — exactly 7 words, ALL of them register-web-split copies that
// this cc1 never emits from C (each is a load/store whose operand lands in a
// different register than the value's home; an empty-asm barrier cannot
// force one, and the only way to emit them literally would be an asm
// template, which is out of bounds for a draft):
//   +0x04  mr r9, r3         a's address web splits into r9 (reads) / r3 (writes)
//   +0x10  addi r11, r1, 8    &w0 materialised once, then `8(r11)` for w0.p1
//   +0x40  fmr f13, f4       b->w copy for the stfs 0x80 (only the a->w
//                            twin at +0x24 is reproduced)
//   +0x48  ps_mr f11, f0     w7.p0 reload lands in f0, the value is wanted in f11
//   +0x78  ps_mr f10, f13    w7.p1 reload lands in f13, the value is wanted in f10
//   +0xEC  ps_mr f13, f0     w8.p0 reload lands in f0, the value is wanted in f13
//   +0x138 fmr f0, f13       w8.p1 lane load lands in f13, the fmsubs wants f0
// Plus a uniform FPR COLOURING shift (retail f4..f13, this build f0..f12 with
// f13/f0 swapped in places) which is downstream of the same splits, and
// retail's two extra arg reloads `psq_l f13,0(r4)` / `psq_l f0,8(r4)` at
// +0x60/+0x70 (this build forwards blo/bhi into the w1.p0/w1.p1 stores).
// Tried and rejected: `volatile` pointer for &w0 (adds stack traffic),
// "+r"/"+f" barriers on the reload results and on the pointer (no effect),
// decl-init vs assignment, variable reuse for web splits, `extern f32*`/
// `sn_ps*volatile` hoisting of the two rodata addresses, and 8 scheduling
// flags (-fno-schedule-insns{,2}, -fno-gcse, -fno-sched-spec,
// -fno-expensive-optimizations, -fno-rerun-cse-after-loop, -fno-thread-jumps).
// Park: needs the original C statement shape, not a flag or a barrier.
#include "types.h"

/* 9 two-pair work quaternions; volatile members force retail's psq_l/st
   traffic and keep the write-only ones (see note (2) in the header). */
typedef struct { volatile __ps_t p0, p1; } W;
typedef struct { f32 x, y, z, w; } Q;

extern f32 lbl_80298828[];   /* .rodata2, size 0x3C, all zeros: the a.z*b.z
                                negation operand in the final ps_madd */
extern f32 lbl_80298994;      /* 1.0f: stored to w8.p0's high lane, dead */

void fn_800B6B58(Q *a, Q *b) {
    W w0, w1, w2, w3, w4, w5, w6, w7, w8;
    __ps_t alo, ahi, blo, bhi, m12, awp, bwp;
    __ps_t t1, t0, u0, u1, a0, a1, d, m01, m10, dd, ee, d2, r2p, g, zb;
    f32 aw, bw, awc, bwc;

    blo = *(__ps_t *)&b->x;
    bhi = *(__ps_t *)&b->z;
    w0.p0 = *(__ps_t *)&a->x;
    aw = a->w;
    bw = b->w;
    awc = aw;
    __asm__("" : "+f"(awc));
    bwc = bw;
    __asm__("" : "+f"(bwc));
    ((volatile f32 *)&w7.p0)[0] = awc;
    ((volatile f32 *)&w7.p1)[0] = bwc;
    w0.p1 = *(__ps_t *)&a->z;
    m12 = __builtin_ps_merge10(blo, bhi);
    awp = w7.p0;
    t0 = __builtin_ps_muls0(bhi, awp);
    w4.p1 = t0;
    t1 = __builtin_ps_muls0(blo, awp);
    w4.p0 = t1;
    w1.p0 = *(__ps_t *)&b->x;
    w1.p1 = *(__ps_t *)&b->z;
    bwp = w7.p1;
    alo = w0.p0;
    u0 = __builtin_ps_muls0(alo, bwp);
    w5.p0 = u0;
    ahi = w0.p1;
    a0 = __builtin_ps_add(t1, u0);
    w3.p0 = a0;
    u1 = __builtin_ps_muls0(ahi, bwp);
    w5.p1 = u1;
    a1 = __builtin_ps_add(t0, u1);
    w3.p1 = a1;
    d = __builtin_ps_mul(alo, m12);
    m10 = __builtin_ps_merge00(blo, bhi);
    dd = __builtin_ps_mul(__builtin_ps_merge10(alo, w0.p1), blo);
    d = __builtin_ps_sub(d, dd);
    w8.p0 = __builtin_ps_merge00(d, d);
    m01 = __builtin_ps_merge00(w0.p1, alo);
    ee = __builtin_ps_mul(m01, m10);
    ((volatile f32 *)&w8.p0)[1] = lbl_80298994;
    ee = __builtin_ps_sub(ee, __builtin_ps_merge10(ee, ee));
    d2 = __builtin_ps_merge10(d, ee);
    r2p = w8.p0;
    w2.p0 = __builtin_ps_add(a0, d2);
    w6.p0 = d2;
    w6.p1 = r2p;
    w2.p1 = __builtin_ps_add(a1, r2p);

    a->x = ((volatile f32 *)&w2.p0)[0];
    a->y = ((volatile f32 *)&w2.p0)[1];
    a->z = ((volatile f32 *)&w2.p1)[0];

    ee = __builtin_ps_mul(w0.p1, bhi);
    zb = *(__ps_t *)lbl_80298828;
    g = __builtin_ps_madd(alo, blo, __builtin_ps_merge00(ee, zb));
    w8.p1 = __builtin_ps_sum0(g, g, g);
    a->w = aw * bw - ((volatile f32 *)&w8.p1)[0];
}
