// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80224734-0x80224774 (64B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8021CEC0(Unk_FFAD6788 *);
void ScriptExitSurveyorMode(s32, s32);
bool fn_80224734(CScript *arg0) {
    s32 temp_r30;

    temp_r30 = arg0->unk0x18;
    ScriptExitSurveyorMode(0, 0);
    fn_8021CEC0(temp_r30);
    return true;
}
