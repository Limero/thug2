// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015BE00-0x8015BE78 (120B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_80305EAC;
extern Unk_C7387A53 * lbl_80305F24;
extern char lbl_802A81A4[];
typedef struct { char _0[0x24]; s32 lvl; } G39_t;
s32 fn_80128294(CStruct *, void *, void *, s32);
s32 fn_801A6CCC(Unk_93C2DF4D *);
s32 fn_801B0F94(Unk_C7387A53 *, s32);
void fn_801B07D4(CStruct *, CStruct *);
bool ScriptUpdateArcadeScores(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    G39_t *temp_r31;

    temp_r31 = (G39_t *)lbl_80305EAC;
    if (fn_80128294(pParams, (s32)lbl_802A81A4, &sp8, 0) == 0) {
        sp8 = fn_801A6CCC(temp_r31->lvl);
    }
    fn_801B07D4(*(s32 *)((char *)fn_801B0F94(lbl_80305F24, sp8) + 0xC), pParams);
    return true;
}
