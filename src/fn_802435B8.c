// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802435B8-0x802435EC (52B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_803060AC[];
void fn_802435B8(Unk_B3CC37CC *arg0, s32 arg1) {
    u8 *var_r9;
    s32 var_ctr;
    s32 zero;

    var_ctr = 0x20;
    arg0->unk0x0 = 0x7D0;
    zero = 0;
    var_r9 = (u8 *)arg0 + 0x80;
    do {
        *(s32 *)var_r9 = zero;
        var_r9 -= 4;
        var_ctr -= 1;
    } while (var_ctr != 0);
    arg0->unk0x104 = arg1;
    *(void * *)&lbl_803060AC = arg0;
}
