// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005E5F4-0x8005E628 (52B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_80293C00[];
void fn_8005E5F4(Unk_C7387A53 *arg0, s32 arg1) {
    arg0->unk0x4C = (s32)lbl_80293C00;
    if (arg1 & 1) {
        Mem_Free();
    }
}
