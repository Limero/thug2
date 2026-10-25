// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005E55C-0x8005E5F4 (152B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
extern const f32 lbl_80293B44;
extern const f32 lbl_80293B48;
extern const f32 lbl_80293B4C;
extern char lbl_80293C00[];
typedef struct E55C_t {
    s32 unk0x0;
    u32 unk0x4;
    f32 unk0x8;
    f32 unk0xC;
    f32 unk0x10;
    f32 unk0x14;
    f32 unk0x18;
    f32 unk0x1C;
    f32 unk0x20;
    f32 unk0x24;
    char pad0x28[4];
    s16 unk0x2C;
    s16 unk0x2E;
    s32 unk0x30;
    s32 unk0x34;
    char pad0x38[4];
    s32 unk0x3C;
    s32 unk0x40;
    s8 unk0x44;
    s8 unk0x45;
    s8 unk0x46;
    s8 unk0x47;
    s32 unk0x48;
    void *unk0x4C;
} E55C_t;
void *fn_8005E55C(E55C_t *arg0, s32 arg1) {
    E55C_t *o;
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f13;
    s8 *temp_r11;

    temp_f0 = lbl_80293B44;
    o = arg0;
    temp_f13 = lbl_80293B48;
    temp_f12 = lbl_80293B4C;
    o->unk0x4C = (void *)lbl_80293C00;
    temp_r11 = (s8 *)((char *)o + 0x44);
    o->unk0x0 = 0;
    o->unk0x8 = temp_f0;
    o->unk0xC = temp_f0;
    o->unk0x10 = temp_f13;
    o->unk0x18 = temp_f0;
    o->unk0x20 = temp_f12;
    o->unk0x14 = temp_f13;
    o->unk0x1C = temp_f0;
    o->unk0x24 = temp_f12;
    o->unk0x2C = 0;
    o->unk0x2E = 0;
    o->unk0x44 = -0x80;
    temp_r11[1] = -0x80;
    temp_r11[2] = -0x80;
    temp_r11[3] = -0x80;
    o->unk0x48 = arg1;
    o->unk0x30 = 1;
    o->unk0x34 = 0;
    o->unk0x3C = 0;
    o->unk0x40 = 0;
    o->unk0x4 = QB_BLEND;
    return arg0;
}
