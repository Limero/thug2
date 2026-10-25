// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8012E88C-0x8012E8D0 (68B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// Event/status check: if the u8 at arg0+2 equals 7 and the global
// lbl_8030342C is non-zero, call fn_80134844(global, arg0->unk0x4).
#include "types.h"
#include "structs.h"
extern s32 lbl_8030342C;
extern void fn_80134844(s32, s32);
void fn_8012E88C(Unk_5AA7B5D7 *arg0) {
    if (*(u8 *)((char *)arg0 + 0x2) == 7 && lbl_8030342C != 0) {
        fn_80134844(lbl_8030342C, arg0->unk0x4);
    }
}