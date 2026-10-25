// GetCacheBytes @ 0x8001B5E4  (retail p_file.o::GetCacheBytes, 120B)
// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001B5E4-0x8001B658 (116B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

void DCFlushRange(s32, s32);
void *memcpy(void *, void *, s32);
extern s32 memcpy_u() __asm__("memcpy");

void GetCacheBytes(void *arg0, void *arg1, s32 arg2) {
    s32 temp_r5;
    void *temp_r28;

    temp_r28 = (char *) arg0 + 4;
    memcpy(arg1, temp_r28, arg2);
    DCFlushRange((s32) arg1, arg2);
    temp_r5 = ((Unk_C7387A53 *) arg0)->unk0x70 - arg2;
    ((Unk_C7387A53 *) arg0)->unk0x70 = temp_r5;
    if (temp_r5 != 0) {
        memcpy_u(temp_r28, (char *) (arg2 + (s32) arg0) + 4, temp_r5);
    }
}
