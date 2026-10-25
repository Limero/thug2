// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8024EECC-0x8024EF18 (76B). Byte-identical.
#include "types.h"
extern void *memset();
extern void *fn_8024EAF4(s32 arg0, s32 size);
s32 fn_8024EECC(void *arg0, s32 w, s32 h) {
    s32 size = w * h;
    void *ret = fn_8024EAF4(arg0, size);
    if (ret != NULL) {
        memset(ret, 0, size);
    }
    return ret;
}
