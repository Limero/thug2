// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80081C84-0x80081CB4 (48B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// Stores a rodata string pointer (lbl_802964B0) into arg0->unk0x40, then
// calls fn_8006A8C0(arg0). Suggested rename: fn_80081C84_bind_name_string.
#include "types.h"
#include "structs.h"
extern char lbl_802964B0[];
void fn_8006A8C0(Unk_C7387A53 *arg0);
void fn_80081C84(Unk_C7387A53 *arg0) {
    arg0->unk0x40 = (s32)lbl_802964B0;
    fn_8006A8C0(arg0);
}