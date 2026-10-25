// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80127174-0x8012720C (152B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_801266EC(Unk_5D1D68CC *);
void fn_80117E28(void *);
void fn_80127174(CStruct *arg0, s32 arg1, s32 arg2) {
    void *temp_r30;
    Unk_C7387A53 *var_r29;
    Unk_D1EBF41B *var_r31;

    var_r31 = arg0->unk0x4;
    var_r29 = NULL;
    if (var_r31 != NULL) {
        do {
            temp_r30 = var_r31->unk0xC;
            if (((s32) var_r31->unk0x4 == arg1) && ((s32) (var_r31->unk0x0 & 0x7F) == arg2)) {
                if (var_r29 != NULL) {
                    var_r29->unk0xC = temp_r30;
                } else {
                    arg0->unk0x4 = temp_r30;
                }
                fn_801266EC(var_r31);
                fn_80117E28(var_r31);
            } else {
                var_r29 = var_r31;
            }
            var_r31 = temp_r30;
            __asm__("" : "=r"(temp_r30) : "0"(temp_r30));
        } while (temp_r30 != NULL);
    }
}