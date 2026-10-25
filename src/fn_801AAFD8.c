// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801AAFD8-0x801AB08C (180B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_801AAE94(CStruct *, CStruct *, CStruct *, CStruct *);
void fn_801AAFD8(void *arg0, Unk_C7387A53 *arg1, Unk_C7387A53 *arg2) {
    s32 var_r9;
    s32 var_r9_2;

    if (arg1->unk0x48 == NULL) {
        arg1->unk0x48 = arg2;
        fn_801AAE94((char *)arg1 + 0x28, (char *)arg2 + 0x28, (char *)arg1 + 8, (char *)arg1 + 0x18);
    } else {
        var_r9 = 1;
        if (!(arg2->unk0x50 & 2)) {
            var_r9 = 0;
        }
        if (var_r9 != 0) {
            arg1->unk0x48 = arg2;
            fn_801AAE94((char *)arg1 + 0x28, (char *)arg2 + 0x28, (char *)arg1 + 8, (char *)arg1 + 0x18);
        }
    }
    if (arg2->unk0x4C == NULL) {
        arg2->unk0x4C = arg1;
    } else {
        var_r9_2 = 1;
        if (!(arg1->unk0x50 & 2)) {
            var_r9_2 = 0;
        }
        if (var_r9_2 != 0) {
            arg2->unk0x4C = arg1;
        }
    }
}
