// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80058778-0x80058800 (136B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct Unk_58778 {
    s32 unk0x0;
    s32 unk0x4;
    s32 unk0x8;
    f32 unk0xC;
    f32 unk0x10;
    f32 unk0x14;
    f32 unk0x18;
    f32 unk0x1C;
    f32 unk0x20;
    f32 unk0x24;
    f32 unk0x28;
    char pad0x2C[8];
    s8 unk0x34;
    s8 unk0x35;
    s8 unk0x36;
    s8 unk0x37;
    s32 unk0x38;
    s32 unk0x3C;
    s32 unk0x40;
    s32 unk0x44;
    s32 unk0x48;
    s32 unk0x4C;
    s32 unk0x50;
} Unk_58778;

extern char lbl_802933C0[];

void *fn_80058778(Unk_58778 *arg0, s32 arg1)
{
    f32 z = 0.0f;
    f32 o = 1.0f;
    s8 *b;

    arg0->unk0x50 = (s32)lbl_802933C0;
    arg0->unk0x0 = 0;
    arg0->unk0x4 = 0;
    arg0->unk0xC = z;
    arg0->unk0x10 = z;
    arg0->unk0x14 = z;
    arg0->unk0x18 = z;
    arg0->unk0x1C = o;
    arg0->unk0x20 = o;
    arg0->unk0x24 = z;
    arg0->unk0x28 = z;
    b = (s8 *)arg0 + 0x34;
    b[0] = -0x80;
    b[1] = -0x80;
    b[2] = -0x80;
    b[3] = -0x80;
    arg0->unk0x40 = 1;
    arg0->unk0x48 = arg1;
    arg0->unk0x38 = 0;
    arg0->unk0x3C = 0;
    arg0->unk0x44 = 0;
    arg0->unk0x4C = 0;
    arg0->unk0x8 = 0;
    return arg0;
}
