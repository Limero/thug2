// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009C8A8-0x8009C918 (112B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-schedule-insns
#include "types.h"
#include "structs.h"
#include "mem.h"
extern char lbl_80297880[];
void fn_8009C8A8(Unk_C8FEE62D *arg0, s32 arg1) {
    void *temp_r11;
    Unk_24B3C57B *temp_r9;

    temp_r11 = arg0->unk0x10;
    arg0->unk0x14 = (s32)lbl_80297880;
    if (temp_r11 != NULL) {
        temp_r9 = (Unk_24B3C57B *)((Unk_C8FEE62D *)temp_r11)->unk0x14;
        temp_r9->unk0xC((void *)((char *)temp_r11 + temp_r9->unk0x8),
                        (void *)3);
    }
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
