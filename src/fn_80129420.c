// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80129420-0x801294BC (156B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

f32 fn_80129420(Unk_5AA7B5D7 *arg0, s32 arg1) {
    if (arg0->unk0x4 == 1) {
        if (*(u8 *)((char *)arg0 + 2) == 2) {
            return *(f32 *)((char *)arg0 + 8);
        }
        return (f32)(*(s32 *)((char *)arg0 + 8));
    }
    if (*(u8 *)((char *)arg0 + 2) == 2) {
        return ((f32 *)(*(s32 *)((char *)arg0 + 8)))[arg1];
    }
    return (f32)(((s32 *)(*(s32 *)((char *)arg0 + 8)))[arg1]);
}
