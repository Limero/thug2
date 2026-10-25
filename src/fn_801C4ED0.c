// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801C4ED0-0x801C4F00 (48B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_802ACBE8[];
extern s32 fn_8009F558(s32 arg0);

void fn_801C4ED0(Unk_C8FEE62D *arg0) {
    register s32 p __asm__("r11");
    p = arg0;
    ((Unk_1D62F22E_2 *)p)->unk0x18 = (s32)lbl_802ACBE8;
    fn_8009F558(arg0);
}
