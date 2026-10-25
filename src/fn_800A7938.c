// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A7938-0x800A7978 (64B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
void fn_800A7978(CStruct *);
void fn_800A7938(CStruct *arg0, s32 arg1) {
    fn_800A7978(arg0);
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
