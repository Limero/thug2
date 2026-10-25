// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001DC30-0x8001DC44 (20B). Byte-identical.
#include "types.h"
extern char lbl_CC008000[];
void fn_8001DC30(u32 arg0) {
    *(volatile u8 *)&lbl_CC008000 = 0x61;
    *(volatile u32 *)&lbl_CC008000 = arg0;
}
