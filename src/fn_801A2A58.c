// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A2A58-0x801A2B1C (196B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_801A26E0(Unk_31DE137E *, s32);
void fn_801A27CC(Unk_C7387A53 *, Unk_C8FEE62D *);
void fn_801A2A58(s32 arg0) {
    s32 var_r9;
    CStruct *temp_r30;
    CStruct *temp_r9;
    CStruct *temp_r9_2;
    Unk_F5317C5D *temp_r9_3;
    void *var_r11;
    void *var_r31;

    var_r9 = 1;
    temp_r30 = arg0 + 0x58;
    if ((s32) temp_r30->unk0x10 == temp_r30) {
        var_r9 = 0;
    }
    if (var_r9 != 0) {
        fn_801A27CC(arg0, fn_801A26E0(arg0, 0));
    }
    temp_r9 = temp_r30->unk0xC;
    if ((s32) temp_r9->unk0x4 == -1) {
        var_r11 = NULL;
    } else {
        var_r11 = temp_r9;
    }
    if (var_r11 != NULL) {
        do {
            temp_r9_2 = ((Unk_C8FEE62D *)var_r11)->unk0xC;
            if ((s32) temp_r9_2->unk0x4 == -1) {
                var_r31 = NULL;
            } else {
                var_r31 = temp_r9_2;
            }
            if (var_r11 != NULL) {
                temp_r9_3 = ((Unk_C8FEE62D *)var_r11)->unk0x14;
                ((s32 (*)(void *, s32))temp_r9_3->unk0xC)(var_r11 + temp_r9_3->unk0x8, 3);
            }
            var_r11 = var_r31;
        } while (var_r11 != NULL);
    }
}
