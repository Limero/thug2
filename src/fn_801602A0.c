// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801602A0-0x80160324 (132B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern void* lbl_80305EAC;
s32 GetString(CStruct *, s32 *, s32 *, s32);
s32 Script_GenerateCRC(s32);
s32 fn_801745B4(s32);
s32 fn_801403CC(void *);
s32 fn_80182150(Unk_FFAD6788 *, s32, s32, s32, s32);
s32 AddInteger(CStruct *, s32, s32);

bool ScriptGetNumberOfTrickOccurrences(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 temp_r30;
    s32 occurrences;

    GetString(pParams, QB_TRICKTEXT, &sp8, 1);
    temp_r30 = Script_GenerateCRC(sp8);
    occurrences = fn_80182150(fn_801403CC(fn_801745B4(lbl_80305EAC)), temp_r30, 0, 0, 1);
    AddInteger(pScript->unk0x18, QB_NUMBER_OF_OCCURRENCES, occurrences);
    return true;
}
