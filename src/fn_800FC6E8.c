// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800FC6E8-0x800FC770 (136B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_800FC6E8(CStruct *arg0, s32 arg1) {
    CStruct *var_r31;
    CStruct *var_r11;
    Unk_18E8A70D *var_r9;
    s32 var_r0;
    var_r11 = *(void **)((char *)*((void * *)&arg0->unk0x10) + 0xC);
    var_r0 = var_r11->unk0x4;
    var_r31 = var_r11;
    if (var_r0 == -1) var_r31 = 0;
    while (var_r31 != 0) {
        var_r11 = *((void * *)&var_r31->unk0x4);
        var_r9 = *((void * *)&var_r11->unk0xC);
        var_r9->unk0x34((char *)var_r11 + var_r9->unk0x30, arg1);
        var_r9 = *((void * *)&var_r31->unk0xC);
        var_r0 = var_r9->unk0x4;
        var_r31 = var_r9;
        if (var_r0 == -1) var_r31 = 0;
    }
    arg0->unk0x38 = 1;
}