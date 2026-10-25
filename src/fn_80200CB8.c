// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80200CB8-0x80200D70 (184B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
typedef struct {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec4;
typedef struct {
    char pad0x0[0x4];
    s32 unk0x4;
    char pad0x8[0x10];
    s32 unk0x18;
    char pad0x1C[0xA14];
    Vec4 v0;
    Vec4 v1;
    char pad0x50[0x18];
    Vec4 v2;
    Vec4 v3;
    char pad0x88[0x10];
    s32 unk0xA98;
    s32 unk0xA9C;
    s32 unk0xAA0;
    s32 unk0xAA4;
    s32 unk0xAA8;
} Unk_80200CB8;
extern f32 lbl_802AEC44;
extern char lbl_802AEC70[];
void fn_8009F53C(Unk_80200CB8 *arg0);
void *fn_80200CB8(Unk_80200CB8 *arg0) {
    f32 temp_f0;
    Vec4 *temp_r10;
    Vec4 *temp_r11;
    Vec4 *temp_r8;
    Vec4 *temp_r9;

    fn_8009F53C(arg0);
    temp_f0 = lbl_802AEC44;
    arg0->unk0x18 = (s32)lbl_802AEC70;
    arg0->unk0x4 = QB_STATSMANAGER;
    temp_r9 = &arg0->v0;
    arg0->unk0xA9C = 0;
    temp_r11 = &arg0->v1;
    arg0->unk0xAA0 = 0;
    temp_r10 = &arg0->v2;
    arg0->unk0xAA4 = 0;
    temp_r8 = &arg0->v3;
    arg0->unk0xAA8 = 0;
    arg0->v0.x = temp_f0;
    temp_r9->y = temp_f0;
    temp_r9->z = temp_f0;
    temp_r9->w = temp_f0;
    arg0->v1.x = temp_f0;
    temp_r11->y = temp_f0;
    temp_r11->z = temp_f0;
    temp_r11->w = temp_f0;
    arg0->v2.x = temp_f0;
    temp_r10->y = temp_f0;
    temp_r10->z = temp_f0;
    temp_r10->w = temp_f0;
    arg0->v3.x = temp_f0;
    temp_r8->y = temp_f0;
    temp_r8->z = temp_f0;
    temp_r8->w = temp_f0;
    arg0->unk0xA98 = 0;
    return arg0;
}
