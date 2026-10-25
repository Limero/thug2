// Promoted from src/wip 2026-10-09 (mwcc region). family=hand range=0x8025F0D4-0x8025F1D4 size=256B
// range 0x8025F0D4-0x8025F1D4 size=0x100 (256B).
// Byte-identical: verified with full SDA/ADDR16 reloc resolution
// against the retail DOL (mwcc GC/1.3.2 + cflags_dolphin).
#include "types.h"

extern u32 *lbl_803CAB64;
extern u32 lbl_803CAB68;
extern u32 lbl_803CAB6C;
extern u32 *lbl_803CAB60;
extern s32 fn_8025EA60(void);
extern s32 fn_8025EA58(void);

u32 fn_8025F0D4(u32 arg0, s32 arg1) {
    u32 pages;
    u32 cap;
    u32 offset;
    u32 va;

    pages = (u32)fn_8025EA60() >> 12;
    cap = pages + ((u32)fn_8025EA58() >> 12);
    if (lbl_803CAB6C < pages) {
        lbl_803CAB6C = pages;
    }
    if (lbl_803CAB68 + (u32)arg1 > (u32)fn_8025EA58()) {
        return 0;
    }
    for (offset = 0; offset < (u32)arg1; offset += 0x1000) {
        va = arg0 + offset;
        do {
            lbl_803CAB6C = lbl_803CAB6C + 1;
            if (lbl_803CAB6C >= cap) {
                lbl_803CAB6C = pages;
            }
        } while (lbl_803CAB60[lbl_803CAB6C] != 0);
        lbl_803CAB60[lbl_803CAB6C] = va;
        lbl_803CAB64[(va >> 12) & 0x1FFF] = lbl_803CAB6C << 12;
        lbl_803CAB68 = lbl_803CAB68 + 0x1000;
    }
    return 1;
}
