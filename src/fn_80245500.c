// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80245500-0x80245570 (112B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_801F9798(Unk_C7387A53 *);
void fn_801F97DC(Unk_C7387A53 *);
void fn_80243FC8(Unk_C8FEE62D *);
void fn_80245500(CStruct *arg0) {
    CScript *var_r31;
    CStruct *var_r31_2;

    var_r31 = arg0->unk0xC;
    if (var_r31 != NULL) {
        do {
            fn_80243FC8(var_r31);
            var_r31 = var_r31->unk0x18;
        } while (var_r31 != NULL);
    }
    var_r31_2 = arg0->unk0x10;
    if (var_r31_2 != NULL) {
        do {
            fn_801F97DC(var_r31_2);
            fn_801F9798(var_r31_2);
            var_r31_2 = var_r31_2->unk0x4;
        } while (var_r31_2 != NULL);
    }
}
