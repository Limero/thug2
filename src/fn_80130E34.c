// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80130E34-0x80130E88 (84B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
bool fn_80130E34(Unk_15EF4A35 *arg0, s32 arg1) {
    s32 i;
    s32 *p;

    if (arg0->unk0xBC == arg1) {
        return true;
    }
    for (i = 0; i < arg0->unk0x38; i += 1) {
        p = (s32 *)(arg0->unk0x94 + 0xC) + i * 0xB;
        if (*p == arg1) {
            return true;
        }
    }
    return false;
}