// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8006A67C-0x8006A6F0 (116B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_80069890(Unk_E80761A5 *);
void fn_8006A67C(void **arg0) {
    void *sp8[4];
    sp8[0] = *arg0 != 0 ? *(void **)((char *)*arg0 + 4) : 0;
    sp8[2] = *arg0;
    if (sp8[0] != *arg0) {
        do {
            fn_80069890(*(Unk_E80761A5 **)(char *)sp8[0]);
            sp8[0] = *(void **)((char *)sp8[0] + 4);
            sp8[2] = *arg0;
        } while (sp8[0] != *arg0);
    }
}
