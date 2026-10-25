// WIP DRAFT (non-matching) — hand-rebuilt from disasm, PS-math reconstruction.
// family=scriptcmd range=0x8015E868-0x8015EA20 size=440B
// Previous park claimed XO5=8 words were a hard wall — WRONG: those three
// words (0x10005890/0x11a00090/0x11805890) decode as XO10=72 = ps_mr (bits
// 21-25=2, xo5=8), emittable via inline asm. The whole !=0 branch is SNAPS
// paired-single math (ps_mul/merge00/madd/sum0/rsqrte/muls0 x3/mr x3),
// reconstructed with __builtin_ps_* + -mps-float.
// Lane0 compare trick: __asm__("" : "=f"(scalar) : "f"(ps_val)) reinterprets
// the pair in-register (union .flt.hi spills; this does not).
// FLAG: -mps-float -fno-cse-follow-jumps
// PERMUTED 2026-09-13 (a permutation-search script, since removed): score now 85.45% ([1]p1->85.5%).
#include "types.h"
extern f32 lbl_802A8228;
extern f32 lbl_802A822C;
extern __ps_t lbl_802A8048;
#include "qb_constants.h"
#include "structs.h"
s32 GetFloat(CStruct *, void *, f32 *, s32);
s32 fn_80128CE0(CStruct *, void *, void *, s32);
void *Mem_Alloc2(s32);
void Mem_Free(void *);

// PARKED 83.6% (-mps-float): 18 word diffs left in 5 clusters — all FPR-role
// colorings + 2 load-order swaps in the SNAPS PS body (buf tail wants
// const->f11/pair->f0, got f0/f13; flo wants f13; mpair/o psq_l order;
// sp3C lfs placement; mr r3,r30 vs li r3,0 tail). Resists: volatile asm
// barriers (restructures block), comma folds, nested fr13/fr11/fr0 pins,
// early-return form (collapses whole frame), sched flag combos.
// FIXED this round: draft used QB_VEL_Y/QB_VEL_Z before they were defined
// (was the COMPILE FAIL) — hashes 0x1680A0FB/0x8F89F141 brute-forced via
// tools/qb_hash.py and added to include/qb_constants.h.
bool ScriptSetSkaterVelocity(CStruct *arg0, Unk_FFAD6788 *arg1) {
    struct {
        __ps_t sp8[2];
        f32 sp18;
        f32 sp1C;
        f32 sp20;
        f32 sp24;
        f32 sp28;
        f32 sp2C;
        f32 sp30;
        f32 sp34;
        f32 sp38;
        f32 sp3C;
        f32 sp40;
        char pad[4];
    } loc;
    f32 temp_f31;
    volatile __ps_t *pv;
    __ps_t plo, sq, u, q, m, g, o, r2, p, vlo2, mpair, m2, rh, rl, flo, fhi, h;
    f32 bufc;
    __ps_t bufpair;
    register __ps_t phi __asm__("fr11");
    f32 speed;
    register void *obj __asm__("r30");

    obj = *((void * *)&arg1->unk0xBC);
    if (obj != NULL) {
        temp_f31 = lbl_802A8228;
        loc.sp28 = temp_f31;
        if (GetFloat(arg0, 0, &loc.sp28, 0) != 0) {
            plo = ((Unk_073F5245 *)obj)->unk0xB8;
            pv = &loc.sp8[0];
            loc.sp8[0] = plo;
            pv[1] = phi;
            phi = ((Unk_073F5245 *)obj)->unk0xC0;
            __asm__("ps_mr %0, %1" : "=&f"(sq) : "f"(phi));
            sq = (q = lbl_802A8048, __builtin_ps_mul(sq, sq));
            u = loc.sp8[0];
            q = __builtin_ps_merge00(sq, q);
            m = __builtin_ps_madd(u, u, q);
            g = __builtin_ps_sum0(m, m, m);
            __asm__("ps_mr %0, %1" : "=&f"(h) : "f"(g));
            __asm__("" : "=f"(speed) : "f"(h));
            if (speed > temp_f31) {
                register __ps_t n __asm__("fr13");
                register __ps_t r2 __asm__("fr11");
                register __ps_t o __asm__("fr0");
                __ps_t scaled_lo;
                __asm__("ps_rsqrte %0, %1" : "=f"(n) : "f"(g));
                scaled_lo = __builtin_ps_muls0(u, n);
                *(__ps_t *)&loc.sp38 = n;
                loc.sp8[0] = scaled_lo;
                loc.sp3C = lbl_802A822C;
                o = pv[1];
                r2 = *(volatile __ps_t *)&loc.sp38;
                p = __builtin_ps_mul(o, r2);
                pv[1] = p;
            }
            {
                register f32 mult __asm__("fr13");
                mult = loc.sp28;
                *(volatile f32 *)&loc.sp40 = mult;
            }
            vlo2 = *(volatile __ps_t *)&loc.sp8[0];
            {
                register __ps_t mpair __asm__("fr11");
                register __ps_t o __asm__("fr0");
                register __ps_t m2 __asm__("fr12");
                mpair = *(__ps_t *)&loc.sp40;
                o = pv[1];
                __asm__("ps_mr %0, %1" : "=f"(m2) : "f"(mpair));
                rh = __builtin_ps_muls0(o, m2);
                rl = __builtin_ps_muls0(vlo2, m2);
            }
            *(volatile __ps_t *)&loc.sp20 = rh;
            loc.sp8[0] = rl;
            *(volatile __ps_t *)&loc.sp18 = rl;
            pv[1] = rh;
            flo = loc.sp8[0];
            ((Unk_073F5245 *)obj)->unk0xB8 = flo;
            fhi = pv[1];
            ((Unk_073F5245 *)obj)->unk0xC0 = fhi;
        } else {
            loc.sp2C = temp_f31;
            loc.sp30 = temp_f31;
            loc.sp34 = temp_f31;
            fn_80128CE0(arg0, (void *)QB_VEL_X, &loc.sp2C, 1);
            fn_80128CE0(arg0, (void *)QB_VEL_Y, &loc.sp30, 1);
            fn_80128CE0(arg0, (void *)QB_VEL_Z, &loc.sp34, 1);
            {
                void *temp_r3;
                f32 v_2c, v_30, temp_f0;

                temp_r3 = Mem_Alloc2(0x10);
                v_2c = loc.sp2C;
                v_30 = loc.sp30;
                temp_f0 = loc.sp34;
                *((volatile f32 *)&((CStruct *)temp_r3)->unk0x0) = v_2c;
                *((volatile f32 *)&((CStruct *)temp_r3)->unk0x4) = v_30;
                *((volatile f32 *)&((CStruct *)temp_r3)->unk0x8) = temp_f0;
                bufc = lbl_802A822C;
                bufpair = *((__ps_t *)&((CStruct *)temp_r3)->unk0x0);
                *((f32 *)&((CStruct *)temp_r3)->unk0xC) = bufc;
                ((Unk_073F5245 *)obj)->unk0xB8 = bufpair;
                fhi = *((__ps_t *)&((CStruct *)temp_r3)->unk0x8);
                ((Unk_073F5245 *)obj)->unk0xC0 = fhi;
                Mem_Free(temp_r3);
            }
        }
        return true;
    }
    return false;
}
