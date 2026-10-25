// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80196564-0x801965D4 (112B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_80196564(Unk_C8FEE62D *arg0) {
    s32 temp_r3;
    s32 var_r30;

    var_r30 = 0;
    if (((Unk_89391A04 *)arg0->unk0x14)->unk0x24(
            (char *)arg0 + ((Unk_89391A04 *)arg0->unk0x14)->unk0x20) != 0) {
        temp_r3 = ((Unk_89391A04 *)arg0->unk0x14)->unk0x9C(
            (char *)arg0 + ((Unk_89391A04 *)arg0->unk0x14)->unk0x98);
        var_r30 = (temp_r3 == 0);
    }
    return var_r30;
}
