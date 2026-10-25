// WIP DRAFT — paired-single semantic reconstruction
// REFRESHED 2026-10-07 (FPR-pin RETARGET sweep): 4.4199% -> 5.4645%
//   the `limit` pin was retargeted fr31 -> fr27 (nothing else touched).  New axis:
//   fr-pin REMOVAL had been swept, retargeting had not.  AGENTS-recipes §6hk.
// family=hand range=0x800FAE1C-0x800FB0F0 size=724B
// PARKED 2026-10-06 (the worker pool was disabled before this
// slice ran — body left as the current best, not re-measured).
// Blocker: paired-single kernel — 67 PS words / 53 op-4 words capstone cannot
// decode; matching needs tools/ps_disasm.py + tools/ps_diff.py.
// BEST 2026-09-25: 4.4% (8/181) with tools/ps_diff.py,
// -fno-schedule-insns -mps-float; GOT is 700B versus 724B. Raw decode has
// no unknown/VMX words; opcode sequence similarity is 77.5%. The 0xe0 frame,
// f31 save, and r23-r31 save span are exact.
// Signature recovered as Sphere *, three PairVec inputs, three PairVec
// outputs; fn_800F76E8 returns the scalar distance used by the final test.
// Exact blocker is ngccc's PS/GPR allocator and branch lowering: pointer
// homes/load order differ, four retail ps_mr and two psq_st copies are
// coalesced, and the retail cror/bso float guard is lowered as ble. No
// whole-body or transcription asm is used.
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// extra_cflags: -mps-float -fno-schedule-insns
#include "types.h"

extern char lbl_8029C060[];
extern f32 lbl_8029C104;
extern f32 lbl_8029C108;

typedef struct {
    __ps_t p[2];
} PairVec;

typedef struct {
    PairVec first;
    PairVec second;
    f32 radius;
} Sphere;

typedef union {
    __ps_t p;
    struct {
        f32 lo;
        f32 hi;
    } f;
} Pair;

typedef struct {
    volatile Pair p[20];
} Frame __attribute__((aligned(8)));

f32 fn_800F76E8(Sphere *, PairVec *, PairVec *, PairVec *, PairVec *,
               volatile f32 *, volatile f32 *, volatile f32 *);

s32 fn_800FAE1C(Sphere *sphere, PairVec *p0, PairVec *p1, PairVec *p2,
                PairVec *out0, PairVec *out1, PairVec *out2) {
    Frame fr;
    Frame *frame;
    register s32 frame_addr __asm__("r26");
    const __ps_t *pair;
    volatile PairVec *v0;
    volatile PairVec *v1;
    volatile PairVec *v2;
    __ps_t a0, a1, b0, b1, c0, c1, t0, t1, t2, t3, t4;
    __ps_t k;
    SN_PS_type sf;
    f32 eps;
    register f32 limit __asm__("fr27");
    f32 distance;

    frame_addr = (s32)&fr;
    frame = (Frame *)frame_addr;
    v2 = p2;
    v0 = p0;
    v1 = p1;

    a0 = v0->p[0];
    a1 = v0->p[1];
    b0 = v1->p[0];
    b1 = v1->p[1];
    c0 = v2->p[0];
    c1 = v2->p[1];

    b0 = __builtin_ps_sub(b0, a0);
    b1 = __builtin_ps_sub(b1, a1);
    c0 = __builtin_ps_sub(c0, a0);
    c1 = __builtin_ps_sub(c1, a1);
    frame->p[3].p = b1;
    frame->p[4].p = c0;

    a0 = __builtin_ps_merge10(c0, c1);
    b1 = __builtin_ps_merge10(b0, b1);
    b0 = __builtin_ps_mul(b0, b0);
    a0 = __builtin_ps_mul(b0, a0);
    c0 = __builtin_ps_merge00(c0, c1);
    a1 = __builtin_ps_merge00(b1, b0);
    a1 = __builtin_ps_mul(a1, c0);
    a0 = __builtin_ps_sub(a0, b0);
    pair = (const __ps_t *)&lbl_8029C060;
    limit = lbl_8029C108;
    c0 = __builtin_ps_merge00(a0, a0);
    frame->p[14].p = c0;

    c0 = __builtin_ps_merge10(a1, a1);
    a1 = __builtin_ps_sub(a1, c0);
    eps = lbl_8029C104;
    frame->p[14].f.hi = eps;
    a0 = __builtin_ps_merge10(a0, a1);
    frame->p[0].p = a0;
    frame->p[1].p = frame->p[14].p;
    out0->p[0] = a0;

    c1 = frame->p[2].p;
    out0->p[1] = c1;
    c0 = __builtin_ps_mul(c1, c1);
    k = *pair;
    c0 = __builtin_ps_merge00(c0, k);
    c0 = __builtin_ps_madd(a0, a0, c0);
    c0 = __builtin_ps_sum0(c0, c0, c0);
    sf.ps = c0;

    if (!(eps > limit)) {
        return 0;
    }
    if (sf.flt.hi > limit) {
        b1 = __builtin_ps_rsqrte(c0);
        a0 = __builtin_ps_muls0(a0, b1);
        out0->p[0] = a0;
        frame->p[15].p = b1;
        frame->p[15].f.hi = eps;
        t0 = frame->p[15].p;
        c0 = __builtin_ps_mul(c1, t0);
        out0->p[1] = c0;
    }

    distance = fn_800F76E8(sphere, out0, p0, p1, p2,
                           &frame->p[12].f.lo, &frame->p[12].f.hi,
                           &frame->p[13].f.lo);
    frame->p[16].f.lo = frame->p[12].f.lo;
    frame->p[17].f.lo = frame->p[12].f.hi;
    frame->p[18].f.lo = frame->p[13].f.lo;

    a1 = p0->p[1];
    b1 = p1->p[1];
    t0 = (__ps_t)frame->p[16].f.lo;
    b1 = __builtin_ps_sub(b1, a1);
    a0 = p0->p[0];
    b0 = p1->p[0];
    t1 = t0;
    t2 = frame->p[17].p;
    t4 = __builtin_ps_muls0(b1, t0);
    c1 = p2->p[1];
    c0 = p2->p[0];
    b0 = __builtin_ps_sub(b0, a0);
    frame->p[6].p = b0;
    c1 = __builtin_ps_sub(c1, a1);
    b0 = __builtin_ps_muls0(b0, t1);
    frame->p[7].p = b1;
    t2 = frame->p[17].p;
    c0 = __builtin_ps_sub(c0, a0);
    frame->p[10].p = c0;
    a0 = __builtin_ps_add(a0, b0);
    b1 = t2;
    c1 = __builtin_ps_muls0(c1, t2);
    t2 = __builtin_ps_muls0(c1, b1);
    frame->p[8].p = c1;
    a1 = __builtin_ps_add(a1, t4);
    frame->p[9].p = t2;
    frame->p[5].p = t4;
    frame->p[3].p = a1;
    frame->p[11].p = t2;
    a0 = __builtin_ps_add(a0, c0);
    frame->p[0].p = a0;
    frame->p[1].p = a1;
    out2->p[0] = a0;
    out2->p[1] = frame->p[2].p;

    t0 = frame->p[18].p;
    c1 = sphere->first.p[0];
    c0 = sphere->second.p[0];
    b0 = sphere->first.p[1];
    b1 = sphere->second.p[1];
    c0 = __builtin_ps_sub(c0, c1);
    t1 = __builtin_ps_muls0(c0, t0);
    frame->p[6].p = c0;
    b1 = __builtin_ps_sub(b1, b0);
    frame->p[7].p = t1;
    t2 = __builtin_ps_muls0(b1, t0);
    frame->p[8].p = b1;
    c1 = __builtin_ps_add(c1, t1);
    frame->p[9].p = t2;
    frame->p[3].p = t2;
    b0 = __builtin_ps_add(b0, t2);
    frame->p[3].p = b0;
    t3 = a0;
    t3 = __builtin_ps_sub(t3, c1);
    frame->p[0].p = t3;
    out1->p[0] = t3;
    c0 = out2->p[1];
    c0 = __builtin_ps_sub(c0, b0);
    frame->p[1].p = c0;
    t1 = frame->p[6].p;
    out1->p[1] = t1;

    a0 = frame->p[3].p;
    b0 = out0->p[1];
    c0 = out0->p[0];
    b0 = __builtin_ps_mul(b0, a0);
    b0 = __builtin_ps_merge00(b0, *pair);
    c0 = __builtin_ps_madd(c0, t3, b0);
    c0 = __builtin_ps_sum0(c0, c0, c0);
    frame->p[19].p = c0;
    sf.ps = frame->p[19].p;

    if (!(sf.flt.hi > limit)) {
        return 0;
    }
    sf.flt.hi = sphere->radius;
    sf.flt.hi = sf.flt.hi * sf.flt.hi;
    return distance < sf.flt.hi;
}

// PARKED 2026-10-06: root cause is an input wall,
// not a source-shape wall — 53 of the WANT's 181 words are undecoded
// paired-single `op4` words (`tools/disasm.py`/capstone stall at 0x800FAE5C),
// so the whole middle 0x800FAE5C..0x800FB0A8 is invisible to the readable
// stream and byte-matching is unreachable from C until `tools/ps_disasm.py`
// decodes the FRT/FRA/FRB/FRC fields.  Best body above (4.57% masked, object
// 700B vs WANT 724B = 6 words short).
// NOTE: legible facts recovered from the WANT, for the PS-aware redraft (the
// body is already correct on all of these except the arg mapping):
//  - 7 incoming params. r3 = sphere (homed r27); r4/r5/r6 = three input
//    PairVecs (homed r30/r29/r28, read as psq_l 0/8 of each); r7/r8/r9 = the
//    three output PairVecs (homed r25/r31/r24). Frame 0xe0, saves r23..r31 +
//    f31 at 0xd8 — the body's frame/save span is already exact.
//  - Constants: lis r11=0x802A0000, addi -0x3fa0 => pair const lbl_8029C060
//    (r23); lfs -0x3ef8(r10) => lbl_8029C108 (limit, pinned f31); lfs
//    -0x3efc(r6) => lbl_8029C104 (eps). All three already named in the body.
//  - ARG MAPPING BUG (next concrete fix): the call at 0x800FAF48 is
//    fn_800F76E8(r27, r31, r30, r29, r28, &sp68, &sp6c, &sp70) — its 2nd
//    argument is the OUTPUT homed in r31 (incoming r8), but the body passes
//    `out0` (incoming r7) there. The r8 output must be declared/live first.
//  - Guards (scalar lanes of the PS results): at 0x800FAF0C the eps-against-
//    limit compare guards with an unordered-OR branch back to return 0 when eps
//    is below limit; at 0x800FAF1C the sum-result-against-limit compare falls
//    through into the rsqrte/rescale block when the result exceeds limit;
//    0x800FB0AC repeats the unordered guard; the 0x800FB0B8 tail squares the
//    radius word at 0x20(r27) and returns whether the callee result is below
//    radius squared, i.e. Sphere.radius at +0x20. Also confirm which PS lane
//    (lo vs hi) each compare reads — the body uses `.flt.hi`.
//  - Second independent divergence: ngccc lowers the equivalent C comparison
//    to ble/bge, not the retail `cror un,eq,{lt,gt} + bso` unordered guard.
// Nothing promoted; no other file touched and no new inline asm.
