// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8003E148-0x8003E328 (480B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_8003E7CC(s32);
s32 fn_80128F94(void);
void fn_80129068(Unk_5AA7B5D7 *, s32, s32);
void fn_80129260(CStruct *, s32, s32);
void AddArrayPointer(CStruct *, s32, s32);
void fn_8012772C(CStruct *, s32, float);
void AddInteger(CStruct *, s32, s32);
// SetFacePointsStruct @ 0x8003E148
bool SetFacePointsStruct(Unk_DB0E2BAB *arg0, CStruct *arg1) {
    s32 temp_r27;
    s32 temp_r28;
    s32 temp_r29;
    s32 temp_r30;

    fn_8003E7CC(0xC);
    temp_r27 = fn_80128F94();
    fn_80129068(temp_r27, 2, 1);
    fn_80129260(temp_r27, 0, arg0->unk0x0);
    fn_80129260(temp_r27, 1, arg0->unk0x4);
    fn_8003E7CC(0xC);
    temp_r28 = fn_80128F94();
    fn_80129068(temp_r28, 2, 1);
    fn_80129260(temp_r28, 0, arg0->unk0x8);
    fn_80129260(temp_r28, 1, arg0->unk0xC);
    fn_8003E7CC(0xC);
    temp_r29 = fn_80128F94();
    fn_80129068(temp_r29, 2, 1);
    fn_80129260(temp_r29, 0, arg0->unk0x10);
    fn_80129260(temp_r29, 1, arg0->unk0x14);
    fn_8003E7CC(0xC);
    temp_r30 = fn_80128F94();
    fn_80129068(temp_r30, 2, 1);
    fn_80129260(temp_r30, 0, arg0->unk0x18);
    fn_80129260(temp_r30, 1, arg0->unk0x1C);
    AddArrayPointer(arg1, QB_LEFT_EYE, temp_r27);
    AddArrayPointer(arg1, QB_RIGHT_EYE, temp_r28);
    AddArrayPointer(arg1, QB_NOSE, temp_r29);
    AddArrayPointer(arg1, QB_LIPS, temp_r30);
    if (arg0->unk0x20 != 0) {
        fn_8012772C(arg1, QB_H, *((float *)&arg0->unk0x24));
        fn_8012772C(arg1, QB_S, *((float *)&arg0->unk0x28));
        fn_8012772C(arg1, QB_V, *((float *)&arg0->unk0x2C));
    }
    AddInteger(arg1, QB_WIDTH, arg0->unk0x30);
    AddInteger(arg1, QB_HEIGHT, arg0->unk0x34);
    return true;
}
