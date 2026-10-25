// WIP DRAFT (non-matching) — hand-rebuilt from disasm (doc-06 PS idioms +
// REFRESHED 2026-10-07 (volatile-subset sweep): 88.6957% -> 90.4348%
//   only the FIRST of the draft body's 8 `volatile` keywords is load-bearing;
//   removing the OTHER seven is a strict gain.  See AGENTS-recipes §6hk.
// doc-30 self-targeting bdnz$ window recipe). NEAR 88.7% masked (-mps-float).
// PARKED: remaining 13 words are the tail-block schedule (0x801B5D64-0x5D90):
// want emits [merge00-resC][st-resA][lfs C100][st resC][stfs lane][lfs lane-read]
// [psq_l reload][cmp][mr f0,f12][st resB] with the compare SPLIT from its branch;
// ngccc 3.9.3 keeps a different order, drops the redundant ps_mr copy and
// rematerializes vmax inside the branch body. ~25 source shapes + volatile
// ordering + memory clobbers + anchor-split asm + register pins tried; the
// rotation matches the intermediate-SN-compiler scheduling family (doc06
// dead-psq_st/unroll artifacts) — not reproducible from C in 3.9.3.
// family=hand range=0x801B5BF8-0x801B5DC4 size=460B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// PAIRED-SINGLE DRAFT: sweep/promote with --extra-cflags "-mps-float".
// FLAG: -mps-float
#include "types.h"
#include "structs.h"

extern f32 lbl_802AC0E8;
extern f32 lbl_802AC0EC;
extern f32 lbl_802AC0F0;
extern f64 lbl_802AC0F8;
extern char lbl_802AC100[];
extern f32 lbl_802AC104;

f32 fn_80005E20(void *a, void *b);
void fn_801B5EE8(void *a, f32 b, f32 c);

void fn_801B5BF8(void *arg0, void *arg1, f32 farg0) {
    struct {
        __ps_t copy[8];
        SN_PS_type e1;
        SN_PS_type e2;
        SN_PS_type d1;
        SN_PS_type d2;
        SN_PS_type resA;
        SN_PS_type resB;
        SN_PS_type resC;
        char _pad[8];
    } fr;
    volatile double _dummyF;
    SN_PS_type ap0;
    SN_PS_type ap1;
    SN_PS_type t1;
    SN_PS_type t2;
    SN_PS_type t3;
    SN_PS_type t4;
    SN_PS_type t5;
    SN_PS_type d1r;
    SN_PS_type d2r;
    SN_PS_type mA;
    SN_PS_type mB;
    SN_PS_type mC;
    SN_PS_type mD;
    SN_PS_type mE;
    SN_PS_type mF;
    f32 vmax2;

    Unk_C7387A53 *a0;
    register char *objp __asm__("r11");
    register char *src __asm__("r10");
    register __ps_t *dst __asm__("r8");
    register void *in_a1 __asm__("r4");
    register void *a1v __asm__("r7");
    register void *pa0 __asm__("r3");
    register void *pa1 __asm__("r4");
    register s32 w9 __asm__("r9");
    register char *a100 __asm__("r9");
    register f32 fv30 __asm__("fr30");
    register f32 var_f8 __asm__("fr8");
    register f32 vmax __asm__("fr7");
    register f32 fv31 __asm__("fr31");

    a0 = arg0;
    in_a1 = arg1;

    __asm__ volatile("li 0, 4\n\tlwz %2, 0xc(%4)\n\tmtctr 0\n\tmr %1, %5\n\tfmr %3, %6\n\taddi %0, 1, 8"
                     : "=r"(dst), "=r"(a1v), "=r"(w9), "=f"(fv30)
                     : "r"(a0), "r"(in_a1), "f"(farg0)
                     : "r0", "ctr");
    __asm__ volatile("addi %0, 1, 0x28\n\taddi %2, %3, 0xd0\n\taddi %1, 1, 0x58\n\tbdnz $"
                     : "=r"(pa0), "=r"(pa1), "=r"(src)
                     : "r"(w9));

    __asm__ volatile("psq_l 0, 0(%0), 0, 0" : : "r"(src) : "fr0");
    fv31 = lbl_802AC0E8;
    __asm__ volatile("psq_st 0, 0(%0), 0, 0\n\tpsq_l 12, 8(%1), 0, 0"
                     : : "r"(dst), "r"(src) : "fr0", "fr12");
    objp = *((char * *)&a0->unk0xC);
    __asm__ volatile("psq_st 12, 8(%0), 0, 0\n\t"
                     "psq_l 0, 16(%1), 0, 0\n\tpsq_st 0, 16(%0), 0, 0\n\t"
                     "psq_l 12, 24(%1), 0, 0\n\tpsq_st 12, 24(%0), 0, 0\n\t"
                     "psq_l 0, 32(%1), 0, 0"
                     : : "r"(dst), "r"(src) : "fr0", "fr12");
    ap1.ps = ((Unk_73778A2B *)a1v)->unk0x8;
    __asm__ volatile("psq_st 0, 32(%0), 0, 0\n\t"
                     "psq_l 12, 40(%1), 0, 0\n\tpsq_st 12, 40(%0), 0, 0\n\t"
                     "psq_l 0, 48(%1), 0, 0\n\tpsq_st 0, 48(%0), 0, 0\n\t"
                     "psq_l 12, 56(%1), 0, 0\n\tpsq_st 12, 56(%0), 0, 0"
                     : : "r"(dst), "r"(src) : "fr0", "fr12");

    __asm__ volatile("psq_l 0, 88(%0), 0, 0\n\tpsq_st 0, 72(1), 0, 0\n\t"
                     "psq_l 12, 96(%0), 0, 0\n\tpsq_st 12, 80(1), 0, 0"
                     : : "r"(objp) : "fr0", "fr12", "memory");
    fr.e1.flt.lo = fv31;
    ((Unk_F6393DBC *)a1v)->unk0x4 = fv31;
    ap0.ps = *(__ps_t *)(char *)a1v;
    __asm__("" : : : "fr0");
    fr.d1.ps = __builtin_ps_sub(fr.e1.ps, ap0.ps);
    fr.d2.ps = __builtin_ps_sub(fr.e2.ps, ap1.ps);

    var_f8 = fn_80005E20(pa0, pa1) + lbl_802AC0EC;
    vmax = lbl_802AC0F0;
    __asm__("" : "+f"(vmax));
    if (var_f8 > vmax) {
        var_f8 -= (f32)(f64)(s32)(var_f8 / vmax) * vmax;
    }

    __asm__("" : : : "fr13");
    t1.ps = *(__ps_t *)&fr.copy[4];
    __asm__ volatile("lis %0, %1@ha" : "=r"(a100) : "s"(lbl_802AC100));
    d1r.ps = *(__ps_t *)&fr.d1;
    t2.ps = *(__ps_t *)&fr.copy[5];
    d2r.ps = *(__ps_t *)&fr.d2;
    mA.ps = __builtin_ps_merge00(t2.ps, t1.ps);
    mB.ps = __builtin_ps_merge00(d1r.ps, d2r.ps);
    mA.ps = __builtin_ps_mul(mA.ps, mB.ps);
    mC.ps = __builtin_ps_merge10(t1.ps, t2.ps);
    mD.ps = __builtin_ps_merge10(d1r.ps, d2r.ps);
    mE.ps = __builtin_ps_mul(t1.ps, mD.ps);
    mC.ps = __builtin_ps_mul(mC.ps, d1r.ps);
    mF.ps = __builtin_ps_merge10(mA.ps, mA.ps);
    mE.ps = __builtin_ps_sub(mE.ps, mC.ps);
    mA.ps = __builtin_ps_sub(mA.ps, mF.ps);
    fr.resA.ps = __builtin_ps_merge10(mE.ps, mA.ps);
    vmax2 = *(f32 *)(a100 - 0x3F00);
    fr.resC.ps = __builtin_ps_merge00(mE.ps, mE.ps);
    fr.resC.flt.lo = vmax2;
    fr.resB.ps = fr.resC.ps;
    if (*(f32 *)&fr.resA.flt.lo > fv31) {
        var_f8 = lbl_802AC0F0 - var_f8;
    }
    fn_801B5EE8(a0, var_f8 * lbl_802AC104, fv30);
}
