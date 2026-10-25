// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8023E290-0x8023E33C (172B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 fn_8023DDA8(Unk_31DE137E * arg0);
extern void *fn_8023897C(void * arg0, s32 arg1, s32 * arg2);
extern void fn_8023DE20(Unk_31DE137E * arg0, s32 arg1);
extern void fn_8023C7A4(CStruct * arg0);
extern void fn_8023EDE4(Unk_C7387A53 * arg0, s32 arg1);
extern void fn_8023E724(CStruct * arg0);

void fn_8023E290(CStruct *arg0) {
    Unk_C7387A53 *var_r28;
    s32 var_r29;
    s32 var_r30;
    Unk_51AF0E3F *temp_r3;

    if (fn_8023DDA8(arg0) != 0) {
        var_r29 = *(s32 *)(arg0->unk0x0 + 0x13C90);
        var_r28 = 0;
        for (var_r30 = 0; var_r30 < var_r29; var_r30++) {
            temp_r3 = fn_8023897C(arg0->unk0x0, var_r30, (char *)arg0 + 0x70);
            if (temp_r3->unk0x151 != 0) {
                arg0->unk0x6C = var_r30;
                var_r28 = (s32)temp_r3;
                break;
            }
        }
        var_r28->unk0x14C = 0;
        fn_8023DE20(arg0, 0);
        fn_8023C7A4(arg0);
        fn_8023EDE4(arg0, 5);
        fn_8023E724(arg0);
    }
}
