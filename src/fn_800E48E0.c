// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800E48E0-0x800E4960 (128B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

typedef struct {
    s32 unk0x0;
    s32 unk0x4;
    s32 unk0x8;
    s32 unk0xC;
    s32 unk0x10;
    s32 unk0x14;
    s32 unk0x18;
    s32 unk0x1C;
    f32 unk0x20;
    f32 unk0x24;
    s32 unk0x28;
    s32 unk0x2C;
    s32 unk0x30;
    s32 unk0x34;
    s32 unk0x38;
} S800E48E0;

extern f32 lbl_8029A91C;
extern char lbl_8029A938[];
extern s32 lbl_80303150;
void fn_8009F53C(void *obj);
s32 Tmr_GetTime(void);

void *fn_800E48E0(S800E48E0 *arg0) {
    f32 temp_f0;
    s32 temp_r3;

    fn_8009F53C(arg0);
    temp_f0 = lbl_8029A91C;
    arg0->unk0x18 = (s32)lbl_8029A938;
    arg0->unk0x4 = QB_COLLIDEANDDIE;
    arg0->unk0x20 = temp_f0;
    arg0->unk0x24 = temp_f0;
    temp_r3 = Tmr_GetTime();
    arg0->unk0x2C = 0;
    arg0->unk0x28 = lbl_80303150 + temp_r3;
    arg0->unk0x34 = 0;
    arg0->unk0x38 = 1;
    return arg0;
}
