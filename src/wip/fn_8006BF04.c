// WIP DRAFT (non-matching) — full hand rewrite (was m2c at 3.3% / 736B)
// family=m2c range=0x8006BF04-0x8006C498 size=1428B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// Reconstructed semantics (see the want at 0x8006BF04):
//   Vec4 v   @sp+0x08   -- {r1,r2,r3,1.0} random direction, 16 bytes (2 paired
//                          singles). Passed by address to fn_80003BE8.
//   Vec4 O[4]@sp+0x18   -- fn_80003BE8 out param (16 floats = a 4x4 matrix)
//   Vec4 R[4]@sp+0x58   -- R[k][j] = sum_i M[k][i]*O[i][j]  (M*O, unrolled 4x4)
//   Vec4 t[3]@sp+0x98   -- t[0] is the {farg0,?,rsq,1.0} pair-scratch; t[1]/t[2]
//                          are declared purely to size the frame (see PARK block)
//   sp+0xE8/0xEC        -- GCC's (f32)(f64)(s32)rand() int->f64 spill slot
//   Obj: {Vec4*unk0x0; Vec4*unk0x4; pad; Vec4*unk0xC; f32 @0x14,0x18,0x1C}
// The `ps_muls0/ps_add/ps_mul/ps_merge00/ps_madd/ps_sum0/ps_rsqrte` chain is a
// hand-normalise of v guarded by `> lbl_80294B88` (0.0f).
//
// === PARKED (2026-10-01) ===
// Score: DIFF 49.7% (176/354 words), object 1416 B vs want 1428 B (3 insns short).
// STRUCTURE IS NOW EXACT: frame -0x140 == want, sp+0x08/0x18/0x58/0x98 and the
// 0xE8/0xEC rand() spill slots all == want, the 16-dot-product block (R[1..3]) and
// the 8 psq_l/psq_st copy-out are byte-identical, and all 16 scalar matrix stores
// land at the right offsets in the right (descending) order.
// STUCK ON: register allocation. want saves 5 GPRs (`stmw r27,0xf4`, Gsave=0xF4,
// frame 0x140 == closed form 0xF4+4*5+8*7); this body needs 7 (`stmw r25`),
// because GCC hoists three extra long-lived values that want re-materialises or
// computes late: (a) &O kept in a callee-saved reg from the top of the guarded
// block instead of `addi` right before the call, (b)+(c) two hoisted `lis 0x8029`
// rodata pages (want re-emits `lis rX,-0x7fd7` at each of 5 uses).
// tried and rejected: inlining pa/pb (len 1416->1460), `volatile`/asm-"m" pad
// (adds a 2-insn address spill; "m" on an f32 array ICEs cc1), declaring t[1..3]
// instead of a separate pad (identical), pad sizes swept 16..64 B (declared local
// size maps 1:1 onto Gsave; 0xEC is the only pad that also lands frame on 0x140).
// NOT tried: `register __asm__("rN")` pins on &O/pm (pins need single-def pseudos
// and the values are call-result webs), any -fno-schedule*/-fno-gcse flag, and the
// 2 remaining length instructions (want's dead `ps_mr f12,f11` operand copy and the
// `fmr f0,f11` before `stfs 0xa4(r1)`, both of which need the constant to stay
// live in an FPR across the whole guarded block).
// Inline asm emitted: 0 instructions (no asm at all in the body).
// AUDIT 2026-10-01: extern lbl_ addresses hand-decoded from want's lis/lfs pairs --
//   B88 f32=0.0 (eps), B90 f64=0x4330000080000000 (int->f64 magic), B98 f32=2^-31,
//   B9C f32=-1.0, BA0 f32=1.0, BA4 f32=0.1, B40 = the {0,0} psq pair. All real
//   .rodata2 entries. NOTE lbl_80294B90 is NOT referenced by this body: GCC
//   synthesises the int->f64 magic itself, so the object has a private 8-byte
//   .rodata pool (3 HA/LO reloc pairs) -- the METHOD/5 doc-14 caveat; would need
//   routing to be promote-clean. Branch census matches want exactly: 4x REL14
//   (2 guards + bdnz + ble) + 5x REL24 (4x rand + fn_80003BE8) = want's 9.
//   .text 0x588 = 1416 B vs want 1428 B (12 B / 3 insns short).
#include "types.h"

typedef float psf __attribute__((mode(PS)));

typedef union {
    psf ps;
    struct {
        f32 hi, lo;
    } flt;
} Ps2;

typedef union {
    Ps2 p[2];
    f32 f[4];
} Vec4;

typedef struct Obj_s {
    Vec4 *unk0x0;
    Vec4 *unk0x4;
    s32 pad0x8;
    Vec4 *unk0xC;
    s32 pad0x10;
    f32 unk0x14;
    f32 unk0x18;
    f32 unk0x1C;
} Obj;

extern f32 lbl_80294B88;
extern f64 lbl_80294B90;
extern f32 lbl_80294B98;
extern f32 lbl_80294B9C;
extern f32 lbl_80294BA0;
extern f32 lbl_80294BA4;
extern char lbl_80294B40[];

s32 rand(void);
void fn_80003BE8(Vec4 *out, Vec4 *v, f32 f);

void fn_8006BF04(Obj *self, s32 arg1, f32 farg0) {
    Vec4 v;
    Vec4 O[4];
    Vec4 R[4];
    Vec4 t[3];
    Vec4 *pa = &self->unk0x4[arg1];
    Vec4 *pb = &self->unk0x0[arg1];
    Vec4 *pm;
    Ps2 s;
    Ps2 rs;
    s32 var_ctr;

    t[0].f[0] = farg0;
    v.p[0].ps = __builtin_ps_muls0(pa->p[0].ps, t[0].p[0].ps);
    v.p[1].ps = __builtin_ps_muls0(pa->p[1].ps, t[0].p[0].ps);
    pb->p[0].ps = __builtin_ps_add(pb->p[0].ps, v.p[0].ps);
    pb->p[1].ps = __builtin_ps_add(pb->p[1].ps, v.p[0].ps);

    if (pb->f[1] < self->unk0x18) {
        if (pa->f[1] < lbl_80294B88) {
            pb->f[1] = self->unk0x18 + (self->unk0x18 - pb->f[1]);
            pa->f[1] = pa->f[1] * -self->unk0x1C;
            v.f[0] = (f32) (f64) (s32) rand() * 2.0f * lbl_80294B98 + lbl_80294B9C;
            v.f[1] = (f32) (f64) (s32) rand() * 2.0f * lbl_80294B98 + lbl_80294B9C;
            v.f[2] = (f32) (f64) (s32) rand() * 2.0f * lbl_80294B98 + lbl_80294B9C;
            v.f[3] = lbl_80294BA0;

            pm = &self->unk0xC[arg1];
            pm->f[0] = lbl_80294BA0;
            pm->f[15] = lbl_80294BA0;
            pm->f[14] = lbl_80294B88;
            pm->f[13] = lbl_80294B88;
            pm->f[12] = lbl_80294B88;
            pm->f[11] = lbl_80294BA0;
            pm->f[10] = lbl_80294B88;
            pm->f[9] = lbl_80294B88;
            pm->f[8] = lbl_80294B88;
            pm->f[7] = lbl_80294BA0;
            pm->f[6] = lbl_80294B88;
            pm->f[5] = lbl_80294B88;
            pm->f[4] = lbl_80294B88;
            pm->f[3] = lbl_80294BA0;
            pm->f[2] = lbl_80294B88;
            pm->f[1] = lbl_80294B88;

            var_ctr = 4;
            do {
                var_ctr -= 1;
            } while (var_ctr != 0);
            fn_80003BE8(O, &v, (f32) (f64) (s32) rand() * lbl_80294B98 * lbl_80294BA4);

            s.ps = __builtin_ps_mul(v.p[1].ps, v.p[0].ps);
            s.ps = __builtin_ps_merge00(s.ps, *(psf *) lbl_80294B40);
            s.ps = __builtin_ps_madd(v.p[0].ps, v.p[0].ps, s.ps);
            s.ps = __builtin_ps_sum0(s.ps, s.ps, s.ps);
            if (s.flt.hi > lbl_80294B88) {
                rs.ps = __builtin_ps_rsqrte(s.ps);
                v.p[0].ps = __builtin_ps_muls1(v.p[0].ps, rs.ps);
                t[0].p[1].ps = rs.ps;
                t[0].f[3] = lbl_80294BA0;
                v.p[1].ps = __builtin_ps_mul(v.p[1].ps, t[0].p[1].ps);
            }

            R[0].f[0] = pm->f[0] * O[0].f[0] + pm->f[1] * O[1].f[0] + pm->f[2] * O[2].f[0] + pm->f[3] * O[3].f[0];
            R[0].f[1] = pm->f[0] * O[0].f[1] + pm->f[1] * O[1].f[1] + pm->f[2] * O[2].f[1] + pm->f[3] * O[3].f[1];
            R[0].f[2] = pm->f[0] * O[0].f[2] + pm->f[1] * O[1].f[2] + pm->f[2] * O[2].f[2] + pm->f[3] * O[3].f[2];
            R[0].f[3] = pm->f[0] * O[0].f[3] + pm->f[1] * O[1].f[3] + pm->f[2] * O[2].f[3] + pm->f[3] * O[3].f[3];
            R[1].f[0] = pm->f[4] * O[0].f[0] + pm->f[5] * O[1].f[0] + pm->f[6] * O[2].f[0] + pm->f[7] * O[3].f[0];
            R[1].f[1] = pm->f[4] * O[0].f[1] + pm->f[5] * O[1].f[1] + pm->f[6] * O[2].f[1] + pm->f[7] * O[3].f[1];
            R[1].f[2] = pm->f[4] * O[0].f[2] + pm->f[5] * O[1].f[2] + pm->f[6] * O[2].f[2] + pm->f[7] * O[3].f[2];
            R[1].f[3] = pm->f[4] * O[0].f[3] + pm->f[5] * O[1].f[3] + pm->f[6] * O[2].f[3] + pm->f[7] * O[3].f[3];
            R[2].f[0] = pm->f[8] * O[0].f[0] + pm->f[9] * O[1].f[0] + pm->f[10] * O[2].f[0] + pm->f[11] * O[3].f[0];
            R[2].f[1] = pm->f[8] * O[0].f[1] + pm->f[9] * O[1].f[1] + pm->f[10] * O[2].f[1] + pm->f[11] * O[3].f[1];
            R[2].f[2] = pm->f[8] * O[0].f[2] + pm->f[9] * O[1].f[2] + pm->f[10] * O[2].f[2] + pm->f[11] * O[3].f[2];
            R[2].f[3] = pm->f[8] * O[0].f[3] + pm->f[9] * O[1].f[3] + pm->f[10] * O[2].f[3] + pm->f[11] * O[3].f[3];
            R[3].f[0] = pm->f[12] * O[0].f[0] + pm->f[13] * O[1].f[0] + pm->f[14] * O[2].f[0] + pm->f[15] * O[3].f[0];
            R[3].f[1] = pm->f[12] * O[0].f[1] + pm->f[13] * O[1].f[1] + pm->f[14] * O[2].f[1] + pm->f[15] * O[3].f[1];
            R[3].f[2] = pm->f[12] * O[0].f[2] + pm->f[13] * O[1].f[2] + pm->f[14] * O[2].f[2] + pm->f[15] * O[3].f[2];
            R[3].f[3] = pm->f[12] * O[0].f[3] + pm->f[13] * O[1].f[3] + pm->f[14] * O[2].f[3] + pm->f[15] * O[3].f[3];

            pm[0].p[0].ps = R[0].p[0].ps;
            pm[0].p[1].ps = R[0].p[1].ps;
            pm[1].p[0].ps = R[1].p[0].ps;
            pm[1].p[1].ps = R[1].p[1].ps;
            pm[2].p[0].ps = R[2].p[0].ps;
            pm[2].p[1].ps = R[2].p[1].ps;
            pm[3].p[0].ps = R[3].p[0].ps;
            pm[3].p[1].ps = R[3].p[1].ps;
        }
    }
    pa->f[1] -= self->unk0x14 * farg0;
}
