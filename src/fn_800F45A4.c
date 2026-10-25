// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F45A4-0x800F4648 (164B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void Mem_Free_3(s32);
void fn_800F3708(void *);
#include "structs.h"
void fn_80054C6C(s32, s32);
void fn_800F45A4(Unk_C7387A53 *arg0) {
    Unk_89391A04 *temp_r9;
    Unk_89391A04 *temp_r9_2;
    Unk_C7387A53 *temp_r9_3;

    temp_r9 = arg0->unk0x50;
    if (((s32 (*)(void *))temp_r9->unk0x14)((char *)arg0 + temp_r9->unk0x10) != 0) {
        temp_r9_2 = arg0->unk0x50;
        fn_80054C6C(((s32 (*)(void *))temp_r9_2->unk0x14)((char *)arg0 + temp_r9_2->unk0x10), 0);
        if ((s32) arg0->unk0x24 != 0) {
            Mem_Free_3((s32) arg0->unk0x24);
            arg0->unk0x24 = 0;
        }
        temp_r9_3 = arg0->unk0x50;
        ((s32 (*)(void *, s32))temp_r9_3->unk0x5C)((char *)arg0 + *((s16 *)&temp_r9_3->unk0x58), 0);
    }
    fn_800F3708(arg0);
}
