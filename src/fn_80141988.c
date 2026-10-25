// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80141988-0x801419CC (68B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_80301A38[];
static s32 fn_800A398C(s32 arg0, s32 arg1);
void fn_80141988(Unk_C7387A53 *arg0) {
    s32 var_r4;

    var_r4 = QB_SKATERCAM0;
    if (arg0->unk0x2E8 == 1) {
        var_r4 = QB_SKATERCAM1;
    }
    fn_800A398C(*(s32 *)&lbl_80301A38, var_r4);
}
