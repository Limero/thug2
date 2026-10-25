// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80070E90-0x80070EC4 (52B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_80295250[];
void fn_80070E90(CStruct *arg0, s32 arg1) {
    arg0->unk0x4 = (s32)lbl_80295250;
    if (arg1 & 1) {
        Mem_Free();
    }
}
