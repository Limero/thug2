// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801178DC-0x8011792C (80B). Byte-identical.
#include "types.h"
#include "structs.h"
void GetChecksum_2(CStruct *, s32, s32 *, s32);
void fn_801320EC(Unk_FFAD6788 *, s32);
// ScriptOnExceptionRun @ 0x801178DC
bool ScriptOnExceptionRun(CStruct *arg0, Unk_FFAD6788 *arg1) {
    s32 sp8;

    sp8 = 0;
    GetChecksum_2(arg0, 0, &sp8, 0);
    fn_801320EC(arg1, sp8);
    return true;
}
