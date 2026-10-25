// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8005BF2C-0x8005BF60 (52B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_80293770[];
void fn_8005BF2C(Unk_9994C3F5 *arg0, s32 arg1) {
    arg0->unk0x8 = (s32)lbl_80293770;
    if (arg1 & 1) {
        Mem_Free();
    }
}
