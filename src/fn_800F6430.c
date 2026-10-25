// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F6430-0x800F64E8 (184B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 fn_8003E7CC(s32);
extern s32 fn_80128F94(Unk_9D4ED6AF *);
extern void fn_80129068(Unk_5AA7B5D7 *, s32, s32);
extern s32 CStruct_new(s32);
extern s32 CStruct_ctor(s32);
extern void fn_80129314(CStruct *, s32, s32);
extern void *fn_8012543C(s32);
extern void fn_8012DE30(Unk_5D1D68CC *);
extern void *fn_80125568(s32);
s32 fn_800F6430(Unk_31DE137E *arg0, s32 arg1, s32 arg2) {
    s32 temp_r29;
    s32 var_r31;
    Unk_1D62F22E *temp_r9;
    void *temp_r3;

    var_r31 = 0;
    temp_r29 = fn_80128F94(fn_8003E7CC(0xC));
    fn_80129068(temp_r29, arg2, 0xA);
    while (var_r31 < arg2) {
        fn_80129314(temp_r29, var_r31, CStruct_ctor(CStruct_new(8)));
        var_r31++;
    }
    temp_r3 = fn_8012543C(arg1);
    if (temp_r3 != 0) {
        fn_8012DE30(temp_r3);
    }
    temp_r9 = fn_80125568(arg1);
    temp_r9->unk0x2 = 0xC;
    temp_r9->unk0xC = temp_r29;
    arg0->unk0x5C = arg1;
    arg0->unk0x60 = temp_r29;
    return temp_r29;
}
