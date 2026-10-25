// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80182E98-0x80182ED8 (64B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
void fn_80182E40(CStruct *);
void fn_80182E98(CStruct *arg0, s32 arg1) {
    fn_80182E40(arg0);
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
