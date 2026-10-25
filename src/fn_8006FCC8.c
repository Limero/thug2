// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8006FCC8-0x8006FD50 (136B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8006FF0C(CStruct *);
s32 fn_8006FFBC(CStruct *, s32 *);
void fn_8006FFA8(CStruct *);
void fn_8006FCC8(s32 *arg0) {
    void *temp_r30;
    Unk_F5317C5D *temp_r9;
    void *var_r31;

    fn_8006FFA8(*arg0);
    var_r31 = fn_8006FFBC(*arg0, 0);
    if (var_r31 != NULL) {
        do {
            temp_r30 = fn_8006FFBC(*arg0, 0);
            if (var_r31 != NULL) {
                temp_r9 = ((Unk_31DE137E *)var_r31)->unk0x60;
                ((s32 (*)(void *, s32))temp_r9->unk0xC)(var_r31 + temp_r9->unk0x8, 3);
            }
            var_r31 = temp_r30;
        } while (var_r31 != NULL);
    }
    fn_8006FF0C(*arg0);
}
