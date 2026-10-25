// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801FCD24-0x801FCE18 (244B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
extern f32 lbl_802AE6A8;
extern f32 lbl_802AE6AC;
extern char lbl_802AE720[];
void fn_8009F53C(void);

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec4f;

typedef struct {
    char pad0x0[0x4];
    s32 unk0x4;
    char pad0x8[0x10];
    s32 unk0x18;
    char pad0x1C[0x4];
    Vec4f v[5];
    f32 f70[9];
    s32 s94[4];
} Unk_801FCD24;

void *fn_801FCD24(Unk_801FCD24 *arg0) {
    f32 temp_f0;
    f32 temp_f13;
    Vec4f *temp_r11;
    Vec4f *temp_r10;
    Vec4f *temp_r7;
    Vec4f *temp_r8;
    Vec4f *temp_r9;

    fn_8009F53C();
    temp_f0 = lbl_802AE6A8;
    arg0->unk0x18 = (s32)lbl_802AE720;
    temp_r11 = (char *)arg0 + 0x20;
    arg0->unk0x4 = QB_EDITORCAMERA;
    temp_f13 = lbl_802AE6AC;
    temp_r9 = (char *)arg0 + 0x30;
    arg0->v[0].x = temp_f0;
    temp_r11->y = temp_f0;
    temp_r11->z = temp_f0;
    temp_r11->w = temp_f13;
    arg0->v[1].x = temp_f0;
    temp_r9->y = temp_f0;
    temp_r9->z = temp_f0;
    temp_r9->w = temp_f13;
    temp_r10 = (char *)arg0 + 0x40;
    arg0->v[2].x = temp_f0;
    temp_r10->y = temp_f0;
    temp_r10->z = temp_f0;
    temp_r10->w = temp_f13;
    temp_r8 = (char *)arg0 + 0x50;
    arg0->v[3].x = temp_f0;
    temp_r8->y = temp_f0;
    temp_r8->z = temp_f0;
    temp_r8->w = temp_f13;
    temp_r7 = (char *)arg0 + 0x60;
    arg0->v[4].x = temp_f0;
    temp_r7->y = temp_f0;
    temp_r7->z = temp_f0;
    temp_r7->w = temp_f13;
    arg0->f70[0] = temp_f0;
    arg0->f70[1] = temp_f0;
    arg0->f70[2] = temp_f0;
    arg0->f70[3] = temp_f0;
    arg0->f70[4] = temp_f0;
    arg0->f70[5] = temp_f0;
    arg0->f70[6] = temp_f0;
    arg0->f70[7] = temp_f0;
    arg0->f70[8] = temp_f0;
    arg0->s94[3] = 0;
    arg0->s94[2] = 0;
    arg0->s94[0] = 0;
    arg0->s94[1] = 0;
    return arg0;
}
