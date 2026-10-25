// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80127848-0x8012788C (68B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_8000A778(s32);
void AddChecksum(CStruct *, s32, s32);
void fn_80127848(CStruct *arg0, void *arg1, s32 arg2) {
    AddChecksum(arg0, fn_8000A778(arg1), arg2);
}