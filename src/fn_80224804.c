// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80224804-0x80224968 (356B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern void* lbl_802FFE98;
s32 fn_802201A4(CScript * arg0);
void fn_8000F2F8(Unk_9F352E7C * arg0, s32 arg1);
void Script_RunScript(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void fn_80009C00(CStruct * arg0);
void fn_8000F320(Unk_F12C5E01 * arg0);
void fn_8021B1CC(Unk_FFAD6788 * arg0);
void fn_8022019C(CScript * arg0, s32 arg1);
s32 fn_80224804(Unk_DB0E2BAB *arg0) {
    s32 *temp_r9;
    Unk_217B54BD *temp_r31;
    s32 var_r0;

    temp_r9 = *((s32 * *)&arg0->unk0x0);
    temp_r31 = arg0->unk0x18;
    switch ((s8)*(s8 *)temp_r9) {
    case 4:
        var_r0 = QB_NET_REASON_BANNED;
        break;
    case 0:
        var_r0 = QB_NET_REASON_FULL;
        break;
    case 5:
        var_r0 = QB_NET_REASON_FULL_OBSERVERS;
        break;
    case 1:
        if (fn_802201A4(temp_r31) == 4) {
            var_r0 = QB_NET_REASON_WRONG_PASSWORD;
            break;
        }
        fn_8000F2F8(lbl_802FFE98, ((Unk_9960D53C *)lbl_802FFE98)->unk0x124);
        Script_RunScript(QB_CREATEENTERPASSWORDCONTROL, 0, 0, 0, 0);
        fn_80009C00(temp_r31->unk0xE8);
        fn_8000F320(lbl_802FFE98);
        return 1;
    case 3:
        Script_RunScript(QB_CREATEGAMEINPROGRESSDIALOG, 0, 0, 0, 0);
        fn_80009C00(temp_r31->unk0xE8);
        return 1;
    case 6:
        var_r0 = QB_NET_REASON_RANK_LIMIT_LOW;
        break;
    case 7:
        var_r0 = QB_NET_REASON_RANK_LIMIT_HIGH;
        break;
    case 2:
        var_r0 = QB_NET_REASON_DEFAULT;
        break;
    default:
        var_r0 = QB_NET_REASON_DEFAULT;
        break;
    }
    temp_r31->unk0x1AC = var_r0;
    fn_8021B1CC(temp_r31);
    fn_8022019C(temp_r31, 8);
    return 3;
}
