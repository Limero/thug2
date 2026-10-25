// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801FA494-0x801FA4F0 (92B). Byte-identical.
#include "types.h"
#include "structs.h"

extern void fn_801FBF44(Unk_C7387A53 * arg0, Unk_C8FEE62D * arg1);
extern void fn_801F962C(Unk_C7387A53 * arg0);

void fn_801FA494(Unk_C7387A53 *arg0) {
    CStruct *var_r31;

    fn_801FBF44(arg0, 0);
    var_r31 = arg0->unk0x24;
    while (var_r31 != 0) {
        fn_801F962C((void *)var_r31);
        var_r31 = var_r31->unk0x4;
    }
    fn_801FBF44(arg0, 1);
}
