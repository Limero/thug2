// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80102D18-0x80102D88 (112B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

s32 fn_80102D18(void *arg0);
void *fn_80105B44(void *);
void *fn_80105B90(void *);

s32 fn_80102D18(void *arg0) {
    void *child;
    s32 left;
    s32 right;

    if ((*(u8 *)((char *)arg0 + 3) & 3) == 3) {
        return *(s32 *)((char *)arg0 + 4);
    }
    child = (char *)arg0 + 4;
    left = fn_80102D18(fn_80105B44(child));
    right = fn_80102D18(fn_80105B90(child));
    if ((u32)left < (u32)right) {
        return left;
    }
    return right;
}
