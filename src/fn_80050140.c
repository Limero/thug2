// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80050140-0x80050178 (56B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-schedule-insns
#include "types.h"
#include "structs.h"
s32 fn_8004F2C4(Unk_C5BAE83F *);
extern char lbl_80292CB0[];
extern char lbl_80292CD0[];
void fn_80050140(Unk_C5BAE83F *arg0) {
    arg0->unk0x1A8 = (s32)lbl_80292CB0;
    arg0->unk0x8 = (s32)lbl_80292CD0;
    fn_8004F2C4(arg0);
}
