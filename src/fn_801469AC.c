// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801469AC-0x801469F8 (76B). Byte-identical.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern char lbl_8029FD38[];
static void fn_8009D020(void);
void fn_801469AC(Unk_C7387A53 *arg0, s32 arg1) {
    arg0->unk0xC = (s32)lbl_8029FD38;
    fn_8009D020();
    if (arg1 & 1) {
        Mem_Free((void *)arg0);
    }
}
