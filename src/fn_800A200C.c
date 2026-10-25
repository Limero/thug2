// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A200C-0x800A205C (80B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
typedef struct Cell {
    s32 key;
    s32 unk0x4;
} Cell;
typedef struct Tbl {
    char pad0[0x50];
    u32 count;
    Cell cells[1];
} Tbl;
extern s32 lbl_803C9E80[];
s32 fn_800A200C(Tbl *arg0, s32 arg1) {
    u32 i;

    for (i = 0; i < arg0->count; i++) {
        if (arg0->cells[i].key == arg1) {
            return lbl_803C9E80[i];
        }
    }
    return 0;
}
