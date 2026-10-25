// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F4A78-0x800F4B20 (168B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern s32 fn_800F38B8(Unk_C7387A53 *);
extern void fn_8005656C(Unk_6A78CE27 *);
extern void Mem_Free_3(void *);
extern s32 fn_800F3708(Unk_C7387A53 *);
void fn_800F4A78(Unk_C7387A53 *arg0) {
    void *temp_r3;
    void *temp_r3_2;
    Unk_89391A04 *temp_r9;
    Unk_89391A04 *temp_r9_2;
    Unk_07FDFB02 *temp_r9_3;

    temp_r9 = arg0->unk0x50;
    if (((s32 (*)(void *))temp_r9->unk0x14)((char *)arg0 + temp_r9->unk0x10) != 0) {
        temp_r3 = fn_800F38B8(arg0);
        temp_r9_2 = ((Unk_C7387A53 *)temp_r3)->unk0x50;
        fn_8005656C(((s32 (*)(void *))temp_r9_2->unk0x14)(temp_r3 + temp_r9_2->unk0x10));
        temp_r3_2 = arg0->unk0x24;
        if (temp_r3_2 != 0) {
            Mem_Free_3(temp_r3_2);
            arg0->unk0x24 = 0;
        }
        temp_r9_3 = arg0->unk0x50;
        ((s32 (*)(void *, s32))temp_r9_3->unk0x5C)((char *)arg0 + temp_r9_3->unk0x58, 0);
    }
    fn_800F3708(arg0);
}
