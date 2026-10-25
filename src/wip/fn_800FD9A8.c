// WIP draft - PARKED. See notes below.
// extra_cflags: -mps-float
// family=m2c range=0x800FD9A8-0x800FDC50 size=680B
// UPDATED 2026-09-25: semantic reconstruction is complete; there is no opcode
// wall. 0x11A00090 is ps_mr (XO10=72), while 0x...582A/602A are ps_add and
// 0x...1028/1828 are ps_sub. The body emits every required PS operation.
// PS-aware tools/ps_diff.py: 3/170 words (1.8%), 612B vs 680B WANT. The 0x48
// frame matches exactly. arg1 is eight f32 values and arg2 is twelve f32 values.
// Dataflow: compute the first 3-component transform, add arg1 pair 0/1 to pair
// 2/3 with PS, run a 2-component transform, subtract the saved first result with
// PS, then repeat from the complementary pair sum and write arg2+0x20.
// Remaining blocker is FPR/scheduler shape, not semantics or PS emission:
// WANT starts with lfs arg1[1], materializes r9=&sp8, then evaluates matrix row
// 1 before row 0; this C starts with row 0/v0 and reassociates all three scalar
// transforms. WANT also keeps the sp8 base and reloads it through r9 three times;
// this C folds those to r1 displacements. Scoped PS register pins recover the
// four psq_l input roles and both ps_add words, but moving the first psq_st past
// the second ps_add cascades into the scalar stages. No whole-body asm is used.
#include "types.h"

typedef struct {
    char pad[0x60];
    f32 m[4][4];
} G5Mtx;

void fn_800FD9A8(G5Mtx *arg0, f32 *arg1, f32 *arg2) {
    volatile f32 s[16];
    __ps_t p;
    __ps_t q;
    __ps_t r;
    __ps_t t;
    f32 v0;
    f32 v1;

    s[4] = arg1[1] * arg0->m[1][0] + arg1[0] * arg0->m[0][0] + arg1[2] * arg0->m[2][0] + arg0->m[3][0];
    s[5] = arg1[1] * arg0->m[1][1] + arg1[0] * arg0->m[0][1] + arg1[2] * arg0->m[2][1] + arg0->m[3][1];
    s[6] = arg1[1] * arg0->m[1][2] + arg1[0] * arg0->m[0][2] + arg1[2] * arg0->m[2][2] + arg0->m[3][2];
    s[7] = arg1[1] * arg0->m[1][3] + arg1[0] * arg0->m[0][3] + arg1[2] * arg0->m[2][3] + arg0->m[3][3];

    p = *(volatile __ps_t *)&s[4];
    *(volatile __ps_t *)&s[0] = p;
    *(volatile __ps_t *)&arg2[0] = p;
    p = *(volatile __ps_t *)&s[6];
    *(volatile __ps_t *)&s[2] = p;
    *(volatile __ps_t *)&arg2[2] = *(volatile __ps_t *)&s[0];

    {
        register __ps_t p0 __asm__("fr12") = *(volatile __ps_t *)&arg1[4];
        register __ps_t p1 __asm__("fr0") = *(volatile __ps_t *)&arg1[0];
        register __ps_t p2 __asm__("fr11") = *(volatile __ps_t *)&arg1[6];
        register __ps_t p3 __asm__("fr13") = *(volatile __ps_t *)&arg1[2];
        p = __builtin_ps_add(p1, p0);
        t = __builtin_ps_add(p3, p2);
        *(volatile __ps_t *)&s[8] = p;
        *(volatile __ps_t *)&s[9] = t;
    }

    v0 = s[8];
    v1 = s[9];
    s[12] = v1 * arg0->m[1][0] + v0 * arg0->m[0][0] + arg0->m[3][0];
    s[13] = v1 * arg0->m[1][1] + v0 * arg0->m[0][1] + arg0->m[3][1];
    s[14] = v1 * arg0->m[1][2] + v0 * arg0->m[0][2] + arg0->m[3][2];
    s[15] = v1 * arg0->m[1][3] + v0 * arg0->m[0][3] + arg0->m[3][3];

    p = *(volatile __ps_t *)&s[12];
    *(volatile __ps_t *)&s[4] = p;
    q = p;
    p = *(volatile __ps_t *)&s[14];
    *(volatile __ps_t *)&s[6] = p;
    r = *(volatile __ps_t *)&arg2[0];
    q = __builtin_ps_sub(q, r);
    *(volatile __ps_t *)&s[0] = q;
    *(volatile __ps_t *)&arg2[4] = q;
    r = *(volatile __ps_t *)&arg2[2];
    p = __builtin_ps_sub(p, r);
    *(volatile __ps_t *)&s[2] = p;
    *(volatile __ps_t *)&arg2[6] = *(volatile __ps_t *)&s[0];

    {
        register __ps_t p0 __asm__("fr12") = *(volatile __ps_t *)&arg1[8];
        register __ps_t p1 __asm__("fr0") = *(volatile __ps_t *)&arg1[0];
        register __ps_t p2 __asm__("fr11") = *(volatile __ps_t *)&arg1[10];
        register __ps_t p3 __asm__("fr13") = *(volatile __ps_t *)&arg1[2];
        p = __builtin_ps_add(p1, p0);
        t = __builtin_ps_add(p3, p2);
        *(volatile __ps_t *)&s[8] = p;
        *(volatile __ps_t *)&s[9] = t;
    }

    v0 = s[8];
    v1 = s[9];
    s[12] = v1 * arg0->m[1][0] + v0 * arg0->m[0][0] + arg0->m[3][0];
    s[13] = v1 * arg0->m[1][1] + v0 * arg0->m[0][1] + arg0->m[3][1];
    s[14] = v1 * arg0->m[1][2] + v0 * arg0->m[0][2] + arg0->m[3][2];
    s[15] = v1 * arg0->m[1][3] + v0 * arg0->m[0][3] + arg0->m[3][3];

    p = *(volatile __ps_t *)&s[12];
    *(volatile __ps_t *)&s[4] = p;
    q = p;
    p = *(volatile __ps_t *)&s[14];
    *(volatile __ps_t *)&s[6] = p;
    r = *(volatile __ps_t *)&arg2[0];
    q = __builtin_ps_sub(q, r);
    *(volatile __ps_t *)&s[0] = q;
    *(volatile __ps_t *)&arg2[8] = q;
    r = *(volatile __ps_t *)&arg2[2];
    p = __builtin_ps_sub(p, r);
    *(volatile __ps_t *)&s[2] = p;
    *(volatile __ps_t *)&arg2[10] = *(volatile __ps_t *)&s[0];
}
