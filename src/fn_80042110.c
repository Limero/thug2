// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80042110-0x8004215C (76B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
typedef struct No42110 {
    char pad0x0[0xC];
    u32 unk0xC;
    char pad0x10[0x48];
    struct No42110 *unk0x58;
} No42110;
bool fn_80042110(No42110 *arg0) {
    if (((arg0->unk0xC & 0x200000) != 0) ||
        ((arg0->unk0x58 != NULL) && (fn_80042110(arg0->unk0x58) != 0))) {
        return true;
    }
    return false;
}
