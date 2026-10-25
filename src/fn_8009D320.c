// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009D320-0x8009D354 (52B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8000C73C(Unk_FFAD6788 *);
void fn_8009D320(s32 arg0, s32 arg1) {
    s32 off = arg1 * 0x94;
    s32 *base = (s32 *)((char *)arg0 + 8);
    s32 v = *(s32 *)((char *)base + off);
    if (v != 0) {
        fn_8000C73C(v);
    }
}