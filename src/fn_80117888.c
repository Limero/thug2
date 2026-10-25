// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80117888-0x801178DC (84B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void GetChecksum_2(CStruct *, s32, s32 *, s32);
void fn_80131EA0(Unk_FFAD6788 *, s32);
// ScriptClearEventHandlerGroup @ 0x80117888
bool ScriptClearEventHandlerGroup(CStruct *arg0, Unk_FFAD6788 *arg1) {
    s32 sp8;

    sp8 = QB_DEFAULT;
    GetChecksum_2(arg0, 0, &sp8, 0);
    fn_80131EA0(arg1, sp8);
    return true;
}
