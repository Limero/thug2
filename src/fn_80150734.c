// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80150734-0x8015077C (72B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_80150590(CStruct *, Unk_FFAD6788 *, s32);
bool ScriptFlushDeadObjects(s32, s32);
// ScriptCreate @ 0x80150734
void ScriptCreate(CStruct *arg0, Unk_FFAD6788 *arg1) {
    ScriptFlushDeadObjects(0, 0);
    fn_80150590(arg0, arg1, 0);
}
