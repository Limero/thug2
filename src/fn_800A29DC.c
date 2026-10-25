// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A29DC-0x800A2A24 (72B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_802FFE98[];
extern char lbl_80301A4C[];
void fn_800A2A54(void);
s32 fn_80011D7C(void);
void fn_8000F320(Unk_F12C5E01 *);
s32 fn_800A29DC(void) {
    s32 temp_r30;

    fn_800A2A54();
    temp_r30 = *(s32 *)&lbl_80301A4C - fn_80011D7C();
    fn_8000F320(*(s32 *)&lbl_802FFE98);
    return temp_r30;
}
