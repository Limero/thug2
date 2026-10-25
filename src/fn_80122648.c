// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80122648-0x801226B4 (108B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
extern s32 lbl_80303140;
extern char lbl_8029DEB4[];
extern char lbl_8029E218[];
void OSPanic(const char *, int, const char *, ...);
s32 fn_80122648(s32 arg0) {
    s32 temp_r31;

    temp_r31 = lbl_80303140;
    if (temp_r31 == 0) {
        OSPanic(lbl_8029DEB4, 0x443, lbl_8029E218);
    }
    lbl_80303140 = (lbl_80303140 + arg0 + 0x1F) & QB_UNKNOWN_0xFFFFFFE0;
    return temp_r31;
}
