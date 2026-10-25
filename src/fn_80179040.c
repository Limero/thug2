// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80179040-0x801790E0 (160B). Byte-identical.
#include "types.h"
#include "structs.h"

extern void* lbl_802FFE98;
extern s32 lbl_80301A38;
extern void fn_8000F2F8(Unk_9F352E7C * arg0, s32 arg1);
extern s32 fn_800A398C(s32 arg0, s32 arg1);
extern s32 CStruct_new(s32 arg0);
extern s32 CStruct_ctor(s32 arg0);
extern void fn_80129EA0(CStruct * arg0, u8 * arg1);
extern s32 Script_RunScript(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern void CStruct_delete(CStruct * arg0, s32 arg1);
extern void fn_8000F320(Unk_F12C5E01 * arg0);

bool fn_80179040(void **arg0) {
    s32 temp_r29;
    CStruct *temp_r30;
    s32 temp_r31;

    fn_8000F2F8(lbl_802FFE98, ((Unk_C7387A53 *)lbl_802FFE98)->unk0x12C);
    temp_r30 = *arg0;
    temp_r29 = fn_800A398C(lbl_80301A38, temp_r30->unk0x4);
    temp_r31 = CStruct_ctor(CStruct_new(8));
    fn_80129EA0(temp_r31, (s32)temp_r30 + 8);
    Script_RunScript(*(s32 *)temp_r30, temp_r31, temp_r29, 0, 0);
    if (temp_r31 != 0) {
        CStruct_delete(temp_r31, 3);
    }
    fn_8000F320(lbl_802FFE98);
    return true;
}
