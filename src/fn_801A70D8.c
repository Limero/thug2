// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A70D8-0x801A7120 (72B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

s32 fn_801A70D8(Unk_93C2DF4D *arg0, s32 arg1)
{
    s32 temp_r0;
    s32 val;
    s32 mask;
    char *pa;
    char *pb;

    temp_r0 = (arg1 >> 5) * 4;
    pa = (char *)arg0 + 0x564;
    pb = (char *)arg0 + 0x2A4;
    val = *(s32 *)(pb + (temp_r0 + (arg0->unk0x630 << 5))) ^
          *(s32 *)(pa + temp_r0);
    mask = 1 << (arg1 & 0x1F);
    return (val & mask) != 0;
}
