// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800913C4-0x80091420 (92B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 Mem_NewZero(s32);
extern char lbl_80296F28[];
void *fn_800913C4(void) {
    s32 var_ctr;
    s32 var_ctr_2;
    Unk_7A675EAB *temp_r31;

    temp_r31 = Mem_NewZero(0x2C0);
    fn_80069130();
    var_ctr = 4;
    temp_r31->unk0x1B8 = (s32)lbl_80296F28;
    do {
        var_ctr -= 1;
    } while (var_ctr != 0);
    var_ctr_2 = 4;
    do {
        var_ctr_2 -= 1;
    } while (var_ctr_2 != 0);
    return temp_r31;
}