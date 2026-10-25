// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80016DBC-0x80016E18 (92B). Byte-identical.
#include "types.h"
#include "mem.h"
extern char lbl_802FFE98[];
void fn_80010E78(s32);
void fn_80010D94(s32, s32);
s32 fn_80016DBC(void) {
    s32 temp_r30;
    s32 temp_r30_2;

    temp_r30_2 = fn_80016D58();
    fn_80010D94(*(s32 *)((s32 *)((char *)(*(void * *)&lbl_802FFE98) + (s32)0x11C)), 0x20);
    temp_r30 = Mem_Alloc(temp_r30_2);
    fn_80010E78(*(s32 *)((s32 *)((char *)(*(void * *)&lbl_802FFE98) + (s32)0x11C)));
    return temp_r30;
}
