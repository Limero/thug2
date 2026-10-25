// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801367D8-0x80136888 (176B). Byte-identical.
#include "types.h"
#include "structs.h"

extern char lbl_8039D940[];
s32 DVDCancel(void *);

bool fn_801367D8(void) {
    char *base = lbl_8039D940;
    register char *p __asm__("r3");
    Unk_74BF3C95 *t;
    s32 temp_r0;
    s32 var_r30;
    s32 var_ctr;
    s32 var_z;
    register s32 var_idx __asm__("r11");

    if (((Unk_74BF3C95 *)base)->unk0xAC != 0) {
        temp_r0 = ((Unk_74BF3C95 *)base)->unk0xBC;
        var_r30 = 0;
        ((Unk_74BF3C95 *)base)->unk0xB4 = var_r30;
        if (temp_r0 != 0) {
            DVDCancel(base + 8);
            ((Unk_74BF3C95 *)base)->unk0xBC = var_r30;
        }
        p = base + 0xF8;
        var_z = 0;
        var_idx = 0;
        var_ctr = 10;
        do {
            *(s32 *)(p + var_idx) = var_z;
            var_idx += 0x10;
            var_ctr -= 1;
        } while (var_ctr != 0);
        __asm__("" : : "r"(base));
        t = lbl_8039D940;
        t->unk0xCC = t->unk0xDC;
        t->unk0xD0 = t->unk0xE0;
        t->unk0xD4 = 0;
        t->unk0xB0 = 0;
        t->unk0xE4 = 0;
        ((Unk_CF07DF0D *)t)->unk0xE8 = 0;
        return true;
    }
    return false;
}
