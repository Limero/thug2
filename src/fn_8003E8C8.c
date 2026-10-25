// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8003E8C8-0x8003E914 (76B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8003DA40(s32);
void fn_8003EEAC(s32, s32);
extern char lbl_802921D8[];
void *fn_8003E8C8(CStruct *arg0) {
    arg0->unk0x4 = 0;
    fn_8003DA40((char *)arg0 + 8);
    fn_8003EEAC(arg0, lbl_802921D8);
    return arg0;
}
