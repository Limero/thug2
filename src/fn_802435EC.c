// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x802435EC-0x80243638 (76B). Byte-identical.
#include "types.h"
#include "mem.h"
extern char lbl_803060AC[];
void fn_80243B14(void *);
void fn_802435EC(s32 arg0, s32 arg1) {
    fn_80243B14(arg0);
    *(s32 *)&lbl_803060AC = 0;
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
