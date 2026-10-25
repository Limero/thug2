// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80171BF4-0x80171D90 (412B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80300458;
s32 CStruct_new(s32);
s32 CStruct_ctor(s32);
void AddInteger(CStruct *, s32, s32);
s32 fn_8003E7CC(s32);
s32 fn_80128F94(Unk_9D4ED6AF *);
void fn_80129068(Unk_5AA7B5D7 *, s32, s32);
void fn_80129260(CStruct *, s32, s32);
void fn_80127AAC(CStruct *, s32, Unk_5AA7B5D7 *);
void fn_80128FB4(Unk_F8A5095F *, s32);
void fn_80070F28(s32, s32, s32);
void CStruct_delete(CStruct *, s32);
void fn_80171BF4(s32 arg0, s32 *arg1) {
    s32 sp8[5];
    s32 *p;
    s32 temp_r30;
    s32 temp_r31;
    s32 temp_r7;

    temp_r30 = CStruct_ctor(CStruct_new(8));
    temp_r7 = arg1[0];
    if (temp_r7 != 0) {
        sp8[0] = temp_r7;
        p = sp8;
        p[1] = arg1[1];
        p[2] = arg1[2];
        p[3] = arg1[3];
        p[4] = arg1[4];
        AddInteger(temp_r30, QB_ON, sp8[0]);
        AddInteger(temp_r30, -QB_UNKNOWN_0x097FEB27, sp8[1]);
        AddInteger(temp_r30, QB_BLOOM2, sp8[2]);
        temp_r31 = fn_80128F94(fn_8003E7CC(0xC));
        fn_80129068(temp_r31, 3, 1);
        fn_80129260(temp_r31, 0, ((Unk_A8B25094 *)sp8)->unk0xC);
        fn_80129260(temp_r31, 1, ((Unk_A8B25094 *)sp8)->unk0xD);
        fn_80129260(temp_r31, 2, ((Unk_A8B25094 *)sp8)->unk0xE);
        fn_80127AAC(temp_r30, QB_STRENGTH, temp_r31);
        fn_80129260(temp_r31, 0, ((Unk_A8B25094 *)sp8)->unk0x10);
        fn_80129260(temp_r31, 1, *((u8 *)&((Unk_A8B25094 *)sp8)->unk0x11));
        fn_80129260(temp_r31, 2, ((Unk_A8B25094 *)sp8)->unk0x12);
        fn_80127AAC(temp_r30, -QB_UNKNOWN_0x665648EA, temp_r31);
        if (temp_r31 != 0) {
            fn_80128FB4(temp_r31, 3);
        }
    } else {
        AddInteger(temp_r30, QB_ON, 0);
    }
    fn_80070F28(lbl_80300458, temp_r30, 0);
    if (temp_r30 != 0) {
        CStruct_delete(temp_r30, 3);
    }
}
