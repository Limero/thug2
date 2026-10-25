// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80013204-0x80013238 (52B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_802908D8[];
void fn_80013204(Unk_C7387A53 *arg0, s32 arg1) {
    arg0->unk0x3C = (s32)lbl_802908D8;
    if (arg1 & 1) {
        Mem_Free();
    }
}
