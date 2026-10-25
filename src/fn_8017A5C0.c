// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8017A5C0-0x8017A6E4 (292B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305F9C;
extern void *lbl_80305EAC;
void fn_80131234(void);
s32 CStruct_new(s32);
s32 CStruct_ctor(s32);
s32 fn_80127E70(s32, s32, s32, s32);
void Script_RunScript(s32, s32, s32, s32, s32);
void CStruct_delete(CStruct *, s32);
void fn_8021D95C(Unk_A7137CF0 *);
void fn_8021B3E0(Unk_6A70655D *);
void fn_8021B1CC(Unk_FFAD6788 *);
void fn_8022019C(CScript *, s32);
s32 fn_8017A5C0(Unk_6A78CE27 *arg0) {
    s32 temp_r29;
    Unk_7258DEBD *temp_r28;
    s32 temp_r31;

    temp_r29 = lbl_80305F9C;
    temp_r28 = lbl_80305EAC;
    fn_80131234();
    temp_r31 = CStruct_ctor(CStruct_new(8));
    fn_80127E70(temp_r31, QB_WIDTH, 1, 0x12C);
    fn_80127E70(temp_r31, QB_TITLE, 0xD, QB_NET_NOTICE_MSG);
    if (arg0->unk0x4 == 0x51) {
        Script_RunScript(QB_CREATESERVERREMOVEDYOUDIALOG, 0, 0, 0, 0);
    } else if (arg0->unk0x4 == 0x56) {
        Script_RunScript(QB_CREATESERVERMOVEDONDIALOG, 0, 0, 0, 0);
    }
    if (temp_r31 != 0) {
        CStruct_delete(temp_r31, 3);
    }
    if (temp_r28->unk0x384 == -QB_UNKNOWN_0x16D13502) {
        fn_8021B1CC(temp_r29);
        fn_8022019C(temp_r29, 9);
        return 2;
    }
    fn_8021D95C(temp_r29);
    fn_8021B3E0(temp_r29);
    return 3;
}
