// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B107C-0x801B1154 (216B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern s32 fn_8003E7CC(s32);
extern s32 fn_80128F94(Unk_9D4ED6AF *);
extern void fn_80129068(Unk_5AA7B5D7 *, s32, s32);
extern s32 CStruct_new(s32);
extern s32 CStruct_ctor(s32);
extern void fn_801B0C78(Unk_C8FEE62D *, s32);
extern void fn_80129314(CStruct *, s32, s32);
extern void fn_80127E70(s32, s32, s32, s32);
extern s32 fn_801B0168(void *);
extern void AddComponent(CStruct *, s32, s32, void *);

void fn_801B107C(CStruct *arg0, CStruct *arg1) {
    s32 temp_r27;
    s32 var_r29;
    s32 var_r28;
    s32 temp_r30;

    var_r29 = 0;
    temp_r27 = fn_80128F94(fn_8003E7CC(0xC));
    fn_80129068(temp_r27, arg0->unk0x4, 0xA);
    if (var_r29 < (s32)arg0->unk0x4) {
        var_r28 = 0;
        do {
            temp_r30 = CStruct_ctor(CStruct_new(8));
            fn_801B0C78((void *)(arg0->unk0xC + var_r28), temp_r30);
            var_r28 += 0x20;
            fn_80129314(temp_r27, var_r29, temp_r30);
            var_r29 += 1;
        } while (var_r29 < (s32)arg0->unk0x4);
    }
    fn_80127E70(arg1, QB_GAMERECORDS, 0xC, temp_r27);
    AddComponent(arg1, QB_DEFAULTINITIALS, 3, fn_801B0168(arg0->unk0x8));
}
