// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A2954-0x800A29DC (136B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_802FFE98[];
extern char lbl_80301A44[];
extern char lbl_80301A48[];
extern char lbl_80301A4C[];
void fn_8000F320(Unk_F12C5E01 *);
void fn_8000F2F8(Unk_9F352E7C *, s32);
bool fn_800A2954(s32 arg0) {
    s32 temp_r30;
    u32 temp_r3;

    temp_r30 = *(s32 *)&lbl_802FFE98;
    fn_8000F2F8(temp_r30, fn_800A2A54());
    fn_800A2A54();
    temp_r3 = fn_80011D7C();
    *(u32 *)&lbl_80301A4C = temp_r3;
    if ((arg0 != 0) && (temp_r3 < (u32) (*(s32 *)&lbl_80301A48 * *(s32 *)&lbl_80301A44))) {
        fn_8000F320(*(s32 *)&lbl_802FFE98);
        return false;
    }
    return true;
}
