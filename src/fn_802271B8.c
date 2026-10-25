// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802271B8-0x8022722C (116B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 lbl_80305EC0;
void fn_8022048C(Unk_C7387A53 *);
s32 ScriptIsObserving(s32, s32);
s32 fn_80198F7C(s32);
void Script_RunScript(s32, s32, s32, s32, s32);
bool fn_802271B8(CScript *arg0) {
    fn_8022048C(*((void * *)&arg0->unk0x18));
    if ((ScriptIsObserving(0, 0) != 0) && (fn_80198F7C(lbl_80305EC0) == QB_NETGOALATTACK)) {
        Script_RunScript(QB_CREATE_RANKINGS, 0, 0, 0, 0);
    }
    return true;
}
