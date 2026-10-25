// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800E0BE0-0x800E0C40 (96B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_8009F558(s32, s32);
s32 fn_8006A4B0(s32, s32);
extern char lbl_80300450[];
extern char lbl_8029A6D0[];
void fn_800E0BE0(CScript *arg0, s32 arg1) {
    s32 temp_r0;
    temp_r0 = arg0->unk0x20;
    arg0->unk0x18 = (s32)lbl_8029A6D0;
    if (temp_r0 != 0) {
        fn_8006A4B0(*(s32 *)lbl_80300450, temp_r0);
    }
    fn_8009F558(arg0, arg1);
}
