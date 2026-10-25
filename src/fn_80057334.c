// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80057334-0x8005742C (248B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
typedef struct { char pad0[0xD0]; void *unk0xD0; } Obj_t;
typedef struct { f32 f0x0, f0x4, f0x8, f0xC, f0x10, f0x14, f0x18; } Box_t;
typedef struct { f32 a, b, c, d, e, f, g, h; } F8_t;
extern void fn_800577A0(void *);
extern s32 fn_800577B4(void *, s32 *);
extern Box_t *fn_80057E2C(void *);
extern void fn_80057D90(void *, s32);
void fn_80057334(Obj_t *arg0, __ps_t *arg1, s32 arg2) {
    F8_t sp8;
    __ps_t *p = (__ps_t *)&sp8;
    void *node;
    Box_t *bx;
    s32 var_r0;
    *(__ps_t *)&sp8.a = arg1[0];
    *(__ps_t *)&p[1] = arg1[1];
    *(__ps_t *)&sp8.e = arg1[2];
    *(__ps_t *)&sp8.g = arg1[3];
    fn_800577A0(arg0->unk0xD0);
    goto latch;
  body:
    bx = fn_80057E2C(node);
    if (sp8.a > bx->f0x10 || bx->f0x0 > sp8.e || ((f32 *)p)[2] > bx->f0x18 ||
        bx->f0x8 > sp8.g || sp8.b > bx->f0x14 || bx->f0x4 > sp8.f) {
        var_r0 = 0;
    } else {
        var_r0 = 1;
    }
    if (var_r0 != 0) {
        fn_80057D90(node, arg2);
    }
  latch:
    node = (void *)fn_800577B4(arg0->unk0xD0, 0);
    if (node != 0) goto body;
}
