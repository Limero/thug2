// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8004DE48-0x8004DED0 (136B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct Unk_4DE48 {
    char pad0x0[0x8];
    s32 unk0x8;
    char pad0xC[0x184];
    s32 unk0x190;
    s32 unk0x194;
    s32 unk0x198;
    s32 unk0x19C;
    f32 unk0x1A0;
    f32 unk0x1A4;
    f32 unk0x1A8;
    f32 unk0x1AC;
    f32 unk0x1B0;
    f32 unk0x1B4;
    s32 unk0x1B8;
    s32 unk0x1BC;
    s32 unk0x1C0;
} Unk_4DE48;

void *fn_8003F360(void *arg0);
extern float lbl_80292AC0[];
extern float lbl_80292ABC[];
extern char lbl_80292BC0[];

void *fn_8004DE48(Unk_4DE48 *arg0)
{
    f32 z;
    f32 o;

    fn_8003F360(arg0);
    z = lbl_80292ABC[0];
    o = lbl_80292AC0[0];
    arg0->unk0x8 = (s32)lbl_80292BC0;
    arg0->unk0x190 = -1;
    arg0->unk0x194 = 0;
    arg0->unk0x198 = 0;
    arg0->unk0x19C = 0;
    arg0->unk0x1AC = z;
    arg0->unk0x1B4 = z;
    arg0->unk0x1A0 = z;
    arg0->unk0x1B0 = o;
    arg0->unk0x1A4 = z;
    arg0->unk0x1B8 = 1;
    arg0->unk0x1BC = 1;
    arg0->unk0x1C0 = -1;
    return arg0;
}
