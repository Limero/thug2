// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A4C68-0x801A4D1C (180B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern void *lbl_802FFE98;
extern void fn_8000F2F8(Unk_9F352E7C * arg0, s32 arg1);
extern void fn_8000F320(Unk_F12C5E01 * arg0);
extern s32 fn_8003AAB0(Unk_31DE137E * arg0, void * arg1);
extern void CStruct_dtor(CStruct * arg0);
extern s32 fn_80129EA0(CStruct * arg0, u8 * arg1);
extern s32 fn_801A568C(s32 arg0, s32 arg1);
extern s32 fn_801A56BC(s32 arg0);
extern s32 fn_801A4F84(s32 arg0, s32 arg1);
register s32 g31 __asm__("r31");
s32 fn_801A4C68(Unk_31DE137E *arg0, void *arg1) {
    register s32 var_r30 __asm__("r30");
    s32 temp_r28;

    fn_8000F2F8(lbl_802FFE98, ((Unk_C7387A53 *)lbl_802FFE98)->unk0x12C);
    var_r30 = fn_8003AAB0((char *)arg0 + 4, arg1);
    CStruct_dtor(fn_801A568C(arg0, QB_TRICK_MAPPING));
    temp_r28 = fn_80129EA0(fn_801A568C(arg0, QB_TRICK_MAPPING), var_r30);
    var_r30 = fn_801A56BC(arg0);
    CStruct_dtor(var_r30);
    __asm__("" : "+r"(temp_r28));
    var_r30 = fn_801A4F84(arg0, fn_80129EA0(var_r30, temp_r28));
    fn_8000F320(lbl_802FFE98);
    return var_r30;
}
