// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8006FC80-0x8006FCC8 (72B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
#include "mem.h"

void *fn_8006FE90(Unk_DB0E2BAB *, s32);

void *fn_8006FC80(CStruct *arg0)
{
    arg0->unk0x0 = fn_8006FE90(Mem_Alloc2(0x18), 8);
    arg0->unk0x4 = 1;
    return arg0;
}
