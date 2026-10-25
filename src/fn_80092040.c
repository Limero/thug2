// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80092040-0x80092084 (68B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
typedef struct Record {
    s32 state;
    s32 enabled;
    s32 id;
    char pad[0x54];   /* +0xC .. +0x60 -> 0x60 stride (lbl_80377AD8 is 0x1800 = 64 records) */
} Record;
extern u32 lbl_803017E8;
extern Record lbl_80377AD8[];
void fn_80092040(s32 arg0, s32 arg1) {
    u32 i;
    Record *p;
    i = 0;
    if (i < lbl_803017E8) {
        p = lbl_80377AD8;
        do {
            if (p->id == arg0) {
                p->enabled = arg1;
            }
            i++;
            p++;
        } while (i < lbl_803017E8);
    }
}
