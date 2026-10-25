// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801225F8-0x80122648 (80B). Byte-identical.
#include "types.h"
#include "mem.h"
void OSPanic(const char *, int, const char *, ...);
extern char lbl_8029DEB4[];
extern char lbl_8029E200[];
void fn_801225F8(s32 arg0) {
    if (arg0 == 0) {
        OSPanic(lbl_8029DEB4, 0x420, lbl_8029E200);
    }
    Mem_Free(arg0);
}
