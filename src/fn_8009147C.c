// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009147C-0x800914AC (48B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// Stores a rodata string pointer (lbl_80297018) into arg0->unk0x5C, then
// calls fn_80070210(arg0). Suggested rename: fn_8009147C_bind_name_string.
#include "types.h"
#include "structs.h"
extern char lbl_80297018[];
void fn_80070210(Unk_C7387A53 *arg0);
void fn_8009147C(Unk_C7387A53 *arg0) {
    arg0->unk0x5C = (s32)lbl_80297018;
    fn_80070210(arg0);
}