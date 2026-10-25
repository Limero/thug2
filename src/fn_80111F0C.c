// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80111F0C-0x80111FA0 (148B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 lbl_8029D05C;
extern f32 lbl_8029D060;
void fn_80128CE0(CStruct *, void *, void *, s32);
void *fn_80054EE8(void);
s32 fn_80111BE0(CStruct *, f32);
bool ScriptNudgeVC(CStruct *pParams, CScript *pScript) {
    f32 sp8;
    void *temp_r9;
    void *var_r31;
    CStruct *var_r3;

    sp8 = lbl_8029D05C;
    fn_80128CE0((s32)pParams, QB_PERCENT, &sp8, 1);
    sp8 = sp8 / lbl_8029D060;
    var_r3 = fn_80054EE8();
    if (var_r3 != NULL) {
        do {
            register void *temp_r9 __asm__("r9");
            s32 temp_r0;
            temp_r9 = *((void * *)&var_r3->unk0xC);
            temp_r0 = ((CStruct *)temp_r9)->unk0x4;
            var_r31 = temp_r9;
            if (temp_r0 == -1) {
                var_r31 = NULL;
            }
            fn_80111BE0(*((void * *)&var_r3->unk0x4), sp8);
            var_r3 = var_r31;
        } while (var_r3 != NULL);
    }
    return true;
}
