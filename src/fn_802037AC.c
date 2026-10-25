// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802037AC-0x80203810 (100B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_802AEE10[];
void *fn_802037AC(Unk_C8FEE62D *arg0) {
    s32 *var_r9;
    s32 var_r0;

    fn_8009F53C();
    arg0->unk0x18 = (s32)lbl_802AEE10;
    arg0->unk0x4 = QB_SPECIALITEM;
    var_r9 = (char *)arg0 + 0x20;
    var_r0 = 1;
    do {
        *((s32 *)var_r9) = 0;
        var_r0 -= 1;
        var_r9 -= 1;
    } while (var_r0 >= 0);
    return arg0;
}
