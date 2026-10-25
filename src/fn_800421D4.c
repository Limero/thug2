// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800421D4-0x80042220 (76B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct No421D4 {
    char pad0x0[0xC];
    u32 unk0xC;
    char pad0x10[0x48];
    struct No421D4 *unk0x58;
} No421D4;

bool fn_800421D4(No421D4 *arg0) {
    if (((arg0->unk0xC & 0x400000) != 0) ||
        ((arg0->unk0x58 != NULL) && (fn_800421D4(arg0->unk0x58) != 0))) {
        return true;
    }
    return false;
}
