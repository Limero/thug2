// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8012227C-0x80122304 (136B). Byte-identical.
#include "types.h"
#include "structs.h"

extern u8 lbl_8039BA58[];
extern u8 lbl_8039B9E0[];
void fn_8001B754(void *);

bool fn_8012227C(void) {
    char *base = (char *)lbl_8039BA58;
    s32 temp_r30;

    if (((s32) ((Unk_5FCDF30E *)base)->unk0x2C0 != 0) && ((s32) ((Unk_5FCDF30E *)base)->unk0x2C8 == 0)) {
        temp_r30 = ((Unk_5FCDF30E *)base)->unk0x2D0;
        if (temp_r30 == 0) {
            ((Unk_5FCDF30E *)base)->unk0x2C0 = temp_r30;
            fn_8001B754(lbl_8039B9E0);
            if ((s32) ((Unk_5FCDF30E *)base)->unk0x2BC != 0) {
                (*(void (**)(s32))((char *)base + (s32)0x4))(((Unk_5FCDF30E *)base)->unk0x2BC);
                ((Unk_5FCDF30E *)base)->unk0x2BC = temp_r30;
            }
            return true;
        }
    }
    return false;
}
