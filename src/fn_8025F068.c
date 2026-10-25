// Promoted from src/wip 2026-10-09 (mwcc region). family=hand range=0x8025F068-0x8025F0D4 size=108B
// range 0x8025F068-0x8025F0D4 size=0x6C (108B).
// Byte-identical: verified with full SDA/ADDR16 reloc resolution
// against the retail DOL (mwcc GC/1.3.2 + cflags_dolphin).
#include "types.h"

extern u32 lbl_803CAB58;
extern s32 lbl_803CA370;
extern s32 fn_8025EA50(void);
extern s32 fn_8025F730(s32 arg0);

u32 fn_8025F068(void) {
    u32 cur;

    for (;;) {
        cur = lbl_803CAB58;
        lbl_803CAB58 = cur + 1;
        if (lbl_803CAB58 >= (u32)fn_8025EA50()) {
            lbl_803CA370 = 0;
            lbl_803CAB58 = 0;
        }
        if (fn_8025F730((s32)cur) == 0) {
            break;
        }
    }
    return cur;
}
