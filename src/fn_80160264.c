// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80160264-0x801602A0 (60B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_80305EAC;
s32 fn_801745B4(s32);
s32 fn_801403CC(void *);
void fn_80182AC8(Unk_C7387A53 *);

bool ScriptResetComboRecords(CStruct *pParams, CScript *pScript) {
    s32 temp_r3;

    temp_r3 = fn_801745B4(lbl_80305EAC);
    if (temp_r3 != 0) {
        fn_80182AC8(fn_801403CC(temp_r3));
    }
    return true;
}
