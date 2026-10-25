// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022DBD4-0x8022DC74 (160B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_8022E028(Unk_DB0E2BAB *, s32);
void fn_8022DBD4(CStruct *arg0) {
    s32 var_r9;
    void *temp_r31;
    Unk_89391A04 *temp_r9;
    void *var_r11;

    var_r9 = 1;
    if (!(arg0->unk0x0 & 8)) {
        var_r9 = 0;
    }
    if (var_r9 != 0) {
        fn_8022E028(arg0, 0);
    }
    var_r11 = arg0->unk0xC;
    if (var_r11 != NULL) {
        do {
            temp_r31 = ((CStruct *)var_r11)->unk0x8;
            if (var_r11 != NULL) {
                temp_r9 = ((CStruct *)var_r11)->unk0xC;
                ((s32 (*)(void *, s32))temp_r9->unk0x14)(var_r11 + temp_r9->unk0x10, 3);
            }
            var_r11 = temp_r31;
        } while (var_r11 != NULL);
    }
    arg0->unk0xC = NULL;
    arg0->unk0x0 = (s32) (arg0->unk0x0 & QB_UNKNOWN_0xFFFFFFFD);
}