// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8002C914-0x8002C948 (52B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_80291808[];
void fn_8002C914(Unk_9994C3F5 *arg0, s32 arg1) {
    arg0->unk0x8 = (s32)lbl_80291808;
    if (arg1 & 1) {
        Mem_Free();
    }
}
