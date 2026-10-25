// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80175AB0-0x80175AFC (76B). Byte-identical.
#include "types.h"
#include "structs.h"
extern void* lbl_802FFE98;
extern void* lbl_80305EAC;
extern void fn_8000F2F8(Unk_9F352E7C * arg0, s32 arg1);
extern void fn_8017503C(Unk_40426380 * arg0);
extern void fn_8000F320(Unk_F12C5E01 * arg0);
bool ScriptLaunchGame(CStruct *pParams, CScript *pScript) {
    Unk_9994C3F5 *temp_r3;

    temp_r3 = (void *)lbl_802FFE98;
    fn_8000F2F8((s32)temp_r3, temp_r3->unk0x11C);
    fn_8017503C(lbl_80305EAC);
    fn_8000F320(lbl_802FFE98);
    return true;
}
