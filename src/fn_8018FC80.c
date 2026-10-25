// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018FC80-0x80190210 (1424B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

s32 GetArray(CStruct *, s32, s32 *, s32);
s32 GetString(CStruct *, s32 *, s32 *, s32);
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 fn_80128978(s32, s32);
s32 ContainsFlag(CStruct *, s32);
void AddString(CStruct *, s32, void *);
void fn_80127AAC(CStruct *, s32, void *);
s32 fn_8003E7CC(s32);
void *fn_80128F94(void *);
void fn_80129068(void *, s32, s32);
s32 fn_8018F89C(CStruct *, CStruct *, CStruct *, s32);
void fn_8018FAE8(char *, char *, void *, void *, s32);
s32 fn_8012935C(void *, s32);
void fn_80129218(void *, s32, s32);
s32 CreateString(char *);
void fn_80126A30(void *);
void fn_80128FB4(void *, s32);

bool fn_8018FC80(Unk_C7387A53 *arg0) {
    char buf[0x200];
    CStruct *combo_array;
    void *goal_desc_str;
    void *goal_desc_arr;
    void *view_text;
    void *view_tip;
    void *goal_text;
    void *key_combo_text;
    s32 cat_index;
    void *scratch_str;
    CStruct *scratch_arr;
    CStruct *arr28;
    CStruct *arr27;
    CStruct *dst;
    s32 n;
    s32 count;
    s32 i;

    combo_array = 0;
    if (GetArray(arg0->unk0x20, QB_KEY_COMBOS, &combo_array, 0) == 0) {
        return false;
    }
    if (fn_80128978(arg0->unk0x20, QB_ORIGINAL_GOAL_DESCRIPTION) == 0) {
        if (GetString(arg0->unk0x20, QB_GOAL_DESCRIPTION, &goal_desc_str, 0) != 0) {
            AddString(arg0->unk0x20, QB_ORIGINAL_GOAL_DESCRIPTION, goal_desc_str);
        } else if (GetArray(arg0->unk0x20, QB_GOAL_DESCRIPTION, &goal_desc_arr, 0) != 0) {
            fn_80127AAC(arg0->unk0x20, QB_ORIGINAL_GOAL_DESCRIPTION, goal_desc_arr);
        }
    }
    if (fn_80128978(arg0->unk0x20, QB_ORIGINAL_VIEW_GOALS_TEXT) == 0) {
        if (GetString(arg0->unk0x20, QB_VIEW_GOALS_TEXT, &view_text, 0) != 0) {
            AddString(arg0->unk0x20, QB_ORIGINAL_VIEW_GOALS_TEXT, view_text);
        }
    }
    if (fn_80128978(arg0->unk0x20, QB_ORIGINAL_VIEW_GOALS_TIP) == 0) {
        if (GetString(arg0->unk0x20, QB_VIEW_GOALS_TIP, &view_tip, 0) != 0) {
            AddString(arg0->unk0x20, QB_ORIGINAL_VIEW_GOALS_TIP, view_tip);
        }
    }
    if (fn_80128978(arg0->unk0x20, QB_ORIGINAL_GOAL_TEXT) == 0) {
        if (GetString(arg0->unk0x20, QB_GOAL_TEXT, &goal_text, 0) != 0) {
            AddString(arg0->unk0x20, QB_ORIGINAL_GOAL_TEXT, goal_text);
        }
    }
    if (fn_80128978(arg0->unk0x20, QB_ORIGINAL_KEY_COMBO_TEXT) == 0) {
        if (GetString(arg0->unk0x20, QB_KEY_COMBO_TEXT, &key_combo_text, 0) != 0) {
            AddString(arg0->unk0x20, QB_ORIGINAL_KEY_COMBO_TEXT, key_combo_text);
        }
    }
    cat_index = -1;
    if (ContainsFlag(arg0->unk0x20, QB_CREATE_A_TRICK) != 0) {
        GetInteger(arg0->unk0x20, QB_PREMADE_CAT_INDEX, &cat_index, 1);
    }
    arr28 = fn_80128F94(fn_8003E7CC(0xC));
    arr27 = fn_80128F94(fn_8003E7CC(0xC));
    n = combo_array->unk0x4;
    fn_80129068(arr28, n, 3);
    fn_80129068(arr27, n, 3);
    if (fn_8018F89C(combo_array, arr28, arr27, cat_index) == 0) {
        fn_80126A30(arr28);
        fn_80126A30(arr27);
        if (arr28 != NULL) {
            fn_80128FB4(arr28, 3);
        }
        if (arr27 != NULL) {
            fn_80128FB4(arr27, 3);
        }
        return false;
    }
    scratch_arr = 0;
    if (GetString(arg0->unk0x20, QB_ORIGINAL_GOAL_DESCRIPTION, &scratch_str, 0) != 0) {
        fn_8018FAE8(scratch_str, buf, arr28, arr27, 0x200);
        AddString(arg0->unk0x20, QB_GOAL_DESCRIPTION, scratch_str);
    } else {
        if (GetArray(arg0->unk0x20, QB_ORIGINAL_GOAL_DESCRIPTION, &scratch_arr, 0) != 0) {
            i = 0;
            count = scratch_arr->unk0x4;
            dst = fn_80128F94(fn_8003E7CC(0xC));
            fn_80129068(dst, count, 3);
            if (i < count) {
                do {
                    scratch_str = fn_8012935C(scratch_arr, i);
                    fn_8018FAE8(scratch_str, buf, arr28, arr27, 0x200);
                    fn_80129218(dst, i, CreateString(buf));
                    i += 1;
                } while (i < count);
            }
            fn_80127AAC(arg0->unk0x20, QB_GOAL_DESCRIPTION, dst);
            fn_80126A30(dst);
            if (dst != NULL) {
                fn_80128FB4(dst, 3);
            }
        }
    }
    if (GetString(arg0->unk0x20, QB_ORIGINAL_VIEW_GOALS_TEXT, &scratch_str, 0) != 0) {
        fn_8018FAE8(scratch_str, buf, arr28, arr27, 0x200);
        AddString(arg0->unk0x20, QB_VIEW_GOALS_TEXT, buf);
    }
    if (GetString(arg0->unk0x20, QB_ORIGINAL_VIEW_GOALS_TIP, &scratch_str, 0) != 0) {
        fn_8018FAE8(scratch_str, buf, arr28, arr27, 0x200);
        AddString(arg0->unk0x20, QB_VIEW_GOALS_TIP, buf);
    }
    if (GetString(arg0->unk0x20, QB_ORIGINAL_GOAL_TEXT, &scratch_str, 0) != 0) {
        fn_8018FAE8(scratch_str, buf, arr28, arr27, 0x200);
        AddString(arg0->unk0x20, QB_GOAL_TEXT, buf);
    }
    if (GetString(arg0->unk0x20, QB_ORIGINAL_KEY_COMBO_TEXT, &scratch_str, 0) != 0) {
        fn_8018FAE8(scratch_str, buf, arr28, arr27, 0x200);
        AddString(arg0->unk0x20, QB_KEY_COMBO_TEXT, buf);
    }
    fn_80126A30(arr28);
    fn_80126A30(arr27);
    if (arr28 != NULL) {
        fn_80128FB4(arr28, 3);
    }
    if (arr27 != NULL) {
        fn_80128FB4(arr27, 3);
    }
    return true;
}
