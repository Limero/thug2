// PARKED 2026-10-03 (a06): NEAR 88.5% (46/52 masked words), size-exact 208B.
//   tools/venv/bin/python tools/test_wip_drafts.py --addr 0x800A0F2C
//   (was NEAR 80.8% / 42-of-52 before this round — see "WHAT CHANGED" below).
//
// REMAINING DIFF: exactly 3 pairwise swaps, ALL registers/encodings already
// agree with retail; only instruction ORDER inside 0x800A0F64-0x800A0F80 is off
// (`tools/want_vs_got.py 0x800A0F2C`, want | got):
//    0064 psq_l  f11,0(r9)     | ps_sub    f13,f13,f0   (const pair load)
//    0068 ps_sub  f13,f13,f0    | psq_l     f11,0(r9)
//    006C psq_st f13,16(r1)     | psq_l     f0,88(r31)   (arg0+0x58 load)
//    0070 ps_mul  f13,f13,f13   | ps_mul    f13,f13,f13  OK
//    0074 lfs    f10,0x7ba4(r11)| lfs       f10,0(r11)   OK (ADDR16 mask)
//    0078 psq_l  f0,88(r31)     | ps_sub    f0,f0,f12
//    007C ps_merge00 f13,f13,f11| psq_st    f13,16(r1)   (d.f8 spill)
//    0080 ps_sub  f0,f0,f12     | ps_merge00 f13,f13,f11
// i.e. ngccc emits [sub1][const][arg0.58][mul][lfs][sub2][spill][merge][...]
// where retail has [const][sub1][spill][mul][lfs][arg0.58][merge][sub2][...].
// ROOT CAUSE (single mechanism): the two dead `psq_st` spills of Pair2 `d` are
// placed at the END of their live range (ngccc `reload1` "late" spill) instead
// of immediately after their defining `ps_sub` (retail's placement == an "early"
// spill).  Measured rule: the spill lands LATE unless the mul/madd that consumes
// the value is emitted IN PLACE (dest reg == source reg) *and* is a separate
// pseudo whose live range ends there; with an in-place self-assignment the whole
// value collapses into one pseudo spanning sub->mul->merge, so the spill slides
// to after the merge.  Retail has BOTH (early spill AND in-place ops), which no
// C form found here produces simultaneously.
//
// WHAT CHANGED THIS ROUND (the real discovery, worth keeping for the siblings
// fn_800A07F0 / 800A1230 / 800A12D0 / 800A1360 and other PS parks):
//   `d.f8 = __builtin_ps_mul(d.f8, d.f8);` — writing the square back through the
//   SAME Pair2 member instead of nesting it inside the merge00 — makes ngccc
//   allocate the whole first chain in f13 IN PLACE (ps_sub/ps_mul/ps_merge00 all
//   f13), which cascades into every other register choice and fixes 6 words at
//   once: ps_mul f13,f13,f13 (was f11), ps_merge00 f13,f13,f11 (was f11), the
//   const pair in f11 (was f10), 12.0f in f10 + the `fdivs f1,f13,f10` pair
//   (was f9 + a broken fdivs).  With that, EVERY FPR in the block matches
//   retail: o60=f0 a60=f13 o58=f12 const=f11 12.0f=f10 a58=f0.
//   The `o58 = obj->unk0x58` fr12 pin is still load-bearing on this body
//   (dropping it -> 39/52 = 75.0%); the `o60 = obj->unk0x60` staging temp is
//   too (direct `obj->unk0x60` read -> o60 lands in f12, 84.6%).
//   -fno-gcse and -fno-thread-jumps are neutral on the new body; every
//   scheduling flag tried earlier is still neutral; -fno-schedule-insns2 hurts
//   (37/52).  `-fno-premove` / `-fno-move-vregs` / `-fno-reorder-blocks` do not
//   exist in this cc1, so the reload-stage knobs are not reachable from flags.
//
// RULED OUT (measured, this round):
//   * nesting `__builtin_ps_mul(d.f8,d.f8)` inside merge00 (the pre-round body):
//     mul result gets its own reg (f10/f11), spill goes late -> 42/52 at best.
//   * `Pair2 d; d.f8 = p;` with a separate `__ps_t p` (explicit dead store):
//     still a late spill (0x7C) -> 42/52.  An explicit source store is NOT what
//     retail's early `psq_st` is.
//   * `register __ps_t v0/v8` locals instead of `Pair2 d` (hoping a register
//     variable forces reload_early): forces a real memory round trip
//     (psq_st f0,16(r1) + lfs f0,0x10(r1)) and shrinks the frame to 0x20 -> 19/52.
//   * computing the second difference BEFORE the merge, and swapping the two
//     difference chains: 84.6% / 86.5%, both lose f13 for a60.
//   * pinning the const pair to fr11 / 12.0f to fr10 on top of the new body:
//     NEUTRAL (the in-place mul already produces f11/f10) -> not needed, dropped.
//   * `__ps_t o60/a58/o58` fully pinned (fr0/fr13/fr12/fr0): two pinned vars on
//     one hard reg -> allocator collapses the load group, 24/52, 204B.
//
// NEXT IDEA: the only thing left is making ngccc's reload1 emit the two `d`
// spills EARLY while keeping the in-place ops.  Untested routes: (1) give the
// first chain TWO live pseudos so both conditions hold — e.g. keep the nested
// mul but force the mul's destination onto the sub's register via an
// `__asm__("reg")`-free construct such as
// `dot.ps = __builtin_ps_mul(d.f8, d.f8); dot.ps = __builtin_ps_merge00(dot.ps, lbl_80297B28);`
// (tested as a variant: collapses to the nested behaviour, 42/52);
// (2) accept a 2-instruction asm window around sub+spill — out of scope while
// parked (the <10%-asm rule).
//
// ORIGINAL DRAFT NOTES (still accurate): the m2c body mistook the whole
// paired-single block for a scalar divide. Retail is the SNAPS "inverse
// 1/sqrt of a squared difference" idiom:
//     dot.ps = __builtin_ps_merge00(__builtin_ps_mul(A, A), lbl_80297B28);
//     dot.ps = __builtin_ps_madd(B, B, dot.ps);
//     dot.ps = __builtin_ps_sum0(dot.ps, dot.ps, dot.ps);
//     dot.ps = __builtin_ps_rsqrte(dot.ps);
//     dot.ps = __builtin_ps_res(dot.ps);
//     x = dot.flt.hi;
// A = arg0->0x60 - obj->0x60, B = arg0->0x58 - obj->0x58, result / 12.0f
// (lbl_80297BA4) pushed as QB_OBJECTDISTANCE. Verified exact: frame 0x30,
// stmw r30 at sp18@0x18, the two dead pair spills (0x08/0x10), the
// lbl_80297BA0 default, the 12.0f page anchor, the psq_st/lfs lane readback and
// the fmr+fdivs tail, all three ADDR16 pairs (0x80297BA0 / 0x80297B28 /
// 0x80297BA4), the lone REL14 (beq -> 0x800A0FD4) and the three REL24 call
// targets (GetChecksum_2 / fn_8009F498 / fn_8012772C). Object emits .text only,
// 0 inline instructions, 0xD0 = symbols.txt size.
// family=m2c range=0x800A0F2C-0x800A0FFC size=208B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// extra_cflags: -mps-float
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern __ps_t lbl_80297B28;
extern f32 lbl_80297BA0;
extern f32 lbl_80297BA4;
typedef struct { __ps_t f0; __ps_t f8; } Pair2;
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 fn_8009F498(s32);
void fn_8012772C(CStruct *, s32, f32);
s32 fn_800A0F2C(Unk_64D775D7 *arg0, CStruct *arg1, CScript *arg2) {
    s32 sp18;
    f32 var_f1;
    f32 x;
    Unk_64D775D7 *obj;
    SN_PS_type dot;
    Pair2 d;
    __ps_t o60;
    register __ps_t o58 __asm__("fr12");

    sp18 = 0;
    GetChecksum_2(arg1, 0, &sp18, 1);
    obj = (Unk_64D775D7 *)fn_8009F498(sp18);
    var_f1 = lbl_80297BA0;
    if (obj != 0) {
        o60 = obj->unk0x60;
        o58 = obj->unk0x58;
        d.f8 = __builtin_ps_sub(arg0->unk0x60, o60);
        d.f8 = __builtin_ps_mul(d.f8, d.f8);
        dot.ps = __builtin_ps_merge00(d.f8, lbl_80297B28);
        d.f0 = __builtin_ps_sub(arg0->unk0x58, o58);
        dot.ps = __builtin_ps_madd(d.f0, d.f0, dot.ps);
        dot.ps = __builtin_ps_sum0(dot.ps, dot.ps, dot.ps);
        dot.ps = __builtin_ps_rsqrte(dot.ps);
        dot.ps = __builtin_ps_res(dot.ps);
        x = dot.flt.hi;
        var_f1 = x / lbl_80297BA4;
    }
    fn_8012772C(arg2->unk0x18, QB_OBJECTDISTANCE, var_f1);
    return 1;
}