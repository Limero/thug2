// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80068EE8-0x80068F70 (136B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
typedef union { __ps_t p[2]; f32 f[4]; } VBuf;
VBuf *fn_80068EE8(VBuf *arg0, VBuf *arg1, VBuf *arg2) {
    VBuf t;
    __ps_t *tp = (__ps_t *)&t;
    tp[0] = arg1->p[0];
    tp[1] = arg1->p[1];
    if (arg2->f[0] > arg1->f[0]) t.f[0] = arg2->f[0];
    if (arg2->f[1] > arg1->f[1]) t.f[1] = arg2->f[1];
    if (arg2->f[2] > arg1->f[2]) ((f32 *)tp)[2] = arg2->f[2];
    if (arg2->f[3] > arg1->f[3]) t.f[3] = arg2->f[3];
    arg0->p[1] = tp[1];
    arg0->p[0] = tp[0];
    return arg0;
}
