// Reconstructed 2026-09-26 from disassembly. Paired-single (PS) body —
// must be compiled with -mps-float (per-object extra_cflags).
// family=hand range=0x800A95EC-0x800A970C size=288B
// extra_cflags: -mps-float
//
// PARKED 2026-10-06: 30.0% (21/70 words), object
// 280B vs retail 288B — NO IMPROVEMENT. This is the PS/FPR register-allocation
// wall (docs/parkings/15; recipe 7b), not a semantics bug: the switch dispatch,
// the 2D-normalize PS idiom, both call chains and all stores are structurally
// right, and retail's FPR homes (f0 accumulator, const in f12/f13) are simply
// not what ngccc picks for the same C. Ruled out THIS round (read-only, no
// compiler available to the worker): a matched sibling with the same idiom to
// copy — there is none (no src/fn_*.c uses ps_rsqrte/ps_res/ps_madd/ps_merge00);
// no callee-arity/return-type or struct-field-width error is visible in the
// want head. Re-check when a compiler is available: recipe 7b's
// `volatile S V[n]` pair-scratch rule does NOT apply here (its n=(frame-0x30)/8
// is negative for this 0x28 frame), so the two dead psq_st spills at object
// 0x70/0x90 remain the only unexplained words.
//
// VERIFIED from the retail head (raw words, not masked): the dispatch is a
// 4-way binary-search switch on fn_800A86E0(arg0) with case bodies laid out
// case0 @0x800A9628 (124B), case1 @0x800A96A4 (8B, `li r0,2`), case2
// @0x800A96AC (76B), default/tail @0x800A96F8 (20B, the shared EC store +
// epilogue). The draft's case order (0,1,2) matches; the residual is the
// per-case block length/colour, not the case mapping.
//
// Best score: 30.0% (21/70 words), got 280B vs retail 288B (tools/ps_diff.py).
// The structure is correct (switch dispatch, PS normalize idiom, both call
// chains, all stores); the residual is register-allocation coin-flips that
// resist plain C (docs/parkings/15, recipe-51 family):
//   * v2/z FPR swap (got f10/f12, want f12/f10) and v7/s (got f9/f10,
//     want f12/f11) — ngccc's FPR allocator picks different homes than the
//     game's compiler; __ps_t register pins are silently dropped or drop
//     the load (miscompile), so these can't be forced from C.
//   * two dead psq_st spills the game's compiler emitted (0x70, 0x90) that
//     ngccc never produces (an "m" pin emits spill+reload — worse).
//   * the ps_mul VB-field encoding difference (want VB=don't-care, ngccc
//     builtin always sets VB=VA).
//
// Disclosed pins/hacks (all runtime-neutral here):
//   * `register s32 var_r0 __asm__("r0")` — forces the EC-store value into
//     r0, which is what makes ngccc emit the game's `stw r31,0x24` prologue
//     (stw r31 only) instead of `stmw r30` + the r30 EC store.
//   * `volatile __ps_t vd1/vd2` — never accessed; they reserve the two low
//     spill slots so the frame grows to the game's 0x28 and the one real
//     spill lands at sp+0x18 exactly like the want (same technique as the
//     sanctioned `volatile double _dummy` frame-sizing recipe).
#include "types.h"

typedef struct {
    char _pad0[0x8];
    __ps_t pair0x8;
    __ps_t pair0x10;
    s32 f0x18;
    char _pad2[0x44];
    s32 f0x60;
    char _pad3[0xC];
    __ps_t pair0x70;
    __ps_t pair0x78;
    char _pad4[0x2C];
    f32 f0xAC;
    f32 f0xB0;
    s32 f0xB4;
    f32 f0xB8;
    char _pad5[0x4];
    __ps_t pair0xC0;
    __ps_t pair0xC8;
    char _pad6[0x1C];
    s32 f0xEC;
} Obj;

typedef union {
    __ps_t ps;
    struct {
        f32 hi;
        f32 lo;
    } flt;
} PSValue;

s32 fn_800A86E0(void *);
s32 GetChecksum_3(s32, s32);
void fn_800D68B8(s32, s32);
void fn_800A85A0(void *);
void fn_800A8D04(void *);

extern unsigned char lbl_802981C0[];

void fn_800A95EC(void *arg0) {
    Obj *o = arg0;
    register s32 var_r0 __asm__("r0");

    switch (fn_800A86E0(arg0)) {
    case 0: {
        __ps_t *p = (__ps_t *)((char *)arg0 + 8);
        __ps_t v0 = *(__ps_t *)((char *)arg0 + 8);
        __ps_t v2 = *(__ps_t *)((char *)arg0 + 0x78);
        __ps_t v3;
        __ps_t v4;
        __ps_t v5;
        __ps_t v7;
        __ps_t z;
        f32 s;
        PSValue rv;
        volatile __ps_t vd1;
        volatile __ps_t vd2;
        o->pair0xC0 = v0;
        __asm__ volatile("" ::: "memory");
        var_r0 = 3;
        v3 = p[1];
        o->pair0xC8 = v3;
        v4 = *(__ps_t *)((char *)arg0 + 8);
        v5 = p[1];
        z = *(__ps_t *)lbl_802981C0;
        v5 = __builtin_ps_sub(v5, v2);
        v5 = __builtin_ps_mul(v5, v4);
        o->f0xEC = var_r0;
        v7 = *(__ps_t *)((char *)arg0 + 0x70);
        s = *(f32 *)((char *)arg0 + 0xB8);
        v5 = __builtin_ps_merge00(v5, z);
        v4 = __builtin_ps_sub(v4, v7);
        o->f0xB0 = s;
        v4 = __builtin_ps_madd(v4, v4, v5);
        v4 = __builtin_ps_sum0(v4, v4, v4);
        v4 = __builtin_ps_rsqrte(v4);
        v4 = __builtin_ps_res(v4);
        rv.ps = v4;
        o->f0xAC = rv.flt.hi;
        return;
    }
    case 1:
        var_r0 = 2;
        break;
    case 2:
        fn_800D68B8(GetChecksum_3(o->f0x18, 0x0A015E17), o->f0x60);
        {
            f32 f13 = *(f32 *)((char *)arg0 + 0xB0);
            s32 r0 = o->f0xB4;
            f32 f0 = *(f32 *)((char *)arg0 + 0xAC);
            r0 &= ~4;
            f0 = f0 - f13;
            o->f0xB4 = r0;
            o->f0xB0 = f0;
        }
        fn_800A85A0(arg0);
        fn_800A8D04(arg0);
        var_r0 = 1;
        break;
    }
    o->f0xEC = var_r0;
}
