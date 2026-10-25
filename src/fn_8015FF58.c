// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015FF58-0x80160018 (192B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern void* lbl_80305EAC;
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 fn_80174A58(void *, CStruct *);
s32 s_find_trick_in_mapping(void *, void *, s32);
s32 AddChecksum(CStruct *, s32, s32);
s32 AddInteger(CStruct *, s32, s32);

bool ScriptGetSpecialTrickInfo(CStruct *pParams, CScript *pScript) {
    s32 sp8[4];
    s32 sp18;

    GetInteger(pParams, QB_INDEX, &sp18, 1);
    s_find_trick_in_mapping(sp8, fn_80174A58(lbl_80305EAC, 0), sp18);
    AddChecksum(pScript->unk0x18, QB_SPECIAL_TRICKSLOT, sp8[2]);
    if (sp8[3] != 0) {
        AddInteger(pScript->unk0x18, QB_SPECIAL_TRICKNAME, sp8[1]);
    } else {
        AddChecksum(pScript->unk0x18, QB_SPECIAL_TRICKNAME, sp8[1]);
    }
    AddInteger(pScript->unk0x18, QB_ISCAT, sp8[3]);
    return true;
}
