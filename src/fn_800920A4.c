// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800920A4-0x80092154 (176B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -lang=cxx
#include "types.h"
#ifdef __cplusplus
extern "C" {
#endif
typedef struct Record {
    s32 state;
    s32 enabled;
    char pad[0x58];
} Record;
extern u32 lbl_803017E8;
extern u32 lbl_803017EC;
extern Record lbl_80377AD8[];
void fn_80091C88(Record *);
void fn_800920A4(void) {
    u32 hit, processed, cursor, count, offset, current;
    Record *base, *record;

    if (lbl_803017E8 == 0) {
        return;
    }
    hit = 0;
    processed = 0;
    base = lbl_80377AD8;
    while (1) {
        cursor = lbl_803017EC;
        offset = cursor * 0x60;
        record = (Record *)((char *)(offset + (s32)base));
        lbl_803017EC = cursor + 1;
        if (record->state == 0) {
            if (record->enabled != 0) {
                hit += 1;
                fn_80091C88(record);
            }
        }
        current = lbl_803017EC;
        processed += 1;
        count = lbl_803017E8;
        if (current >= count) {
            lbl_803017EC = 0;
        }
        if (processed < count) {
            if (hit <= 3) {
                continue;
            }
        }
        break;
    }
}
#ifdef __cplusplus
}
#endif
