// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A8D04-0x800A8D9C (152B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
typedef struct {
    __ps_t v00;
    __ps_t v08;
    __ps_t v10;
    char pad18[0x58];
    __ps_t v70;
    __ps_t v78;
    __ps_t v80;
    __ps_t v88;
    char pad90[0x1C];
    f32 fac;
    f32 fb0;
} S;

void fn_800A8D04(S *arg0) {
    volatile __ps_t *p = (volatile __ps_t *)arg0;
    volatile __ps_t *u;
    __ps_t b;
    __ps_t t[4];
    union { f32 f; __ps_t p; } q;
    u = t;
    p[1] = arg0->v70;
    p++;
    p[1] = arg0->v78;
    q.f = arg0->fb0 / arg0->fac;
    t[0] = __builtin_ps_sub(arg0->v80, arg0->v70);
    t[3] = __builtin_ps_sub(arg0->v88, arg0->v78);
    t[2] = __builtin_ps_sub(arg0->v80, arg0->v70);
    u[1] = __builtin_ps_sub(arg0->v88, arg0->v78);
    t[0] = __builtin_ps_muls0(t[0], q.p);
    b = u[1];
    b = __builtin_ps_muls0(b, q.p);
    u[1] = b;
    arg0->v08 = __builtin_ps_add(arg0->v08, t[0]);
    p[1] = __builtin_ps_add(p[1], b);
}
