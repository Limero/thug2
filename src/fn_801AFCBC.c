// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801AFCBC-0x801AFD1C (96B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_80305EAC[];
extern s32 GetInteger(CStruct *, s32, s32 *, s32);
extern s32 fn_801A6B64(Unk_93C2DF4D *, s32);
s32 fn_801AF780(CStruct *, s32, CScript *);

s32 ScriptGetLevelGapTotals(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    GetInteger(pParams, QB_LEVEL, &sp8, 1);
    return fn_801AF780(fn_801A6B64(*(s32 *)((char *)*(s32 *)&lbl_80305EAC + 0x24), sp8), pParams, pScript);
}
