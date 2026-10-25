// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80146D88-0x80146DD4 (76B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
void fn_80230C54(void);
extern char lbl_8029FBE8[];
void fn_80146D88(Unk_C7387A53 *arg0, s32 arg1) {
    arg0->unk0xC = (s32)lbl_8029FBE8;
    fn_80230C54();
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
