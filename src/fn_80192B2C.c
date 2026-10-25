// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80192B2C-0x80192B3C (16B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_80192B2C(Unk_C7387A53 *arg0) {
    return ((u32) (*((u32 *)&arg0->unk0x70) ^ 0x80000) >> 0x13U) & 1;
}
