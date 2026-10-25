// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A4EE0-0x800A4F5C (124B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-schedule-insns
#include "types.h"
#include "structs.h"
extern char lbl_80301A78[];
extern char lbl_80301A7C[];
void fn_800A4EE0(void) {
    u32 temp_r9;
    void *temp_r10;
    Unk_24B3C57B *temp_r11;

    temp_r9 = *(u32 *)&lbl_80301A7C;
    if (temp_r9 > 1U) {
        *(u32 *)&lbl_80301A7C = temp_r9 - 1;
        return;
    }
    temp_r10 = *(void * *)&lbl_80301A78;
    if (temp_r10 != NULL) {
        temp_r11 = (Unk_24B3C57B *)((Unk_AD65BA9A *)temp_r10)->unk0xB21C;
        ((s32 (*)(void *, s32))temp_r11->unk0xC)(
            (char *)temp_r10 + temp_r11->unk0x8, 3);
    }
    *(u32 *)&lbl_80301A7C = 0U;
    *(void * *)&lbl_80301A78 = NULL;
}
