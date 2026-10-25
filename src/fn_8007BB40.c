// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007BB40-0x8007BBE0 (160B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct Src_s {
    void *f0;
    s32 f4;
    s32 f8;
    f32 fC;
    f32 f10;
    f32 f14;
    f32 f18;
    f32 f1C;
    f32 f20;
    f32 f24;
    char _pad[0xC];
    s32 f34;
    s32 f38;
    char _pad2[0x18];
    void *f54;
} Src;

typedef struct Dst_s {
    char _pad0[0x14];
    s32 f14;
    s32 f18;
    s32 f1C;
    f32 f20;
    f32 f24;
    f32 f28;
    f32 f2C;
    f32 f30;
    f32 f34;
    f32 f38;
    s32 f3C;
    s32 f40;
} Dst;

void fn_8007BB40(Src *arg0) {
    void *temp_r11;

    temp_r11 = arg0->f0;
    (*(Dst **)((char *)arg0 + 0x54))->f1C = arg0->f8;
    if (temp_r11 != NULL) {
        (*(Dst **)((char *)arg0 + 0x54))->f14 = *(s32 *)((char *)temp_r11 + 8);
    }
    (*(Dst **)((char *)arg0 + 0x54))->f30 = arg0->f14;
    (*(Dst **)((char *)arg0 + 0x54))->f34 = arg0->f18;
    (*(Dst **)((char *)arg0 + 0x54))->f18 = arg0->f4;
    (*(Dst **)((char *)arg0 + 0x54))->f38 = arg0->f24;
    (*(Dst **)((char *)arg0 + 0x54))->f20 = arg0->fC;
    (*(Dst **)((char *)arg0 + 0x54))->f24 = arg0->f10;
    (*(Dst **)((char *)arg0 + 0x54))->f28 = arg0->f1C;
    (*(Dst **)((char *)arg0 + 0x54))->f2C = arg0->f20;
    (*(Dst **)((char *)arg0 + 0x54))->f3C = arg0->f34;
    (*(Dst **)((char *)arg0 + 0x54))->f40 = arg0->f38;
}
