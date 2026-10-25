// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80042180-0x800421CC (76B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
typedef struct {
    char p0[0xC];
    s32 unk0xC;
    char p1[0x48];
    s32 unk0x58;
} R80042180;
s32 fn_80042180(R80042180 *arg0);
bool fn_80042180(R80042180 *arg0) {
    s32 temp_r9 = arg0->unk0xC & 0x10000000;

    if ((temp_r9 != 0) || ((arg0->unk0x58 != 0) && (fn_80042180((R80042180 *) arg0->unk0x58) != 0))) {
        return true;
    }
    return false;
}
