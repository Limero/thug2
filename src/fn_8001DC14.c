// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001DC14-0x8001DC30 (28B). Byte-identical.
#include "types.h"
extern char lbl_CC008000[];
void fn_8001DC14(u32 arg0) {
    *(volatile u8 *)&lbl_CC008000 = (u8) (arg0 >> 0x10U);
    *(volatile u8 *)&lbl_CC008000 = (u8) (arg0 >> 8U);
    *(volatile u8 *)&lbl_CC008000 = arg0;
}
