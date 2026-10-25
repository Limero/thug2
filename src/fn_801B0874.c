// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B0874-0x801B092C (184B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern s32 fn_8003E7CC(s32);
extern s32 fn_80128F94(Unk_9D4ED6AF *);
extern void fn_80129068(Unk_5AA7B5D7 *, s32, s32);
extern s32 CStruct_new(s32);
extern s32 CStruct_ctor(s32);
extern void fn_801B0430(CStruct *, CStruct *);
extern void fn_80129314(CStruct *, s32, s32);
extern void fn_80127E70(s32, s32, s32, s32);

void fn_801B0874(CStruct *arg0, s32 arg1) {
    s32 temp_r27;
    s32 temp_r30;
    s32 temp_r4;
    s32 var_r28;
    s32 var_r31;

    var_r31 = 0;
    fn_80129068(temp_r27 = fn_80128F94(fn_8003E7CC(0xC)), arg0->unk0x4, 0xA);
    if (var_r31 < arg0->unk0x4) {
        var_r28 = 0;
        do {
            temp_r30 = CStruct_ctor(CStruct_new(8));
            fn_801B0430(arg0->unk0x8 + var_r28, temp_r30);
            var_r28 += 0x14;
            temp_r4 = var_r31;
            var_r31 += 1;
            fn_80129314(temp_r27, temp_r4, temp_r30);
        } while (var_r31 < arg0->unk0x4);
    }
    fn_80127E70(arg1, QB_RECORDTABLE, 0xC, temp_r27);
}
