// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80186A14-0x80186B90 (380B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

s32 fn_801850D4(s32, s32);
s32 GetArray(CStruct *, s32, s32 *, s32);
s32 fn_8003E7CC(s32);
s32 fn_80128F94(Unk_9D4ED6AF *);
void fn_80129068(Unk_5AA7B5D7 *, s32, s32);
s32 ContainsFlag(CStruct *, s32);
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 fn_8018F89C(CStruct *, CStruct *, CStruct *, s32);
s32 fn_8018FAE8(s32, s32, s32, s32, s32);
void fn_80126A30(Unk_5AA7B5D7 *);
void fn_80128FB4(Unk_F8A5095F *, s32);

bool fn_80186A14(s32 arg0, s32 arg1, void *arg2, void *arg3, s32 arg4) {
    void *sp8;
    s32 spC;
    s32 temp_r28;
    s32 temp_r29;
    s32 temp_r30;
    s32 temp_r31;

    GetArray((temp_r28 = fn_801850D4(arg0, arg1)), QB_KEY_COMBOS, &sp8, 1);
    temp_r31 = fn_80128F94(fn_8003E7CC(0xC));
    temp_r29 = fn_80128F94(fn_8003E7CC(0xC));
    temp_r30 = ((CStruct *)sp8)->unk0x4;
    fn_80129068(temp_r31, temp_r30, 3);
    fn_80129068(temp_r29, temp_r30, 3);
    spC = -1;
    if (ContainsFlag(temp_r28, QB_CREATE_A_TRICK) != 0) {
        GetInteger(temp_r28, QB_TRICKNAME, &spC, 1);
    }
    if (fn_8018F89C(sp8, temp_r31, temp_r29, spC) == 0) {
        fn_80126A30(temp_r31);
        fn_80126A30(temp_r29);
        if (temp_r31 != 0) {
            fn_80128FB4(temp_r31, 3);
        }
        if (temp_r29 != 0) {
            fn_80128FB4(temp_r29, 3);
        }
        return false;
    }
    fn_8018FAE8(arg2, arg3, temp_r31, temp_r29, arg4);
    fn_80126A30(temp_r31);
    fn_80126A30(temp_r29);
    if (temp_r31 != 0) {
        fn_80128FB4(temp_r31, 3);
    }
    if (temp_r29 != 0) {
        fn_80128FB4(temp_r29, 3);
    }
    return true;
}
