// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80159CE4-0x80159D7C (152B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_80305F9C[];
extern char lbl_80305EAC[];

s32 GetInteger(CStruct *, u32, s32 *, s32);
s32 NextItem(s32, s32);
s32 fn_801746A4(s32);
s32 fn_80141988(Unk_C7387A53 *);
s32 GetChecksum_3(Unk_6A70655D *, s32);
void fn_801BEC5C(Unk_C7387A53 *);

bool ScriptToggleSkaterCamMode(CStruct *pParams, CScript *pScript) {
    s32 sp8;
    CScript *temp_r3;
    register s32 temp_r4 __asm__("r4");
    s32 var_r31;
    s32 temp_r27;

    GetInteger(pParams, QB_SKATER, &sp8, 0);
    var_r31 = 0;
    temp_r4 = sp8;
    __asm__("" : "+r"(temp_r4));
    temp_r27 = *(s32 *)&lbl_80305F9C;
    if (temp_r4 == 0) {
        temp_r3 = NextItem(temp_r27, temp_r4);
        if (temp_r3 != NULL) {
            var_r31 = temp_r3->unk0x18;
        }
    } else {
        var_r31 = fn_801746A4(*(s32 *)&lbl_80305EAC);
    }
    if (var_r31 != 0) {
        fn_801BEC5C(GetChecksum_3(fn_80141988(var_r31), QB_SKATERCAMERA));
    }
    return true;
}
