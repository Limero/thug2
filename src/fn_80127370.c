// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80127370-0x80127438 (200B). Byte-identical.
#include "types.h"
#include "structs.h"
void *fn_80125480(s32);
void *fn_8009F4C4(s32);
void *fn_801252BC(Unk_5D1D68CC *);
void fn_80126808(Unk_80577C09 *, Unk_5D1D68CC *, s32);
void fn_80127438(CStruct *, CStruct *);
void fn_80127370(CStruct *arg0, CStruct *arg1, s32 arg2) {
    s32 temp_r30;
    s32 var_r30;
    Unk_1D62F22E *temp_r3;
    CStruct *var_r31;

    var_r31 = arg0->unk0x4;
    if (var_r31 != NULL) {
        do {
            var_r30 = 0;
            if (((s32) var_r31->unk0x4 == 0) && ((s32) (var_r31->unk0x0 & 0x7F0000) == 0xD0000)) {
                temp_r3 = fn_80125480(var_r31->unk0x8);
                if ((temp_r3 != NULL) && ((s32) *((s8 *)&temp_r3->unk0x2) == 0xA)) {
                    fn_80127370(temp_r3->unk0xC, arg1, arg2 + 1);
                    var_r30 = 1;
                }
            }
            if (var_r30 == 0) {
                temp_r30 = fn_801252BC(fn_8009F4C4(0x10));
                fn_80126808(temp_r30, var_r31, 0);
                fn_80127438(arg1, temp_r30);
            }
            var_r31 = var_r31->unk0xC;
        } while (var_r31 != NULL);
    }
}
