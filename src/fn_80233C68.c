// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80233C68-0x80233E84 (540B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_4(CStruct * arg0, void * arg1, void *arg2, s32 arg3);
void fn_80230FA8(Unk_C7387A53 * arg0);
void fn_80232D14(Unk_C7387A53 * arg0, s32 arg1);
void fn_80232B98(Unk_C7387A53 * arg0, s32 arg1);
void fn_80232A40(void *arg0, s32 arg1, s32 arg2);
void fn_80230F50(void *arg0, s32 arg1);
s32 fn_80238970(void);
void fn_8022D89C(Unk_C7387A53 * o, s32 v);
void fn_8023C5A4(void);
s32 fn_8023C598(s32 arg0);
void fn_8023E724(CStruct * arg0);
extern char lbl_80305FF8[];
extern char lbl_802B0950[];
extern char lbl_802B0958[];

bool ScriptSetParkEditorState(CStruct *arg0) {
    s32 sp8;
    s32 spC;
    s32 temp_r31;

    temp_r31 = *(s32 *)&lbl_80305FF8;
    sp8 = 0;
    GetChecksum_4(arg0, (s32)lbl_802B0950, &sp8, 0);
    spC = 0;
    GetChecksum_4(arg0, (s32)lbl_802B0958, &spC, 0);
    switch ((u32)sp8) {
    case QB_OFF:
        fn_80232B98(temp_r31, QB_OFF);
        fn_80230FA8(temp_r31);
        fn_80232D14(temp_r31, 0);
        break;
    case QB_TEST_PLAY:
        fn_80232A40(temp_r31, QB_TEST_PLAY, 0x1625EDA);
        fn_80232B98(temp_r31, QB_TEST_PLAY);
        break;
    case QB_REGULAR_PLAY:
        fn_80230F50(temp_r31, QB_REGULAR_PLAY);
        fn_80232A40(temp_r31, QB_REGULAR_PLAY, 0x1625EDA);
        fn_80232B98(temp_r31, QB_REGULAR_PLAY);
        break;
    case QB_EDIT:
        if ((u32)spC == (u32)QB_CLEAR) goto L_body;
        if ((u32)spC <= (u32)QB_CLEAR) goto L_after;
        if (spC == QB_UNKNOWN_0x2A907CBC) goto L_body;
        if ((u32)spC > (u32)QB_UNKNOWN_0x2A907CBC) goto L_nuke;
        if (spC == QB_INITIALIZE) goto L_init;
        goto L_after;
    L_nuke:
        if (spC == QB_NUKE_PARK) goto L_body;
        goto L_after;
    L_init:
        fn_80230F50(temp_r31, QB_EDIT);
        goto L_after;
    L_body:
        fn_80232A40(temp_r31, QB_EDIT, spC);
        fn_8022D89C((void *)(*(s32 *)fn_80238970()), 2);
    L_after:
        fn_8023C5A4();
        if (fn_8023C598(0) != 0) {
            fn_8023E724((void *)fn_8023C598(1));
        }
        fn_80232B98(temp_r31, QB_EDIT);
        break;
    default:
        return false;
    }
    return true;
}
