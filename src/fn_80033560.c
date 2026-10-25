// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80033560-0x80033594 (52B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_80291BD8[];
void fn_80033560(Unk_C8FEE62D *arg0, s32 arg1) {
    arg0->unk0x14 = (s32)lbl_80291BD8;
    if (arg1 & 1) {
        Mem_Free();
    }
}
