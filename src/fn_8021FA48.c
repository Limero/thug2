// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8021FA48-0x8021FAB4 (108B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_80137744(s32);
s32 fn_8022BC98(s32, s32);
void fn_8000A578(s32, s32);
extern char lbl_80303148[];
extern char lbl_80303448[];
void fn_8021FA48(Unk_26CD8A51 *arg0, s32 arg1) {
    s32 g1 = *(s32 *)lbl_80303148;
    s32 g2 = *(s32 *)lbl_80303448;
    arg0->unk0x1D0 = -1;
    if (arg1 != 0) {
        arg0->unk0x1F4 = arg1;
    }
    fn_8000A578(g1 + 8, arg0->unk0xE4);
    fn_8022BC98((s32)arg0, 2);
    fn_80137744(g2);
}
