// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8019D388-0x8019D3BC (52B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern char lbl_80303148[];
#include "structs.h"
s32 fn_8000A578(s32, s32);
void fn_8019D388(Unk_C8FEE62D *arg0, s32 arg1) {
    s32 g = *(s32 *)lbl_80303148;
    arg0->unk0x58 = arg1;
    fn_8000A578(g + 8, arg0->unk0x1C);
}
