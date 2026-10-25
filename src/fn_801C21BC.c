// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801C21BC-0x801C2254 (152B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_802AC9E8[];
extern char lbl_802ACA60[];
extern char lbl_802ACA90[];
void fn_8009F53C(void);
void *fn_801C21BC(Unk_C8FEE62D *arg0) {
    Unk_C8FEE62D *temp_r11;
    Unk_C8FEE62D *temp_r9;

    fn_8009F53C();
    temp_r11 = (char *)arg0 + 0x1C;
    arg0->unk0x18 = (s32)lbl_802AC9E8;
    temp_r11->unk0x14 = (s32)lbl_802ACA90;
    temp_r11->unk0x8 = 0;
    temp_r11->unk0xC = temp_r11;
    temp_r11->unk0x10 = temp_r11;
    temp_r11->unk0x4 = -1;
    temp_r9 = (char *)arg0 + 0x34;
    temp_r9->unk0x14 = (s32)lbl_802ACA60;
    temp_r9->unk0x4 = -1;
    temp_r9->unk0xC = temp_r9;
    temp_r9->unk0x10 = temp_r9;
    temp_r9->unk0x8 = 0;
    arg0->unk0x4 = QB_SKATERGAP;
    arg0->unk0x54 = 0;
    arg0->unk0x58 = 0;
    return arg0;
}
