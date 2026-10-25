// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802297C0-0x80229810 (80B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void *GetChecksum_3(void *, s32);
s32 fn_802069BC(void *);
s32 fn_802297C0(void *arg0) {
    s32 temp;

    if (*(s32 *)((char *)arg0 + 0x18) == 0) {
        return 0;
    }
    temp = GetChecksum_3(*(void **)((char *)arg0 + 0x18), 0x5B512EDC);
    if (temp == 0) {
        return 0;
    }
    return fn_802069BC((void *)temp);
}
