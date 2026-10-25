// PARKED 2026-10-05 (a-w2/0x80024AC4): NEAR 45.36% masked (53/97 words wrong),
// REFRESHED 2026-10-07 (scaffold/flag/volatile re-sweep): 45.3608% -> 49.4845% `volatile` keyword(s) removed from the body
// up from the m2c draft's 36.08%. Two real fixes landed: (1) SEMANTIC BUG —
// blk[4]/blk[5] lane reads (ax/ay/bx) must happen AFTER the two `blk[i].ps =
// arg0->unk0x18/20` pair stores, not before (the draft read the padding lanes,
// so it emitted 0.0/1.0 where retail reloads ax/ay/bx out of 0x48/0x4c/0x50);
// (2) FPR `register ... __asm__("frN")` pins on the tail's lane values + their
// negations put every lfs/fneg of the blk block in retail's register
// (ay=f11, -ay=f12, bx=f8, -bx=f10, ax/-ax=f13, 0.0=f0, 1.0=f9).
//
// Residual (all FPR-allocation / scheduler, no semantic lever left):
//  * first half: retail allocates A=f12, B=f11 (each via a `ps_mr` operand
//    copy), the 0.0 threshold=f10, the {0,0} pair const=f13, acc=f0. This
//    draft allocates A=f10, 0.0=f12 with NO operand copies. Getting retail's
//    shape needs the `t=arg1[0]; arg0->unk0x18=t; A=t;` temp+copy form *plus*
//    pins on t/A/B, but a pinned `f32 c1` makes cc1 DROP the `lfs f10,
//    0x13dc(r11)` entirely (fr10 reserved, load deleted -> `fcmpu cr0,f13,f10`
//    reads an unwritten reg). Hoisting it through a pointer
//    (`p1=&lbl_802913DC; c1=*p1;`) restores the lfs, but then cc1 folds the
//    f32-constant base onto the pair constant's r9 (one `lis`+`addi` instead
//    of retail's `lis r9/addi r9` + `lis r11`) and the whole first half
//    re-schedules: 23-25%.
//  * if-body: retail `ps_rsqrte f13,f0` writes the rsqrte straight into the
//    compare copy's reg; this draft emits `ps_rsqrte f0,f0` + a redundant
//    `ps_mr f13,f0`, stores iv before na (retail: na then iv) and computes
//    `nb = B*sc.ps` into f11 instead of the dead acc f0. Pinning `iv` to fr13
//    grows the object to 396B (2 words over) -> worse.
//  * blk block: the `psq_l/psq_st f13` pair temp lands in f10 (retail f13) —
//    f10 is taken by the (later) pinned `nbx`, and cc1 will not pin a __ps_t
//    that is a struct-field load+store temp.
//  * the 12 blk stores: cc1's scheduler scrambles them (got
//    0x38,0x30,0x3c,0x2c,0x28,0x64,0x34,0x40,0x60,0x5c,0x58,0x44 vs retail
//    0x60,0x64,0x30,0x38,0x3c,0x40,0x34,0x44,0x58,0x5c,0x28,0x2c). Both
//    "reverse source order" and "literal retail order" seeds were tried and
//    score lower (43.3%); the rest of the space is a 12-way permutation.
//  Ruled out: `-fno-schedule-insns` (11.6%), `-fno-schedule-insns2` (32-34%),
//  volatile SN_PS_type slot for iv (14.6%), `__builtin_ps_*` -> no spelling
//  change, `lbl_802913DC`/`E0` are 0.0f/1.0f and `lbl_80291398` is the pair
//  {0.0f,0.0f} (verified in .rodata2) so the draft's constant NAMES are
//  misleading but the emitted code is right. Sibling that already matches:
//  src/fn_801B19DC.c (same ps_mul/merge00/madd/sum0/rsqrte normalise chain,
//  uses frN pins + -fno-schedule-insns + inline-asm ps ops; the inline-asm ops
//  were not used here).
// family=m2c range=0x80024AC4-0x80024C48 size=388B
// extra_cflags: -mps-float
#include "types.h"

extern f32 lbl_802913DC;
extern f32 lbl_802913E0;
extern __ps_t lbl_80291398;

void *fn_80024660(void *);
void fn_8002464C(__ps_t *, __ps_t *);
void fn_80024668(__ps_t *, __ps_t *);
void fn_800550B4(s32, s32);

typedef struct {
    char pad0[0xC];
    __ps_t *unk0xC;
    s32 unk0x10;
    s32 unk0x14;
    __ps_t unk0x18;
    __ps_t unk0x20;
    f32 unk0x28;
} Obj24AC4;

void fn_80024AC4(Obj24AC4 *arg0, __ps_t *arg1) {
    __ps_t loc[2];
    SN_PS_type tv[2];
    SN_PS_type blk[8];
    __ps_t A, B, t, iv, na, nb;
    SN_PS_type sc, sv;
    __ps_t *pv;
    register f32 ay __asm__("fr11");
    register f32 ax __asm__("fr13");
    register f32 bx __asm__("fr8");
    register f32 nay __asm__("fr12");
    register f32 nax __asm__("fr13");
    register f32 nbx __asm__("fr10");
    s32 ctr;

    pv = (__ps_t *)fn_80024660(arg0->unk0xC);
    loc[0] = pv[0];
    loc[1] = pv[1];

    A = arg1[0];
    arg0->unk0x18 = A;
    B = arg1[1];
    arg0->unk0x20 = B;

    t = B * B;
    t = __builtin_ps_merge00(t, lbl_80291398);
    t = __builtin_ps_madd(A, A, t);
    sv.ps = __builtin_ps_sum0(t, t, t);
    if (sv.flt.hi > lbl_802913DC) {
        iv = __builtin_ps_rsqrte(sv.ps);
        na = __builtin_ps_muls0(A, iv);
        arg0->unk0x18 = na;
        sc.ps = iv;
        sc.flt.lo = lbl_802913E0;
        nb = B * sc.ps;
        arg0->unk0x20 = nb;
    }

    tv[0].flt.hi = lbl_802913DC;
    tv[0].flt.lo = lbl_802913DC;
    tv[1].flt.hi = lbl_802913DC;
    tv[1].flt.lo = lbl_802913E0;
    fn_8002464C(arg0->unk0xC, (SN_PS_type *)tv);

    ctr = 4;
    do {
        ctr -= 1;
    } while (ctr != 0);

    blk[4].flt.hi = lbl_802913DC;
    blk[4].flt.lo = lbl_802913DC;
    blk[5].flt.hi = lbl_802913E0;
    blk[5].flt.lo = lbl_802913DC;
    blk[4].ps = arg0->unk0x18;
    blk[5].ps = arg0->unk0x20;
    ay = ((f32 *)&blk[4].ps)[1];
    ax = ((f32 *)&blk[4].ps)[0];
    bx = ((f32 *)&blk[5].ps)[0];
    nay = -ay;
    nax = -ax;
    nbx = -bx;
    blk[7].flt.lo = lbl_802913E0;
    blk[7].flt.hi = lbl_802913DC;
    blk[6].flt.lo = lbl_802913DC;
    blk[6].flt.hi = lbl_802913DC;
    blk[3].flt.lo = lbl_802913DC;
    blk[3].flt.hi = nax;
    blk[2].flt.lo = nbx;
    blk[2].flt.hi = ay;
    blk[1].flt.lo = lbl_802913DC;
    blk[1].flt.hi = nay;
    blk[0].flt.lo = nax;
    blk[0].flt.hi = bx;
    fn_80024668(arg0->unk0xC, (SN_PS_type *)blk);

    fn_8002464C(arg0->unk0xC, loc);
    fn_800550B4(arg0->unk0x10, arg0->unk0xC);
}
