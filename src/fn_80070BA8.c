// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80070BA8-0x80070BF0 (72B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-schedule-insns
#include "types.h"
#include "structs.h"
typedef struct DispEntry {
    s16 unk0x0;
    char pad0x2[0x2];
    s32 unk0x4;
} DispEntry;
void fn_80070BA8(Unk_C8FEE62D *arg0) {
    DispEntry *temp_r9;

    temp_r9 = (DispEntry *)arg0->unk0x20;
    ((s32 (*)(void *))temp_r9[5].unk0x4)((char *)arg0 + temp_r9[5].unk0x0);
    arg0->unk0x14 = 1;
}
