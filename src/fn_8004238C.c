// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8004238C-0x800423F0 (100B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void fn_800438E8(void *, void *);
#include "structs.h"
#include "mem.h"
s32 fn_8003F608(s32, s32);
extern char lbl_80292598[];
void fn_8004238C(Unk_4313CFEA *arg0, s32 arg1) {
    arg0->unk0x8 = (s32)lbl_80292598;
    CTextElement_DetachBlurEffect();
    fn_800438E8(arg0, 0);
    if ((s32) arg0->unk0x190 != 0) {
        Mem_Free((void *) arg0->unk0x190);
    }
    fn_8003F608(arg0, arg1);
}
