// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801BB1B8-0x801BB444 (652B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern s32 lbl_80305EFC;
extern char lbl_802AC298[];
extern char lbl_802AC2A0[];

s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 GetString(CStruct *, s32 *, s32 *, s32);
s32 GetStructure_2(CStruct *, s32, s32 *, s32);
s32 fn_801259C8(s32, s32);
s32 fn_80129528(CStruct *, s32);
s32 fn_801A5D88(Unk_C7387A53 *);
s32 fn_800F0F84(s32, s32);
s32 AddString(CStruct *, s32, void *);

bool fn_801BB1B8(void *arg0, s32 arg1, void *arg2) {
    s32 sp8;
    s32 spC;
    s32 sp10;
    s32 sp14;
    s32 sp18;
    s32 sp1C;
    s32 sp20;
    s32 sp24;
    s32 sp28;
    s32 mgr;
    CStruct *arr;
    register s32 count __asm__("r29");
    s32 entry;
    s32 i;
    s32 res;
    s32 zero;
    s32 prof;
    s32 flag24;
    register void *a0 __asm__("r26");
    register void *a2 __asm__("r27");

    a0 = arg0;
    a2 = arg2;
    flag24 = *(s32 *)(((Unk_C7387A53 *)a0)->unk0xC + 0x24);
    if (flag24 == 0 || GetChecksum_2(flag24, QB_PROFILE_NAME, &sp8, 0) == 0) {
        goto block_18;
    }
    if (sp8 == QB_CUSTOM) {
        mgr = fn_801A5D88(lbl_80305EFC) + 0x6C;
        if (GetChecksum_2(mgr, QB_VOICE, &spC, 0) == 0) {
            goto fallback;
        }
        arr = fn_801259C8(QB_PLAYER_VOICES, 1);
        count = arr->unk0x4;
        for (i = 0; i < count; i++) {
            entry = fn_80129528(arr, i);
            GetChecksum_2(entry, QB_ID, &sp10, 1);
            if (sp10 == spC) {
                sp14 = 0;
                GetString(entry, QB_STREAM_NAME, &sp14, 1);
                res = sp14;
                goto check;
            }
        }
        goto zero;

fallback:
            GetInteger(mgr, QB_IS_MALE, &sp18, 1);
            if (sp18 == 1) {
                res = (s32)lbl_802AC298;
            } else {
                res = (s32)lbl_802AC2A0;
            }
            goto check;

zero:
            res = 0;

check:
        if (res == 0) {
            goto block_18;
        }
        AddString(((CScript *)a2)->unk0x18, QB_VOICEPREFIX, res);
        return true;
    }
    arr = fn_801259C8(QB_MASTER_SKATER_LIST, 1);
    count = arr->unk0x4;
    for (i = 0; i < count; i++) {
        entry = fn_80129528(arr, i);
        GetChecksum_2(entry, QB_NAME, &sp1C, 1);
        if (sp1C == sp8) {
            GetString(entry, QB_LAST_NAME, &sp20, 1);
            res = sp20;
            goto tail_b;
        }
    }
    goto block_18;

tail_b:
    AddString(((CScript *)a2)->unk0x18, QB_VOICEPREFIX, res);
    return true;

block_18:
    prof = fn_800F0F84(*(s32 *)(((Unk_C7387A53 *)a0)->unk0xC + 0x18), 1);
    if (prof == 0) {
        return false;
    }
    zero = 0;
    sp24 = zero;
    GetStructure_2(prof, QB_PROFILE, &sp24, 0);
    if (sp24 == 0) {
        return false;
    }
    sp28 = zero;
    GetString(sp24, QB_VOICE_PREFIX, &sp28, 0);
    res = sp28;
    if (res == 0) {
        return false;
    }
    AddString(((CScript *)a2)->unk0x18, QB_VOICEPREFIX, res);
    return true;
}
