// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800EB4E0-0x800EB548 (104B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "structs.h"
s32 fn_8020D2E4(s32, s32);
extern char lbl_8029ACA0[];
void fn_801EC3F0(Unk_83A1E37F *, void *);
void fn_80212C54(Unk_9C8D3F51 *, void *, void *);
void fn_800EB4E0(Unk_298A0A9D *arg0) {
    fn_8020D2E4(arg0, 1);
    fn_801EC3F0(arg0->unk0x1858, (s32)lbl_8029ACA0);
    ((__ps_t *)arg0)[0x32B] = ((__ps_t *)arg0)[10];
    ((__ps_t *)arg0)[0x32C] = ((__ps_t *)arg0)[11];
    fn_80212C54(arg0, (char *)arg0 + 0x38, (char *)arg0 + 0x48);
}
