// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801AF780-0x801AF82C (172B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_801AED20(Unk_C7387A53 *);
void AddInteger(CStruct *, s32, s32);
bool fn_801AF780(CStruct *arg0, s32 arg1, CScript *arg2) {
    register void *temp_r9 __asm__("r9");
    void *var_r31;
    Unk_C7387A53 *var_r3;
    s32 temp_r0;
    s32 var_r29;
    s32 var_r30;

    temp_r9 = *((void * *)&arg0->unk0x10);
    if (((CStruct *)temp_r9)->unk0x4 == -1) {
        temp_r9 = NULL;
    }
    var_r30 = 0;
    var_r29 = 0;
    var_r3 = temp_r9;
    if (var_r3 == NULL) {
        goto block_5;
    }
    do {
        temp_r9 = *((void * *)&var_r3->unk0xC);
        temp_r0 = ((CStruct *)temp_r9)->unk0x4;
        var_r31 = temp_r9;
        if (temp_r0 == -1) {
            var_r31 = NULL;
        }
        var_r30 += 1;
        if (fn_801AED20(var_r3) != 0) {
            var_r29 += 1;
        }
        var_r3 = var_r31;
    } while (var_r3 != NULL);
block_5:
    AddInteger(arg2->unk0x18, QB_NUM_GAPS, var_r30);
    AddInteger(arg2->unk0x18, QB_NUM_COLLECTED_GAPS, var_r29);
    return true;
}
