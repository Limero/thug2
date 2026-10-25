// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80014EDC-0x80014F5C (128B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct W14EDC_Big {
    u32 w[30];
} W14EDC_Big;

extern s32 fn_8001B6A8(void *arg0);

bool fn_80014EDC(char *arg0) {
    W14EDC_Big tmp;

    tmp = *(W14EDC_Big *) (arg0 + 0x8C);
    if (fn_8001B6A8(&tmp) != 0) {
        return true;
    }
    return false;
}
