// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801567D8-0x801568B8 (224B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 fn_801259C8(s32, s32);
extern s32 fn_80129528(CStruct *, s32);
extern s32 GetInteger(CStruct *, s32, s32 *, s32);
extern s32 GetText(CStruct *, void *, void *, s32);
extern s32 fn_800551B4(s32);
extern void fn_80060490(s32, s32, s32, s32, s32, s32, s32, s32);
extern void fn_800551D4(void *);
void fn_801567D8(s32 arg0) {
    s32 sp8[4];
    s32 temp_r30;
    s32 temp_r30_2;
    u32 var_r31;
    CStruct *temp_r3;

    var_r31 = 0U;
    temp_r3 = fn_801259C8(arg0, 0);
    if (var_r31 < (u32) *((u32 *)&temp_r3->unk0x4)) {
        do {
            temp_r30 = fn_80129528(temp_r3, var_r31);
            sp8[2] = 0;
            GetInteger(temp_r30, QB_ALLOW_RANDOM, &sp8[2], 0);
            if ((sp8[2] != 0) && (GetText(temp_r30, QB_MESH, &sp8[3], 0) != 0)) {
                temp_r30_2 = fn_800551B4(1);
                sp8[0] = 0;
                fn_80060490(temp_r30_2, sp8[3], 0, 1, 0, 0, 0, 1);
                fn_800551D4(temp_r30_2);
            }
            var_r31 += 1;
        } while (var_r31 < (u32) *((u32 *)&temp_r3->unk0x4));
    }
}
