// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A269C-0x801A26E0 (68B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_801A269C(Unk_31DE137E *arg0) {
    CStruct *var_r9;
    s32 count = 0;

    var_r9 = arg0->unk0x64;
    if (var_r9->unk0x4 == -1) {
        var_r9 = NULL;
    }
    if (var_r9 != NULL) {
        do {
            var_r9 = var_r9->unk0xC;
            count += 1;
            if (var_r9->unk0x4 == -1) {
                var_r9 = NULL;
            }
        } while (var_r9 != NULL);
    }
    return count;
}
