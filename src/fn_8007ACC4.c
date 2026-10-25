// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007ACC4-0x8007AD08 (68B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// Handler dispatch: when arg1 is non-NULL, calls the function pointer stored
// at descriptor+0xC (descriptor = *(arg1+8)) with (arg1 + (s16)descriptor+8,
// 3) — the offset field is a SIGNED halfword (lha) and the call is 2-arg.
// Always returns 1. Suggested rename: DispatchViaDescriptor
#include "types.h"
#include "structs.h"
bool fn_8007ACC4(void *arg0, void *arg1) {
    if (arg1 != NULL) {
        void *t = *(void **)((char *)arg1 + 8);
        ((s32 (*)(void *, s32))*(void **)((char *)t + 0xC))((char *)arg1 + *(s16 *)((char *)t + 8), 3);
    }
    return true;
}