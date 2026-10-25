// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801639A4-0x801639F0 (76B). Byte-identical.
#include "types.h"
extern void* lbl_80305EAC;
#include "qb_constants.h"
#include "structs.h"
s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 fn_801746A4(Unk_C7387A53 *, s32);
s32 fn_801403CC(void *);
s32 fn_80180528(Unk_C7387A53 *);
bool ScriptSetSpecialBarColors(CStruct *pParams, CScript *pScript) {
    s32 sp8;

    GetInteger(pParams, QB_SKATER, &sp8, 1);
    fn_80180528(fn_801403CC(fn_801746A4(lbl_80305EAC, sp8)));
    return true;
}
