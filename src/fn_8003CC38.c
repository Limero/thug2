// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8003CC38-0x8003CF18 (736B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern f32 lbl_80292064;
extern f32 lbl_80292068;
extern s32 lbl_803003E8;
extern char lbl_803003F0[];
extern char lbl_802FFE98[];
extern s32 lbl_803018F8;
extern s32 lbl_80366474;
extern s32 lbl_80366478;
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 GetFloat(CStruct *, s32, f32 *, s32);
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 GetText(CStruct *, void *, void *, s32);
s32 fn_8003AB44(s32);
void fn_8000F2F8(Unk_9994C3F5 *, s32);
void fn_8000F320(void *);
s32 fn_8005CA70(CStruct *, s32, s32, s32, s32);
void fn_8005C0D8(s32, s32, s32);
s32 fn_8005CF80(void *, s32);
s32 fn_8005C21C(s32, s32, s32);
s32 fn_8005C2F8(void *, void *);
s32 fn_8005C250(s32, f32, f32);
void fn_8005C284(s32, f32, f32, f32);
s32 fn_8005C6E8(s32, s32, s32);
s32 fn_8005C10C(s32, s32, s32);
s32 fn_8005CC88(CStruct *, CStruct *);
s32 fn_8005C140(s32);
s32 fn_80061140(CStruct *, s32, s32, s32);

s32 fn_8003CC38(void) {
    s32 sp30;
    s32 sp2C;
    s32 sp28;
    s32 sp24;
    s32 sp20;
    s32 sp1C;
    f32 sp18;
    f32 sp14;
    s32 sp10;
    s32 spC;
    s8 sp8;
    s8 *sp8p;
    f32 temp_f2;
    Unk_9994C3F5 *temp_r3_2;
    s32 temp_r3;
    s32 temp_r26;
    register s32 temp_r30 __asm__("r30");
    s32 temp_r31;
    s32 var_r25;
    s32 var_r27;
    s32 var_r28;

    var_r25 = 0;
    temp_r3 = fn_8003AB44(*(s32 *)&lbl_803003F0);
    if (temp_r3 != 0) {
        GetChecksum_2(temp_r3, QB_DESC_ID, &spC, 1);
        if (spC == QB_CREATEDGRAPHIC) {
            temp_r3_2 = *(Unk_9994C3F5 **)lbl_802FFE98;
            fn_8000F2F8(temp_r3_2, temp_r3_2->unk0x118);
            GetChecksum_2(temp_r3, QB_IN, &sp10, 1);
            GetFloat(temp_r3, QB_X_SCALE, &sp14, 1);
            GetFloat(temp_r3, QB_Y_SCALE, &sp18, 1);
            GetChecksum_2(temp_r3, QB_WITH, &sp1C, 0);
            GetText(temp_r3, QB_TEMP_TEXTURE, &sp20, 1);
            temp_r30 = lbl_803018F8;
            lbl_803018F8 = 1;
            temp_r31 = fn_8005CA70(lbl_80366474, sp20, 0, 0, 1);
            lbl_803018F8 = temp_r30;
            fn_8005C0D8(temp_r31, 0, 0);
            temp_r26 = fn_8005CF80(lbl_80366478, QB_CAG_WORKSPACE);
            fn_8005C0D8(temp_r26, 0, 0);
            fn_8005C21C(temp_r31, temp_r26, 1);
            sp8p = &sp8;
            sp8p[0] = 0;
            sp8p[1] = 0;
            sp8p[2] = 0;
            sp8p[3] = 0;
            fn_8005C2F8(temp_r31, sp8p);
            fn_8005C250(temp_r31, sp14, sp18);
            if (GetInteger(temp_r3, QB_ROTATE, &sp24, 0) != 0) {
                temp_f2 = lbl_80292068;
                fn_8005C284(temp_r31, lbl_80292064, temp_f2, temp_f2);
            }
            var_r27 = 0;
            var_r28 = 0;
            if (GetInteger(temp_r3, QB_IS_DECK, &sp28, 0) != 0) {
                var_r27 = 1;
                GetText(temp_r3, QB_BASE_TEXTURE, &sp2C, 1);
                temp_r30 = lbl_803018F8;
                lbl_803018F8 = var_r27;
                var_r28 = fn_8005CA70(lbl_80366474, sp2C, 0, 0, 1);
                lbl_803018F8 = temp_r30;
                fn_8005C0D8(var_r28, 0, 0);
                fn_8005C6E8(var_r28, temp_r31, 1);
                fn_8005C10C(var_r28, 1, 0);
            }
            fn_8005C10C(temp_r31, 1, 0);
            GetText(temp_r3, QB_LOGO_TEXTURE, &sp30, 1);
            var_r25 = fn_80061140(lbl_803003E8, sp10, sp30, sp1C);
            if (var_r27 != 0) {
                fn_8005CC88(lbl_80366474, var_r28);
            }
            fn_8005CC88(lbl_80366474, temp_r31);
            fn_8005C140(temp_r26);
            fn_8000F320(*(void **)lbl_802FFE98);
        }
    }
    return var_r25;
}
