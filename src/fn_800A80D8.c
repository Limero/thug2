// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A80D8-0x800A8288 (432B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_800A807C(void);
s32 fn_800F0FE4(void);
void AddInteger(CStruct *, s32, s32);
s32 fn_800F0648(s32, s32);
s32 fn_800F100C(void);
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 fn_80128978(s32, s32);
s32 fn_800F054C(s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
void fn_800F0FB8(s32);
void fn_800A80D8(CStruct *arg0) {
    s32 sp10;
    s32 spC;
    s32 sp8;
    s32 temp_cr0_eq;
    s32 var_r29;
    s32 var_r30;
    s32 var_r31;

    if ((s32) arg0->unk0x0 != 0) {
        fn_800A807C();
        arg0->unk0x8 = 0;
        fn_800F0FB8(0);
        var_r29 = fn_800F0FE4();
        if (var_r29 != 0) {
            do {
                sp8 = 0;
                GetChecksum_2(var_r29, QB_CLASS, &sp8, 0);
                if (sp8 == QB_RAILNODE || sp8 == QB_CLIMBINGNODE) {
                    ;
                } else if (sp8 == QB_WAYPOINT && GetChecksum_2(var_r29, QB_TYPE, &spC, 0) != 0 && spC == -QB_UNKNOWN_0x345EF006) {
                    ;
                } else {
                    temp_cr0_eq = fn_800F054C(var_r29) == 0;
                    sp10 = 0;
                    if (((temp_cr0_eq == 0) || (sp8 == QB_WAYPOINT)) && (fn_80128978(var_r29, QB_PATHNUM) == 0)) {
                        var_r30 = arg0->unk0x8;
                        var_r31 = var_r29;
                        goto loop_13;
loop_back:
                        var_r31 = fn_800F0648(var_r31, 0);
loop_13:
                        if (GetInteger(var_r31, QB_PATHNUM, &sp10, 0) != 0) {
                            if (sp10 != var_r30) {
                                var_r30 = sp10;
                                var_r31 = var_r29;
                                goto block_16;
                            }
                        } else {
block_16:
                            AddInteger(var_r31, QB_PATHNUM, var_r30);
                            if (fn_800F054C(var_r31) != 0) {
                                goto loop_back;
                            }
                        }
                        if (var_r30 == (s32) arg0->unk0x8) {
                            arg0->unk0x8 = (s32) (var_r30 + 1);
                        }
                    }
                }
                var_r29 = fn_800F0FE4();
            } while (var_r29 != 0);
        }
        fn_800F100C();
    }
}
