// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80026AA8-0x80026AD4 (44B). Byte-identical.
// GetBoneIndex: conditional indexed load from bone data. If flag bit 22
// (0x00400000) is set, loads a signed 16-bit index from base + idx*4 + 2
// (stride-4 mode). Otherwise loads an unsigned 8-bit index from
// base + idx*2 + 1 (stride-2 mode).
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_80026AA8(CStruct *arg0, void *arg1, s32 arg2) {
    u32 flags = *((u32 *)&arg0->unk0x4);
    if (flags & QB_UNKNOWN_0x00400000) {
        return *(s16 *)((char *)arg1 + (arg2 << 2) + 2);
    } else {
        s32 offset = arg2 + arg2;
        return *(u8 *)((char *)arg1 + offset + 1);
    }
}
