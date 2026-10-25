// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A4FF0-0x801A513C (332B). Byte-identical.
// extra_cflags: -fno-schedule-insns2
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

s32 CStruct_new(s32 arg0);
s32 CStruct_ctor(s32 arg0);
void fn_80127E70(s32 arg0, u32 arg1, s32 arg2, u32 arg3);
s32 fn_801A572C(s32 arg0);
s32 fn_80126FF4(Unk_80577C09 * arg0, CStruct * arg1);
s32 fn_8003AE20(Unk_31DE137E * arg0);
s32 fn_8003EDD0(CStruct * arg0);
s32 fn_8003EC7C(s32 arg0, CStruct * arg1);
s32 fn_801A56F4(s32 arg0);

void fn_801A4FF0(CStruct *arg0, s32 arg1) {
    s32 temp_r29;
    s32 temp_r30;
    s32 temp_r30_2;
    s32 temp_r30_3;
    s32 temp_r31;

    fn_80127E70((temp_r29 = CStruct_ctor(CStruct_new(8))), QB_VERSION_NUMBER, 1, 2);
    if (fn_801A572C(arg0) == 0) {
        fn_80126FF4((temp_r30 = CStruct_ctor(CStruct_new(8))), (char *)arg0 + 0x5C);
        fn_80127E70(temp_r29, QB_APPEARANCE, 0xB, temp_r30);
    }
    temp_r31 = fn_8003AE20((char *)arg0 + 4);
    if ((temp_r31 != 0) && (fn_8003EDD0(temp_r31) != 0)) {
        fn_8003EC7C(temp_r31, (temp_r30_2 = CStruct_ctor(CStruct_new(8))));
        fn_80127E70(temp_r29, QB_FACETEXTURE, 0xB, temp_r30_2);
    }
    fn_80126FF4((temp_r30_3 = CStruct_ctor(CStruct_new(8))), (char *)arg0 + 0x6C);
    fn_80127E70(temp_r29, QB_INFO, 0xB, temp_r30_3);
    temp_r30 = fn_801A56F4(arg0);
    fn_80127E70(temp_r29, QB_DECKFLAGS, 1, 0);
    fn_80127E70(arg1, temp_r30, 0xB, temp_r29);
}
