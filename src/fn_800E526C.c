// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800E526C-0x800E5314 (168B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"
typedef struct { char pad[4]; f32 u4; f32 u8; f32 uC; } FRec526C;
FRec526C *fn_801294E0(void *, s32);
extern f32 lbl_8029A9EC;
void fn_800E526C(Unk_C7387A53 *arg0, void *arg1) {
    __ps_t sp[2];
    volatile f32 *f;
    __ps_t *dst;
    f32 temp_f31;
    register f32 fa __asm__("fr0"); f32 fb, fc;
    s32 temp_r28;
    s32 var_r29;
    FRec526C *r;

    temp_r28 = *(s32 *)((char *)arg1 + 4);
    var_r29 = 0;
    arg0->unk0x70 = temp_r28;
    if (var_r29 < temp_r28) {
        temp_f31 = lbl_8029A9EC;
        f = (f32 *)sp;
        dst = (__ps_t *)((char *)arg0 + 0x20);
        do {
            r = fn_801294E0(arg1, var_r29);
            var_r29 += 1;
            fa = r->u4;
            fb = r->u8;
            fc = r->uC;
            ((volatile f32 *)sp)[0] = fa;
            f[2] = fc;
            f[3] = temp_f31;
            f[1] = fb;
            dst[0] = sp[0];
            __asm__("" : "+r"(dst));
            dst[1] = *(__ps_t *)((char *)f + 8);
            dst += 2;
        } while (var_r29 < temp_r28);
    }
    arg0->unk0x74 = 0;
}
