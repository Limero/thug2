// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8003FC34-0x8003FD14 (224B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_800145AC(void);
extern f32 lbl_80292314;
// CScreenElement_SetAnimTime @ 0x8003FC34
void CScreenElement_SetAnimTime(Unk_5EE4163F *arg0, s32 arg1) {
    char *src;
    char *dst;

    arg0->unk0x118 = fn_800145AC();
    *(f32 *)((char *)arg0 + 0x124) = *(f32 *)((char *)arg0 + 0x120) = lbl_80292314;
    arg0->unk0x11C = arg1;
    if (arg1 == 0) {
        src = (char *)arg0 + 0xD0;
        dst = (char *)arg0 + 0x88;
        ((__ps_t *)((char *)arg0 + 0x90))[0] = ((__ps_t *)((char *)arg0 + 0xD8))[0];
        *(f32 *)((char *)arg0 + 0x88) = *(f32 *)((char *)arg0 + 0xD0);
        ((__ps_t *)((char *)arg0 + 0x98))[0] = ((__ps_t *)((char *)arg0 + 0xE0))[0];
        *(f32 *)(dst + 0x18) = *(f32 *)(src + 0x18);
        *(f32 *)(dst + 0x1C) = *(f32 *)(src + 0x1C);
        *(s32 *)(dst + 0x20) = *(s32 *)(src + 0x20);
        *(f32 *)(dst + 0x24) = *(f32 *)(src + 0x24);
        *(f32 *)(dst + 0x28) = *(f32 *)(src + 0x28);
        *(f32 *)(dst + 0x2C) = *(f32 *)(src + 0x2C);
        *(f32 *)(dst + 0x30) = *(f32 *)(src + 0x30);
        *(f32 *)(dst + 0x34) = *(f32 *)(src + 0x34);
        *(f32 *)(dst + 0x38) = *(f32 *)(src + 0x38);
        *(f32 *)(dst + 0x3C) = *(f32 *)(src + 0x3C);
        *(s32 *)(dst + 0x40) = *(s32 *)(src + 0x40);
        *(s32 *)(dst + 0x44) = *(s32 *)(src + 0x44);
    }
    arg0->unk0xC = (arg0->unk0xC | 0x400) & (s32)QB_UNKNOWN_0xFFF9FFFF;
}
