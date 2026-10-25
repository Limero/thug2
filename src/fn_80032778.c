// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80032778-0x800327B8 (64B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-gcse
#include "types.h"
#include "structs.h"
void *fn_80032778(Unk_C7387A53 *arg0, s32 arg1) {
    s32 count;
    s32 i;
    CStruct **entries;
    CStruct *entry;

    i = 0;
    if (i < arg0->unk0x58) {
        count = arg0->unk0x58;
        entries = (CStruct **)((char *)arg0 + 0x40);
        do {
            entry = entries[i];
            if ((s32)entry->unk0x10 == arg1) {
                return entry;
            }
            i++;
        } while (i < count);
    }
    return NULL;
}
