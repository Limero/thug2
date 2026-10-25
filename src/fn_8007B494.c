// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8007B494-0x8007B4EC (88B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
#include "mem.h"
void fn_8005E55C(void *, s32);
void *fn_8009A710(void *, f32);
extern f32 lbl_80295B44;
extern char lbl_80295B58[];
void *fn_8007B494(Unk_C7387A53 *arg0) {
    fn_8005E55C(arg0, 0);
    arg0->unk0x4C = (s32)lbl_80295B58;
    arg0->unk0x50 = fn_8009A710(Mem_Alloc2(0x44), lbl_80295B44);
    return arg0;
}
