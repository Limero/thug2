// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800EF294-0x800EF3A8 (276B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
typedef struct {
    s32 pad0[3];
    s32 f_0C;
    s32 pad1[3];
    s32 f_1C;
} S_t;

extern f32 lbl_8029B0D4;
extern f32 lbl_8029B0D8;
extern void fn_801AC980(s32 obj, __ps_t *src);

s32 fn_800EF294(s32 arg0, S_t *arg1) {
    __ps_t v[8];
    __ps_t *p;
    __ps_t *q;
    __ps_t *d = (__ps_t *)arg0;
    __ps_t *pw;
    __ps_t *pz;
    s32 var_ctr;
    s32 var_ctr_2;

    p = (__ps_t *)((char *)arg1->f_0C + 0x78);
    pw = v;
    pz = pw;
    var_ctr = 4;
    do {
        var_ctr -= 1;
    } while (var_ctr != 0);
    pw[0] = p[0];
    pw[1] = p[1];
    pw[2] = p[2];
    pw[3] = p[3];
    pw[4] = p[4];
    pw[5] = p[5];
    pw[6] = p[6];
    pw[7] = p[7];
    ((f32 *)v)[3] = lbl_8029B0D4;
    ((f32 *)v)[7] = lbl_8029B0D4;
    ((f32 *)v)[11] = lbl_8029B0D4;
    q = (__ps_t *)arg1->f_0C;
    v[6] = q[11];
    v[7] = q[12];
    ((f32 *)v)[15] = lbl_8029B0D8;
    pz = v;
    fn_801AC980(arg1->f_1C, pz);
    var_ctr_2 = 4;
    do {
        var_ctr_2 -= 1;
    } while (var_ctr_2 != 0);
    d[7] = pz[7];
    d[0] = pz[0];
    d[1] = pz[1];
    d[2] = pz[2];
    d[3] = pz[3];
    d[4] = pz[4];
    d[5] = pz[5];
    d[6] = pz[6];
    return arg0;
}
