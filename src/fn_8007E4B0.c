// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007E4B0-0x8007E504 (84B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_8007E4B0(CStruct *arg0, CStruct *arg1) {
    u32 a = arg0->unk0x4;
    u32 b = arg1->unk0x4;
    u32 ahi = a >> 16;
    u32 bhi = b >> 16;
    u32 alo;
    u32 blo;
    if (ahi > bhi) return 1;
    if (ahi < bhi) return -1;
    alo = a & 0xFFFF;
    blo = b & 0xFFFF;
    if (alo > blo) return 1;
    if (alo < blo) return -1;
    return 0;
}
