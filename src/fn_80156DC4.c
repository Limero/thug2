// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80156DC4-0x80156E90 (204B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_80305EFC[];

s32 GetChecksum_2(CStruct * arg0, s32 hash, s32 * out, s32 defval);
s32 GetInteger(CStruct * arg0, s32 hash, s32 * out, s32 defval);
s32 fn_801A5D9C(s32 a, s32 b);
s32 fn_801A6464(Unk_C7387A53 * a, s32 b);
s32 ContainsFlag(CStruct * a, s32 b);
void CStruct_dtor(CStruct * a);
void fn_80126FF4(Unk_80577C09 * a, CStruct * b);
void fn_8003A80C(Unk_31DE137E * a, Unk_31DE137E * b);

bool ScriptRestoreTemporaryAppearance(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    s32 spC;
    s32 lblval;
    s32 prof;
    s32 prof4;
    s32 entry;
    s32 entry4;
    s32 chk;
    s32 t;

    GetChecksum_2(pParams, QB_NAME, &sp8, 1);
    GetInteger(pParams, QB_PLAYER, &spC, 1);
    lblval = *(s32 *)&lbl_80305EFC;
    prof = fn_801A5D9C(lblval, spC);
    prof4 = prof + 4;
    entry = fn_801A6464(lblval, sp8);
    entry4 = entry + 4;
    chk = ContainsFlag(pParams, QB_NOFACETEXTURE);
    if (chk != 0) {
        t = prof + 0x5C;
        entry += 0x5C;
        CStruct_dtor(t);
        fn_80126FF4(t, entry);
    } else {
        fn_8003A80C(prof4, entry4);
    }
    return true;
}
