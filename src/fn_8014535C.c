// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8014535C-0x801453E4 (136B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_8003E7CC(s32);
s32 fn_80128F94(Unk_9D4ED6AF *);
void fn_80129068(Unk_5AA7B5D7 *, s32, s32);
s32 fn_80202438(void *, s32);
void fn_80129260(CStruct *, s32, s32);
void AddArrayPointer(CStruct *, s32, s32);
void fn_8014535C(Unk_7258DEBD *arg0, CStruct *arg1) {
    s32 temp_r30;
    s32 var_r31;

    s32 temp_r4;
    s32 temp_r5;

    var_r31 = 0;
    temp_r30 = fn_80128F94(fn_8003E7CC(0xC));
    fn_80129068(temp_r30, 0x46, 1);
    do {
        temp_r5 = fn_80202438(arg0->unk0x2B8, var_r31);
        temp_r4 = var_r31;
        var_r31 += 1;
        fn_80129260(temp_r30, temp_r4, temp_r5);
    } while (var_r31 <= 0x45);
    AddArrayPointer(arg1, QB_STATGOALS, temp_r30);
}
