// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8004F2C4-0x8004F320 (92B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
extern char lbl_80292DC0[];
extern char lbl_80292DE0[];
void fn_800A3C50(void *, s32);
void fn_8003F608(Unk_C5BAE83F *, s32);
void fn_8004F2C4(Unk_C5BAE83F *arg0, s32 arg1) {
    arg0->unk0x1A8 = (s32)lbl_80292DC0;
    arg0->unk0x8 = (s32)lbl_80292DE0;
    fn_800A3C50((char *)arg0 + 0x190, 0);
    fn_8003F608(arg0, arg1);
}
