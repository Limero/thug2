// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F3F3C-0x800F3FE8 (172B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void fn_800F3708(void *);
#include "structs.h"
s32 fn_80026B4C(s32, s32);
void fn_800F3F3C(Unk_C7387A53 *arg0) {
    s32 temp_r3;
    Unk_89391A04 *temp_r9;
    Unk_89391A04 *temp_r9_2;
    Unk_C7387A53 *temp_r9_3;
    Unk_C7387A53 *temp_r9_4;

    temp_r9 = arg0->unk0x50;
    if (((s32 (*)(void *))temp_r9->unk0x14)((char *)arg0 + temp_r9->unk0x10) != 0) {
        temp_r9_2 = arg0->unk0x50;
        temp_r3 = ((s32 (*)(void *))temp_r9_2->unk0x14)((char *)arg0 + temp_r9_2->unk0x10);
        if (temp_r3 != 0) {
            fn_80026B4C(temp_r3, 3);
        }
        temp_r9_3 = arg0->unk0x50;
        ((s32 (*)(void *, s32))temp_r9_3->unk0x5C)((char *)arg0 + *((s16 *)&temp_r9_3->unk0x58), 0);
    }
    temp_r9_4 = arg0->unk0x50;
    ((s32 (*)(void *))temp_r9_4->unk0x84)((char *)arg0 + *((s16 *)&temp_r9_4->unk0x80));
    fn_800F3708(arg0);
}
