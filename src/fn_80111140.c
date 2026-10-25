// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80111140-0x801111A8 (104B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_8012834C(CStruct *, void *, void *, s32);
void fn_8006EB90(f32);
void fn_8005DDBC(s32);
extern f32 lbl_8029CFA0;
extern char lbl_8029CF94[];
bool ScriptSetFogDistance(CStruct *pParams, CScript *pScript) {
    f32 sp8;
    s32 var_r31;

    sp8 = lbl_8029CFA0;
    var_r31 = 0;
    fn_8012834C(pParams, (void *)lbl_8029CF94, &sp8, 0);
    fn_8006EB90(sp8);
    do {
        fn_8005DDBC(var_r31);
        var_r31 += 1;
    } while (var_r31 <= 1);
    return true;
}
