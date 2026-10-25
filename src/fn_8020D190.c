// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8020D190-0x8020D1D4 (68B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"
extern f32 lbl_802AF4B8;
extern f32 lbl_802AF4BC;

typedef union {
    f32 f[4];
    __ps_t p[2];
} V4U;

void fn_8020D190(Unk_CA1C78B1 *arg0) {
    V4U v;
    V4U *vp;
    __ps_t *dst;
    f32 a;

    a = lbl_802AF4B8;
    vp = &v;
    v.f[0] = a;
    vp->f[1] = a;
    vp->f[2] = a;
    vp->f[3] = lbl_802AF4BC;
    dst = (__ps_t *)arg0->unk0x1844;
    dst[64] = vp->p[0];
    dst[65] = vp->p[1];
}
