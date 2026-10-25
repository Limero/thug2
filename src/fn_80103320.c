// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80103320-0x80103470 (336B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

typedef struct A3320_1 {
    u16 unk0x0;
    u8 _2;
    u8 unk0x3;
    u16 *unk0x4;
} A3320_1;

typedef struct A3320_0 {
    char _0[8];
    u16 unk0x8;
} A3320_0;

extern s32 lbl_80302BC8;
extern u16 *lbl_80301BC4;
extern f32 lbl_8029C9A8;

A3320_1 *fn_80105B44(A3320_1 *arg0);
A3320_1 *fn_80105B90(A3320_1 *arg0);

void fn_80103320(A3320_0 *arg0, A3320_1 *arg1, f32 *arg2) {
    register u32 idx0 __asm__("r0");
    register u32 idx __asm__("r8");
    register u32 off __asm__("r28");
    register A3320_0 *a0 __asm__("r29") = arg0;
    register f32 *a2 __asm__("r30") = arg2;
    volatile double _dummy;

    idx0 = *(u8 *)((char *)arg1 + 3);
    idx = idx0 & 3;
    if (idx == 3) {
        u16 n = arg1->unk0x0;
        s32 c = lbl_80302BC8;
        u16 *src = arg1->unk0x4;
        u16 *dst = lbl_80301BC4 + c;
        s32 nv = c + n;
        u32 i;

        lbl_80302BC8 = nv;
        if (nv > a0->unk0x8) {
            lbl_80302BC8 = -1;
            return;
        }
        for (i = 0; i < n; i++) {
            *dst++ = *src++;
        }
    } else {
        s32 raw = *(s32 *)arg1;
        f32 f;

        off = idx << 2;
        f = (f32)(f64)(raw >> 2) * lbl_8029C9A8;

        if (*(f32 *)((char *)a2 + off) < f) {
            fn_80103320(a0, fn_80105B44((A3320_1 *)((char *)arg1 + 4)), a2);
        }
        {
            register f32 *q __asm__("r9") = (f32 *)((char *)a2 + 0x10);
            if (*(f32 *)((char *)q + off) >= f) {
                if (lbl_80302BC8 >= 0) {
                    fn_80103320(a0, fn_80105B90((A3320_1 *)((char *)arg1 + 4)), a2);
                }
            }
        }
    }
}
