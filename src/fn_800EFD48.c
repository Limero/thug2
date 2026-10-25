// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800EFD48-0x800EFDC0 (120B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void * Mem_Alloc_3(s32);
s32 Mem_Free_3(s32);
void fn_800EFD48(CStruct *arg0) {
    s32 old;
    s32 i;

    old = arg0->unk0x8;
    arg0->unk0x8 = (s32) Mem_Alloc_3(arg0->unk0x4 * 2);
    for (i = 0; i < arg0->unk0x4; i++) {
        *(u16 *)((char *)arg0->unk0x8 + i * 2) = *(u16 *)((char *)old + i * 2);
    }
    Mem_Free_3(old);
}
