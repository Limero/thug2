// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80016810-0x8001685C (76B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern char lbl_80290B50[];
void fn_80016810(Unk_C7387A53 *arg0, s32 arg1) {
    arg0->unk0xC = (s32)lbl_80290B50;
    fn_800158D8();
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
