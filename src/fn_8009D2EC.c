// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009D2EC-0x8009D320 (52B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8000C6A0(Unk_E93B8C39 *);
void fn_8009D2EC(s32 arg0, s32 arg1) {
    s32 off = arg1 * 0x94;
    s32 *base = (s32 *)((char *)arg0 + 8);
    s32 v = *(s32 *)((char *)base + off);
    if (v != 0) {
        fn_8000C6A0(v);
    }
}