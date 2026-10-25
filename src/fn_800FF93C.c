// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800FF93C-0x800FF980 (68B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_800071D4(void *);
extern char lbl_8029C2E0[];
void *fn_800FF93C(Unk_C7387A53 *arg0) {
    fn_800FD388();
    arg0->unk0xC = (s32)lbl_8029C2E0;
    fn_800071D4((char *)arg0 + 0xA0);
    return arg0;
}
