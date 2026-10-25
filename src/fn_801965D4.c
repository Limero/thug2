// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801965D4-0x80196674 (160B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern char lbl_802AA668[];

void fn_8018B6F8(Unk_9AA07378 *, CStruct *);
s32 fn_8003E7CC(s32);
s32 fn_80128F94(Unk_9D4ED6AF *);
s32 fn_80129068(Unk_5AA7B5D7 *, s32, s32);
s32 GetArray(CStruct *, s32, s32 *, s32);
s32 GetInteger(CStruct *, s32, s32 *, s32);
void fn_80196740(Unk_3F93CF38 *, Unk_5AA7B5D7 *, s32);

void *fn_801965D4(Unk_5BB06F5F *arg0, CStruct *arg1) {
    s32 sp8;
    s32 spC;
    s32 temp_r3;

    fn_8018B6F8((s32)arg0, arg1);
    arg0->unk0x14 = (s32)lbl_802AA668;
    temp_r3 = fn_80128F94(fn_8003E7CC(0xC));
    arg0->unk0x53C = temp_r3;
    fn_80129068(temp_r3, 0x10, 0xA);
    GetArray(arg1, QB_BEAT_PATTERN, &sp8, 1);
    GetInteger(arg1, QB_TEMPO, &spC, 1);
    fn_80196740(arg0, sp8, spC);
    return arg0;
}
