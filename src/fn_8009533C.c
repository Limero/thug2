// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009533C-0x800953AC (112B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-schedule-insns
#include "types.h"
#include "structs.h"
typedef struct DispEntry {
    s16 unk0x0;
    char pad0x2[0x2];
    s32 unk0x4;
} DispEntry;
void fn_8009533C(CStruct *arg0) {
    DispEntry *temp_r9;
    DispEntry *temp_r9_2;
    DispEntry *temp_r9_3;

    temp_r9 = (DispEntry *)arg0->unk0x10;
    ((s32 (*)(void *))temp_r9[2].unk0x4)((char *)arg0 + temp_r9[2].unk0x0);
    temp_r9_2 = (DispEntry *)arg0->unk0x10;
    ((s32 (*)(void *))temp_r9_2[3].unk0x4)((char *)arg0 + temp_r9_2[3].unk0x0);
    temp_r9_3 = (DispEntry *)arg0->unk0x10;
    ((s32 (*)(void *))temp_r9_3[4].unk0x4)((char *)arg0 + temp_r9_3[4].unk0x0);
}
