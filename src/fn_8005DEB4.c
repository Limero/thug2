// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005DEB4-0x8005DFBC (264B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "dolphin/SN_PS.h"

typedef struct {
    __ps_t p[2];
} DEB4Obj;

typedef struct {
    __ps_t p[2];
} DEB4Ent;

extern __ps_t lbl_8029398C;
extern f32 lbl_80293AD4;
extern f32 lbl_80293AD8;

s32 fn_8005DFBC(void);
s32 fn_8005DE90(s32);
DEB4Ent *fn_80024660(s32);

s32 fn_8005DEB4(DEB4Obj *arg0, f32 *arg1) {
    f32 best;
    f32 thresh;
    s32 count;
    s32 bestid;
    s32 i;
    s32 id;
    DEB4Ent *p;
    __ps_t *k;
    __ps_t v11;
    __ps_t v13;
    __ps_t v0;
    __ps_t v10;
    __ps_t v12;
    SN_PS_type res;
    f32 x;

    count = fn_8005DFBC();
    bestid = 0;
    best = lbl_80293AD4;
    i = 0;
    if (bestid < count) {
        thresh = lbl_80293AD8;
        k = &lbl_8029398C;
        do {
            id = fn_8005DE90(i);
            if (id != 0) {
                p = fn_80024660(id);
                v11 = arg0->p[0];
                v13 = p->p[0];
                v0 = p->p[1];
                v10 = arg0->p[1];
                v13 = __builtin_ps_sub(v13, v11);
                v12 = k[0];
                v13 = __builtin_ps_mul(v13, v13);
                v0 = __builtin_ps_sub(v0, v10);
                v0 = __builtin_ps_merge00(v0, v12);
                v0 = __builtin_ps_madds0(v0, v0, v13);
                v0 = __builtin_ps_sum0(v0, v0, v0);
                res.ps = v0;
                x = res.flt.hi;
                if (best < thresh || x < best) {
                    best = x;
                    bestid = id;
                }
            }
            i += 1;
        } while (i < count);
    }
    if (bestid == 0) {
        return 0;
    }
    if (arg1 != NULL) {
        *arg1 = sqrtf(best);
    }
    return bestid;
}
