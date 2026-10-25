// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A17EC-0x800A1808 (28B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_800A17EC(Unk_31DE137E *arg0) {
    s32 var_r3;

    var_r3 = 1;
    if (!(arg0->unk0x114 & 1)) {
        var_r3 = 0;
    }
    return var_r3 ^ 1;
}
