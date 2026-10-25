// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80195668-0x801957E0 (376B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305EAC;
s32 fn_801745B4(s32);
s32 GetStructure_2(CStruct *, s32, s32 *, s32);
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 fn_801403CC(void *);
s32 fn_80182B5C(s32, s32);
s32 fn_8017EC44(CStruct *, s32);
s32 fn_80128978(void *, s32);
s32 AddInteger(CStruct *, s32, s32);
s32 CStruct_new(s32);
s32 CStruct_ctor(s32);
s32 fn_8018E24C(Unk_C7387A53 *);
void AddChecksum(CStruct *, s32, s32);
s32 Script_RunScript(s32, s32, s32, s32, s32);
s32 CStruct_delete(CStruct *, s32);
void fn_80195668(Unk_C7387A53 *arg0) {
    void *sp8;
    s32 spC;
    s32 temp_r28;
    Unk_FFAD6788 *temp_r3;
    register s32 temp_r30 __asm__("r30");
    s32 var_r26;
    s32 var_r29;

    var_r26 = 0;
    var_r29 = 0;
    temp_r30 = fn_801745B4(lbl_80305EAC);
    GetStructure_2(arg0->unk0x20, QB_COMPLETEDGAPS, &sp8, 1);
    GetInteger(arg0->unk0x20, QB_UNKNOWN_0xF1E59083, &spC, 1);
    temp_r3 = fn_801403CC(temp_r30);
    temp_r28 = temp_r3->unk0x68;
    while (var_r29 < temp_r28) {
        if (fn_80182B5C(temp_r3, var_r29) != 0) {
            temp_r30 = fn_8017EC44(temp_r3, var_r29);
            if (fn_80128978(sp8, temp_r30) == 0) {
                var_r26 = 1;
                AddInteger(sp8, temp_r30, 1);
                spC += 1;
            }
        }
        var_r29 += 1;
    }
    AddInteger(arg0->unk0x20, QB_UNKNOWN_0xF1E59083, spC);
    AddInteger(arg0->unk0x20, QB_NUMBER_COLLECTED, spC);
    if (var_r26 != 0) {
        temp_r30 = CStruct_ctor(CStruct_new(8));
        AddChecksum(temp_r30, QB_GOAL_ID, fn_8018E24C(arg0));
        Script_RunScript(QB_UNKNOWN_0x851AA6B8, temp_r30, 0, 0, 0);
        if (temp_r30 != 0) {
            CStruct_delete(temp_r30, 3);
        }
    }
}
