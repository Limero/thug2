// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802572D8-0x802575C4 (748B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -O1 -mps-float
#include "types.h"

register __ps_t v0 __asm__("fr0");
register __ps_t v1 __asm__("fr1");
register __ps_t v2 __asm__("fr2");
register __ps_t v3 __asm__("fr3");
register __ps_t v4 __asm__("fr4");
register __ps_t v5 __asm__("fr5");
register __ps_t v6 __asm__("fr6");
register __ps_t v7 __asm__("fr7");
register __ps_t v8 __asm__("fr8");
register __ps_t v9 __asm__("fr9");
register __ps_t v10 __asm__("fr10");
register __ps_t v11 __asm__("fr11");
register __ps_t v12 __asm__("fr12");
register __ps_t v13 __asm__("fr13");
register __ps_t v14 __asm__("fr14");
register __ps_t v15 __asm__("fr15");
register __ps_t c16 __asm__("fr16");
register __ps_t c17 __asm__("fr17");
register __ps_t n18 __asm__("fr18");
register __ps_t K __asm__("fr19");
register __ps_t om __asm__("fr20");
register __ps_t mo __asm__("fr21");
register __ps_t s22 __asm__("fr22");
register __ps_t s23 __asm__("fr23");
register __ps_t s24 __asm__("fr24");

extern char lbl_802572C4[];

void fn_802572D8(__ps_t *p)
{
    volatile f32 fr[22];

    __asm__("" : : "m"(fr[0]));
    __asm__ volatile("stfd 14,8(1)\n\t"
                     "stfd 15,16(1)\n\t"
                     "stfd 16,24(1)\n\t"
                     "stfd 17,32(1)\n\t"
                     "stfd 18,40(1)\n\t"
                     "stfd 19,48(1)\n\t"
                     "stfd 20,56(1)\n\t"
                     "stfd 21,64(1)\n\t"
                     "stfd 22,72(1)\n\t"
                     "stfd 23,80(1)\n\t"
                     "stfd 24,88(1)" : : : "memory");
    v0 = p[0];
    v1 = p[1];
    v2 = p[2];
    v3 = p[3];
    v4 = p[4];
    v5 = p[5];
    v6 = p[6];
    v7 = p[7];
    v8 = p[8];
    v9 = p[9];
    v10 = p[10];
    v11 = p[11];
    v12 = p[12];
    v13 = p[13];
    v14 = p[14];
    v15 = p[15];

    /* literal pool @0x802572C4: K scalar, (C8,S8) pair, (1,-1) pair */
    __asm__ volatile("lis 4,%0@ha\n\t"
                     "lfsu 19,%0@l(4)\n\t"
                     "psq_l 17,4(4),0,0\n\t"
                     "psq_l 20,12(4),0,0"
                     : : "s"(lbl_802572C4) : "memory");
    mo = __builtin_ps_merge10(om, om);

    c16 = c17 * om;
    c17 = __builtin_ps_merge10(c17, c17);

    /* stage 1 */
    s22 = v15 - v7;
    v15 = v15 + v7;
    v7 = s22;

    s22 = v14 - v6;
    v14 = v14 + v6;
    s23 = s22 * c16;
    s22 = s22 * c17;
    v6 = __builtin_ps_sum0(s23, v6, s23);
    v6 = __builtin_ps_sum1(s22, v6, s22);

    n18 = K * om;
    s22 = v13 - v5;
    v13 = v13 + v5;
    s23 = s22 * n18;
    s22 = s22 * K;
    v5 = __builtin_ps_sum0(s23, v5, s23);
    v5 = __builtin_ps_sum1(s22, v5, s22);

    c16 = __builtin_ps_merge10(c16, c16);
    c17 = __builtin_ps_merge10(c17, c17);
    c16 = -c16;

    s22 = v12 - v4;
    v12 = v12 + v4;
    s23 = s22 * c16;
    s22 = s22 * c17;
    v4 = __builtin_ps_sum0(s23, v4, s23);
    v4 = __builtin_ps_sum1(s22, v4, s22);

    s22 = __builtin_ps_merge10(v3, v11);
    s23 = __builtin_ps_merge10(v11, v3);
    v11 = v11 + v3;
    v3 = s22 - s23;

    c16 = c16 * om;
    c17 = c17 * mo;

    s22 = v2 - v10;
    v10 = v10 + v2;
    s23 = s22 * c16;
    s22 = s22 * c17;
    v2 = __builtin_ps_sum0(s23, v2, s23);
    v2 = __builtin_ps_sum1(s22, v2, s22);

    n18 = K * mo;

    s22 = v1 - v9;
    v9 = v9 + v1;
    s23 = s22 * K;
    s22 = s22 * n18;
    v1 = __builtin_ps_sum0(s23, v1, s23);
    v1 = __builtin_ps_sum1(s22, v1, s22);

    c17 = __builtin_ps_merge10(c17, c17);
    c16 = __builtin_ps_merge10(c16, c16);
    c17 = -c17;

    s22 = v0 - v8;
    v8 = v8 + v0;
    s23 = s22 * c16;
    s22 = s22 * c17;
    v0 = __builtin_ps_sum0(s23, v0, s23);
    v0 = __builtin_ps_sum1(s22, v0, s22);

    /* combine pass A over T */
    s22 = v0 - v4;
    v4 = v4 + v0;
    s23 = __builtin_ps_muls1(K, s22);
    s22 = __builtin_ps_muls0(om, s22);
    v0 = __builtin_ps_madd(s22, K, s23);

    s22 = __builtin_ps_merge10(v1, v5);
    s23 = __builtin_ps_merge10(v5, v1);
    v5 = v5 + v1;
    v1 = s22 - s23;

    s22 = v6 - v2;
    v6 = v6 + v2;
    s23 = __builtin_ps_muls0(K, s22);
    s22 = __builtin_ps_muls1(mo, s22);
    v2 = __builtin_ps_madd(s22, K, s23);

    s22 = v7 - v3;
    v7 = v7 + v3;
    v3 = s22;

    c16 = v3 + v1;
    c17 = v3 - v1;
    s24 = v2 - v0;
    n18 = v2 + v0;
    s24 = __builtin_ps_merge10(s24, s24);
    v2 = c16 - n18;
    v3 = c16 + n18;
    v0 = __builtin_ps_madd(s24, om, c17);
    v1 = __builtin_ps_madd(s24, mo, c17);

    c16 = v7 + v5;
    c17 = v7 - v5;
    s24 = v6 - v4;
    n18 = v6 + v4;
    s24 = __builtin_ps_merge10(s24, s24);
    v6 = c16 - n18;
    v7 = c16 + n18;
    v4 = __builtin_ps_madd(s24, om, c17);
    v5 = __builtin_ps_madd(s24, mo, c17);

    /* combine pass B over U */
    s22 = v8 - v12;
    v12 = v12 + v8;
    s23 = __builtin_ps_muls1(K, s22);
    s22 = __builtin_ps_muls0(om, s22);
    v8 = __builtin_ps_madd(s22, K, s23);

    s22 = __builtin_ps_merge10(v9, v13);
    s23 = __builtin_ps_merge10(v13, v9);
    v13 = v13 + v9;
    v9 = s22 - s23;

    s22 = v14 - v10;
    v14 = v14 + v10;
    s23 = __builtin_ps_muls0(K, s22);
    s22 = __builtin_ps_muls1(mo, s22);
    v10 = __builtin_ps_madd(s22, K, s23);

    s22 = v15 - v11;
    v15 = v15 + v11;
    v11 = s22;

    c16 = v11 + v9;
    c17 = v11 - v9;
    s24 = v10 - v8;
    n18 = v10 + v8;
    s24 = __builtin_ps_merge10(s24, s24);
    v10 = c16 - n18;
    v11 = c16 + n18;
    v8 = __builtin_ps_madd(s24, om, c17);
    v9 = __builtin_ps_madd(s24, mo, c17);

    c16 = v15 + v13;
    c17 = v15 - v13;
    s24 = v14 - v12;
    n18 = v14 + v12;
    s24 = __builtin_ps_merge10(s24, s24);
    v14 = c16 - n18;
    v15 = c16 + n18;
    v12 = __builtin_ps_madd(s24, om, c17);
    v13 = __builtin_ps_madd(s24, mo, c17);

    p[0] = v0;
    p[1] = v1;
    p[2] = v2;
    p[3] = v3;
    p[4] = v4;
    p[5] = v5;
    p[6] = v6;
    p[7] = v7;
    p[8] = v8;
    p[9] = v9;
    p[10] = v10;
    p[11] = v11;
    p[12] = v12;
    p[13] = v13;
    p[14] = v14;
    p[15] = v15;

    __asm__ volatile("lfd 14,8(1)\n\t"
                     "lfd 15,16(1)\n\t"
                     "lfd 16,24(1)\n\t"
                     "lfd 17,32(1)\n\t"
                     "lfd 18,40(1)\n\t"
                     "lfd 19,48(1)\n\t"
                     "lfd 20,56(1)\n\t"
                     "lfd 21,64(1)\n\t"
                     "lfd 22,72(1)\n\t"
                     "lfd 23,80(1)\n\t"
                     "lfd 24,88(1)" : : : "memory");
}
