// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80018DEC-0x80018E2C (64B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
s32 OSIsThreadSuspended(s32);
extern char lbl_8031FB28[];
void OSResumeThread(s32);
void fn_80018DEC(void) {
    if (OSIsThreadSuspended((s32)lbl_8031FB28) != 0) {
        OSResumeThread((s32)lbl_8031FB28);
    }
}