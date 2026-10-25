// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8021E0E0-0x8021E18C (172B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

void *fn_801259C8(s32, s32);
void *fn_80129528(CStruct *, s32);
s32 fn_80128E34(CStruct *, void *, void *, s32);
s32 fn_80128C80(CStruct *, void *, void *, s32);

typedef struct listhdr {
    s32 unk0;
    s32 count;
} listhdr_t;

s32 fn_8021E0E0(s32 arg0, s32 arg1, s32 arg2, void *arg3) {
    s32 spC;
    s32 sp8;
    listhdr_t *temp_r29;
    void *temp_r31;
    s32 var_r30;

    temp_r29 = (listhdr_t *)fn_801259C8(arg1, 0);
    var_r30 = 0;
    __asm__("li %0,0" : "=r"(spC));
    while (var_r30 < temp_r29->count) {
        temp_r31 = fn_80129528(temp_r29, var_r30);
        fn_80128E34(temp_r31, QB_CHECKSUM, &sp8, 1);
        if (sp8 == arg2) {
            fn_80128C80(temp_r31, arg3, &spC, 1);
        }
        var_r30 += 1;
    }
    return spC;
}
