// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8013644C-0x801364DC (144B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_8039D940[];
bool fn_8013644C(void) {
    s32 (*temp_r9)(s32);
    register s32 sz __asm__("r31");
    s32 aligned;
    s32 var_ctr;
    s32 var_z;
    s32 var_r3;
    s32 var_r11;
    char *p;
    char *arr;
    char *var_r10;

    p = lbl_8039D940;
    sz = ((Unk_7A9FCCD0 *)p)->unk0x9A;
    temp_r9 = *(s32 (*)(s32)) *(s32 *)&lbl_8039D940;
    aligned = (sz + 0x37) & ~0x1F;
    var_r3 = temp_r9(aligned * 0xA);
    ((Unk_7A9FCCD0 *)p)->unk0x18C = var_r3;
    if (var_r3 == 0) {
        return false;
    }
    var_ctr = 10;
    arr = p + 0xF8;
    var_z = 0;
    var_r10 = arr;
    var_r11 = 0;
    do {
        *(s32 *)(var_r10 - 0xC) = var_r3;
        *(s32 *)(arr + var_r11) = var_z;
        var_r3 += aligned;
        var_r10 += 0x10;
        var_r11 += 0x10;
    } while (--var_ctr != 0);
    return true;
}
