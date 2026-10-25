// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801604EC-0x801605AC (192B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_8009D364(void *, void *);
s32 GetInteger(CStruct *, void *, s32 *, void *);
void *fn_801746A4(Unk_C7387A53 *, void *);
extern void * lbl_8030191C;
extern s32 lbl_80305EAC;

bool ScriptControllerBoundToDifferentSkater(CStruct *pParams, CScript *pScript) {
    s32 spC;
    s32 sp8;
    s32 temp_r30;
    s32 var_r31;
    Unk_FFAD6788 *temp_r3;

    GetInteger(pParams, QB_SKATER, &sp8, (s32 *)1);
    GetInteger(pParams, (s32 *)QB_CONTROLLER, &spC, 1);
    temp_r30 = lbl_80305EAC;
    for (var_r31 = 0; var_r31 < 8; var_r31++) {
        if (var_r31 != sp8) {
            temp_r3 = fn_801746A4(temp_r30, var_r31);
            if ((temp_r3 != NULL) && (temp_r3->unk0xC8 != 0) &&
                (fn_8009D364(lbl_8030191C, var_r31) == spC)) {
                return true;
            }
        }
    }
    return false;
}
