// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80231248-0x80231284 (60B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_80231248(Unk_C7387A53 *arg0) {
    s32 var_r9;

    var_r9 = 1;
    if (!(arg0->unk0x4C & 2)) {
        var_r9 = 0;
    }
    if (var_r9 == 0) {
        fn_80232614();
    }
}
