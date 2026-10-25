// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80129504-0x80129528 (36B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_80129504(CStruct *arg0, s32 arg1) {
    if (*((u32 *)&arg0->unk0x4) == 1)
        return *((u32 *)&arg0->unk0x8);
    return ((u32 *) * (u32 *)((char *)arg0 + 8))[arg1];
}