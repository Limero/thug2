// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80069D24-0x80069D68 (68B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
typedef struct {
    char pad0x0[0x13C];
    s32 unk0x13C[31];
    Unk_C6B642AC *unk0x1B8;
} Unk_69D24;

void fn_80069D24(Unk_69D24 *arg0, s32 arg1, s32 *arg2) {
    Unk_C6B642AC *temp_r9;

    ((s32 *)arg0)[0x4F + arg1] = *arg2;
    temp_r9 = arg0->unk0x1B8;
    ((void (*)(void *))temp_r9->unk0x3C)((char *)arg0 + temp_r9->unk0x38);
}
