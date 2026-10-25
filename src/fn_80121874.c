// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80121874-0x80121900 (140B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern char lbl_8029DEB4[];
extern char lbl_8029DF8C[];
extern char lbl_8029DFAC[];
extern char lbl_8039BA58[];
int OSPanic();
void fn_80121874(void) {
    char *mgr = lbl_8039BA58;
    if (*(s32 *)(mgr + 4) == 0) {
        OSPanic(lbl_8029DEB4, 0x129, lbl_8029DF8C);
    }
    if (*(s32 *)(mgr + 0x394) == 0) {
        OSPanic(lbl_8029DEB4, 0x12A, lbl_8029DFAC);
    }
    ((void (*)(s32))*(s32 *)(mgr + 4))(*(s32 *)(mgr + 0x394));
}