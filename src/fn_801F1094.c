// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F1094-0x801F10F8 (100B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_802ADFE8[];
void *fn_801F1094(Unk_C8FEE62D *arg0) {
    s32 *var_r9;
    s32 var_r0;

    fn_8009F53C();
    arg0->unk0x18 = (s32)lbl_802ADFE8;
    arg0->unk0x4 = QB_SKATERSTATE;
    var_r9 = (char *)arg0 + 0x190;
    var_r0 = 0;
    do {
        *((s32 *)var_r9) = 0;
        var_r0 -= 1;
        var_r9 -= 1;
    } while (var_r0 >= 0);
    return arg0;
}
