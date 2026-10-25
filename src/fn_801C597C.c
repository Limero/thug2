// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801C597C-0x801C59AC (48B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_802ACCB8[];
extern s32 fn_8009F558(s32 arg0);

void fn_801C597C(Unk_C8FEE62D *arg0) {
    register s32 p __asm__("r11");
    p = arg0;
    ((Unk_1D62F22E_2 *)p)->unk0x18 = (s32)lbl_802ACCB8;
    fn_8009F558(arg0);
}
