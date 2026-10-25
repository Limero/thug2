// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80117840-0x80117888 (72B). Byte-identical.
#include "types.h"
#include "structs.h"
void GetChecksum_2(CStruct *, s32, s32 *, s32);
void fn_80131E50(Unk_FFAD6788 *, s32);
// ScriptClearEventHandler @ 0x80117840
bool ScriptClearEventHandler(CStruct *arg0, Unk_FFAD6788 *arg1) {
    s32 sp8;

    GetChecksum_2(arg0, 0, &sp8, 1);
    fn_80131E50(arg1, sp8);
    return true;
}
