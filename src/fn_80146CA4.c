// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80146CA4-0x80146CF0 (76B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
void fn_80172A18(void);
extern char lbl_8029FC30[];
void fn_80146CA4(Unk_C7387A53 *arg0, s32 arg1) {
    arg0->unk0xC = (s32)lbl_8029FC30;
    fn_80172A18();
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
