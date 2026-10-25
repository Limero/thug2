// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007DC58-0x8007DCC0 (104B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern s32 lbl_80301758;
extern bool lbl_8030175C;
extern volatile s32 lbl_803017A8;
extern volatile s32 lbl_803017AC;
extern bool lbl_803017B0;

void fn_8007DC58(void) {
    if (lbl_803017B0 != 0) {
        lbl_803017AC = 0;
        lbl_803017A8 = 1;
        for (;;) {
            if (lbl_803017AC) break;
        }
        lbl_803017B0 = 0;
    }
    lbl_80301758 = 0;
    lbl_8030175C = 0;
}
