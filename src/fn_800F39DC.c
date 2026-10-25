// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F39DC-0x800F3A1C (64B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-schedule-insns
#include "types.h"
#include "structs.h"
typedef struct DispEntry {
    s16 unk0x0;
    char pad0x2[0x2];
    s32 unk0x4;
} DispEntry;
void fn_800F39DC(void *arg0, void *arg1, s32 arg2, Unk_C7387A53 *arg3, s32 arg4) {
    DispEntry *temp_r9;

    if (arg4 == 0) {
        arg3->unk0x28 = arg2;
        temp_r9 = (DispEntry *)arg3->unk0x50;
        ((s32 (*)(void *))temp_r9[18].unk0x4)((char *)arg3 + temp_r9[18].unk0x0);
    }
}
