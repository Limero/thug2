// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80060DEC-0x80060E4C (96B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_80060DEC(CStruct *arg0, s32 arg1) {
    s32 var_r3;
    Unk_89391A04 *temp_r9;

    var_r3 = 0;
    if (arg1 != arg0->unk0x4) {
        temp_r9 = (Unk_89391A04 *)arg0->unk0x50;
        var_r3 = temp_r9->unk0x24((char *)arg0 + temp_r9->unk0x20);
        if (var_r3 != 0) {
            arg0->unk0x4 = arg1;
        }
    }
    return var_r3;
}
