// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A2688-0x800A26DC (84B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-schedule-insns
#include "types.h"
#include "structs.h"
typedef struct DispEntry {
    s16 unk0x0;
    char pad0x2[0x2];
    s32 unk0x4;
} DispEntry;
void fn_800A2688(Unk_9994C3F5 *arg0, Unk_9994C3F5 *arg1) {
    DispEntry *temp_r9;
    s32 d;

    temp_r9 = (DispEntry *)arg1->unk0x8;
    ((s32 (*)(void *))temp_r9[7].unk0x4)((char *)arg1 + temp_r9[7].unk0x0);
    d = arg1->unk0x118;
    arg0->unk0x8 = arg0->unk0x8 + d;
}
