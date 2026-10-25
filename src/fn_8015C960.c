// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015C960-0x8015C9D8 (120B). Byte-identical.
#include "types.h"
#include "structs.h"
extern void* lbl_80305EAC;
extern void* lbl_802FFE98;
extern s32 fn_801745B4(s32 arg0);
extern s32 fn_801403CC(void * arg0);
extern s32 fn_801813F0(CStruct * arg0);
extern void fn_8000F2F8(Unk_9F352E7C * arg0, s32 arg1);
extern void fn_8019AA88(Unk_BB31683B * arg0, s32 arg1);
extern void fn_8019B49C(Unk_9994C3F5 * arg0);
extern void fn_8000F320(Unk_F12C5E01 * arg0);

bool ScriptEndCompetitionRun(CStruct *pParams, CScript *pScript) {
    s32 temp_r29;

    temp_r29 = fn_801813F0(fn_801403CC(fn_801745B4(lbl_80305EAC)));
    fn_8000F2F8(lbl_802FFE98, ((Unk_3EBD2634 *)lbl_802FFE98)->unk0x5F8);
    fn_8019AA88(((Unk_7251BA8A *)lbl_80305EAC)->unk0x370, temp_r29);
    fn_8019B49C(((Unk_7251BA8A *)lbl_80305EAC)->unk0x370);
    fn_8000F320(lbl_802FFE98);
    return true;
}
