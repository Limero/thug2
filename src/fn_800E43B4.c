// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800E43B4-0x800E43E8 (52B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern s32 fn_80065220(s32);
s32 fn_800E43B4(Unk_31DE137E *arg0) {
    s32 temp_r0;
    s32 var_r3;

    temp_r0 = arg0->unk0x1C;
    var_r3 = 0;
    if (temp_r0 == 0) {
        return var_r3;
    }
    return fn_80065220(temp_r0);
}
