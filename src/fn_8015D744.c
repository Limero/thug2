// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8015D744-0x8015D7CC (136B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305EAC;
s32 fn_80128C80(CStruct *, void *, void *, s32);
void *fn_801746A4(Unk_C7387A53 *, s32);
s32 fn_801403CC(void *);
s32 fn_80182E20(Unk_C7387A53 *);
void AddInteger(CStruct *, s32, s32);
bool ScriptGetBonusValue(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    Unk_FFAD6788 *temp_r3;
    s32 temp_r30;
    s32 g;

    g = lbl_80305EAC;
    sp8 = 0;
    fn_80128C80(pParams, QB_SKATER, &sp8, 1);
    temp_r3 = fn_801746A4(g, sp8);
    if (temp_r3->unk0xC8 != 0) {
        temp_r3 = fn_801403CC(temp_r3);
        temp_r30 = pScript->unk0x18;
        AddInteger(temp_r30, QB_BONUS, fn_80182E20((s32)temp_r3));
    }
    return true;
}
