// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80144CC4-0x80145008 (836B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern f32 lbl_8029F844;
extern f32 lbl_8029F848;
extern void *lbl_802FFE98;
extern s32 lbl_803018F8;
extern CStruct * lbl_80366474;

extern s32 GetStructure(s32, s32);
extern void fn_8000F2F8(Unk_9F352E7C *, s32);
extern s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
extern s32 GetFloat(CStruct *, s32, f32 *, s32);
extern s32 GetText(CStruct *, void *, void *, s32);
extern s32 fn_8005CA70(CStruct *, s32, s32, s32, s32);
extern void fn_8005C0D8(s32, s32, s32);
extern s32 GetChecksum_3(Unk_6A70655D *, s32);
extern s32 fn_802069BC(void);
extern s32 fn_8005C21C(s32, s32, s32);
extern void fn_8005C2F8(s32, u32 *);
extern void fn_8005C250(s32, f32, f32);
extern s32 GetInteger(CStruct *, s32, s32 *, s32);
extern void fn_8005C284(s32, f32, f32, f32);
extern s32 fn_8005C6E8(s32, s32, s32);
extern s32 fn_8005C10C(s32, s32, s32);
extern void fn_800B6958(s32, s32, s32, s32);
extern void fn_8005CC88(CStruct *, CStruct *);
extern void fn_8005C140(s32);
extern void fn_8000F320(Unk_F12C5E01 *);

void fn_80144CC4(Unk_6A70655D *arg0, u32 arg1) {
    s8 sp8;
    s8 *sp8p;
    s32 spC;
    f32 sp10;
    f32 sp14;
    s32 sp18;
    s32 sp1C;
    f32 sp20;
    s32 sp24;
    s32 sp28;
    s32 sp2C;
    s32 temp_r26;
    s32 temp_r30;
    s32 temp_r30_2;
    s32 temp_r31;
    Unk_9994C3F5 *temp_r3;
    s32 var_r27;
    s32 var_r28;
    s32 var_r29;

    var_r28 = 0;
    switch (arg1) {
    case QB_HAT_LOGO:
        var_r28 = GetStructure(QB_CUSTOM_HATLOGO_PARAMS, 0);
        break;
    case QB_FRONT_LOGO:
        var_r28 = GetStructure(QB_CUSTOM_FRONTLOGO_PARAMS, 0);
        break;
    case QB_BACK_LOGO:
        var_r28 = GetStructure(QB_CUSTOM_BACKLOGO_PARAMS, 0);
        break;
    case 0x7CB4FA9:
        var_r28 = GetStructure(QB_CUSTOM_DECKLOGO_PARAMS, 0);
        break;
    }
    if (var_r28 != 0) {
        temp_r3 = lbl_802FFE98;
        fn_8000F2F8(temp_r3, temp_r3->unk0x118);
        GetChecksum_2(var_r28, QB_IN, &spC, 1);
        GetFloat(var_r28, QB_X_SCALE, &sp10, 1);
        GetFloat(var_r28, QB_Y_SCALE, &sp14, 1);
        GetChecksum_2(var_r28, QB_WITH, &sp18, 1);
        GetText(var_r28, QB_TEMP_TEXTURE, &sp1C, 1);
        temp_r30 = lbl_803018F8;
        lbl_803018F8 = 1;
        temp_r31 = fn_8005CA70(lbl_80366474, sp1C, 0, 0, 1);
        lbl_803018F8 = temp_r30;
        fn_8005C0D8(temp_r31, 0, 0);
        GetChecksum_3(arg0, QB_TAGGING);
        fn_8005C0D8(temp_r26 = fn_802069BC(), 0, 0);
        fn_8005C21C(temp_r31, temp_r26, 1);
        sp8p = &sp8;
        sp8p[0] = 0;
        sp8p[1] = 0;
        sp8p[2] = 0;
        sp8p[3] = 0;
        fn_8005C2F8(temp_r31, sp8p);
        fn_8005C250(temp_r31, sp10, sp14);
        if (GetInteger(var_r28, QB_ROTATE, &sp20, 0) != 0) {
            fn_8005C284(temp_r31, lbl_8029F844, lbl_8029F848, lbl_8029F848);
        }
        var_r27 = 0;
        var_r29 = 0;
        if (GetInteger(var_r28, QB_IS_DECK, &sp24, 0) != 0) {
            var_r27 = 1;
            GetText(var_r28, QB_BASE_TEXTURE, &sp28, 1);
            temp_r30_2 = lbl_803018F8;
            lbl_803018F8 = var_r27;
            var_r29 = fn_8005CA70(lbl_80366474, sp28, 0, 0, 1);
            lbl_803018F8 = temp_r30_2;
            fn_8005C0D8(var_r29, 0, 0);
            fn_8005C6E8(var_r29, temp_r31, 1);
            fn_8005C10C(var_r29, 1, 0);
        }
        fn_8005C10C(temp_r31, 1, 0);
        GetText(var_r28, QB_LOGO_TEXTURE, &sp2C, 1);
        fn_800B6958(GetChecksum_3(arg0, QB_MODEL), spC, sp2C, sp18);
        if (var_r27 != 0) {
            fn_8005CC88(lbl_80366474, var_r29);
        }
        fn_8005CC88(lbl_80366474, temp_r31);
        fn_8005C140(temp_r26);
        fn_8000F320(lbl_802FFE98);
    }
}
