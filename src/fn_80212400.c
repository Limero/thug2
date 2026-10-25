// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80212400-0x80212490 (144B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_80303150[];
s32 Tmr_GetTime(void);
bool fn_80212400(Unk_F1DBC2A0 *arg0) {
    s32 temp_r3;
    s32 var_r0;
    s32 newval;

    if ((((s32) arg0->unk0xB8 == 0) && ((s32) arg0->unk0x198 == 0) && (var_r0 = arg0->unk0x5F8, ((var_r0 == 0) != 0))) || (var_r0 = arg0->unk0xA4, ((var_r0 == 0) != 0))) {
        arg0->unk0x1874 = var_r0;
        return false;
    }
    if ((s32) arg0->unk0x1874 == 0) {
        temp_r3 = Tmr_GetTime();
        newval = (s32) (*(s32 *)&lbl_80303150 + temp_r3);
        arg0->unk0x1874 = 1;
        arg0->unk0x1878 = newval;
    }
    return true;
}
