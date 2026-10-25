// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800A1840-0x800A1874 (52B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_80297BF0[];
void fn_800A1840(Unk_9994C3F5 *arg0, s32 arg1) {
    arg0->unk0x8 = (s32)lbl_80297BF0;
    if (arg1 & 1) {
        Mem_Free();
    }
}
