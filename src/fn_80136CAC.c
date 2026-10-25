// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80136CAC-0x80136D30 (132B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// Crack note (doc-24 store/call-placement coin) preserved in src/wip/fn_80136CAC.c
#include "types.h"
#include "structs.h"
extern char lbl_8039D940[];
s32 DVDClose(void *);

bool fn_80136CAC(void) {
    char *base = lbl_8039D940;
    s32 temp_r30;
    s32 temp_r3;

    if (((((Unk_74BF3C95 *)base)->unk0xAC != 0) &&
         (((Unk_74BF3C95 *)base)->unk0xB4 == 0)) &&
        ((temp_r30 = ((Unk_74BF3C95 *)base)->unk0xBC) == 0)) {
        ((Unk_74BF3C95 *)base)->unk0xAC = temp_r30;
        DVDClose(base + 8);
        temp_r3 = ((Unk_74BF3C95 *)base)->unk0xA8;
        if (temp_r3 != 0) {
            (*(void (**)(s32))(base + 4))(temp_r3);
            ((Unk_74BF3C95 *)base)->unk0xA8 = temp_r30;
        }
        return true;
    }
    return false;
}