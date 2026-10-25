// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80165C10-0x80165E58 (584B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80301A78;
extern s32 lbl_80305EAC;
extern s32 lbl_80305F9C;
extern s32 lbl_80305FF8;
extern char lbl_802A8450[];
extern char lbl_802A8460[];
extern char lbl_802A8470[];
s32 CStruct_new(s32 arg0);
s32 CStruct_ctor(void);
void fn_80127CD4(CStruct * arg0, s32 arg1, s32 arg2);
void s_insert_story_info(CStruct * arg0);
void s_insert_story_skater_info(CStruct * arg0);
void s_insert_custom_skater_info(s32 arg0);
s32 fn_801259C8(s32 arg0, s32 arg1);
void fn_80127AAC(CStruct * arg0, s32 arg1, Unk_5AA7B5D7 * arg2);
s32 fn_8021E024(void * arg0);
void fn_80126FF4(Unk_80577C09 * arg0, CStruct * arg1);
s32 fn_801746A4(Unk_C7387A53 * arg0, s32 arg1);
void fn_80127C90(CStruct * arg0, void * arg1, CStruct * arg2);
void fn_80127B28(CStruct * arg0, void * arg1, Unk_5AA7B5D7 * arg2);
void fn_802331B8(s32 arg0, CStruct * arg1);
s32 fn_800A5308(CStruct * arg0, s32 arg1);
s32 GetChecksum_3(Unk_6A70655D * arg0, s32 arg1);
void fn_801F4F88(s32 arg0, CStruct * arg1);
void s_insert_global_info(CStruct * arg0);
void s_insert_game_save_info(s32 arg0, CStruct *arg1) {
    register s32 temp_r30 __asm__("r30");
    s32 obj;

    obj = lbl_80305EAC;
    switch ((u32)arg0) {
    case QB_OPTIONSANDPROS:
        CStruct_new(8);
        temp_r30 = CStruct_ctor();
        s_insert_global_info(temp_r30);
        fn_80127CD4(arg1, QB_GLOBALINFO, temp_r30);
        CStruct_new(8);
        temp_r30 = CStruct_ctor();
        s_insert_story_info(temp_r30);
        fn_80127CD4(arg1, QB_STORY, temp_r30);
        CStruct_new(8);
        temp_r30 = CStruct_ctor();
        s_insert_story_skater_info(temp_r30);
        fn_80127CD4(arg1, QB_STORYSKATER, temp_r30);
        CStruct_new(8);
        temp_r30 = CStruct_ctor();
        s_insert_custom_skater_info(temp_r30);
        fn_80127CD4(arg1, QB_CUSTOMSKATER, temp_r30);
        fn_80127AAC(arg1, QB_LAYER_INFOS, fn_801259C8(QB_EDIT_GRAPHIC_LAYER_INFOS, 1));
        return;
    case QB_NETWORKSETTINGS:
        fn_80126FF4(arg1, fn_8021E024(lbl_80305F9C) + 4);
        return;
    case QB_CAT: {
        s32 p;
        p = fn_801746A4(obj, 0);
        temp_r30 = ((Unk_31DE137E *)p)->unk0x194;
        fn_80127C90(arg1, (s32)lbl_802A8450, ((CStruct *)temp_r30)->unk0x0);
        fn_80127B28(arg1, (s32)lbl_802A8460, ((CStruct *)temp_r30)->unk0x4);
        fn_80127B28(arg1, (s32)lbl_802A8470, ((CStruct *)temp_r30)->unk0x8);
        return;
    }
    case QB_PARK:
        fn_802331B8(lbl_80305FF8, arg1);
        return;
    case QB_CREATEDGOALS:
        fn_801F4F88(GetChecksum_3(fn_800A5308(lbl_80301A78, QB_GOALEDITOR), QB_GOALEDITOR), arg1);
        return;
    case QB_CREATEDGRAPHIC:
        fn_80127AAC(arg1, QB_LAYER_INFOS, fn_801259C8(QB_EDIT_GRAPHIC_LAYER_INFOS, 1));
        return;
    case QB_UNKNOWN_0xF0000000:
        break;
    }
}
