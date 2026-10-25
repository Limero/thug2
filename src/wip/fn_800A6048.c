// PARKED 2026-10-03 — base 5.1% (752 B, 198 words).  Random-sample pick.
// m2c best guess retained; residual is prototype/decode, not codegen.  No
// hash switch in the want, so recipe 7w does not apply.
//
// family=m2c range=0x800A6048-0x800A6338 size=752B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum(s32, s32);
extern char lbl_80300434[];
extern char lbl_80301A78[];
static s32 sp1C;

bool ScriptLaunchEvent(CStruct *arg0, Unk_FFAD6788 *arg1) {
    s32 sp28;
    s32 sp20;
    void *sp1C;
    s32 sp18;
    f32 sp14;
    s32 sp10;
    s32 spC;
    s32 sp8;
    s32 var_r4;
    s32 var_r4_2;
    s32 var_r4_3;
    s32 temp_r27;
    s32 temp_r30;
    s32 temp_r30_2;
    s32 var_cr0_eq;
    s32 var_cr0_eq_2;
    s32 var_r0;
    s32 var_r0_2;
    u32 temp_r29;
    u32 temp_r4;
    u32 var_r31;
    CScript *temp_r9;
    CScript *temp_r9_2;
    Unk_9994C3F5 *var_r31_2;

    sp28 = 0;
    temp_r30 = *(s32 *)lbl_80300434;
    if (ResolveComplexID(temp_r30, arg0, QB_TARGET, &sp8, 0x80300000) != 0) {

    } else {
        if ( (arg1 != NULL) && (temp_r9 = arg1->unk0xBC, ((temp_r9 == NULL) == 0))) {
            var_r0 = temp_r9->unk0x18;
        } else {
            var_r0 = QB_SYSTEM;
        }
        sp8 = var_r0;
    }
    if (ResolveComplexID(temp_r30, arg0, QB_SOURCE, &spC) != 0) {

    } else {
        if ((arg1 != NULL) && (temp_r9_2 = arg1->unk0xBC, ((temp_r9_2 == NULL) == 0))) {
            var_r0_2 = temp_r9_2->unk0x18;
        } else {
            var_r0_2 = QB_SYSTEM;
        }
        spC = var_r0_2;
    }
    sp10 = 0;
    GetStructure_2(arg0, QB_DATA, &sp10, 0);
    temp_r27 = ContainsFlag(arg0, QB_BROADCAST);
    sp14 = *(f32 *)0x802980AC;
    fn_80128CE0(arg0, QB_RADIUS, &sp14, 0);
    temp_r30_2 = *(s32 *)lbl_80301A78;
    if (GetChecksum_2(arg0, QB_TYPE, &sp18, 0) != 0) {
        
        fn_800A5A14(temp_r30_2, (((arg1 != NULL) && ((s32) arg1->unk0xC8 != 0)) == 0 ));
        fn_800A54AC(temp_r30_2, sp18, sp8, spC, sp10, temp_r27, sp14);
    } else if (GetArray(arg0, QB_TYPE, &sp1C, 0) != 0) {
        var_r31 = 0U;
        temp_r29 = ((CStruct *)sp1C)->unk0x4;
        var_cr0_eq = temp_r29 == 0U;
        if (temp_r29 > 0U) {
            0;
            do {
                var_r4_2 = 0;
                if ((var_cr0_eq == 0) && ((s32) arg1->unk0xC8 != 0)) {
                    var_r4_2 = 1;
                }
                fn_800A5A14(temp_r30_2, var_r4_2);
                temp_r4 = var_r31;
                var_r31 += 1;
                fn_800A54AC(temp_r30_2, GetChecksum(sp1C, temp_r4), sp8, spC, sp10, temp_r27, sp14);
                var_cr0_eq = var_r31 == temp_r29;
            } while (var_r31 < temp_r29);
        }
    } else if (GetStructure_2(arg0, QB_TYPE, &sp20, 0) != 0) {
        var_r31_2 = fn_80127358(sp20, NULL);
        if (var_r31_2 != NULL) {
            var_cr0_eq_2 = arg1 == NULL;
            0;
            do {
                var_r4_3 = 0;
                0;
                if ((var_cr0_eq_2 == 0) && ((s32) arg1->unk0xC8 != 0)) {
                    var_r4_3 = 1;
                }
                fn_800A5A14(temp_r30_2, var_r4_3);
                fn_800A54AC(temp_r30_2, var_r31_2->unk0x8, sp8, spC, sp10, temp_r27, sp14);
                var_r31_2 = fn_80127358(sp20, var_r31_2);
                var_cr0_eq_2 = var_r31_2 == NULL;
            } while (var_cr0_eq_2 == 0);
        }
    }
    0;
    return true;
}