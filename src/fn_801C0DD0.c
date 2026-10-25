// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801C0DD0-0x801C0E00 (48B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8009F558(Unk_C8FEE62D * arg0, s32 arg1);
extern char lbl_802AC708[];
void fn_801C0DD0(Unk_C8FEE62D *arg0, s32 arg1) {
    register s32 p __asm__("r11");
    p = (s32)arg0;
    ((Unk_1D62F22E_2 *)p)->unk0x18 = (s32)lbl_802AC708;
    fn_8009F558(arg0, arg1);
}
