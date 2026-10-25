// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80068760-0x800687D8 (120B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void *fn_80068760(CStruct *arg0, s32 arg1) {
    Unk_C7387A53 *temp_r9;
    Unk_52F5DCA2 *var_r3;
    void *var_r9;
    temp_r9 = arg0->unk0x10;
    if (temp_r9 != NULL) {
        var_r9 = temp_r9->unk0xC;
        if (((CStruct *)var_r9)->unk0x4 == -1) {
            var_r9 = NULL;
        }
        var_r3 = (var_r9 != NULL) ? var_r9 - 0xC : NULL;
        if (var_r3 != NULL) {
            do {
                if (var_r3->unk0xF8 == arg1) {
                    return var_r3;
                }
                var_r9 = var_r3->unk0x18;
                if (((CStruct *)var_r9)->unk0x4 == -1) {
                    var_r9 = NULL;
                }
                var_r9 = (var_r9 != NULL) ? var_r9 - 0xC : NULL;
                var_r3 = var_r9;
            } while (var_r3 != NULL);
        }
    }
    return NULL;
}
