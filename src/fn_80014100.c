// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80014100-0x80014150 (80B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
bool fn_80014100(char *arg0, s32 a1, s32 a2) {
    s32 i;
    for (i = 0; i < *(s32 *)(arg0 + 0x10); i++) {
        s32 *p = (s32 *)(arg0 + 0x24 + i * 0x10);
        if (p[-1] == a1 && p[0] == a2) {
            return true;
        }
    }
    return false;
}
