// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80057BEC-0x80057C90 (164B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-schedule-insns
#include "types.h"
#include "structs.h"
#include "mem.h"
extern char lbl_80293350[];
typedef struct DispEntry {
    s16 unk0x0;
    char pad0x2[0x2];
    s32 unk0x4;
} DispEntry;
void fn_80057BEC(Unk_C8FEE62D *arg0, s32 arg1) {
    void *temp_r11;
    void *temp_r11_2;
    DispEntry *temp_r9;
    DispEntry *temp_r9_2;

    temp_r11 = arg0->unk0x14;
    arg0->unk0x18 = (s32)lbl_80293350;
    if ((temp_r11 != NULL) && (arg0->unk0x4 & 2)) {
        temp_r9 = (DispEntry *)((Unk_C7387A53 *)temp_r11)->unk0xC;
        ((s32 (*)(void *, s32))temp_r9[1].unk0x4)(
            (char *)temp_r11 + temp_r9[1].unk0x0, 3);
    }
    temp_r11_2 = arg0->unk0x10;
    if (temp_r11_2 != NULL) {
        temp_r9_2 = (DispEntry *)((Unk_C8FEE62D *)temp_r11_2)->unk0x14;
        ((s32 (*)(void *, s32))temp_r9_2[1].unk0x4)(
            (char *)temp_r11_2 + temp_r9_2[1].unk0x0, 3);
    }
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
