// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80234FC0-0x80235000 (64B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void fn_802401C8(void *);
s32 fn_80128E34(s32, s32, s32, s32);
bool ScriptParkEdMemSnapshot(s32 arg0) {
    s32 sp8;

    if (fn_80128E34(arg0, 0, (s32) &sp8, 0) != 0) {
        fn_802401C8((void *) sp8);
    }
    return true;
}
