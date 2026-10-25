// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80050428-0x8005049C (116B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
s32 fn_800145AC(void);
typedef struct {
    s32 w[6];
} S24;
void fn_80050428(char *arg0, s32 arg1) {
    if (arg1 == 0) {
        *(S24 *)(arg0 + 0x498) = *(S24 *)(arg0 + 0x480);
    }
    *(s32 *)(arg0 + 0x4B4) = arg1;
    *(s32 *)(arg0 + 0x4B0) = fn_800145AC();
}
