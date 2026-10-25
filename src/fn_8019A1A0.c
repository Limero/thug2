// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8019A1A0-0x8019A1D4 (52B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_802AAA50[];
void fn_8019A1A0(CStruct *arg0, s32 arg1) {
    arg0->unk0x4 = (s32)lbl_802AAA50;
    if (arg1 & 1) {
        Mem_Free();
    }
}
