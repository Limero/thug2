// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8006A8C0-0x8006A91C (92B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
#include "mem.h"
extern char lbl_80294A68[];
extern char lbl_80366590[];
s32 fn_8006A960(s32, s32);
void fn_8006A8C0(Unk_C7387A53 *arg0, s32 arg1) {
    void *sp8;

    arg0->unk0x40 = (s32)lbl_80294A68;
    sp8 = arg0;
    fn_8006A960((s32)lbl_80366590, &sp8);
    if (arg1 & 1) {
        Mem_Free(arg0);
    }
}
