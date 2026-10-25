// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F3E78-0x800F3F3C (196B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

typedef struct F3E78_vt {
    char pad0x00[0x58];
    s16 off0x58;
    char pad0x5A[0x2];
    s32 (*fn0x5C)(char *, s32);
} F3E78_vt;

s32 Mem_Alloc2(s32);
s32 fn_80026AEC(CStruct *);
s32 fn_80026CA0(s32, CStruct *, CStruct *, s32);
s32 Script_GetInteger(s32, s32);
void fn_80026B4C(s32, s32);
void fn_80013788(s32);
void fn_800F3794(Unk_C7387A53 *, CStruct *, CStruct *);

void fn_800F3E78(Unk_C7387A53 *arg0, CStruct *arg1, CStruct *arg2) {
    s32 var_r31;
    F3E78_vt *temp_r9;

    var_r31 = fn_80026AEC((CStruct *)Mem_Alloc2(0x3C));
    if (fn_80026CA0(var_r31, arg1, arg2, 1) == 0) {
        Script_GetInteger(QB_ASSERTONMISSINGASSETS, 0);
        if (var_r31 != 0) {
            fn_80026B4C(var_r31, 3);
        }
        var_r31 = 0;
    }
    temp_r9 = (F3E78_vt *)arg0->unk0x50;
    temp_r9->fn0x5C((char *)arg0 + temp_r9->off0x58, var_r31);
    if (arg0->unk0x20 != 0) {
        fn_80013788(arg0->unk0x20);
        arg0->unk0x20 = 0;
    }
    fn_800F3794(arg0, arg1, arg2);
}
