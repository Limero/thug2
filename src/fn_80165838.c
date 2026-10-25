// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80165838-0x80165B44 (780B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_802FFE50;
extern s32 lbl_80302C34;
extern s32 lbl_80305EAC;
extern s32 lbl_80305EFC;
extern s32 lbl_80305F24;
extern s32 lbl_80305F9C;
extern char lbl_802A843C[];
void CStruct_new(s32 arg0);
s32 CStruct_ctor(void);
s32 fn_8017480C(Unk_FFAD6788 * arg0);
void fn_80126FF4(Unk_80577C09 * arg0, CStruct * arg1);
void fn_80127CD4(CStruct * arg0, s32 arg1, s32 arg2);
void fn_8011A8FC(s32 arg0);
void fn_8012772C(s32 arg0, s32 arg1);
void fn_8012570C(s32 arg0, s32 arg1);
void fn_8011E04C(void *arg0, void *arg1);
void AddInteger(CStruct * arg0, s32 arg1, s32 arg2);
s32 fn_8012587C(s32 arg0, s32 arg1);
void AddChecksum(CStruct * arg0, s32 arg1, s32 arg2);
s32 fn_8011D804(void);
s32 fn_8003E7CC(s32 arg0);
s32 fn_80128F94(Unk_9D4ED6AF * arg0);
void fn_80129068(Unk_5AA7B5D7 * arg0, s32 arg1, s32 arg2);
void fn_80129314(CStruct * arg0, s32 arg1, s32 arg2);
void AddArrayPointer(CStruct * arg0, s32 arg1, s32 arg2);
s32 fn_8021E02C(void * arg0);
void fn_80127C14(CStruct * arg0, s32 arg1, CStruct * arg2);
void fn_801A71DC(void * arg0, s32 arg1);
void fn_801B107C(CStruct * arg0, CStruct * arg1);
void fn_801A5E38(Unk_DB0E2BAB * arg0, CStruct * arg1);
void s_insert_global_info(CStruct *arg0) {
    u64 spA;
    u64 spB;
    register s32 *pp __asm__("r27");
    register s32 *qq __asm__("r26");
    s32 obj;
    s32 temp_r24;
    s32 h28;
    s32 x31;
    s32 var_r29;
    s32 walk_r30;
    char *pA4;
    s32 temp_r3;
    s32 v1;
    s32 v2;
    s32 v3;
    s32 v4;
    {
        pp = (s32 *)&spA;
        qq = (s32 *)&spB;
        CStruct_new(8);
        temp_r24 = CStruct_ctor();
        obj = lbl_80305EAC;
        h28 = fn_8017480C(obj);
        CStruct_new(8);
        x31 = CStruct_ctor();
        fn_80126FF4(x31, h28 + 4);
        fn_80127CD4(temp_r24, QB_SPLITSCREENPREFERENCES, x31);
        CStruct_new(8);
        x31 = CStruct_ctor();
        fn_8011A8FC(lbl_80302C34);
        fn_8012772C(x31, QB_MAINVOLUME);
        fn_8012570C(QB_MUSICVOLOUTSIDEBOX, 0);
        fn_8012772C(x31, QB_MUSICVOLUME);
        fn_8011E04C(pp, qq);
        v1 = (s32)(spA >> 32);
        v2 = (s32)spA;
        v3 = (s32)(spB >> 32);
        v4 = (s32)spB;
    }
    AddInteger(x31, QB_PLAYLISTFORBIDDENTRACKFLAGS1, v1);
    AddInteger(x31, QB_PLAYLISTFORBIDDENTRACKFLAGS2, v2);
    AddInteger(x31, QB_PLAYLISTFORBIDDENTRACKFLAGS3, v3);
    AddInteger(x31, QB_PLAYLISTFORBIDDENTRACKFLAGS4, v4);
    if (lbl_802FFE50 == 4) {
        AddChecksum(x31, QB_CURRENT_SOUNDTRACK, fn_8012587C((s32)lbl_802A843C, 0));
    }
    if (fn_8011D804() != 0) {
        AddChecksum(x31, 0, QB_RANDOMMODE);
    }
    fn_80127CD4(temp_r24, QB_SOUNDOPTIONS, x31);
    h28 = fn_80128F94(fn_8003E7CC(0xC));
    var_r29 = 0;
    qq = (char *)obj + 0x3A8;
    pp = (char *)obj + 0x3AC;
    pA4 = (char *)obj + 0x3A4;
    walk_r30 = 0;
    fn_80129068(h28, 8, 0xA);
    do {
        CStruct_new(8);
        x31 = CStruct_ctor();
        if (*(s32 *)((char *)(walk_r30 + (s32)qq)) != 0) {
            AddChecksum(x31, 0, QB_AUTOKICKON);
        }
        if (*(s32 *)((char *)(walk_r30 + (s32)pp)) != 0) {
            AddChecksum(x31, 0, QB_SPINTAPSON);
        }
        if (*(s32 *)((char *)(walk_r30 + (s32)pA4)) != 0) {
            AddChecksum(x31, 0, QB_VIBRATIONON);
        }
        fn_80129314(h28, var_r29++, x31);
        walk_r30 += 0x10;
    } while (var_r29 <= 7);
    AddArrayPointer(temp_r24, QB_CONTROLLERPREFERENCES, h28);
    fn_80127C14(temp_r24, QB_TAUNTS, fn_8021E02C(lbl_80305F9C) + 4);
    fn_80127CD4(arg0, QB_OPTIONS, temp_r24);
    fn_801A71DC(((Unk_975100B4 *)lbl_80305EAC)->unk0x24, arg0);
    fn_801B107C(lbl_80305F24, arg0);
    CStruct_new(8);
    temp_r3 = CStruct_ctor();
    fn_801A5E38(lbl_80305EFC, temp_r3);
    fn_80127CD4(arg0, QB_PROS, temp_r3);
}
