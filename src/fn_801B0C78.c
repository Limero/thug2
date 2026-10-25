// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B0C78-0x801B0E1C (420B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern s32 CStruct_new(s32 arg0);
extern s32 CStruct_ctor(s32 arg0);
extern void fn_801B0874(CStruct * arg0, s32 arg1);
extern void fn_80127E70(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void fn_801B0430(CStruct * arg0, CStruct * arg1);

void fn_801B0C78(Unk_C8FEE62D *arg0, s32 arg1) {
    s32 temp_r31;

    temp_r31 = CStruct_ctor(CStruct_new(8));
    fn_801B0874(arg0->unk0x4, temp_r31);
    fn_80127E70(arg1, QB_HIGHSCORES, 0xB, temp_r31);
    temp_r31 = CStruct_ctor(CStruct_new(8));
    fn_801B0874(arg0->unk0x8, temp_r31);
    fn_80127E70(arg1, QB_BESTCOMBOS, 0xB, temp_r31);
    if ((s32)arg0->unk0xC != 0) {
        temp_r31 = CStruct_ctor(CStruct_new(8));
        fn_801B0874(arg0->unk0xC, temp_r31);
        fn_80127E70(arg1, QB_ARCADESCORES, 0xB, temp_r31);
    }
    temp_r31 = CStruct_ctor(CStruct_new(8));
    fn_801B0430(arg0->unk0x1C, temp_r31);
    fn_80127E70(arg1, QB_LONGESTCOMBO, 0xB, temp_r31);
    temp_r31 = CStruct_ctor(CStruct_new(8));
    fn_801B0430(arg0->unk0x10, temp_r31);
    fn_80127E70(arg1, QB_LONGESTGRIND, 0xB, temp_r31);
    temp_r31 = CStruct_ctor(CStruct_new(8));
    fn_801B0430(arg0->unk0x18, temp_r31);
    fn_80127E70(arg1, QB_LONGESTLIPTRICK, 0xB, temp_r31);
    temp_r31 = CStruct_ctor(CStruct_new(8));
    fn_801B0430(arg0->unk0x14, temp_r31);
    fn_80127E70(arg1, QB_LONGESTMANUAL, 0xB, temp_r31);
}
