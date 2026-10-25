// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B1C94-0x801B1CC4 (48B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_802ABF40[];
void fn_8009F558(Unk_C8FEE62D *, s32);
void fn_801B1C94(Unk_C8FEE62D *arg0, s32 arg1) {
    register s32 p __asm__("r11");
    p = arg0;
    ((CScript *)p)->unk0x18 = (s32)lbl_802ABF40;
    fn_8009F558(arg0, arg1);
}
