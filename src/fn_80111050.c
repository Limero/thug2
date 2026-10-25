// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80111050-0x801110F0 (160B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_8012834C(CStruct *, void *, void *, s32);
void *fn_8005DDBC(s32);
extern f32 lbl_80291314;
extern f32 lbl_80291318;
extern char lbl_8029CF88[];
extern char lbl_8029CF90[];
bool ScriptSetClippingDistances(CStruct *pParams, CScript *pScript) {
    f32 sp8;
    f32 spC;
    f32 temp_f0;
    f32 temp_f13;
    s32 var_r31;
    Unk_FFAD6788 *temp_r3;

    sp8 = lbl_80291318;
    spC = lbl_80291314;
    fn_8012834C(pParams, (void *)lbl_8029CF88, &sp8, 0);
    var_r31 = 0;
    fn_8012834C(pParams, (void *)lbl_8029CF90, &spC, 0);
    do {
        temp_r3 = fn_8005DDBC(var_r31);
        if (temp_r3 != NULL) {
            temp_f0 = sp8;
            temp_f13 = spC;
            *((f32 *)&temp_r3->unk0xC4) = temp_f0;
            *((f32 *)&temp_r3->unk0xC8) = temp_f13;
        }
        var_r31 += 1;
    } while (var_r31 <= 1);
    return true;
}
