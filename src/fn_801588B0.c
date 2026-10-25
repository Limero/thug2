// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801588B0-0x8015896C (188B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern void* lbl_80305EAC;
extern s32 ContainsFlag(CStruct *, s32);
extern void *fn_801746A4(Unk_C7387A53 *, s32);

bool ScriptToggleAlwaysSpecial(CStruct *pParams, CScript *pScript) {
    Unk_C7387A53 *skater;
    s32 v;
    s32 w;
    s32 i;

    v = ContainsFlag(pParams, QB_ON);
    w = ContainsFlag(pParams, QB_OFF);
    for (i = 0; i <= 7; i++) {
        skater = (void *)fn_801746A4(lbl_80305EAC, i);
        if (skater != NULL) {
            if (v != 0) {
                skater->unk0x180 = 1;
            } else if (w != 0) {
                skater->unk0x180 = v;
            } else {
                skater->unk0x180 ^= 1;
            }
        }
    }
    return true;
}
