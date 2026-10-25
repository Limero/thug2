// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80165E58-0x80166640 (2024B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_802A8480[];
extern char lbl_802A8484[];
extern CStruct * lbl_80301A78;
extern s32 lbl_80305EAC;
extern s32 lbl_80305F9C;
extern s32 lbl_80305FF8;
s32 GetStructure_2(CStruct *, s32, s32 *, s32);
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 GetArray(CStruct *, s32, s32 *, s32);
s32 GetString(CStruct *, s32 *, s32 *, s32);
void AddInteger(CStruct *, s32, s32);
void AddChecksum(CStruct *, s32, s32);
void AddString(CStruct *, s32, void *);
void fn_801275D4(CStruct *, void *, void *);
s32 Game_GetGoalManager();
s32 fn_801869E4(Unk_31DE137E *);
s32 fn_8021E024(void *);
s32 fn_801746A4(Unk_C7387A53 *, s32);
s32 fn_800A5308(CStruct *, s32);
s32 GetChecksum_3(Unk_6A70655D *, s32);
s32 fn_801F59CC(s32);
s32 fn_80233908(void);
void fn_80233294(s32);
s32 fn_802332B8(s32, s32);
void fn_80233230(s32, s32, s32 *, s32 *, u16 *, s32 *, s32 *, s32 *);
s32 fn_801291FC(void *);

void s_generate_summary_info(s32 arg0, u32 arg1, CStruct *arg2) {
    u16 sp8;
    u16 spA;
    s32 spC;
    s32 sp10;
    s32 sp14;
    s32 sp18;
    s32 sp1C;
    s32 sp20;
    s32 sp24;
    s32 sp28;
    s32 sp2C;
    s32 sp30;
    s32 sp34;
    s32 sp38;
    s32 sp3C;
    s32 sp40;
    s32 sp44;
    s32 sp48;
    s32 sp4C;
    s32 sp50;
    s32 sp54;
    s32 sp58;
    s32 sp5C;
    s32 sp60;
    s32 sp64;
    s32 sp68;
    s32 sp6C;
    s32 sp70;
    s32 sp74;
    s32 sp78;
    s32 sp7C;
    s32 sp80;
    s32 sp84;
    s32 sp88;
    s32 var_r30;
    s32 p0;
    s32 temp_r3;
    register char *pFF8 __asm__("r29");

    p0 = arg0;
    if (arg2 != 0) {
        switch (arg1) {
        case QB_OPTIONSANDPROS:
            spC = 0;
            GetStructure_2(arg2, QB_STORY, &spC, 1);
            sp10 = 0;
            GetStructure_2(spC, QB_GOALMANAGERPARAMS, &sp10, 1);
            sp14 = 0;
            GetStructure_2(sp10, QB_GOALMANAGER_PARAMS, &sp14, 1);
            sp18 = 0;
            GetStructure_2(arg2, QB_GLOBALINFO, &sp18, 0);
            if (sp18 != 0) {
                sp1C = 0;
                GetStructure_2(sp18, QB_CAREER, &sp1C, 0);
                if (sp1C != 0) {
                    if (GetInteger(sp1C, QB_CLASSICTOTALSCORE, &sp20, 0) != 0) {
                        AddInteger(p0, QB_TOTAL_GOALS_COMPLETE, sp20);
                        GetInteger(sp1C, QB_UNKNOWN_0x7A6BF912, &sp20, 0);
                        AddInteger(p0, QB_TOTAL_GOALS_POSSIBLE, sp20);
                        GetInteger(sp1C, QB_UNKNOWN_0x0444419A, &sp20, 0);
                        AddInteger(p0, QB_TOTAL_SCORE, sp20);
                        GetInteger(sp1C, QB_UNKNOWN_0x95947B61, &sp20, 0);
                        AddInteger(p0, QB_TOTAL_SCORE_POTENTIAL, sp20);
                    }
                }
            }
            sp24 = 0;
            GetStructure_2(arg2, QB_CUSTOMSKATER, &sp24, 1);
            sp28 = 0;
            GetStructure_2(sp24, QB_CUSTOM, &sp28, 1);
            sp2C = 0;
            GetStructure_2(sp28, QB_INFO, &sp2C, 1);
            sp30 = 0;
            GetInteger(sp2C, QB_IS_MALE, &sp30, 0);
            AddInteger(p0, QB_IS_MALE, sp30);
            sp34 = (s32)lbl_802A8480;
            GetString(sp2C, QB_DISPLAY_NAME, &sp34, 0);
            AddString(p0, QB_NAME, sp34);
            break;
        case QB_NETWORKSETTINGS:
            fn_801275D4(p0, (s32)lbl_802A8484, (s32)lbl_802A8480);
            break;
        case QB_CAT:
            sp38 = 0;
            GetStructure_2(arg2, QB_OTHER_PARAMS, &sp38, 1);
            sp3C = (s32)lbl_802A8480;
            GetString(sp38, QB_NAME, &sp3C, 1);
            AddString(p0, QB_NAME, sp3C);
            break;
        case QB_PARK:
            var_r30 = 0;
            sp44 = NULL;
            sp40 = 0;
            GetStructure_2(arg2, QB_PARK_EDITOR_GOALS, &sp40, 0);
            if (sp40 != 0) {
                GetArray(sp40, QB_GOALS, &sp44, 0);
                if (sp44 != NULL) {
                    var_r30 = ((CStruct *)sp44)->unk0x4;
                }
            }
            AddInteger(p0, QB_NUM_EDITED_GOALS, var_r30);
            sp48 = 1;
            GetInteger(arg2, QB_MAXPLAYERS, &sp48, 0);
            AddInteger(p0, QB_MAXPLAYERS, sp48);
            sp4C = NULL;
            GetArray(arg2, QB_PARK_EDITOR_MAP, &sp4C, 1);
            sp50 = 0;
            sp54 = 0;
            sp8 = 0;
            sp58 = 0;
            sp5C = 0;
            sp60 = 0;
            fn_80233230(*(s32 *)&lbl_80305FF8, fn_801291FC(sp4C), &sp50, &sp54,
                        &sp8, &sp58, &sp5C, &sp60);
            AddInteger(p0, QB_NUM_GAPS, sp50);
            AddInteger(p0, QB_NUM_PIECES, sp54);
            AddInteger(p0, QB_THEME, sp8);
            AddChecksum(p0, QB_TOD_SCRIPT, sp58);
            AddInteger(p0, QB_WIDTH, sp5C);
            AddInteger(p0, QB_LENGTH, sp60);
            break;
        case QB_CREATEDGOALS:
            var_r30 = 0;
            sp64 = NULL;
            GetArray(arg2, QB_GOALS, &sp64, 0);
            if (sp64 != NULL) {
                var_r30 = ((CStruct *)sp64)->unk0x4;
            }
            AddInteger(p0, QB_NUM_EDITED_GOALS, var_r30);
            break;
        case QB_CREATEDGRAPHIC:
            break;
        case QB_UINT32_MAX:
            break;
        }
    } else {
        switch (arg1) {
        case QB_OPTIONSANDPROS: {
            register s32 obj __asm__("r30");
            register u16 *q __asm__("r29");
            u8 *b;
            GetStructure_2(fn_801869E4(Game_GetGoalManager()), QB_GOALMANAGER_PARAMS,
                        (sp68 = arg2, &sp68), 0);
            obj = *(s32 *)((s32)*(s32 *)&lbl_80305EAC + 0x24);
            __asm__("" : "=r"(q) : "r"((char *)obj + 0x5D8));
            __asm__("" : "=r"(b) : "r"((char *)obj + 0x5EE));
            AddInteger(p0, QB_TOTAL_SCORE, ((Unk_B0DD7FE7 *)obj)->unk0x5D8);
            AddInteger(p0, QB_TOTAL_SCORE_POTENTIAL, *(u16 *)(q + 1));
            AddInteger(p0, QB_TOTAL_GOALS_COMPLETE, ((Unk_B0DD7FE7 *)obj)->unk0x5EE);
            AddInteger(p0, QB_TOTAL_GOALS_POSSIBLE, ((Unk_1D62F22E_2 *)b)->unk0x1);
            break;
        }
        case QB_NETWORKSETTINGS:
            GetStructure_2(fn_8021E024(*(s32 *)&lbl_80305F9C) + 4, QB_NETWORK_ID,
                        (sp6C = arg2, &sp6C), 0);
            sp70 = (s32)lbl_802A8480;
            GetString(sp6C, QB_UI_STRING, &sp70, 0);
            AddString(p0, QB_NETWORK_ID, sp70);
            break;
        case QB_CAT:
            GetString(
                *(s32 *)*(s32 *)((char *)fn_801746A4(*(s32 *)&lbl_80305EAC, 0) +
                                 0x194),
                QB_NAME, (sp74 = (s32)lbl_802A8480, &sp74), 1);
            AddString(p0, QB_NAME, sp74);
            break;
        case QB_CREATEDGOALS:
        case QB_PARK:
            AddInteger(p0, QB_NUM_EDITED_GOALS,
                        fn_801F59CC(GetChecksum_3(
                            fn_800A5308(lbl_80301A78, QB_GOALEDITOR),
                            QB_GOALEDITOR)));
            if (arg1 == QB_PARK) {
                AddInteger(p0, QB_MAXPLAYERS, fn_80233908());
                pFF8 = (char *)0x80300000;
                temp_r3 = ((Unk_FCD5D187 *)pFF8)->unk0x5FF8;
                sp78 = 0;
                sp7C = 0;
                spA = 0;
                sp80 = 0;
                sp84 = 0;
                sp88 = 0;
                fn_80233294(temp_r3);
                var_r30 = ((Unk_FCD5D187 *)pFF8)->unk0x5FF8;
                fn_80233230(var_r30, fn_802332B8(var_r30, 0), &sp78, &sp7C,
                            &spA, &sp80, &sp84, &sp88);
                AddInteger(p0, QB_NUM_GAPS, sp78);
                AddInteger(p0, QB_NUM_PIECES, sp7C);
                AddInteger(p0, QB_THEME, spA);
                AddChecksum(p0, QB_TOD_SCRIPT, sp80);
                AddInteger(p0, QB_WIDTH, sp84);
                AddInteger(p0, QB_LENGTH, sp88);
            }
            break;
        case QB_CREATEDGRAPHIC:
            break;
        case QB_UINT32_MAX:
            break;
        }
    }
}
