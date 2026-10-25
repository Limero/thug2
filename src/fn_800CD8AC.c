// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800CD8AC-0x800CD8E4 (56B). Byte-identical.
#include "types.h"
s32 fn_800CD8AC(s32 arg0) {
    s32 i;

    for (i = 0; i < 3; i++) {
        if (*(s32 *)((char *)arg0 + 0x1C + i * 4) == 0) {
            return i + 1;
        }
    }
    return 0;
}
