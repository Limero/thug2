// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015FDF4-0x8015FF58 (356B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 GetStructure(s32, s32);
s32 GetStructure_2(CStruct *, s32, s32 *, s32);
s32 fn_801281BC(s32, s32, s32 *, s32);
s32 AddString(CStruct *, s32, void *);
s32 GetArray(CStruct *, s32, s32 *, s32);
s32 GetChecksum(CStruct *, s32);
s32 fn_801259C8(s32, s32);
s32 fn_80129528(CStruct *, s32);
s32 GetString(CStruct *, s32 *, s32 *, s32);
s32 AddChecksum(CStruct *, s32, s32);

bool ScriptGetTrickDisplayText(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 spC;
    s32 sp10;
    s32 sp14;
    s32 sp18;
    s32 sp1C;
    s32 sp20;
    s32 temp_r3;

    GetChecksum_2(pParams, QB_TRICK, &sp8, 1);
    temp_r3 = GetStructure(sp8, 1);
    if (temp_r3 != 0) {
        GetStructure_2(temp_r3, QB_PARAMS, &spC, 1);
        fn_801281BC(spC, QB_NAME, &sp10, 1);
        AddString(pScript->unk0x18, QB_TRICK_DISPLAY_TEXT, sp10);
        sp14 = 0;
        if ((GetChecksum_2(spC, QB_EXTRATRICKS, &sp14, 0) == 0) &&
            (GetArray(spC, QB_EXTRATRICKS, &sp18, 0) != 0)) {
            sp14 = GetChecksum(sp18, 0);
        }
        if (sp14 != 0) {
            GetStructure_2(fn_80129528(fn_801259C8(sp14, 1), 0), QB_PARAMS, &sp1C, 1);
            GetString(sp1C, QB_NAME, &sp20, 1);
            temp_r3 = pScript->unk0x18;
            __asm__("" : "+r"(temp_r3));
            AddString(temp_r3, QB_EXTRA_TRICK_STRING, sp20);
            AddChecksum(pScript->unk0x18, QB_EXTRA_TRICK_CHECKSUM, sp14);
        }
        return true;
    }
    return false;
}
