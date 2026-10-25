// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80099460-0x800994C8 (104B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void Mem_Free2(void *arg0);
void Mem_Free(void *arg0);
void fn_80099460(CStruct *arg0, s32 arg1) {
    s32 temp_r9;

    if ((s32)arg0->unk0x8 != 0) {
        temp_r9 = arg0->unk0x4 & 0xC00;
        if (temp_r9 == 0) {
            Mem_Free2((void *)arg0->unk0x8);
        }
    }
    if ((s32)arg0->unk0x58 != 0) {
        Mem_Free2((void *)arg0->unk0x58);
    }
    if (arg1 & 1) {
        Mem_Free((void *)arg0);
    }
}
