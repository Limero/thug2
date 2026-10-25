// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8021F840-0x8021F89C (92B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_8000A578(s32, s32);
s32 fn_80009C00(s32);
extern char lbl_80303148[];
void fn_8021F840(Unk_7A675EAB *arg0) {
    s32 g = *(s32 *)&lbl_80303148;
    s32 v = 1;
    if (arg0->unk0x48 == 1) v = 0;
    arg0->unk0x48 = v;
    if (v != 0) {
        fn_8000A578(g + 8, arg0->unk0xD0);
        return;
    }
    fn_80009C00(arg0->unk0xD0);
}