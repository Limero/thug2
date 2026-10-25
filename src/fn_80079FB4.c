// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80079FB4-0x8007A044 (144B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
typedef struct DispEntry { s16 unk0x0; char pad0x2[0x2]; s32 unk0x4; } DispEntry;
void fn_80079FB4(Unk_9994C3F5 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    DispEntry *temp_r9;
    DispEntry *temp_r9_2;
    s32 res;

    temp_r9 = (DispEntry *)arg0->unk0x8;
    if (((s32 (*)(void *))temp_r9[43].unk0x4)((char *)arg0 + temp_r9[43].unk0x0) != 0) {
        temp_r9_2 = (DispEntry *)arg0->unk0x8;
        res = ((s32 (*)(void *))temp_r9_2[43].unk0x4)((char *)arg0 + temp_r9_2[43].unk0x0);
        *(s32 *)(res + (((arg3 * (u16)(1 << *(u8 *)(*(s32 *)((char *)arg0 + 0xC) + 6))) + arg2) * 4)) = arg1;
    }
}
