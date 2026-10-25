// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80146DD4-0x80146E20 (76B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
void fn_8004A460(void);
extern char lbl_8029FBD0[];
void fn_80146DD4(Unk_C7387A53 *arg0, s32 arg1) {
    arg0->unk0xC = (s32)lbl_8029FBD0;
    fn_8004A460();
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
