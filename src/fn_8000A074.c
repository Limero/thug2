// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000A074-0x8000A0A8 (52B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern char lbl_8028FF40[];
void fn_8000A074(Unk_9994C3F5 *arg0, s32 arg1) {
    arg0->unk0x8 = (s32)lbl_8028FF40;
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
