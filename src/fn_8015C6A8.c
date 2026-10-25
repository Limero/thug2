// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015C6A8-0x8015C7E0 (312B). Byte-identical.
#include "types.h"
extern void* lbl_80305EAC;
extern s32 lbl_80305EC0;
#include "qb_constants.h"
#include "structs.h"
extern s32 fn_8017480C(Unk_FFAD6788 * arg0);
extern s32 fn_8013FF5C(s32 arg0, s32 arg1);
extern s32 fn_80128E34(CStruct * arg0, void * arg1, void *arg2, s32 arg3);
extern void fn_8019915C(s32 arg0, s32 arg1);
extern s32 fn_80140010(s32 arg0, s32 arg1, void * arg2);
extern s32 IsTrue(s32 arg0, void * arg1);
extern s32 fn_8013FFB8(s32 arg0, s32 arg1, void * arg2);
extern void fn_80009218(void *arg0, s32 arg1);
extern void fn_8019BB98(s32 arg0, Unk_9994C3F5 * arg1);
extern s32 CStruct_new(s32 arg0);
extern s32 CStruct_ctor(s32 arg0);
extern void fn_80127E70(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void fn_801992A8(s32 arg0, CStruct * arg1);
extern void fn_80174090(Unk_C5855798 * arg0, s32 arg1);
extern void CStruct_delete(CStruct * arg0, s32 arg1);

bool ScriptApplySplitScreenOptions(CStruct *pParams, CScript *pScript) {
    s32 sp8[4];
    s32 sp18[2];
    s32 h4;
    s32 h5;
    s32 temp_r30;
    s32 temp_r31;

    temp_r31 = fn_8017480C(lbl_80305EAC);
    fn_80128E34(fn_8013FF5C(temp_r31, QB_GAME_TYPE), QB_CHECKSUM, &sp18, 1);
    fn_8019915C(lbl_80305EC0, sp18[0]);
    fn_80140010(temp_r31, QB_TIME_LIMIT, QB_TIME);
    if (IsTrue(lbl_80305EC0, QB_IS_HORSE) != 0) {
        h4 = QB_HORSE_TIME_LIMIT;
        h5 = QB_TIME;
        __asm__ volatile("" : "+r"(h4), "+r"(h5));
        temp_r30 = fn_80140010(temp_r31, h4, h5);
        fn_80009218(&sp8, fn_8013FFB8(temp_r31, QB_HORSE_WORD, QB_UI_STRING));
        fn_8019BB98(((Unk_544AB658 *)lbl_80305EAC)->unk0x374, &sp8);
        temp_r31 = CStruct_ctor(CStruct_new(8));
        fn_80127E70(temp_r31, QB_DEFAULT_TIME_LIMIT, 1, temp_r30);
        fn_801992A8(lbl_80305EC0, temp_r31);
        fn_80174090(lbl_80305EAC, temp_r30);
        if (temp_r31 != 0) {
            CStruct_delete(temp_r31, 3);
        }
    }
    return true;
}
