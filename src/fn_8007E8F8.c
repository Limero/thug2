// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007E8F8-0x8007E984 (140B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct {
    char pad0x00[0x14];
    void *unk0x14;
    char pad0x18[0x04];
    s32 unk0x1C;
    s32 unk0x20;
    char pad0x24[0x04];
    s32 unk0x28;
    s32 unk0x2C;
    s32 unk0x30;
    char pad0x34[0x04];
    f32 unk0x38;
    f32 unk0x3C;
    f32 unk0x40;
    f32 unk0x44;
    f32 unk0x48;
    f32 unk0x4C;
    f32 unk0x50;
    f32 unk0x54;
} E8F8_obj;

extern f32 lbl_8029624C;
extern f32 lbl_80296250;
extern char lbl_802962C8[];
void fn_8005EEFC(void);

void *fn_8007E8F8(E8F8_obj *arg0) {
    f32 f0;
    f32 f13;

    fn_8005EEFC();
    f0 = lbl_8029624C;
    f13 = lbl_80296250;
    arg0->unk0x14 = (void *)lbl_802962C8;
    arg0->unk0x28 = 0x55;
    arg0->unk0x1C = 0;
    arg0->unk0x20 = 0;
    arg0->unk0x30 = 0;
    arg0->unk0x2C = 1;
    arg0->unk0x38 = f0;
    arg0->unk0x3C = f0;
    arg0->unk0x40 = f0;
    arg0->unk0x44 = f0;
    arg0->unk0x48 = f13;
    arg0->unk0x4C = f13;
    arg0->unk0x50 = f13;
    arg0->unk0x54 = f13;
    return arg0;
}
