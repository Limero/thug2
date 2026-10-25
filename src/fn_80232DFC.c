// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80232DFC-0x80232F24 (296B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 fn_80238970();
s32 fn_8022D76C(Unk_9994C3F5 *, s32);
void fn_8022D7C0(Unk_9994C3F5 *, s32);
void fn_8022D824(Unk_9994C3F5 *, s32);
void Script_RunScript(s32, s32, s32, s32, s32);
void fn_80232DFC(void *arg0, s32 arg1) {
    fn_8022D76C(*(s32 *)fn_80238970(), 0);
    fn_8022D7C0(*(s32 *)fn_80238970(), arg1);
    fn_8022D824(*(s32 *)fn_80238970(), arg1);
    if (arg1 != 0) {
        Script_RunScript(QB_PAUSE_TRICK_TEXT, 0, 0, 0, 0);
        Script_RunScript(QB_GOALMANAGER_HIDEPOINTS, 0, 0, 0, 0);
        Script_RunScript(QB_GOALMANAGER_HIDEGOALPOINTS, 0, 0, 0, 0);
        Script_RunScript(QB_SK4_HIDE_DEATH_MESSAGE, 0, 0, 0, 0);
        return;
    }
    Script_RunScript(QB_UNPAUSE_TRICK_TEXT, 0, 0, 0, 0);
    Script_RunScript(QB_GOALMANAGER_SHOWPOINTS, 0, 0, 0, 0);
    Script_RunScript(QB_GOALMANAGER_SHOWGOALPOINTS, 0, 0, 0, 0);
}
