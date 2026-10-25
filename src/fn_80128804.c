// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80128804-0x80128850 (76B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_8000A778(s32);
void GetChecksum_2(CStruct *, s32, s32 *, s32);
// GetChecksum_4 @ 0x80128804
void GetChecksum_4(CStruct *arg0, void *arg1, void *arg2, s32 arg3) {
    GetChecksum_2(arg0, fn_8000A778(arg1), arg2, arg3);
}