// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A5BF4-0x800A5CAC (184B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_800A6DB8(s32, s32, s32);
void fn_800A5E8C(s32, s32);
void fn_800A6EFC(s32, s32);
void fn_800A6FB4(s32);
extern char lbl_802980E0[];
void fn_800A5BF4(CStruct *arg0, s32 arg1, s32 arg2) {
    s32 sp8;
    s32 temp_r3;
    s32 var_r9;
    Unk_C8FEE62D *temp_r31;

    sp8 = arg1;
    temp_r3 = fn_800A6DB8(arg0->unk0x10, &sp8, 1);
    if (temp_r3 != 0) {
        fn_800A5E8C(temp_r3, arg2);
        temp_r31 = temp_r3 + 4;
        var_r9 = 1;
        if (temp_r31->unk0x10 == (s32)temp_r31) {
            var_r9 = 0;
        }
        if (var_r9 == 0) {
            fn_800A6EFC(arg0->unk0x10, &sp8);
            temp_r31->unk0x14 = (s32)lbl_802980E0;
            *(s32 *)(*(s32 *)((char *)((char *)temp_r31) + 0x10) + 0xC) =  temp_r31->unk0xC;
            *(s32 *)(*(s32 *)((char *)((char *)temp_r31) + 0xC) + 0x10) =  temp_r31->unk0x10;
            temp_r31->unk0xC = temp_r31;
            temp_r31->unk0x10 = temp_r31;
            fn_800A6FB4(temp_r3);
        }
    }
}
