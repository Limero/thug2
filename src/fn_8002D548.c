// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8002D548-0x8002D598 (80B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
typedef struct EventRecord {
    s32 unk0x0;
    s32 id;
} EventRecord;
typedef struct EventTable {
    s32 unk0x0;
    EventRecord *entries[50];
} EventTable;
s32 fn_8002D03C(EventRecord *);
s32 fn_8002D548(s32 arg0, s32 arg1) {
    EventTable *table = (EventTable *)arg0;
    EventRecord **base = &table->entries[0];
    s32 index = 0;

    for (;;) {
        EventRecord *record = *base++;
        if (record->id != arg1) {
            index++;
            if (index <= 49) {
                continue;
            }
            return -1;
        }
        return fn_8002D03C(record);
    }
}
