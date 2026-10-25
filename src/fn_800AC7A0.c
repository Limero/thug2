// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800AC7A0-0x800AC810 (112B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_801259C8(s32, s32);
s32 GetChecksum(CStruct *, s32);
s32 GetStructure(s32, s32);
void fn_8005AEC4(void);
void fn_800AC7A0(void) {
    s32 temp_r30;
    s32 var_r31;
    CStruct *temp_r3;

    temp_r3 = fn_801259C8(QB_LEVELLIGHTNAMES, 0);
    if (temp_r3 != NULL) {
        temp_r30 = temp_r3->unk0x4;
        for (var_r31 = 0; var_r31 < temp_r30; var_r31++) {
            GetStructure(GetChecksum(temp_r3, var_r31), 1);
            fn_8005AEC4();
        }
    }
}
