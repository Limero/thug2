// WIP DRAFT — hand-reconstructed from disasm (m2c draft was statics-DCE garbage
// and misdecoded all primary-opcode-4 words as VMX; M5.0q probe proved they are
// emittable Gekko PS ops: xo5=20=__builtin_ps_sub, XO10=72=ps_mr, xo5=25=mul,
// 16=merge00, 29=madd, 10=sum0, 26=rsqrte, 24=res).
// family=m2c range=0x801B1D00-0x801B234C size=1612B
// extra_cflags: -mps-float
//
// PARKED ~43% (ps_diff masked, -mps-float): semantics fully reconstructed
// (rot-matrix x 4-point transform via fn_80003EB0/fn_801B175C/fn_801745B4 +
// two PS distance tests), all opcode-4 words emitted via __builtin_ps_*,
// doc-30 spin-window reproduced via split volatile asm fragments ending in
// `bdnz $`. Remaining walls, in order of severity:
//  1. Frame +8 (locals 196 vs 188): every function-scope __ps_t local gets a
//     dead reserved stack slot under -mps-float here (6 slots seen, accesses
//     fully optimized out); nesting builtins into expressions did not remove
//     them. Want fits exactly 5 slots of slack around its identical buffer
//     struct; no shape tried dropped the 6th.
//  2. Param-home fmr placement: want sinks `fmr f25,f2 / fmr f24,f3` INTO
//     the spin window (positions 0x70/0x78); ngccc always emits float-param
//     homes at prologue top (+2 insn shift through the whole window). Pins
//     rebind/double-copy; asm-output forms collapse allocation.
//  3. Want's page-anchor `lis r9` sits pre-window (slot 2); hardcoded inside
//     the asm tail instead (reloc-safe literal, but shifts one slot).
//  4. Residual FPR web rotation in products/copyback (f11<->f12 etc.) once
//     streams desync at the window.
// Retry hints: solve (1) via a source shape whose PS locals die before any
// call (block-scoped re-declaration per block was tried; reservations
// persisted); solve (2)/(3) only if cc1 gains a way to defer param homing.
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// SEARCHED 2026-09-11 (tools/store_order_search.py): store/assignment block(s) re-ordered (reversed / ascending / descending); score now 42.4% ([3]rev->42.4%).
#include "types.h"
#include "structs.h"

extern f32 lbl_802ABEE0;
extern f32 lbl_802ABEE4;
extern f32 lbl_802ABEE8;
extern f32 lbl_802ABEEC;
extern f32 lbl_802ABEF0;
extern f32 lbl_802ABEDC;
extern char lbl_802ABE50[];
extern s32 lbl_80305EAC;

void *fn_80003EB0(Unk_DB0E2BAB *, f32);
s32 fn_801B175C(s32, void *);
s32 fn_801745B4(s32);

s32 fn_801B1D00(s32 arg0, s32 arg1, void *arg2, f32 farg0, f32 farg1, f32 farg2) {
    struct {
        f32 u[16]; /* sp08: fn_80003EB0 out matrix, reused as point/vector temps */
        f32 t[16]; /* sp48: product temp */
        void *mp; /* sp88 */
        void *ax; /* sp8C */
        f32 d0; /* sp90 */
        char p94[4];
        f32 d1; /* sp98 */
    } fr;
    __ps_t *dp;
    f32 *m;
    register s32 a0 __asm__("r24");
    register s32 a1 __asm__("r30");
    register s32 a2 __asm__("r31");
    register char *wr29 __asm__("r29");
    register char *wr28 __asm__("r28");
    register char *wr27 __asm__("r27");
    register char *wr26 __asm__("r26");
    register char *wr25 __asm__("r25");
    register char *wr23 __asm__("r23");
    register f32 scaled __asm__("fr1");
    f32 temp_f26;
    f32 temp_f27;
    f32 temp_f28;
    f32 temp_f29;
    f32 temp_f30;
    f32 temp_f31;
    f32 var_A;
    f32 var_C;
    f32 var_B;
    f32 var_D;
    __ps_t accA;
    __ps_t prod;
    __ps_t diffX;
    __ps_t P2;
    __ps_t P3;
    __ps_t P4;

    a0 = arg0;
    a1 = arg1;
    a2 = (s32)arg2;
    dp = (__ps_t *)a2;
    __asm__ volatile(
        "psq_l 0, 0(30), 0, 0\n\t"
        "li 0, 4\n\t"
        "psq_st 0, 0(31), 0, 0\n\t"
        : : : "memory");
    __asm__ volatile(
        "mtctr 0\n\t"
        "addi %0, 1, 0x88\n\t"
        "addi %1, 1, 0x18\n\t"
        "psq_l 13, 8(30), 0, 0\n\t"
        "addi %2, 1, 0x28\n\t"
        "addi %3, 1, 0x1c\n\t"
        "addi %4, 1, 0x20\n\t"
        "psq_st 13, 8(31), 0, 0\n\t"
        "addi %5, 1, 0x24\n\t"
        : "=r"(wr29), "=r"(wr28), "=r"(wr23), "=r"(wr27), "=r"(wr26),
          "=r"(wr25)
        :
        : "fr0", "fr13", "ctr", "memory");
    __asm__ volatile(
        "psq_l 0, 16(30), 0, 0\n\t"
        "psq_st 0, 16(31), 0, 0\n\t"
        "psq_l 13, 24(30), 0, 0\n\t"
        "psq_st 13, 24(31), 0, 0\n\t"
        "psq_l 0, 32(30), 0, 0\n\t"
        "psq_st 0, 32(31), 0, 0\n\t"
        "psq_l 13, 40(30), 0, 0\n\t"
        "psq_st 13, 40(31), 0, 0\n\t"
        "psq_l 0, 48(30), 0, 0\n\t"
        "psq_st 0, 48(31), 0, 0\n\t"
        "psq_l 13, 56(30), 0, 0\n\t"
        "psq_st 13, 56(31), 0, 0\n\t"
        "lis 9, -0x7fd5\n\t"
        "lfs 0, -0x4124(9)\n\t"
        "fmuls %0, %0, 0\n\t"
        "bdnz $"
        : "=f"(scaled)
        :
        : "fr0", "fr13", "r9", "ctr", "memory");

    fr.mp = fn_80003EB0(&fr.u[0], scaled);
    ((Unk_3DC8081F_3 *)wr29)->unk0x4 = a2;
    m = (f32 *)fr.mp;
    temp_f26 = *((f32 *)&((Unk_DB0E2BAB *)a2)->unk0x10);
    temp_f27 = *((f32 *)&((Unk_DB0E2BAB *)a2)->unk0x0);
    temp_f31 = *((f32 *)&((Unk_DB0E2BAB *)a2)->unk0x20);
    temp_f30 = *((f32 *)&((Unk_DB0E2BAB *)a2)->unk0x14);
    temp_f29 = *((f32 *)&((Unk_DB0E2BAB *)a2)->unk0x4);
    temp_f28 = *((f32 *)&((Unk_DB0E2BAB *)a2)->unk0x24);

    fr.t[0] = m[0] * temp_f27 + m[1] * temp_f26 + m[2] * temp_f31 +
              m[3] * (*((f32 *)&((Unk_DB0E2BAB *)a2)->unk0x30));
    fr.t[1] = m[0] * temp_f29 + m[1] * temp_f30 + m[2] * temp_f28 +
              m[3] * (*((f32 *)&((Unk_DB0E2BAB *)a2)->unk0x34));
    fr.t[2] = m[0] * (*((f32 *)&((Unk_DB0E2BAB *)a2)->unk0x8)) +
              m[1] * (*((f32 *)&((Unk_DB0E2BAB *)a2)->unk0x18)) +
              m[2] * (*((f32 *)&((Unk_DB0E2BAB *)a2)->unk0x28)) +
              m[3] * (*((f32 *)&((Unk_DB0E2BAB *)a2)->unk0x38));
    fr.t[3] = m[0] * (*((f32 *)&((Unk_DB0E2BAB *)a2)->unk0xC)) +
              m[1] * (*((f32 *)&((Unk_DB0E2BAB *)a2)->unk0x1C)) +
              m[2] * (*((f32 *)&((Unk_DB0E2BAB *)a2)->unk0x2C)) +
              m[3] * (*((f32 *)&((Unk_DB0E2BAB *)a2)->unk0x3C));
    fr.t[4] = m[4] * temp_f27 + m[5] * temp_f26 + m[6] * temp_f31 +
              m[7] * (*((f32 *)&((Unk_DB0E2BAB *)a2)->unk0x30));
    fr.t[5] = m[4] * temp_f29 + m[5] * temp_f30 + m[6] * temp_f28 +
              m[7] * (*((f32 *)&((Unk_DB0E2BAB *)a2)->unk0x34));
    fr.t[6] = m[4] * (*((f32 *)&((Unk_DB0E2BAB *)a2)->unk0x8)) +
              m[5] * (*((f32 *)&((Unk_DB0E2BAB *)a2)->unk0x18)) +
              m[6] * (*((f32 *)&((Unk_DB0E2BAB *)a2)->unk0x28)) +
              m[7] * (*((f32 *)&((Unk_DB0E2BAB *)a2)->unk0x38));
    fr.t[7] = m[4] * (*((f32 *)&((Unk_DB0E2BAB *)a2)->unk0xC)) +
              m[5] * (*((f32 *)&((Unk_DB0E2BAB *)a2)->unk0x1C)) +
              m[6] * (*((f32 *)&((Unk_DB0E2BAB *)a2)->unk0x2C)) +
              m[7] * (*((f32 *)&((Unk_DB0E2BAB *)a2)->unk0x3C));
    fr.t[8] = m[8] * temp_f27 + m[9] * temp_f26 + m[10] * temp_f31 +
              m[11] * (*((f32 *)&((Unk_DB0E2BAB *)a2)->unk0x30));
    fr.t[9] = m[8] * temp_f29 + m[9] * temp_f30 + m[10] * temp_f28 +
              m[11] * (*((f32 *)&((Unk_DB0E2BAB *)a2)->unk0x34));
    fr.t[10] = m[8] * (*((f32 *)&((Unk_DB0E2BAB *)a2)->unk0x8)) +
               m[9] * (*((f32 *)&((Unk_DB0E2BAB *)a2)->unk0x18)) +
               m[10] * (*((f32 *)&((Unk_DB0E2BAB *)a2)->unk0x28)) +
               m[11] * (*((f32 *)&((Unk_DB0E2BAB *)a2)->unk0x38));
    fr.t[11] = m[8] * (*((f32 *)&((Unk_DB0E2BAB *)a2)->unk0xC)) +
               m[9] * (*((f32 *)&((Unk_DB0E2BAB *)a2)->unk0x1C)) +
               m[10] * (*((f32 *)&((Unk_DB0E2BAB *)a2)->unk0x2C)) +
               m[11] * (*((f32 *)&((Unk_DB0E2BAB *)a2)->unk0x3C));
    fr.t[12] = m[12] * temp_f27 + m[13] * temp_f26 + m[14] * temp_f31 +
               m[15] * (*((f32 *)&((Unk_DB0E2BAB *)a2)->unk0x30));
    fr.t[13] = m[12] * temp_f29 + m[13] * temp_f30 + m[14] * temp_f28 +
               m[15] * (*((f32 *)&((Unk_DB0E2BAB *)a2)->unk0x34));
    fr.t[14] = m[12] * (*((f32 *)&((Unk_DB0E2BAB *)a2)->unk0x8)) +
               m[13] * (*((f32 *)&((Unk_DB0E2BAB *)a2)->unk0x18)) +
               m[14] * (*((f32 *)&((Unk_DB0E2BAB *)a2)->unk0x28)) +
               m[15] * (*((f32 *)&((Unk_DB0E2BAB *)a2)->unk0x38));
    fr.t[15] = m[12] * (*((f32 *)&((Unk_DB0E2BAB *)a2)->unk0xC)) +
               m[13] * (*((f32 *)&((Unk_DB0E2BAB *)a2)->unk0x1C)) +
               m[14] * (*((f32 *)&((Unk_DB0E2BAB *)a2)->unk0x2C)) +
               m[15] * (*((f32 *)&((Unk_DB0E2BAB *)a2)->unk0x3C));

    dp[0] = *(__ps_t *)&fr.t[0];
    var_A = lbl_802ABEE4;
    dp[1] = *(__ps_t *)&fr.t[2];
    var_B = farg1 + lbl_802ABEE0;
    dp[2] = *(__ps_t *)&fr.t[4];
    var_C = lbl_802ABEE8;
    dp[3] = *(__ps_t *)&fr.t[6];
    var_D = lbl_802ABEEC;
    fr.u[4] = var_A;
    ((Unk_E266FB50_3 *)wr28)->unk0x4 = var_C;
    dp[7] = *(__ps_t *)&fr.t[14];
    dp[6] = *(__ps_t *)&fr.t[12];
    dp[5] = *(__ps_t *)&fr.t[10];
    dp[4] = *(__ps_t *)&fr.t[8];
    fr.u[7] = var_D;
    fr.u[6] = var_B;

    /* second transform: coefficients (A,C,B,D) over arg2 columns */
    fr.u[8] = *(f32 *)wr25 * (*((f32 *)&((Unk_DB0E2BAB *)a2)->unk0x30)) +
              (var_B * (*((f32 *)&((Unk_DB0E2BAB *)a2)->unk0x20)) +
               (var_A * (*((f32 *)&((Unk_DB0E2BAB *)a2)->unk0x0)) +
                var_C * (*((f32 *)&((Unk_DB0E2BAB *)a2)->unk0x10))));
    fr.u[9] = (*((f32 *)&((Unk_DB0E2BAB *)a2)->unk0x34)) +
              (var_B * (*((f32 *)&((Unk_DB0E2BAB *)a2)->unk0x24)) +
               (var_A * (*((f32 *)&((Unk_DB0E2BAB *)a2)->unk0x4)) +
                var_C * (*((f32 *)&((Unk_DB0E2BAB *)a2)->unk0x14))));
    fr.u[10] = (*((f32 *)&((Unk_DB0E2BAB *)a2)->unk0x38)) +
               (var_B * (*((f32 *)&((Unk_DB0E2BAB *)a2)->unk0x28)) +
                (var_A * (*((f32 *)&((Unk_DB0E2BAB *)a2)->unk0x8)) +
                 var_C * (*((f32 *)&((Unk_DB0E2BAB *)a2)->unk0x18))));
    fr.u[11] = (*((f32 *)&((Unk_DB0E2BAB *)a2)->unk0x3C)) +
               (var_B * (*((f32 *)&((Unk_DB0E2BAB *)a2)->unk0x2C)) +
                (var_A * (*((f32 *)&((Unk_DB0E2BAB *)a2)->unk0xC)) +
                 var_C * (*((f32 *)&((Unk_DB0E2BAB *)a2)->unk0x1C))));
    *(__ps_t *)&fr.u[0] = *(__ps_t *)&fr.u[8];
    *(__ps_t *)&fr.u[2] = *(__ps_t *)&fr.u[10];
    if (fn_801B175C((s32)a1 + 0x30, &fr.u[0]) != 0) {
        return 0;
    }
    fr.u[8] = var_A;
    ((Unk_E266FB50_3 *)wr23)->unk0x4 = var_A;
    {
        s32 chase;
        s32 mp2;
        chase = lbl_80305EAC;
        /* third transform: scale by var_A around origin, offset farg1 */
        fr.u[13] = farg1 * (*((f32 *)&((Unk_DB0E2BAB *)a2)->unk0x24)) +
                   (var_A * (*((f32 *)&((Unk_DB0E2BAB *)a2)->unk0x4)) +
                    var_A * (*((f32 *)&((Unk_DB0E2BAB *)a2)->unk0x14))) +
                   (*((f32 *)&((Unk_DB0E2BAB *)a2)->unk0x34));
        fr.u[12] = farg1 * (*((f32 *)&((Unk_DB0E2BAB *)a2)->unk0x20)) +
                   (var_A * (*((f32 *)&((Unk_DB0E2BAB *)a2)->unk0x0)) +
                    var_A * (*((f32 *)&((Unk_DB0E2BAB *)a2)->unk0x10))) +
                   (*((f32 *)&((Unk_DB0E2BAB *)a2)->unk0x30));
        fr.u[15] = farg1 * (*((f32 *)&((Unk_DB0E2BAB *)a2)->unk0x2C)) +
                   (var_A * (*((f32 *)&((Unk_DB0E2BAB *)a2)->unk0xC)) +
                    var_A * (*((f32 *)&((Unk_DB0E2BAB *)a2)->unk0x1C))) +
                   (*((f32 *)&((Unk_DB0E2BAB *)a2)->unk0x3C));
        fr.u[14] = farg1 * (*((f32 *)&((Unk_DB0E2BAB *)a2)->unk0x28)) +
                   (var_A * (*((f32 *)&((Unk_DB0E2BAB *)a2)->unk0x8)) +
                    var_A * (*((f32 *)&((Unk_DB0E2BAB *)a2)->unk0x18))) +
                   (*((f32 *)&((Unk_DB0E2BAB *)a2)->unk0x38));
        *(__ps_t *)&fr.u[4] = *(__ps_t *)&fr.u[12];
        *((f32 *)&((Unk_DB0E2BAB *)a2)->unk0x30) =
            __builtin_ps_merge00(*(__ps_t *)&fr.u[4], *(__ps_t *)&fr.u[4]);
        fr.u[11] = var_D;
        *(__ps_t *)&fr.u[6] = *(__ps_t *)&fr.u[14];
        *((f32 *)&((Unk_DB0E2BAB *)a2)->unk0x38) =
            __builtin_ps_merge00(*(__ps_t *)&fr.u[6], *(__ps_t *)&fr.u[6]);
        fr.u[10] = farg1;
        mp2 = fn_801745B4(chase);

        P2 = *(__ps_t *)&fr.u[6];
        accA = ((Unk_DF2324A8 *)mp2)->unk0x60;
        P3 = ((Unk_DF2324A8 *)mp2)->unk0x58;
        P4 = *(__ps_t *)&fr.u[4];
        accA = __builtin_ps_sub(P2, accA);
        diffX = __builtin_ps_sub(P4, P3);
        __asm__ volatile("stfs %1, %0" : "=m"(fr.u[8]) : "f"(diffX));
        accA = __builtin_ps_madd(diffX,
            __builtin_ps_merge00(__builtin_ps_mul(accA, P3),
                *(__ps_t *)&lbl_802ABE50), diffX);
        accA = __builtin_ps_sum0(accA, accA, accA);
        accA = __builtin_ps_rsqrte(accA);
        accA = __builtin_ps_res(accA);
        __asm__ volatile("stfs %1, %0" : "=m"(fr.d0) : "f"(accA));
        if (fr.d0 < lbl_802ABEF0) {
            return 0;
        }
        accA = ((Unk_073F5245 *)a0)->unk0xC0;
        diffX = __builtin_ps_sub(P4, accA);
        __asm__ volatile("stfs %1, %0" : "=m"(fr.u[12]) : "f"(diffX));
        accA = __builtin_ps_sub(P2, ((Unk_073F5245 *)a0)->unk0xC8);
        fr.u[13] = var_A;
        __asm__ volatile("stfs %1, %0" : "=m"(fr.u[14]) : "f"(accA));
        prod = *(__ps_t *)&fr.u[12];
        prod = __builtin_ps_madd(prod,
            __builtin_ps_merge00(__builtin_ps_mul(accA, diffX),
                *(__ps_t *)&lbl_802ABE50), prod);
        prod = __builtin_ps_sum0(prod, prod, prod);
        prod = __builtin_ps_rsqrte(prod);
        prod = __builtin_ps_res(prod);
        __asm__ volatile("stfs %1, %0" : "=m"(fr.d1) : "f"(prod));
        if (fr.d1 >= farg2) {
            return 0;
        }
        return 1;
    }
}
