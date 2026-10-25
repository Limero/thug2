// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80043A34-0x80043AD0 (156B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

extern char lbl_80292530[];
extern const f32 lbl_802924FC;
extern const f32 lbl_80292500;

void *fn_8003F360(void *);
void fn_8009E274(void *, s32);

typedef struct {
    char pad0[8];
    s32 unk8;
    char padC[0x184];
    s32 unk190;
    char pad194[0x20];
    f32 unk1b4;
    f32 unk1b8;
    f32 unk1bc;
    s32 unk1c0;
    s32 unk1c4;
    char pad1c8[4];
    s32 unk1cc;
    char pad1d0[8];
    u8 unk1d8;
    u8 unk1d9;
    u8 unk1da;
    s8 unk1db;
    s32 unk1dc;
    s32 unk1e0;
} T43A34;

void *fn_80043A34(T43A34 *arg0) {
    f32 f0;
    f32 f13;
    s32 z;
    s8 *base;

    fn_8003F360(arg0);
    arg0->unk8 = (s32)lbl_80292530;
    f0 = lbl_802924FC;
    base = (s8 *)&arg0->unk1d8;
    z = 0;
    arg0->unk1d8 = z;
    f13 = lbl_80292500;
    base[3] = -0x80;
    base[2] = z;
    base[1] = z;
    arg0->unk1b4 = (arg0->unk190 = z, f0);
    arg0->unk1b8 = f0;
    arg0->unk1bc = f13;
    arg0->unk1c0 = z;
    arg0->unk1c4 = z;
    arg0->unk1cc = z;
    arg0->unk1dc = z;
    arg0->unk1e0 = z;
    fn_8009E274(arg0, 0x40D92263);
    return arg0;
}
