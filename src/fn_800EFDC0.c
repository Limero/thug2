// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800EFDC0-0x800EFE0C (76B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
#include "mem.h"
void *fn_800F10F0(Unk_DB0E2BAB *, s32);
void *fn_800EFDC0(CStruct *arg0) {
    arg0->unk0x4 = (s32) fn_800F10F0(Mem_Alloc2(0x18), 8);
    arg0->unk0x8 = 0;
    arg0->unk0xC = 0;
    return arg0;
}
