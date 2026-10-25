// PARKED 2026-10-03 (b69): DIFF (baseline DIFF 7.5%; ps_diff 2/132 = 1.5%,
// got 528B vs want 532B). Reproduce:
// LEAF_TMPDIR=<scratch> tools/venv/bin/python tools/test_wip_drafts.py --addr 0x80025010
//
// WHAT THIS IS NOW (not the m2c draft): a full semantic reconstruction in C
// using the SN Systems SNAPS paired-single API (`sn_ps` = mode(PS) +
// __builtin_ps_*), compiled with `// FLAG: -mps-float`. Every PS opcode the
// want contains is emitted by this body, and the *instruction sequence* of
// block A (0x80025060..0x800250CC) is byte-identical to the want modulo the
// prologue's frame size:
//
//   The want's block A is a pair multiply of f11 by itself into f0, a merge of
//   f0 with the f13 zero pair, a multiply-add of f12 by itself plus f0, a
//   four-operand sum of f0, a pair copy of f0 into f13, an unordered compare
//   of f13 against f31, and a branch on below-or-equal; this build emits the
//   identical mnemonic sequence in the same floating-point registers.
//   => the intrinsic *sequence* is right; only the scheduler/regalloc differ.
//
// SEMANTICS RECOVERED (worth keeping — none of this is in the m2c draft):
//   * signature is 4 params, not 3: (self, s32 UNUSED, V2 *v, f32 f).
//     m2c dropped the phantom r4, which put `v` in r4 instead of r5. The want
//     does `mr r29, r5`.
//   * self+0x08 = 0x80291538 (type tag), +0x04 = 3, +0x6c = arg f1,
//     +0x0c = fn_8002439C(Mem_NewZero(0xD0)) [bl 0x800098f4, 1 arg],
//     +0x50 = +0x68 = 0 at the end. Return value = self.
//   * self+0x58/+0x60 are two 8-byte sn_ps slots = a 4-float vector; the
//     function first copies *v into them, then NORMALISES them in place.
//   * The length is a 3-COMPONENT dot product. The want squares the p1 pair,
//     merges the result with the all-zero pair at 0x802914E8, accumulates the
//     squared p0 pair onto that, and reduces the total with a four-operand sum
//     i.e. {p0.x^2, p0.y^2 + p1.x^2} — the merge00 with the all-zero pair at
//     0x802914E8 shifts p1.x^2 into the high lane and zeroes the low lane.
//     Compare is `len2 > 0.0f` against the *literal* 0.0f at 0x80291524
//     (`ble` skips when <=), NOT `0 > x` as m2c guessed.
//   * Branch bodies use ps_rsqrte:  vec0 = ps_muls0(p0, inv)  (both lanes
//     scaled)  but  vec1 = ps_mul(p1, {inv, 1.0f})  (only lane 0 scaled) —
//     the want really does overwrite the high lane of the spilled inv pair
//     with 1.0f (psq_st f13,88(r1) then stfs 1.0,0x5c(r1) then psq_l f9),
//     so `SP.sp = inv; SP.flt.hi = 1.0f;` is required, not a bug in my read.
//   * The 64-byte callee arg (r28 = r1+0x18) is a 4x4 row-major matrix
//     (fn_80024668 copies 64B to dst+0x78): row0={1,0,0,0} row1={0,1,0,0}
//     row3={0,0,0,1}, row2 = {0,0,1,0} overwritten by the normalised vector.
//     The 16-byte callee arg (r30 = r1+0x8, fn_8002464C copies 16B to
//     dst+0x68) gets .y=f1, .z=1.0f — and the want stores 8(r1) TWICE.
//   * Final fixups (all read back out of the stack, so they must be
//     separate statements): r0={r2.z,-r2.x,-r2.y,0}, r1={r2.y,-r2.z,-r2.x,0}.
//
// THE REMAINING DIFF (the whole blocker):
//   frame 0xc0 vs 0x88 and stfd f29/f30/f31 (0xa8/0xb0/0xb8) vs stfd f31
//   (0x80) only. The want has ZERO scalar stack slots — every f32/sn_ps
//   temporary lives in an FPR — while ProDG 3.9.3 spills ~0x38 bytes of
//   them and burns three callee-saved FPRs. Because the frame word is
//   instruction 0, that one mismatch shifts the whole body and the
//   positional score collapses to ~2%. The PS *ops* are right; the register
//   colouring is not.
//
// RULED OUT (so nobody repeats it):
//   * Not the flag set. `-mps-float` is mandatory: `mode(PS)` is a hard error
//     without it ("use of paired single mode illegal without -mps-float").
//     The want's 0x88 frame is consistent with -mps-float's documented +8
//     FPR-save quirk (0x80 without it).
//   * Not `__ps_t` vs `sn_ps`, and not float-struct loads: the want's
//     psq_l/psq_st all come from 8-byte sn_ps copies, which is what
//     `sn_ps` fields give.
//   * Not the `else` branch: the want has NO else (the row-2 pair store is
//     unconditional, before the `if`); adding one costs 2 extra stores + a
//     branch.  Removing it did not fix the frame though.
//   * Matrix-row layout: `Vec r2` + `union { Vec v; V2 p; }` overlay
//     reproduces the mixed stfs (rows 0/1/3) vs psq_st (row 2) pattern.
//     Replacing it with a row of `SP` union members is WORSE (frame 0xf0).
//   * Store order: ngccc emitted the 16 init stores in plain source order
//     here, so writing them in the want's order (r2.z,x,y,w then r0,r1,r3)
//     does reproduce that order — it just does not change the frame.
//   * Dropping the named `in` / `z` temporaries shrinks the body (492B) but
//     the frame stays 0xb0, i.e. the spill is not caused by them.
//
// MOST PROMISING NEXT IDEA: attack the spill directly. The want keeps only
// f11=p1, f12=p0, f0=len2, f13=zero/0.0f, f10=1.0f live through the block-B
// store run, and reuses f13 (which held `zero`) for the 0.0f literal after
// the merge00 kills it. So the original source almost certainly has *no*
// live sn_ps union across the store run — try expressing the whole of block
// B as one expression tree with no named SP unions at all (e.g. assign the
// 0.0f/1.0f literals into locals of type `f32` declared BEFORE the vec
// locals, so the local-slot rule hands them the low addresses), and only
// materialise `SP` for the two spilled inv pairs.
// WIP DRAFT (non-matching) — C body generated by tools/fill_wip_drafts.py
// family=m2c range=0x80025010-0x80025224 size=532B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// FLAG: -mps-float
#include "types.h"
#include "dolphin/SN_PS.h"

typedef union {
    sn_ps ps;
    struct { f32 hi, lo; } flt;
} SP;

typedef struct { sn_ps a, b; } V2;
typedef struct { f32 x, y, z, w; } Vec;
typedef union { Vec v; V2 p; } Row2;
typedef struct { Vec r0, r1; Row2 r2; Vec r3; } Mat;

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    char pad10[0x40];
    s32 unk50;
    s32 unk54;
    sn_ps vec0;
    sn_ps vec1;
    s32 unk68;
    f32 unk6c;
} CStruct;

extern char lbl_80291538[];
extern V2 lbl_802914E8;

void fn_80024724(void *);
void *fn_8002439C(void *);
void fn_8002464C(void *, void *);
void fn_80024668(void *, void *);
void *Mem_NewZero(u32);

void *fn_80025010(CStruct *arg0, s32 arg1, V2 *arg2, f32 farg0) {
    Vec sp8;
    Mat sp18;
    SP sp58;
    SP sp60;
    V2 in;
    sn_ps p0;
    sn_ps p1;
    sn_ps z;
    SP len2;
    SP inv;
    sn_ps t;
    s32 var_ctr;

    fn_80024724(arg0);
    var_ctr = 4;
    arg0->unk8 = (s32)lbl_80291538;
    do {
        var_ctr -= 1;
    } while (var_ctr != 0);
    arg0->unk6c = farg0;
    arg0->unk4 = 3;

    in = *arg2;
    p0 = in.a;
    p1 = in.b;
    arg0->vec0 = p0;
    arg0->vec1 = p1;

    z = lbl_802914E8.a;
    t = ps_mul(p1, p1);
    t = ps_merge00(t, z);
    t = ps_madd(p0, p0, t);
    len2.ps = ps_sum0(t, t, t);
    if (len2.flt.lo > 0.0f) {
        inv.ps = ps_rsqrte(len2.ps);
        arg0->vec0 = ps_muls0(p0, inv.ps);
        sp58.ps = inv.ps;
        sp58.flt.hi = 1.0f;
        arg0->vec1 = ps_mul(p1, sp58.ps);
    }

    arg0->unkC = fn_8002439C(Mem_NewZero(0xD0));

    sp8.y = farg0;
    sp8.y = farg0;
    sp8.z = 1.0f;
    fn_8002464C((void *)arg0->unkC, &sp8);

    p1 = arg0->vec1;
    p0 = arg0->vec0;
    z = lbl_802914E8.a;
    t = ps_mul(p1, p1);
    t = ps_merge00(t, z);
    t = ps_madd(p0, p0, t);
    len2.ps = ps_sum0(t, t, t);

    sp18.r2.v.z = 1.0f;
    sp18.r2.v.x = 0.0f;
    sp18.r2.v.y = 0.0f;
    sp18.r2.v.w = 0.0f;
    sp18.r0.x = 1.0f;
    sp18.r0.y = 0.0f;
    sp18.r0.z = 0.0f;
    sp18.r0.w = 0.0f;
    sp18.r1.x = 0.0f;
    sp18.r1.y = 1.0f;
    sp18.r1.z = 0.0f;
    sp18.r1.w = 0.0f;
    sp18.r3.x = 0.0f;
    sp18.r3.y = 0.0f;
    sp18.r3.z = 0.0f;
    sp18.r3.w = 1.0f;

    sp18.r2.p.a = arg0->vec0;
    sp18.r2.p.b = arg0->vec1;

    if (len2.flt.lo > 0.0f) {
        inv.ps = ps_rsqrte(len2.ps);
        sp60.ps = inv.ps;
        sp18.r2.p.a = ps_muls0(p0, inv.ps);
        sp60.flt.hi = 1.0f;
        sp18.r2.p.b = ps_mul(p1, sp60.ps);
    }

    sp18.r0.z = -sp18.r2.v.y;
    sp18.r1.x = sp18.r2.v.y;
    sp18.r1.y = -sp18.r2.v.z;
    sp18.r1.z = -sp18.r2.v.x;
    sp18.r0.x = sp18.r2.v.z;
    sp18.r0.y = -sp18.r2.v.x;

    fn_80024668((void *)arg0->unkC, &sp18);
    arg0->unk50 = 0;
    arg0->unk68 = 0;
    return arg0;
}
