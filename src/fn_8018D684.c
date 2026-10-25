// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018D684-0x8018D7BC (312B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
void AddInteger(void *, void *, void *);
#include "qb_constants.h"
#include "structs.h"
s32 ContainsFlag(s32, s32);
s32 fn_80127358(CStruct *arg0, Unk_C7387A53 *arg1);
void fn_8018D684(Unk_A9157FE7 *arg0) {
    s32 temp_r29;
    s32 temp_r29_2;
    void *temp_r28;
    void *temp_r3;
    void *temp_r3_2;
    CStruct *var_r31;
    CStruct *var_r31_2;
    CStruct *var_r31_3;
    if (ContainsFlag(arg0->unk0x24, QB_SKATER_FLAGS) != 0) {
        var_r31 = fn_80127358(arg0->unk0x24, NULL);
        if (var_r31 != NULL) {
            do {
                temp_r28 = fn_80127358(arg0->unk0x24, var_r31);
                if ((s32) (var_r31->unk0x0 & 0x7F0000) == 0xA0000) {
                    temp_r29 = var_r31->unk0x8;
                    var_r31_2 = fn_80127358(temp_r29, NULL);
                    if (var_r31_2 != NULL) {
                        do {
                            temp_r3 = fn_80127358(temp_r29, var_r31_2);
                            if ((s32) var_r31_2->unk0x4 != QB_NUM_FLAGS) {
                                var_r31_2->unk0x8 = 0;
                                var_r31_2 = temp_r3;
                            }
                        } while (var_r31_2 != NULL);
                    }
                }
                var_r31 = temp_r28;
            } while (var_r31 != NULL);
        }
    } else {
        temp_r29_2 = arg0->unk0x24;
        var_r31_3 = fn_80127358(temp_r29_2, NULL);
        if (var_r31_3 != NULL) {
            do {
                temp_r3_2 = fn_80127358(temp_r29_2, var_r31_3);
                if ((s32) var_r31_3->unk0x4 != QB_NUM_FLAGS) {
                    var_r31_3->unk0x8 = 0;
                    var_r31_3 = temp_r3_2;
                }
            } while (var_r31_3 != NULL);
        }
    }
    arg0->unk0x60 = 0;
    AddInteger(arg0->unk0x20, QB_NUM_FLAGS_SET, 0);
}
