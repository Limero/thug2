// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80240B80-0x80240BB4 (52B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_802B1250[];
void fn_80240B80(Unk_C7387A53 *arg0, s32 arg1) {
    arg0->unk0xC = (s32)lbl_802B1250;
    if (arg1 & 1) {
        Mem_Free();
    }
}
