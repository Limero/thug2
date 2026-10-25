// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802388E4-0x80238920 (60B). Byte-identical.
#include "types.h"
#include "mem.h"
extern char lbl_80306004[];
s32 fn_802351F4(void);
void fn_802388E4(void) {
    s32 *p = (s32 *)lbl_80306004;
    Mem_Alloc2(0x177D0);
    *p = fn_802351F4();
}
