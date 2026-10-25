// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80058580-0x800585B4 (52B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_80293400[];
void fn_80058580(CStruct *arg0, s32 arg1) {
    arg0->unk0x4 = (s32)lbl_80293400;
    if (arg1 & 1) {
        Mem_Free();
    }
}
