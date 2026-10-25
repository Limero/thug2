// WIP DRAFT — hand rebuild (2026-08-25). Impact-reaction magnitude: script
// threshold gate + vec normalize/clamp vs plane normal, blended return.
// PARKED 25.3% (-mps-float): full hand-rebuild from decoded disasm; guard dance
// (plain bgt + cror/bns pair), script chain, dot/rsqrte/muls0 PS block all
// structurally present. Residue = stack-slot assignment cascade: want lays
// p1@8/p2@0x10/sp18@0x18/rs@0x20/K560@0x24/dot@0x28 (frame 0x50) while got
// coalesces several into registers (frame 0x38) shifting every psq disp;
// downstream FPR names follow (f11/f12 vs want f12/f13 in the normalize
// block). Tried: flat/nested/goto guard forms (G1-G4), named src/pp pointer
// mixes, staged k3/base, product-array staging; -fno-sched-spec/-interblock/
// -schedule-insns[2] no help. Needs a slot-forcing frame-template rebuild
// (S6p-105 style) in a fresh session.
// Decoded structure (ps ops hand-decoded from raw words):
//   guard1: arg0->0x1864 > lbl_802AF558 -> return farg0 (plain bgt)
//   script: GetFloat(GetStructure(6775E538,0), 79D182AD, &sp18, 1)
//   guard2: if (!(farg0 <= sp18)) BODY else return farg0 (cror un,eq,lt + bns)
//   BODY: pp=&p1; p1/p2 <- pair(arg0+0x1860/68); pp[0]=p1; pp[1]=p2; lane
//   overwrite *(f32*)((char*)&p1+4)=K55C; dot=sum0(madd(mul(pp[1],pp[1])
//   merge00 R, p1)); if dot>K55C: rs=rsqrte(dot); p1=muls0(p1,rs); p2=mul(p2,rs)
//   tail: dot2=sum0(madd(pair(arg1), pair(arg1), mul(pair(arg1+8),p2) merge00 R));
//   return ((|dot2|*base)*farg0)+((K560-|dot2|)*farg0).
// family=m2c range=0x8020F078-0x8020F1D4 size=348B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// FLAG: -mps-float -Os
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_802AF450[];
extern f32 lbl_802AF558;
extern f32 lbl_802AF55C;
extern f32 lbl_802AF560;
s32 GetStructure(s32 arg0, s32 arg1);
s32 GetFloat(CStruct * arg0, s32 arg1, f32 * arg2, s32 arg3);
f32 fn_8020F078(Unk_0BDCDD75 *arg0, Unk_EA529D06 *arg1, f32 farg0) {    Unk_560A7BB5 p1;
    __ps_t p2;
    __ps_t rs;
    __ps_t *pp;
    __ps_t *src;
    f32 sp18;
    SN_PS_type dot;
    f32 d;
    f32 ad;
    src = (__ps_t *)((char *)arg0 + 0x1860);
    if (arg0->unk0x1864 > lbl_802AF558) {
        return farg0;
    }
    GetFloat(GetStructure(QB_WALK_PARAMETERS, 0), QB_WALK_SPEED, &sp18, 1);
    if (farg0 <= sp18) {
        return farg0;
    }
        *((__ps_t *)&p1) = src[0];
        p2 = arg0->unk0x1868;
        pp = &p1;
        pp[0] = *((__ps_t *)&p1);
        pp[1] = p2;
        p1.unk0x4 = lbl_802AF55C;
        dot.ps = __builtin_ps_mul(pp[1], pp[1]);
        dot.ps = __builtin_ps_merge00(dot.ps, *(__ps_t *)&lbl_802AF450);
        dot.ps = __builtin_ps_madd(*((__ps_t *)&p1), *((__ps_t *)&p1), dot.ps);
        dot.ps = __builtin_ps_sum0(dot.ps, dot.ps, dot.ps);
        if (!(dot.flt.hi <= lbl_802AF55C)) {
            rs = __builtin_ps_rsqrte(dot.ps);
            pp[0] = __builtin_ps_muls0(pp[0], rs);
            pp[1] = __builtin_ps_mul(pp[1], rs);
        }
        {
            __ps_t n;
            n = arg1->unk0x8;
            n = __builtin_ps_merge00(__builtin_ps_mul(n, pp[1]), *(__ps_t *)&lbl_802AF450);
            dot.ps = __builtin_ps_madd(*(__ps_t *)(char *)arg1, *(__ps_t *)(char *)arg1, n);
            dot.ps = __builtin_ps_sum0(dot.ps, dot.ps, dot.ps);
        }
        d = dot.flt.hi;
        ad = __builtin_fabsf(d);
        return (((ad * arg0->unk0x1864) * farg0) +
                ((lbl_802AF560 - ad) * farg0));
    return farg0;
}
