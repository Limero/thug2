// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800FC56C-0x800FC678 (268B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_8029C7B0[];
extern void fn_80106244(void *);
extern void fn_800FB114(CStruct *, s32);
void fn_800FC56C(CStruct *arg0, s32 arg1) {
    Unk_C8FEE62D *var_r31;
    void *var_r30;
    Unk_C8FEE62D *var_r11;
    Unk_C7387A53 *var_r11_2;
    Unk_0E2E8431 *var_r9;
    void *var_r9_2;
    Unk_F5317C5D *var_r9_3;
    Unk_F5317C5D *var_r9_4;
    s32 var_r0;
    *((void * *)&arg0->unk0xC) = (void *)lbl_8029C7B0;
    var_r11 = *((void * *)&arg0->unk0x10);
    if (var_r11 == (void *)0) goto end_outer;
    var_r9 = *((void * *)&var_r11->unk0xC);
    var_r0 = var_r9->unk0x4;
    var_r31 = var_r9;
    if (var_r0 == -1) var_r31 = (void *)0;
    if (var_r31 == (void *)0) goto after_inner;
    do {
        var_r9 = *((void * *)&var_r31->unk0xC);
        var_r0 = var_r9->unk0x4;
        var_r30 = var_r9;
        if (var_r0 == -1) var_r30 = (void *)0;
        var_r11_2 = *((void * *)&var_r31->unk0x4);
        if (var_r11_2 != (void *)0) {
            var_r9_3 = *((void * *)&var_r11_2->unk0xC);
            ((void (*)(void *, s32))*((void * *)&var_r9_3->unk0xC))((char *)var_r11_2 + var_r9_3->unk0x8, 3);
        }
        if (var_r31 != (void *)0) {
            var_r9_4 = *((void * *)&var_r31->unk0x14);
            ((void (*)(void *, s32))*((void * *)&var_r9_4->unk0xC))((char *)var_r31 + var_r9_4->unk0x8, 3);
        }
        var_r31 = var_r30;
    } while (var_r31 != (void *)0);
after_inner:
    var_r11 = *((void * *)&arg0->unk0x10);
    if (var_r11 != (void *)0) {
        var_r9 = *((void * *)&var_r11->unk0x14);
        ((void (*)(void *, s32))*((void * *)&var_r9->unk0xC))((char *)var_r11 + var_r9->unk0x8, 3);
    }
end_outer:
    fn_80106244(arg0);
    fn_800FB114(arg0, arg1);
}