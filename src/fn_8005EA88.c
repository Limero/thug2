// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005EA88-0x8005EABC (52B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_80293BD0[];
void fn_8005EA88(CStruct *arg0, s32 arg1) {
    arg0->unk0x4 = (s32)lbl_80293BD0;
    if (arg1 & 1) {
        Mem_Free();
    }
}
