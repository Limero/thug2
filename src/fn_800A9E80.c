// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A9E80-0x800A9F70 (240B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct {
    void *unk0x0;
    s32 unk0x4;
    s32 unk0x8;
    s32 unk0xC;
    s32 unk0x10;
    s32 unk0x14;
    s32 unk0x18;
    char pad0x1C[0x4];
    f32 unk0x20;
} S9E80;

extern f32 lbl_802982A0;
extern f64 lbl_802982A8;
extern s32 lbl_80303150;
s32 fn_800145AC(void);
s32 Tmr_GetTime(void);

void fn_800A9E80(S9E80 *arg0, s32 arg1) {
    volatile double _dummy;
    f32 zero = lbl_802982A0;
    s32 var;
    if (arg0->unk0x20 != zero) {
        if (arg1 > 0x40) {
            f64 cvt = (f64)(u32)fn_800145AC();
            f32 t = (f32)cvt;
            if (!(t > arg0->unk0x20)) return;
            arg0->unk0x20 = zero;
        } else {
            arg0->unk0x20 = zero;
        }
    }
    arg0->unk0x10 = arg1;
    if (arg1 > 0x40) {
        if (arg0->unk0x4 == 0) {
            arg0->unk0x8 = lbl_80303150 + Tmr_GetTime();
            arg0->unk0x14 = 1;
        }
        var = 1;
    } else {
        if (arg0->unk0x4 != 0) {
            arg0->unk0xC = lbl_80303150 + Tmr_GetTime();
            arg0->unk0x18 = 1;
        }
        var = 0;
    }
    arg0->unk0x4 = var;
}
