// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800D5AEC-0x800D5BA0 (180B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 lbl_80299B64;
extern s32 GetFloat(CStruct *, s32, f32 *, s32);
extern s32 fn_800D81F0(Unk_87C37330 *, CStruct *, s32, void *, s32);
typedef union {
    __ps_t p;
    f32 f[2];
} PU;
s32 fn_800D5AEC(Unk_87C37330 *arg0, CStruct *arg1, s32 arg2) {
    f32 out[8];
    f32 dist;
    PU u;
    __ps_t ch;
    __ps_t m;
    __ps_t a;
    __ps_t b;
    __ps_t c;
    __ps_t e;
    void *p;

    dist = lbl_80299B64;
    GetFloat(arg1, QB_DIST, &dist, 0);
    u.f[0] = dist;
    p = *(void **)((char *)arg0 + 0xC);
    ch = u.p;
    m = ch;
    a = *(__ps_t *)((char *)p + 0x98);
    b = *(__ps_t *)((char *)p + 0xA0);
    a = __builtin_ps_muls0(a, m);
    b = __builtin_ps_muls0(b, m);
    *(__ps_t *)&out[4] = a;
    *(__ps_t *)&out[6] = b;
    e = *(__ps_t *)((char *)p + 0x58);
    c = *(__ps_t *)((char *)p + 0x60);
    c = __builtin_ps_add(c, b);
    e = __builtin_ps_add(e, a);
    *(__ps_t *)&out[2] = c;
    *(__ps_t *)&out[0] = e;
    fn_800D81F0(arg0, arg1, arg2, out, 0);
    return 1;
}
