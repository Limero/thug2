// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015C7E0-0x8015C930 (336B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_802A81B4[];
extern char lbl_802A81BC[];
extern char lbl_802A81C4[];
extern char lbl_802A81CC[];
extern char lbl_802A81D8[];
extern char lbl_802A81E8[];
extern char lbl_802A81F8[];
extern void* lbl_80305EAC;
extern void* lbl_802FFE98;
extern s32 fn_8012834C(CStruct * arg0, void * arg1, void *arg2, s32 arg3);
extern s32 GetStructure_2(CStruct * arg0, s32 arg1, s32 * arg2, s32 arg3);
extern void fn_8000F2F8(Unk_9F352E7C * arg0, s32 arg1);
extern void fn_8019A410(s32 arg0, s32 arg1);
extern void fn_8019A49C(Unk_B97C1601 * arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7);
extern void fn_8000F320(Unk_F12C5E01 * arg0);

bool ScriptStartCompetition(CStruct *pParams, CScript *pScript) {
    f32 sp8;
    f32 spC;
    f32 sp10;
    f32 sp14;
    f32 sp18;
    f32 sp1C;
    f32 sp20;
    s32 sp24;

    fn_8012834C(pParams, (s32)lbl_802A81B4, &sp8, 0);
    fn_8012834C(pParams, (s32)lbl_802A81BC, &spC, 0);
    fn_8012834C(pParams, (s32)lbl_802A81C4, &sp10, 0);
    fn_8012834C(pParams, (s32)lbl_802A81CC, &sp14, 0);
    fn_8012834C(pParams, (s32)lbl_802A81D8, &sp18, 0);
    fn_8012834C(pParams, (s32)lbl_802A81E8, &sp1C, 0);
    fn_8012834C(pParams, (s32)lbl_802A81F8, &sp20, 0);
    sp24 = 0;
    GetStructure_2(pParams, QB_EXTRA_PARAMS, &sp24, 0);
    fn_8000F2F8(lbl_802FFE98, ((Unk_3EBD2634 *)lbl_802FFE98)->unk0x5F8);
    if (sp24 != 0) {
        fn_8019A410(((Unk_7251BA8A *)lbl_80305EAC)->unk0x370, sp24);
    }
    fn_8019A49C(((Unk_7251BA8A *)lbl_80305EAC)->unk0x370, sp10, spC, sp8, sp1C, sp18, sp14, sp20);
    fn_8000F320(lbl_802FFE98);
    return true;
}
