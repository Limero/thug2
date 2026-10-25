// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80166C7C-0x80166F7C (768B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern CStruct * lbl_80301A78;
extern s32 lbl_80305E8C;
extern bool lbl_80305E90;
extern s32 lbl_80305EAC;
extern s32 lbl_80305EFC;
extern void* lbl_80305F9C;
extern s32 lbl_80305FF8;
extern char lbl_802A8450[];
extern char lbl_802A8460[];
extern char lbl_802A8470[];
s32 GetStructure_2(CStruct *, s32, s32 *, s32);
s32 GetArray(CStruct *, s32, s32 *, s32);
s32 GetStructure_3(CStruct *, void *, void *, s32);
s32 fn_80128610(CStruct *, void *, void *, s32);
void fn_80127AAC(CStruct *, s32, Unk_5AA7B5D7 *);
void s_read_global_info(CStruct *, CScript *);
void s_read_story_info(CStruct *);
void s_read_story_skater_info(s32, s32);
void s_read_custom_skater_info(s32);
s32 fn_8021E024(void *);
void fn_8013FF94(s32, s32);
s32 fn_801745B4(s32);
void fn_802331EC(s32, CStruct *, s32, s32);
s32 fn_800A5308(CStruct *, s32);
s32 GetChecksum_3(Unk_6A70655D *, s32);
void fn_801F5374(Unk_F0C166E4 *, CStruct *, s32);
void fn_80126FF4(Unk_80577C09 *, CStruct *);
void fn_80126E28(Unk_5AA7B5D7 *, Unk_5AA7B5D7 *);
void s_read_game_save_info(u32 arg0, CStruct *arg1, CScript *arg2, CStruct *arg3) {
    s32 sp8;
    s32 spC;
    s32 sp10;
    s32 sp14;
    s32 sp18;
    s32 sp1C;
    s32 sp20;
    s32 sp24;
    s32 sp28;
    s32 sp2C;
    Unk_31DE137E *temp_r30;

    lbl_80305E90 = 0;
    switch (arg0) {
    case QB_OPTIONSANDPROS:
        if (lbl_80305E8C & 1) {
            sp8 = 0;
            GetStructure_2(arg1, QB_GLOBALINFO, &sp8, 1);
            s_read_global_info(sp8, arg2);
        }
        if (lbl_80305E8C & 2) {
            spC = 0;
            GetStructure_2(arg1, QB_STORY, &spC, 1);
            s_read_story_info(spC);
        }
        if (lbl_80305E8C & 8) {
            sp10 = 0;
            GetStructure_2(arg1, QB_CUSTOMSKATER, &sp10, 1);
            s_read_custom_skater_info(sp10);
            lbl_80305E90 = 1;
        }
        if (lbl_80305E8C & 4) {
            sp14 = 0;
            GetStructure_2(arg1, QB_STORYSKATER, &sp14, 1);
            sp18 = 0;
            GetStructure_2(arg1, QB_CUSTOMSKATER, &sp18, 1);
            s_read_story_skater_info(sp14, sp18);
        }
        GetArray(arg1, QB_LAYER_INFOS, &sp1C, 1);
        fn_80127AAC(arg3, QB_LAYER_INFOS, sp1C);
        lbl_80305E8C = 0;
        break;
    case QB_NETWORKSETTINGS:
        fn_8013FF94(fn_8021E024(lbl_80305F9C), arg1);
        break;
    case QB_CAT:
        temp_r30 = fn_801745B4(lbl_80305EAC);
        if (temp_r30 != NULL) {
            GetStructure_3(arg1, (s32)lbl_802A8450, &sp20, 1);
            fn_80126FF4(**((s32 * *)&temp_r30->unk0x194), sp20);
            fn_80128610(arg1, (s32)lbl_802A8460, &sp24, 1);
            fn_80126E28(*(s32 *)(temp_r30->unk0x194 + 4), sp24);
            fn_80128610(arg1, (s32)lbl_802A8470, &sp28, 1);
            fn_80126E28(*(s32 *)(temp_r30->unk0x194 + 8), sp28);
        }
        break;
    case QB_PARK:
        fn_802331EC(lbl_80305FF8, arg1, 1, 0);
        break;
    case QB_CREATEDGOALS:
        fn_801F5374(GetChecksum_3(fn_800A5308(lbl_80301A78, QB_GOALEDITOR), QB_GOALEDITOR), arg1, 0);
        break;
    case QB_CREATEDGRAPHIC:
        GetArray(arg1, QB_LAYER_INFOS, &sp2C, 1);
        fn_80127AAC(arg3, QB_LAYER_INFOS, sp2C);
        break;
    case QB_UNKNOWN_0xF0000000:
        break;
    }
}
