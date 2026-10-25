// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001DC7C-0x8001DC98 (28B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
//
// Identification: DB (debug) command-register writer. Writes the command
// byte 0x10, then arg1-1 and arg0 as halfwords to the DB FIFO register at
// 0xCC008000. Suggested rename: DBWriteCommand.
#include "types.h"
extern char lbl_CC008000[];
void fn_8001DC7C(s16 arg0, s32 arg1) {
    *(volatile u8 *)&lbl_CC008000 = 0x10;
    *(volatile u16 *)&lbl_CC008000 = (s16) (arg1 - 1);
    *(volatile u16 *)&lbl_CC008000 = arg0;
}
