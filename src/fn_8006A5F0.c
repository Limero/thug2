// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8006A5F0-0x8006A67C (140B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

s32 fn_80069840(s32, s32);
extern s32 lbl_80300460;

void fn_8006A5F0(void **arg0) {
    void *sp8[4];
    if (*(s32 *)((char *)arg0 + 4) == 0) {
        return;
    }
    sp8[0] = *arg0 != 0 ? *(void **)((char *)*arg0 + 4) : 0;
    sp8[2] = *arg0;
    if (sp8[0] != *arg0) {
        do {
            fn_80069840(*(s32 *)sp8[0], lbl_80300460 ^ 1);
            sp8[0] = *(void **)((char *)sp8[0] + 4);
            sp8[2] = *arg0;
        } while (sp8[0] != *arg0);
    }
}
