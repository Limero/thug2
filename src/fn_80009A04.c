// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80009A04-0x80009A44 (64B). Byte-identical.
#include "types.h"
void memset(s32, s32, s32);
s32 fn_80009A04(s32 arg0, s32 arg1) {
    if (arg1 != 0) {
        memset(arg1, 0, arg0);
    }
    return arg1;
}
