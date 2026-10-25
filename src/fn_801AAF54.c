// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801AAF54-0x801AAF94 (64B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
void fn_801AAF94(Unk_C7387A53 *);
void fn_801AAF54(Unk_C7387A53 *arg0, s32 arg1) {
    fn_801AAF94(arg0);
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
