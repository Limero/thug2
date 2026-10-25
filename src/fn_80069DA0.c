// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80069DA0-0x80069EB8 (280B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void fn_80069DA0(void *arg0, void *arg1) {
    void **t;
    void **u;
    void (*fp)(void *);
    void (*gp)(void *);
    u8 *c;

    if (arg1 == 0) {
        t = *(void ***)((char *)arg0 + 0x1B8);
        fp = (void (*)(void *))t[0x3C / 4];
        fp((char *)arg0 + (signed short)((s16 *)t)[0x38 / 2]);
        return;
    }
    if (*(s32 *)((char *)arg0 + 0x184) != 0) {
        c = (u8 *)arg1;
        *(f32 *)((char *)arg0 + 0x48) = (f32)(f64)(s32)c[0] / 255.0f;
        *(f32 *)((char *)arg0 + 0x4C) = (f32)(f64)(s32)c[1] / 255.0f;
        *(f32 *)((char *)arg0 + 0x50) = (f32)(f64)(s32)c[2] / 255.0f;
        *(f32 *)((char *)arg0 + 0x54) = (f32)(f64)(s32)c[3] / 255.0f;
        u = *(void ***)((char *)arg0 + 0x1B8);
        gp = (void (*)(void *))u[0x3C / 4];
        gp((char *)arg0 + (signed short)((s16 *)u)[0x38 / 2]);
    }
}
