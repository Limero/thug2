// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801224E8-0x80122554 (108B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern char lbl_8029DEB4[];
extern char lbl_8029E1E0[];
extern char lbl_8039BA58[];
int OSPanic();
void fn_801224E8(s32 *arg0, s32 *arg1) {
    char *mgr = lbl_8039BA58;
    if (*(s32 *)(mgr + 0x2C0) == 0) {
        OSPanic(lbl_8029DEB4, 0x390, lbl_8029E1E0);
    }
    *arg0 = (s32) *(u16 *)(mgr + 0x88);
    *arg1 = (s32) *(u16 *)(mgr + 0x8A);
}