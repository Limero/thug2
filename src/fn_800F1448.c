// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F1448-0x800F14E8 (160B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_800121D8(s32);
CStruct *fn_800F10C0(void);
bool fn_800F1448(CStruct *arg0, s32 *arg1, s32 arg2) {
    s32 key;
    s32 idx;
    CStruct *slot;
    CStruct *node;

    key = *arg1;
    idx = (key & ((1 << arg0->unk0x0) - 1)) * 0xC;
    slot = (CStruct *)((char *)arg0->unk0x4 + idx);
    if (slot->unk0x4 != 0) {
        fn_800121D8(0);
        node = fn_800F10C0();
        node->unk0x0 = *arg1;
        node->unk0x4 = arg2;
        node->unk0x8 = slot->unk0x8;
        slot->unk0x8 = (s32)node;
    } else {
        *(s32 *)((char *)arg0->unk0x4 + idx) = key;
        slot->unk0x4 = arg2;
    }
    arg0->unk0x8 = arg0->unk0x8 + 1;
    return true;
}
