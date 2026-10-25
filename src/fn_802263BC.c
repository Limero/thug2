// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802263BC-0x8022640C (80B). Byte-identical.
#include "types.h"
extern s32 lbl_80305FF8;
void fn_802332EC(s32 arg0, void * arg1, s32 arg2);
s32 fn_802332B8(s32 arg0, s32 arg1);
void Crc_GenerateCRCCaseSensitive(s32 arg0, s32 arg1);
register s32 g31 __asm__("r31");
bool fn_802263BC(s32 *arg0) {
    fn_802332EC(lbl_80305FF8, *arg0, 1);
    Crc_GenerateCRCCaseSensitive(fn_802332B8(lbl_80305FF8, 0), 0x3A98);
    return true;
}
