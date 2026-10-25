// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F1DB0-0x800F1E1C (108B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_800F16C8(void *, s32, s32, s32);
bool fn_800F1DB0(Unk_A231C4C2 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    u32 i;

    for (i = 0; i < (u32) arg0->unk0x10008; i++) {
        if (arg1 == *(s32 *)((char *)arg0 + 0x1000C + i * 0xC)) {
            fn_800F16C8(arg0, (s32) i, arg2, arg3);
            return true;
        }
    }
    return false;
}
