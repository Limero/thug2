// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800CC9A8-0x800CC9FC (84B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_80119FB4(s32, s32);
void fn_8009F558(CScript *, s32);
extern char lbl_80299658[];
extern s32 lbl_80302C34;
void fn_800CC9A8(CScript *arg0, s32 arg1) {
    arg0->unk0x18 = (s32)lbl_80299658;
    fn_80119FB4(*(s32 *)&lbl_80302C34, arg0);
    fn_8009F558(arg0, arg1);
}
