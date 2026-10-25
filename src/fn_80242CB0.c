// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80242CB0-0x80242CF8 (72B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_802B1198[];
void *fn_80242CB0(CStruct *arg0) {
    fn_80241638();
    arg0->unk0x38 = (s32)lbl_802B1198;
    arg0->unk0x8 = (s32) (arg0->unk0x8 | 2);
    return arg0;
}
