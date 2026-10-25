// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007671C-0x80076778 (92B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "structs.h"
#include "mem.h"
void *fn_8007DE80(void *, s32);
s32 fn_80099428(void);
void *fn_8007671C(s32 a0, s32 a1, s32 a2) {
    Unk_8F0E9453 *temp_r3;

    temp_r3 = fn_8007DE80(Mem_Alloc2(0x290), 0xA);
    temp_r3->unk0x88 = a2;
    temp_r3->unk0x8C = 0;
    Mem_Alloc2(0x70);
    temp_r3->unk0x288 = fn_80099428();
    return temp_r3;
}
