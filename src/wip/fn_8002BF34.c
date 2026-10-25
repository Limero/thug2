// WIP DRAFT — hand-reconstructed from scratch out of the want disassembly.
// family=m2c range=0x8002BF34-0x8002C128 size=500B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// PARKED 2026-10-05: best = DIFF **18.6%** (24/125 words,
// object 496 B vs want 500 B — ONE word short). The old m2c bulk-fill draft was
// 1.9% / 636 B with a bogus 0x80 FPR frame; this body is now semantically
// complete and the frame is byte-exact, so the only thing left is FPR schedule
// order.
//
// WHAT THE FUNCTION IS
//   `fn_8002BA5C(arg0,1)` is a 2-word thunk -> `*(s32 *)(arg0+4) = 1`.
//   `fn_80024660(a)` -> `a + 0x68`, `fn_800246AC(a)` -> `a + 0x78`.
//   If `*(s32 *)arg0 == 0` return 0.  Otherwise: assert(QB_MOVIECAM_DEBUG),
//   copy arg0->{0x20,0x24,0x28,0x2C} -> (arg1+0x68)[0..3], then build the
//   **inverse** (conjugate) rotation matrix from the quaternion at
//   arg0+0x10..0x1F into the 16-float matrix at arg1+0x78:
//       q = (m0, m1, m2, m3);  used as x=-m0, y=-m1, z=-m2, w=m3
//       out[0]=1-2(y2+z2) out[1]=2(xy+wz)  out[2]=2(xz-wy)   out[3]=0
//       out[4]=2(xy-wz)   out[5]=1-2(x2+z2) out[6]=2(yz-wx)  out[7]=0
//       out[8]=2(xz+wy)   out[9]=2(yz+wx)   out[10]=1-2(x2+y2) out[11]=0
//       out[12..15] = (0,0,0,1)
//   The negations are exactly what want shows: `psq_l; ps_neg; psq_st` for the
//   first __ps_t (whole pair negated) and a plain `fneg; stfs` for z alone.
//   0.0f/1.0f are the extern floats lbl_802916CC / lbl_802916D0.
//
// TYPIST (this is the whole trick — the m2c draft had none of it)
//   * `-mps-float` (auto-added by the sweep because of `__ps_t`).
//   * `QB_MOVIECAM_DEBUG` (0x2F510F45) is an INTEGER constant, not a pointer:
//     it must come out as `lis r3,0x2f51 ; ori r3,r3,0xf45`.  The old draft's
//     `*(char *)0x802AF45` produced `lis 0x802 ; ori 0xaf45` = 0x0802AF45,
//     a totally different (wrong) value.
//   * The quaternion and the (0,0,0,1) pad are `union { __ps_t ps[2]; f32 f[4]; }`
//     locals.  That is the ONLY shape that reproduces want's `psq_l f0,16(r31);
//     ps_neg; psq_st f0,24(r1)` for the pair AND `fneg; stfs f0,0x20(r1)` for
//     one half AND `lfs f13,0x18 / lfs f7,0x1c / lfs f0,0x20 / lfs f11,0x24`.
//     A plain `__ps_t` + `((f32 *)&x)[1]` **reads** fine but the matching write
//     ICEs cc1 (`expmed.c:347/1115`), and a 2-member union falls back to the
//     GPR lwz/stw path.  A 4-member `__ps_t ps[2]` union compiles clean.
//   * The nine products MUST live in memory.  They are stored to frame slots
//     0x28..0x50 (indices 0,1,2,4,5,6,8,9,10 — 3 and 7 are dead, which is
//     where want's 0x34/0x44 frame gaps come from) and re-loaded twice each in
//     the output block, while `C = t[1]+t[2]` is still register-fed.  A local
//     ARRAY of 11 reproduces this exactly (frame 0x68 + the two gaps, and the
//     object lands 1 word under the want); nine separate `f32` scalars do NOT
//     (frame collapses to 0x38 and the object to 396 B) because GCC keeps them
//     in FPRs.  This is the single biggest lever found on this function.
//
// RESIDUAL / BLOCKER
//   24 of 125 words match (the whole prologue, the QB assert, both calls, and
//   the first psq_l).  Everything after that is the classic PS float
//   scheduling wall: ngccc's list scheduler emits the nine `fmuls` in a
//   different order than want (got: t2,t10,t1,t9,t6,t5,t4,C,t0,t8; want:
//   t1,(fneg),t2,C,t8,t10,t9,t0,t4,t5,t6) and wants `addi r10,r1,8` so the pad
//   stores go through r10 (want) instead of plain r1 displacements (got).
//   `-fno-schedule-insns` gets the order much closer to want but drops the
//   object to 492 B and the score to 12.2%; `-fno-schedule-insns2` and
//   `-fno-sched-interblock` are exact no-ops here.  Per AGENTS.md §6/§4m the
//   next thing to try is statement-order nudges of the t[] assignments (they
//   are the schedule's only degree of freedom here), not more flags.
// REVIEWED 2026-10-18 (random triage): note the t[] source order above
// ALREADY equals want's fmuls order (t1,t2,C,t8,t10,t9,t0,t4,t5,t6) yet got
// emits a rotation — so the scheduler ignores assignment order here and
// statement nudges likely attack the wrong axis; the axis is operand
// readiness (q-load/neg timing through the frame round-trips) or a pure
// heuristic wall. Body untouched.
#include "types.h"
#include "qb_constants.h"

extern f32 lbl_802916CC;
extern f32 lbl_802916D0;

void fn_80125A3C(void *, s32);
void *fn_80024660(void *);
void *fn_800246AC(void *);
void fn_8002BA5C(void *, s32);

typedef union {
    __ps_t ps[2];
    f32 f[4];
} Q4;

typedef struct S2BF34 {
    s32 unk0x0;
    char pad0x4[0xC];
    f32 f_0x10;
    f32 f_0x14;
    f32 f_0x18;
    f32 f_0x1C;
    f32 f_0x20;
    f32 f_0x24;
    f32 f_0x28;
    f32 f_0x2C;
} S2BF34;

s32 fn_8002BF34(S2BF34 *arg0, void *arg1) {
    Q4 pad;
    Q4 q;
    f32 *out;
    __ps_t *dst;
    __ps_t *src;
    f32 t[11];
    f32 C;
    f32 zero, one;
    s32 ret;

    ret = 0;
    if (arg0->unk0x0 != 0) {
        fn_80125A3C((void *)QB_MOVIECAM_DEBUG, 0);
        dst = (__ps_t *)fn_80024660(arg1);
        out = (f32 *)fn_800246AC(arg1);
        zero = lbl_802916CC;
        one = lbl_802916D0;
        src = (__ps_t *)&arg0->f_0x20;
        dst[0] = src[0];
        dst[1] = src[1];
        pad.f[0] = zero;
        pad.f[1] = zero;
        q.ps[0] = -*(__ps_t *)&arg0->f_0x10;
        pad.f[2] = zero;
        pad.f[3] = one;
        q.ps[1] = *(__ps_t *)&arg0->f_0x18;
        t[1] = q.f[1] * q.f[1];
        q.f[2] = -q.f[2];
        t[2] = q.f[2] * q.f[2];
        C = t[1] + t[2];
        t[8] = q.f[3] * q.f[0];
        t[10] = q.f[3] * q.f[2];
        t[9] = q.f[3] * q.f[1];
        t[0] = q.f[0] * q.f[0];
        t[4] = q.f[1] * q.f[2];
        t[5] = q.f[2] * q.f[0];
        t[6] = q.f[0] * q.f[1];
        out[0] = one - (C + C);
        out[1] = (t[6] + t[10]) + (t[6] + t[10]);
        out[2] = (t[5] - t[9]) + (t[5] - t[9]);
        out[3] = zero;
        out[4] = (t[6] - t[10]) + (t[6] - t[10]);
        out[5] = one - ((t[0] + t[2]) + (t[0] + t[2]));
        out[6] = (t[4] + t[8]) + (t[4] + t[8]);
        out[7] = zero;
        out[8] = (t[5] + t[9]) + (t[5] + t[9]);
        out[9] = (t[4] - t[8]) + (t[4] - t[8]);
        out[10] = one - ((t[0] + t[1]) + (t[0] + t[1]));
        out[11] = zero;
        *(__ps_t *)&out[12] = pad.ps[0];
        *(__ps_t *)&out[14] = pad.ps[1];
        out[15] = one;
        fn_8002BA5C(arg0, 1);
        ret = 1;
    }
    return ret;
}