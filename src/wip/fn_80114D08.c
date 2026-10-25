// WIP DRAFT (concrete attempt;)
// family=m2c range=0x80114D08-0x80114E4C size=324B
// PARKED: array-contains candidate scored 3.7%; target CR-field loop and element-helper dispatch need deeper ABI reconstruction.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
static s32 sp8;

bool ScriptArrayContains(CStruct *arg0) {
    s32 sp18;
    s32 sp14;
    s32 sp10;
    s32 spC;
    void *sp8;
    s32 var_cr0_eq;
    s32 var_cr0_eq_2;
    s32 var_cr0_gt;
    u32 temp_r0;
    u32 temp_r0_2;
    u32 var_r29;

    sp18 = 0;
    fn_80128E94(QB_ARRAY, &sp8, 1);
    var_r29 = 0U;
    temp_r0 = ((CStruct *)sp8)->unk0x4;
    var_cr0_eq = temp_r0 == 0U;
    var_cr0_gt = temp_r0 < 0U;
    if (temp_r0 > 0U) {
        0;
        0;
        0;
loop_2:
        if (var_cr0_eq == 0) {
            if (var_cr0_gt == 0) {
                if (var_cr0_eq == 0) {
                    goto block_13;
                }
                fn_80128C80(arg0, QB_CONTAINS, &spC, 1);
                var_cr0_eq_2 = spC == fn_801293FC(sp8, var_r29);
                goto block_11;
            }
            if (var_cr0_eq == 0) {
                goto block_13;
            }
            fn_80128E34(arg0, QB_CONTAINS, &sp10, 1);
            var_cr0_eq_2 = sp10 == GetChecksum(sp8, var_r29);
            goto block_11;
        }
        GetText(arg0, QB_CONTAINS, &sp14, 1);
        var_cr0_eq_2 = strcasecmp(sp14, fn_8012935C(sp8, var_r29)) == 0;
block_11:
        if (var_cr0_eq_2 != 0) {
            0;
            return true;
        }
block_13:
        var_r29 += 1;
        temp_r0_2 = ((CStruct *)sp8)->unk0x4;
        var_cr0_eq = var_r29 == temp_r0_2;
        var_cr0_gt = var_r29 > temp_r0_2;
        if (var_r29 >= temp_r0_2) {
            goto block_14;
        }
        goto loop_2;
    }
block_14:
    0;
    return false;
}
