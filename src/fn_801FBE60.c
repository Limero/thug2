// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801FBE60-0x801FBEDC (124B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_802AE5B4[];
s32 sprintf();
s32 Script_GenerateCRC(s32);
void *fn_801FBE60(Unk_C7387A53 *arg0, s32 arg1) {
    char sp8[0x38];
    s32 var_r30;
    CStruct *var_r31;

    var_r31 = arg0->unk0x24;
    var_r30 = 0;
    while (var_r31 != NULL) {
        sprintf(sp8, lbl_802AE5B4, var_r30);
        if (arg1 == Script_GenerateCRC(sp8)) {
            return var_r31;
        }
        var_r31 = var_r31->unk0x4;
        var_r30 += 1;
    }
    return NULL;
}
