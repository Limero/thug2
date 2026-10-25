// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80125020-0x80125088 (104B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct {
    u32 checksum;
    char *str;
} Entry;

extern u32 lbl_80303188;
extern char* lbl_8030318C;
extern u32 lbl_80303190;
extern Entry *lbl_80303194;
extern bool lbl_80303198;
extern u32 lbl_8030319C;

void* Mem_Alloc_3(u32); // malloc

void fn_80125020(u32 arg0, u32 arg1) {
    lbl_8030319C = arg1;
    lbl_80303190 = arg0;

    lbl_80303188 = (u32)Mem_Alloc_3(arg0);
    lbl_8030318C = (char*)lbl_80303188;

    lbl_80303194 = (Entry*)Mem_Alloc_3(lbl_8030319C * sizeof(Entry));
    lbl_80303198 = 0;
}
