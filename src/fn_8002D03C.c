// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8002D03C-0x8002D084 (72B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
typedef struct {
    char pad0x0[0x168];
    u32 hi : 13;
    u32 lo : 19;
} Rec_8002D03C;
s32 fn_8002CF60(void);
void fn_8002D03C(Rec_8002D03C *arg0) {
    if (fn_8002CF60() != -1) {
        arg0->hi++;
    }
}
