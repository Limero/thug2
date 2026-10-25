// WIP DRAFT - PARKED (full C reconstruction from disasm; 7.21% -> 15.32%)
// family=m2c range=0x800639E8-0x80064294 size=2220B
// extra_cflags: -mps-float
// INERT: not registered in splits.txt/configure.py - never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// MEASURED: object 2224 B vs want 2220 B (1 word long), 85/555 words match
// = 15.32% (tools/ps_diff.py 0x800639E8, official verdict DIFF).
// Previous best in this file was 7.21% at 2272 B.
//
// WHAT THIS ROUND FIXED (all four are SEMANTIC bugs found by re-reading the
// want, not scheduling tweaks; together 7.21% -> 15.32% and -48 B of size):
//  S1. STRUCT: the 5th flag lives at 0x134, not 0x138. The want reads
//      0x130 / 0x134 / 0x13C / 0x140 / 0x14C / 0x160 (lwz r0,0x134(r31) at
//      0x8006403C is the vertex-offset test). The draft had `pad0x134[4]` then
//      `i134`, i.e. 0x138.
//  S2. VERTEX OFFSET VECTOR: 0x28 is a plain float[4] read as SCALARS
//      0x28 / 0x2C / 0x30 in the vertex loop (`lfs f10,0x28(r31)`,
//      `lfs f9,0x2c(r31)`, `lfs f12,0x30(r31)`), i.e. v28.hi / v28.lo /
//      v30.hi. The draft used v28.hi / v30.lo(0x34) / v38.hi(0x38).
//      The PS block still reads the same 12 floats as pairs 0x28/0x30/0x38/0x40.
//  S3. `self->verts` MUST be hoisted into a local `f32 *vp`: the want loads
//      0x124 ONCE per inner-loop body (`lwz r9,0x124(r31)` then
//      `stfsx`/`add r9,r9,r11`/`stfs 8(r9)`/`stfs 4(r9)`), while
//      `self->slots` (0x100) is deliberately RELOADED three times per store
//      group. Hoisting the pointer is worth 8 words of size; hoisting `slots`
//      would be wrong.
//  S4. The `f[11]` random has NO 2x-1 wrapper. Want:
//      `lfd;fsub;frsp;fmuls` then straight into `fmadds f13,f13,f0,f9`
//      (0x80063FB0..0x80063FE4 and 0x800641CC..0x800641F8) - no
//      `fadds f0,f0,f0` / `fsubs`. Only the u/v/w/sc/sG uses have it.
//      So `RR()` = `(f32)((f64)rand() * lbl_80294078)`, `RR2(a,b)` =
//      `2.0f * ((f32)((f64)rand()) * (a)) - (b)`.
//  Also: the `Q -> out` copy must be written AFTER the `f[0..2]` stores, not
//  before them; 3.9.3 hoists it above them otherwise and the vertex then
//  comes from Q instead of P (the want stores P, reads it, then stores Q).
//
// WHAT MATCHES THE WANT EXACTLY NOW
//  - every local stack displacement in 0x48..0xF0 (verified by dumping the
//    set of r1 displacements of both listings and diffing them),
//  - the whole PS opcode census: 98 paired-single instructions, identical
//    opcode mix (psq_l 28 / psq_st 33 / ps_mr 7 / ps_muls0 14 / ps_add 10 /
//    ps_sub 2 / ps_mul 1 / ps_merge00 1 / ps_madd 1 / ps_sum0 1),
//  - the int->float conversion idiom (`xoris 0x8000` + the 0x43300000 magic
//    word + `fsub`/`frsp`) and hence the `(f64)rand()` spelling,
//  - 7 saved FPRs (f25-f31), and 6 of the 7 loop-invariant constants held in
//    callee-saved registers across the outer loop.
//
// REMAINING BLOCKERS (why this is parked; doc-06 M5.0o/M5.0r class)
//  B1. FRAME 0x1a8 vs WANT 0x1a0, caused by TWO independent 8-byte effects:
//      (a) the local area is 8 bytes longer, so the rand magic double sits at
//          0x138/0x13C instead of 0x130/0x134, and
//      (b) only r21-r31 are saved (11 GPRs, `stmw r21,0x144`) where the want
//          saves r20-r31 (12 GPRs, `stmw r20,0x138`).
//      frame = locals + gpr_save + 0x38 (FPR) + 8. Want 0x130+0x30+0x40.
//      Probed: removing `f32 zero;` DOES fix (a) (magic lands on 0x130) but
//      costs an FPR and a GPR, so the frame becomes 0x198 and the score drops
//      to 5.6%. `__ps_t m[7]` fixes both (frame 0x1a0, 12 GPRs, magic 0x130)
//      but shifts every local -8 and scores 6.3%. Removing `k`, `len`/`sc2`,
//      `sc`, `n1`, the `ctr` delay loop or hoisting `cA`/`cB` out of the
//      `if (i14C)` body changes nothing. The 8 extra bytes are in the
//      0xF8..0x137 gap (64 B here, 56 B in the want) and no declaration
//      shape I tried shrinks it without freeing a register.
//  B2. ONE WORD LONG (2224 vs 2220). The tail is now positionally aligned;
//      the surplus is the two `lis` the want hoists into the preheader that
//      3.9.3 re-materialises inside the loop (see B3) plus one `lfs` reload
//      of 1.0 in the sqrtf path.
//  B3. CONSTANT-HOIST SHAPE. The want's preheader holds FOUR callee-saved
//      constant-address registers (r9, r20, r21, r23 = 0x8029, plus r22 =
//      0x4330) and only re-materialises `lis` for lbl_8029408C inside the
//      loop. That is why it numbers the constants f26 = 2^-31, f27 = 1.0,
//      f29 = magic and needs no `lfs` reload; 3.9.3 assigns f27 = 2^-31,
//      f28 = magic, f29 = 1.0 and re-emits `lis`+`lfs` for 1.0 twice inside
//      the loop, plus drops the want's `fmr f13,f9` before `fcmpu cr0,f13,f25`
//      (it compares a reloaded zero in f10 instead of the hoisted f25).
//      Reading the constants into locals (`f32 cA, cB`) inside the loop body
//      is what keeps the 7 saved FPRs; hoisting them to function scope or
//      using the globals inline both score far worse (8.1% / 3.9%).
//  B4. The want's SECOND multiply block's six products live 0x10 higher than
//      the first's (0x88..0xB0 vs 0x78..0xA0) and its partials land on
//      0x78/0x80, i.e. block 2 is block 1 shifted by one pair. Reproducing
//      that with a 10-member `Prod` (`Vec4p r; __ps_t p0..p7;`) plus a
//      one-member-shifted block-2 assignment DOES make the set of r1
//      displacements match 0x48..0xF0 including 0xA8/0xB0, but it reorders
//      the ps_add/psq_st stream and costs 8 more words: 6.3%. Two separate
//      `Prod` aggregates do NOT overlap (the allocator gives prB its own
//      0xA8..0xE7 and the frame explodes to 0x1d8). Left as the single
//      `Prod pr` shape, which is the better-scoring one.
//
// NOTES ON THE SOURCE SHAPES THAT MATTER (transferable)
//  1. Looping-invariant float CONSTANTS must be read into named locals
//     (`f32 cA = lbl_80294078, cB = lbl_8029407C;`) inside the loop body.
//     With the constants written inline in a RAND()-style macro, 3.9.3
//     re-emits `lis`+`lfs` for every call site, does not CSE them across the
//     rand() calls in one iteration, and drops to 4 saved FPRs.
//  2. `if (a > b) S1; else S2;` emits `ble` to S2 with S1 falling through.
//     The want has the OPPOSITE polarity (`bgt` to the `else` arm). Writing
//     the test as `if (a <= b) S2; else S1;` reproduces it.
//  3. The two 4x3-matrix-times-3-vector products need MEMORY-RESIDENT PS
//     intermediates - that is what emits the six product `psq_st`s and the
//     two partial `psq_st`s the want has, with the values still forwarded to
//     registers. Plain `__ps_t` pseudos emit none of them (doc-06 M5.0j-2r).
//  4. A `Vec4`-shaped local needs BOTH a scalar view and a pair view at the
//     same address (the want does `stfs f27,0x54` and `psq_st f12,80(r1)` on
//     the same 4 words). A `union { Vec4 v; __ps_t p[2]; }` expresses that
//     without casts.
//  5. THE OUTPUT VECTOR IS NOT A SEPARATE LOCAL. The want's vertex output is
//     read from 0x68/0x6C/0x70, which is the same pair the FIRST block's
//     partial sums use, so the output must be `pr.r` (the union view of the
//     Prod's first pair), not a `Vec4p R`. Declaring `pr` before `R` in
//     function scope puts pr at 0x68 and leaves 0xA8..0xB7 free; a 16-byte
//     local declared between `Prod pr;` and the splats then keeps the splats
//     at 0xB8.
//  6. ** ngccc GIVES A COMPLETELY UNUSED LOCAL A STACK SLOT. ** A `Vec4p R;`
//     that is never referenced still consumes 16 bytes and moves every later
//     local up by 0x10. That is the only lever found for holding the splat
//     block at 0xB8 while `Prod pr` sits at 0x68 (see note 5), and it is
//     also the cheapest way to pad/trim the frame by whole pairs.
//  7. Declaration order = ascending stack address (source order for scalars),
//     so reordering the locals is a real (if blunt) frame-size lever.
//  8. The vertex index must stay an integer expression
//     `((j*3)*ncols + i*3)` (no `*4`, NOT strength-reduced): the want re-does
//     `mullw` + `slwi r11,r11,2` every iteration.
//  9. STORE ORDER: the splat branch's vertex loop must be written
//     `vp[idx]; vp[idx+2]; vp[idx+1];` (the want emits
//     `stfsx`,`stfs 8(r)`,`stfs 4(r)`). The `else` branch already emits
//     8-before-4 from the ascending spelling - swapping it there is WRONG
//     (9.7% instead of 15.3%). This single store reordering is worth
//     +5.8 points.
// 10. `dot` and `sG` must be declared in the order `sA..sF, dot, sG` so that
//     dot takes 0xE8 and sG 0xF0 (the want `lfs`es the dot pair as a scalar
//     and `psq_l`s the sG pair); the other order swaps them.
//
// FLAGS PROBED AND REJECTED: -fno-schedule-insns2, -fno-expensive-
// optimizations, -fno-gcse, -fno-caller-saves, -fno-peephole, -fno-regmove,
// -fno-schedule-insns2. Default -O2 -G0 -mcpu=750 -fno-common + per-object
// -mps-float is the best measured. No __asm__ and no register pins are used.
#include "types.h"

typedef struct {
    char pad0x0[0x18];
    s16 off18;
    char pad0x1A[2];
    s32 (*fn)(void *);
} SplatVtbl;

typedef struct {
    f32 f[12];
} SplatSlot;

typedef struct {
    char pad0x00[0x08];
    SplatVtbl *vtbl;
    char pad0x0C[0x1C];
    SN_PS_type v28, v30, v38, v40;
    char pad0x48[0x3C];
    s32 ncols;
    char pad0x88[0x0C];
    s32 i94;
    f32 f98, f9C;
    f32 fA0, fA4, fA8, fAC;
    f32 fB0, fB4, fB8, fBC, fC0, fC4, fC8;
    f32 fCC, fD0, fD4;
    char pad0xD8[0x28];
    SplatSlot *slots;
    char pad0x104[0x20];
    f32 *verts;
    char pad0x128[0x08];
    s32 i130;
    s32 i134;
    char pad0x138[0x04];
    s32 i13C;
    s32 i140;
    char pad0x144[0x08];
    s32 i14C;
    char pad0x150[0x10];
    s32 i160;
} SplatObj;

typedef struct {
    f32 x, y, z, w;
} Vec4;

/* One object with two views: scalar lanes (x/y/z/w) and the two PS pairs the
   compiler's vectorised store/load pattern addresses. */
typedef union {
    Vec4 v;
    __ps_t p[2];
} Vec4p;

/* Memory-resident PS intermediates: each member is STORE-then-READ, which is
   what makes ngccc emit the game's `psq_st` product/partial spills. */
typedef struct {
    Vec4p r;
    __ps_t p0, p1, p2, p3, p4, p5;
} Prod;

extern f32 lbl_80294078;
extern f32 lbl_8029407C;
extern f32 lbl_80294080;
extern f32 lbl_80294084;
extern f32 lbl_80294088;
extern f32 lbl_8029408C;
extern __ps_t lbl_80293FE8;

int rand(void);
f32 sqrtf(f32);
f32 fabsf(f32);
void fn_800637C0(SplatObj *self, __ps_t *out);

#define RR() ((f32)((f64)rand() * lbl_80294078))
#define RR2(A, B) (2.0f * ((f32)((f64)rand()) * (A)) - (B))

void fn_800639E8(SplatObj *self, s32 arg1) {
    __ps_t m[8];
    Vec4p P, Q;
    Prod pr;
    Vec4p R;
    SN_PS_type sA, sB, sC, sD, sE, sF, dot, sG;
    s32 n0, nmax, n1, lim, i, j, ctr, idx;
    f32 sc;
    f32 u, v, w, k;
    f32 zero;

    if (self->i130 != 0) {
        return;
    }
    n0 = self->i94;
    nmax = self->ncols;
    n1 = n0 + arg1;
    if (n1 <= nmax) {
        self->i94 = n1;
    } else {
        self->i94 = nmax;
    }
    ctr = 4;
    do {
        ctr -= 1;
    } while (ctr != 0);
    lim = self->i94;
    fn_800637C0(self, m);
    zero = lbl_80294088;
    for (i = n0; i < lim; i++) {
        if (self->i14C != 0) {
            f32 cA = lbl_80294078;
            f32 cB = lbl_8029407C;
            u = RR2(cA, cB);
            v = RR2(cA, cB);
            w = RR2(cA, cB);
            k = self->fAC * lbl_80294080 * lbl_80294084;
            P.v.x = u * k;
            P.v.y = v * k;
            P.v.z = lbl_8029407C - ((P.v.x * P.v.x) + (P.v.y * P.v.y));
            P.v.w = lbl_8029407C;
            sA.flt.hi = P.v.x;
            sB.flt.hi = P.v.y;
            sC.flt.hi = P.v.z;
            pr.p0 = __builtin_ps_muls0(m[0], sA.ps);
            pr.p1 = __builtin_ps_muls0(m[1], sA.ps);
            pr.p2 = __builtin_ps_muls0(m[2], sB.ps);
            pr.p3 = __builtin_ps_muls0(m[3], sB.ps);
            pr.p4 = __builtin_ps_muls0(m[4], sC.ps);
            pr.p5 = __builtin_ps_muls0(m[5], sC.ps);
            pr.r.p[0] = __builtin_ps_add(pr.p0, pr.p2);
            pr.r.p[1] = __builtin_ps_add(pr.p1, pr.p3);
            P.p[0] = __builtin_ps_add(pr.r.p[0], pr.p4);
            P.p[1] = __builtin_ps_add(pr.r.p[1], pr.p5);
            Q.p[0] = P.p[0];
            Q.p[1] = P.p[1];
            sc = self->f98 + ((self->f9C - self->f98) * RR2(cA, cB));
            P.v.x = P.v.x * sc;
            P.v.y = P.v.y * sc;
            P.v.z = P.v.z * sc;
            if (self->i13C != 0) {
                u = RR2(cA, cB);
                v = RR2(cA, cB);
                w = RR2(cA, cB);
            }
            if (self->i140 != 0) {
                f32 len = sqrtf((u * u) + (v * v));
                f32 sc2 = lbl_8029407C / len;
                u = u * (sc2 * fabsf(u));
                v = v * (sc2 * fabsf(v));
            }
            Q.v.x = self->fA0 * u;
            Q.v.y = self->fA4 * v;
            Q.v.z = self->fA8 * w;
            Q.v.w = lbl_8029407C;
            sD.flt.hi = Q.v.x;
            sE.flt.hi = Q.v.y;
            sF.flt.hi = Q.v.z;
            pr.p0 = __builtin_ps_muls0(m[0], sD.ps);
            pr.p1 = __builtin_ps_muls0(m[1], sD.ps);
            pr.p2 = __builtin_ps_muls0(m[2], sE.ps);
            pr.p3 = __builtin_ps_muls0(m[3], sE.ps);
            pr.p4 = __builtin_ps_muls0(m[4], sF.ps);
            pr.p5 = __builtin_ps_muls0(m[5], sF.ps);
            pr.r.p[0] = __builtin_ps_add(pr.p0, pr.p2);
            pr.r.p[1] = __builtin_ps_add(pr.p1, pr.p3);
            Q.p[0] = __builtin_ps_add(pr.r.p[0], pr.p4);
            Q.p[1] = __builtin_ps_add(pr.r.p[1], pr.p5);
            if (self->i160 != 0) {
                pr.r.p[1] = __builtin_ps_sub(self->v40.ps, self->v30.ps);
                pr.r.p[0] = __builtin_ps_sub(self->v38.ps, self->v28.ps);
                dot.ps = __builtin_ps_madd(pr.r.p[0], pr.r.p[0],
                        __builtin_ps_merge00(__builtin_ps_mul(pr.r.p[1], pr.r.p[1]), lbl_80293FE8));
                dot.ps = __builtin_ps_sum0(dot.ps, dot.ps, dot.ps);
                if (dot.flt.hi != lbl_80294088) {
                    sG.flt.hi = (RR2(cA, cB) + cB) * lbl_8029408C;
                    pr.p2 = __builtin_ps_muls0(pr.r.p[1], sG.ps);
                    pr.p3 = __builtin_ps_muls0(pr.r.p[0], sG.ps);
                    Q.p[0] = __builtin_ps_add(Q.p[0], pr.p3);
                    Q.p[1] = __builtin_ps_add(Q.p[1], pr.p2);
                }
            }
            pr.r.p[0] = P.p[0];
            pr.r.p[1] = P.p[1];
            self->slots[i].f[3] = self->fB0;
            self->slots[i].f[4] = self->fB4;
            self->slots[i].f[5] = self->fB8;
            self->slots[i].f[6] = self->fBC;
            self->slots[i].f[7] = self->fC0;
            self->slots[i].f[8] = self->fC4;
            self->slots[i].f[9] = self->fC8;
            if (self->fCC != lbl_8029407C) {
                self->slots[i].f[6] = self->slots[i].f[6] * self->fCC;
                self->slots[i].f[7] = self->slots[i].f[7] * self->fCC;
                self->slots[i].f[8] = self->slots[i].f[8] * self->fCC;
                self->slots[i].f[9] = self->slots[i].f[9] * self->fCC;
            }
            self->slots[i].f[10] = zero;
            self->slots[i].f[11] = self->fD0 + ((self->fD4 - self->fD0) * RR());
            self->slots[i].f[0] = pr.r.v.x;
            self->slots[i].f[1] = pr.r.v.y;
            self->slots[i].f[2] = pr.r.v.z;
            pr.r.p[0] = Q.p[0];
            pr.r.p[1] = Q.p[1];
            for (j = 0; j < self->vtbl->fn((char *)self + self->vtbl->off18); j++) {
                f32 *vp = self->verts;
                idx = ((j * 3) * self->ncols) + (i * 3);
                if (self->i134 != 0) {
                    vp[idx] = pr.r.v.x + self->v28.flt.hi;
                    vp[idx + 2] = pr.r.v.z + self->v30.flt.hi;
                    vp[idx + 1] = pr.r.v.y + self->v28.flt.lo;
                } else {
                    vp[idx] = pr.r.v.x;
                    vp[idx + 1] = pr.r.v.y;
                    vp[idx + 2] = pr.r.v.z;
                }
            }
        } else {
            self->slots[i].f[6] = self->fBC;
            self->slots[i].f[7] = self->fC0;
            self->slots[i].f[8] = self->fC4;
            self->slots[i].f[9] = self->fC8;
            if (self->fCC != lbl_8029407C) {
                self->slots[i].f[6] = self->slots[i].f[6] * self->fCC;
                self->slots[i].f[7] = self->slots[i].f[7] * self->fCC;
                self->slots[i].f[8] = self->slots[i].f[8] * self->fCC;
                self->slots[i].f[9] = self->slots[i].f[9] * self->fCC;
            }
            self->slots[i].f[10] = zero;
            self->slots[i].f[11] = self->fD0 + ((self->fD4 - self->fD0) * RR());
            for (j = 0; j < self->vtbl->fn((char *)self + self->vtbl->off18); j++) {
                f32 *vp = self->verts;
                idx = ((j * 3) * self->ncols) + (i * 3);
                vp[idx] = zero;
                vp[idx + 1] = zero;
                vp[idx + 2] = zero;
            }
        }
    }
}
