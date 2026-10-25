// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800EC39C-0x800EC448 (172B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct Unk_C7387A53 {
    char pad0x0[0x4C];
    void *unk0x4C;
} Unk_C7387A53;

typedef struct Unk_800EC39C {
    s32 unk0x0;
    s32 unk0x4;
    f32 f0x8;
    f32 f0xC;
    f32 f0x10;
    f32 f1x14;
    s32 unk0x18;
    s32 unk0x1C;
    s32 unk0x20;
    char pad0x24[0x644];
    s32 unk0x668;
    f32 f0x66C;
    f32 f0x670;
    s32 unk0x674;
    f32 f0x678;
    s32 unk0x67C;
    s32 unk0x680;
    s32 unk0x684;
} Unk_800EC39C;

extern f32 lbl_8029ADAC;
extern f32 lbl_8029ADB0;

void fn_800EC324(Unk_C7387A53 *o);

Unk_800EC39C *fn_800EC39C(Unk_800EC39C *arg0) {
    Unk_C7387A53 *q;
    f32 *v;
    s32 i;

    i = 0x13;
    q = (Unk_C7387A53 *)((char *)arg0 + 0x28);
    do {
        fn_800EC324(q);
        q++;
    } while (0 != i--);
    arg0->unk0x0 = 0;
    arg0->unk0x4 = 0;
    arg0->f0x8 = lbl_8029ADAC;
    v = (f32 *)arg0 + 2;
    v[1] = lbl_8029ADAC;
    v[2] = lbl_8029ADAC;
    v[3] = lbl_8029ADB0;
    arg0->unk0x18 = 0;
    arg0->unk0x1C = 0;
    arg0->unk0x20 = 0;
    arg0->f0x678 = lbl_8029ADAC;
    arg0->unk0x67C = 0;
    arg0->unk0x680 = 0;
    arg0->unk0x668 = 0;
    arg0->f0x66C = lbl_8029ADAC;
    arg0->f0x670 = lbl_8029ADAC;
    arg0->unk0x674 = 1;
    arg0->unk0x684 = 0;
    return arg0;
}
