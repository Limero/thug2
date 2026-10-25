// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8022A42C-0x8022A470 (68B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_80305EC0[];
extern s32 fn_80198F3C(s32);
void fn_8022A42C(CScript *arg0) {
    arg0->unk0x20 = fn_80198F3C(*(s32 *)&lbl_80305EC0);
    arg0->unk0x1D8 = (s32) (arg0->unk0x1D8 | 0x20000);
}
