// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800EFBF4-0x800EFC38 (68B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-schedule-insns
#include "types.h"
#include "structs.h"
s32 Mem_Alloc_3(s32);
void *fn_800EFBF4(CStruct *arg0) {
    arg0->unk0x4 = 0;
    arg0->unk0xC = 0;
    arg0->unk0x8 = Mem_Alloc_3(0xC8);
    return arg0;
}