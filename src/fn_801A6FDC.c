// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A6FDC-0x801A700C (48B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

s32 fn_801A6FDC(Unk_93C2DF4D *arg0, s32 arg1)
{
    s32 *base = (s32 *)((char *)arg0 + 0x5F0);
    s32 val = base[arg1 >> 5];
    s32 mask = 1 << (arg1 & 0x1F);

    return (val & mask) != 0;
}
