// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80070210-0x80070244 (52B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_80294D90[];
void fn_80070210(Unk_C7387A53 *arg0, s32 arg1) {
    arg0->unk0x5C = (s32)lbl_80294D90;
    if (arg1 & 1) {
        Mem_Free();
    }
}
