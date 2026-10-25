// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F1AE8-0x800F1B14 (44B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

s32 fn_800F1AE8(Unk_A231C4C2 *arg0)
{
    s32 n;
    char *q;
    s32 off;

    arg0 = (Unk_A231C4C2 *)((char *)arg0 + 0x10000);
    n = *(s32 *)((char *)arg0 + 8);
    if (n != 0) {
        q = (char *)arg0 + 0x10;
        off = (n - 1) * 0xC;
        return *(s32 *)(q + off);
    }
    return 0;
}
