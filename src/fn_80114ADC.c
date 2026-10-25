// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80114ADC-0x80114BAC (208B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_8029D1C4[];

void fn_801270B4(CStruct *, s32);
s32 AddInteger(CStruct *, s32, s32);
s32 GetString(CStruct *, s32 *, s32 *, s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 strlen(const char *);

bool ScriptStringToInteger(CStruct *arg0, CScript *arg1) {
    char *spC;
    s32 sp8;
    s32 temp_r3;
    s32 var_ctr;
    s32 var_r31;
    char *var_r11;

    sp8 = 0;
    if (GetChecksum_2(arg0, 0, &sp8, 0) == 0)
        return false;
    spC = lbl_8029D1C4;
    if (GetString(arg1->unk0x18, sp8, &spC, 0) == 0)
        return false;
    fn_801270B4(arg1->unk0x18, sp8);
    var_r31 = 0;
    temp_r3 = strlen(spC);
    var_r11 = spC;
    if (var_r31 < temp_r3) {
        var_ctr = temp_r3;
        do {
            var_r31 = (var_r31 * 10) + (s8)*var_r11 - 0x30;
            var_r11++;
        } while (--var_ctr != 0);
    }
    AddInteger(arg1->unk0x18, sp8, var_r31);
    return true;
}
