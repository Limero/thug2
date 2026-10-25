// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A5CAC-0x800A5D90 (228B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_802980E0[];
void fn_800A6FB4(void *);
void fn_800A6EFC(CStruct *, s32 *);
void fn_800A5E8C(CStruct *, s32);
s32 fn_800A707C(CStruct *, s32 *);
void fn_800A7068(CStruct *);
void fn_800A5CAC(CStruct *arg0, s32 arg1) {
    s32 spC;
    s32 sp8;
    s32 temp_r29;
    s32 var_r31;
    s32 neq;
    Unk_C8FEE62D *temp_r30;
    fn_800A7068(arg0->unk0x10);
    var_r31 = fn_800A707C(arg0->unk0x10, &sp8);
    if (var_r31 != 0) {
        do {
            temp_r30 = var_r31 + 4;
            temp_r29 = fn_800A707C(arg0->unk0x10, &spC);
            fn_800A5E8C(var_r31, arg1);
            neq = temp_r30->unk0x10 != temp_r30;
            if (neq == 0) {
                fn_800A6EFC(arg0->unk0x10, &sp8);
                if (var_r31 != 0) {
                    temp_r30->unk0x14 = (s32)lbl_802980E0;
                    *(s32 *)(*(s32 *)((char *)((char *)temp_r30) + 0x10) + 0xC) =  temp_r30->unk0xC;
                    *(s32 *)(*(s32 *)((char *)((char *)temp_r30) + 0xC) + 0x10) =  temp_r30->unk0x10;
                    temp_r30->unk0xC = temp_r30;
                    temp_r30->unk0x10 = temp_r30;
                    fn_800A6FB4(var_r31);
                }
            }
            var_r31 = temp_r29;
            sp8 = spC;
        } while (var_r31 != 0);
    }
}
