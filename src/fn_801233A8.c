// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801233A8-0x80123408 (96B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern s32 lbl_8039BAF8;
extern s32 lbl_8039BE60;
extern s32 lbl_8039BE64;
extern s32 lbl_8039BE7C;
extern s32 lbl_8039BE80;
void OSDisableInterrupts(void);
void OSRestoreInterrupts(void);
void fn_801233A8(void) {
    if (lbl_8039BAF8 != 0x4E4F4E45) {
        OSDisableInterrupts();
        *(volatile s32 *)&lbl_8039BE7C = 0;
        lbl_8039BE60 = 0;
        lbl_8039BE64 = 0;
        *(volatile s32 *)&lbl_8039BE80 = 0;
        OSRestoreInterrupts();
    }
}
