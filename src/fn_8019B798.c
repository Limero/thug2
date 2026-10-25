// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8019B798-0x8019B7C0 (40B). Byte-identical.
#include "types.h"
#include "structs.h"
extern s32 lbl_802AAB74;
void fn_8019B798(void *arg0_in) {
    register s32 arg0 __asm__("r9");
    s32 v1;
    u16 v2;
    arg0 = (s32)arg0_in;
    v1 = lbl_802AAB74;
    v2 = ((Unk_638CF717 *)&lbl_802AAB74)->unk0x4;
    ((Unk_47A9D377 *)arg0)->unk0x14 = v2;
    ((Unk_47A9D377 *)arg0)->unk0x434 = 0;
    ((Unk_47A9D377 *)arg0)->unk0x10 = v1;
}
