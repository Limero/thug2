// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80103234-0x80103280 (76B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
typedef struct {
    char pad0x00[0x34];
    s32 unk0x34;
} S_80103234;
extern u16 lbl_80301BC8[];
s32 fn_80103234(S_80103234 *arg0, s32 arg1, s32 arg2) {
    s32 i;

    if (lbl_80301BC8[0] != 0) {
        for (i = 0x7FF; i >= 0; i--) {
            lbl_80301BC8[i] = (u16)i;
        }
    }
    return arg0->unk0x34 != 0;
}
