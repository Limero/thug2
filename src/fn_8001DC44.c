// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001DC44-0x8001DC5C (24B). Byte-identical.
#include "types.h"
extern char lbl_CC008000[];
void fn_8001DC44(u8 arg0, u32 arg1) {
    *(volatile u8 *)&lbl_CC008000 = 8;
    *(volatile u8 *)&lbl_CC008000 = arg0;
    *(volatile u32 *)&lbl_CC008000 = arg1;
}
