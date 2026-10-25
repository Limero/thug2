// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801294BC-0x801294E0 (36B). Byte-identical.
#include "types.h"
#include "structs.h"
// GetChecksum @ 0x801294BC
s32 GetChecksum(CStruct *arg0, s32 arg1) {
    if (*((u32 *)&arg0->unk0x4) == 1)
        return *((u32 *)&arg0->unk0x8);
    return ((u32 *) * (u32 *)((char *)arg0 + 8))[arg1];
}