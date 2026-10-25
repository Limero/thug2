// PARKED 2026-09-28 (b2_09): best 37.0% (was 25.9%). Two real fixes: (1) the
// source's `t = ps_mul(d1, d1)` was WRONG — want's ps_mul is f13*f0 = d1*a0
// (arg0->unk0x0), so a0 is loaded early and used for BOTH t and d0; (2) the
// load order now matches want (arg1->unk0x8, arg0->unk0x8, a0, lbl). Residual
// = the known doc-06 M5.0j dead-spill wall: want emits 3 psq_st spills (d1@0x10,
// d0@0x8, dot@0x18, frame 0x20) but 3.9.3 with -fno-expensive-optimizations
// omits the 2 dead ones (d1, d0) → frame 0x18. Also the reload differs (got
// integer roundtrip lwz/stw/lfs vs want lfs/fmr) and arg1->unk0x0/z land in
// f11/f12 vs want f12/f11. Tried and failed: volatile __ps_t (stfd save,
// 9.4%), -fno-tree-dce (not in cc1), lbl-early via named var (29.6% — GCC
// sinks the load past d1 anyway), a1_0 named load (C89 mid-fn decl). Family:
// doc-06 M5.0j dead psq_st spills + PS regalloc. The dead spills need a
// compiler that emits them (the game's did); 3.9.3's -fno-expensive-optimizations
// only recovers the frame to 0x18, not the 2 dead spills.
// WIP DRAFT (non-matching) — SNAPS reconstruction (see parking doc 06 M5.0j)
// family=m2c range=0x8005A114-0x8005A180 size=108B
// BLOCKED: the game emits DEAD psq_st spills after each ps_sub (keeps the
// value in-register too); 3.9.3 omits them and shrinks the frame 0x20->0x10.
// Compiles to 100B vs 108B WANT (structurally identical, minus 2 dead spills).
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// FLAG: -mps-float -fno-expensive-optimizations
#include "types.h"
#include "structs.h"
extern __ps_t lbl_80293458;
s32 fn_8005A114(Unk_F68EF90C *arg0, Unk_EA529D06 *arg1) {
    __ps_t d1;
    __ps_t d0;
    __ps_t t;
    __ps_t a0;
    __ps_t lblv;
    f32 z;
    SN_PS_type dot;
    __ps_t a1_8 = arg1->unk0x8;
    __ps_t a0_8 = arg0->unk0x8;
    a0 = *(__ps_t *)arg0;
    lblv = lbl_80293458;
    d1 = __builtin_ps_sub(a0_8, a1_8);
    d0 = __builtin_ps_sub(a0, *(__ps_t *)arg1);
    z = arg0->unk0x14;
    t = __builtin_ps_mul(d1, a0);
    t = __builtin_ps_merge00(t, lblv);
    dot.ps = __builtin_ps_madd(d0, d0, t);
    dot.ps = __builtin_ps_sum0(dot.ps, dot.ps, dot.ps);
    {
        f32 x = dot.flt.hi;
        return x <= z * z;
    }
}
