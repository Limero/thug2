// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80241E68-0x80241EB8 (80B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_802B11C0[];
void *fn_80241E68(CStruct *arg0) {
    fn_80241638();
    arg0->unk0x38 = (s32)lbl_802B11C0;
    arg0->unk0x8 = (s32) (arg0->unk0x8 | 1);
    arg0->unk0xC = 0;
    return arg0;
}
