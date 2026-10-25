// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800687D8-0x80068924 (332B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_802FFE98;
s32 fn_800645D8(s32, s32);
s32 fn_80064618(void *, void *);
s32 fn_80068510(void *);
void *fn_80081920(void *, s32, s32, s32, s32, s32, s32, s32, f32, s32, s32);
void fn_8000F2F8(s32, s32);
void fn_8000F320(s32);
void *fn_800687D8(CStruct *arg0, Unk_3FE1622A *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, f32 farg0, s32 arg_sp8, s32 arg_spC, s32 arg_sp10, s32 arg_sp14, s32 arg_sp18) {
    volatile double _dummy;
    s32 spC;
    s32 sp8;
    s32 temp_r0;
    s32 temp_r30_2;
    s32 var_r9;
    CStruct *temp_r10;
    CStruct *temp_r11;
    void *temp_r30;

    temp_r30_2 = lbl_802FFE98;
    fn_8000F2F8(temp_r30_2, fn_80068510(arg0));
    sp8 = arg_spC;
    spC = arg_sp18;
    temp_r30 = fn_80081920(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg_sp8, farg0, sp8, spC);
    fn_8000F320(lbl_802FFE98);
    if (temp_r30 == NULL) {
        return NULL;
    }
    var_r9 = 1;
    if (arg_sp10 == 0) {
        var_r9 = 0;
    }
    ((Unk_BEEADC60 *)temp_r30)->unk0x154 = var_r9;
    ((Unk_BEEADC60 *)temp_r30)->unk0x128 = (s32) (((Unk_BEEADC60 *)temp_r30)->unk0x128 | 1);
    fn_80064618(temp_r30, 1);
    ((Unk_BEEADC60 *)temp_r30)->unk0x148 = 0;
    temp_r0 = (((Unk_BEEADC60 *)temp_r30)->unk0x128 | 0x10000) & QB_UNKNOWN_0xFFFFFFFE;
    ((Unk_BEEADC60 *)temp_r30)->unk0x128 = temp_r0;
    if (arg_sp14 != 0) {
        ((Unk_BEEADC60 *)temp_r30)->unk0x128 = (s32) (temp_r0 | 0x10000);
        fn_800645D8(temp_r30, (char *)arg0 + 0x18);
    }
    temp_r10 = arg0->unk0x10;
    temp_r11 = temp_r30 + 0xC;
    temp_r0 = (s32) temp_r10->unk0x10;
    temp_r11->unk0xC = temp_r10;
    temp_r11->unk0x10 = temp_r0;
    *(void **)((char *)temp_r10->unk0x10 + 0xC) = temp_r11;
    temp_r10->unk0x10 = temp_r11;
    return temp_r30;
}
