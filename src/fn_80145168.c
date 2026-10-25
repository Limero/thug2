// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80145168-0x80145240 (216B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_8003E7CC(s32);
s32 fn_80128F94(Unk_9D4ED6AF *);
void fn_80129068(Unk_5AA7B5D7 *, s32, s32);
s32 CStruct_new(s32);
s32 CStruct_ctor(s32);
void fn_80127C14(CStruct *, s32, CStruct *);
void fn_80127AAC(CStruct *, s32, Unk_5AA7B5D7 *);
void fn_80129314(CStruct *, s32, s32);
void AddArrayPointer(CStruct *, s32, s32);
void fn_80145168(void *arg0, CStruct *arg1) {
    s32 temp_r28;
    s32 temp_r30;
    s32 temp_r4;
    s32 var_r29;
    s32 *var_r31;

    temp_r28 = fn_80128F94(fn_8003E7CC(0xC));
    var_r29 = 0;
    fn_80129068(temp_r28, 0xB, 0xA);
    var_r31 = (s32 *)((char *)arg0 + (s32)0x194);
    do {
        temp_r30 = CStruct_ctor(CStruct_new(8));
        fn_80127C14(temp_r30, QB_OTHER, **(s32 **)var_r31);
        fn_80127AAC(temp_r30, QB_ANIMATIONS, *(s32 *)((char *)*(s32 **)var_r31 + (s32)8));
        fn_80127AAC(temp_r30, QB_ROTATIONS, *(s32 *)((char *)*(s32 **)var_r31 + (s32)4));
        var_r31 = (s32 *)((char *)var_r31 + (s32)4);
        temp_r4 = var_r29;
        var_r29 += 1;
        fn_80129314(temp_r28, temp_r4, temp_r30);
    } while (var_r29 <= 0xA);
    AddArrayPointer(arg1, QB_TRICKS, temp_r28);
}
