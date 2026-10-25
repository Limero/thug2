// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80036078-0x800360B0 (56B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// Scans up to 4 entries (0x78-byte stride) at arg0+0x1C for one equal to
// arg1; returns the index or -1 (mtctr/bdnz countdown).
// Suggested rename: fn_80036078_find_entry.
#include "types.h"
s32 fn_80036078(s32 *arg0, s32 arg1) {
    char *p = (char *)arg0 + 0x1C;
    s32 i = 0;
    s32 ctr = 4;
    do {
        s32 t = *(s32 *)p;
        p += 0x78;
        if (t != arg1) {
            i++;
            ctr--;
            continue;
        }
        return i;
    } while (ctr != 0);
    return -1;
}