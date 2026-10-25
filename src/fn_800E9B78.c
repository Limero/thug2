// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800E9B78-0x800E9BFC (132B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern char lbl_8029ABA4[];

void fn_8020D2E4(void *arg0, s32 arg1);
void fn_8009F010(void *arg0, s32 arg1, s32 arg2);
void fn_801EC3F0(void *arg0, void *arg1);
void fn_80212C54(void *arg0, void *arg1, void *arg2);

void fn_800E9B78(Unk_2215E5E2 *arg0) {
    fn_8020D2E4(arg0, 1);
    fn_8009F010((void *)arg0->unk0xC, QB_SKATEREXITHANG, 0);
    fn_801EC3F0((void *)arg0->unk0x1858, lbl_8029ABA4);
    *(__ps_t *)((char *)arg0 + 0x1958) = *(__ps_t *)((char *)arg0 + 0x50);
    *(__ps_t *)((char *)arg0 + 0x1960) = *(__ps_t *)((char *)arg0 + 0x58);
    fn_80212C54(arg0, (char *)arg0 + 0x38, (char *)arg0 + 0x48);
    arg0->unk0xB4 = arg0->unk0x1A04;
}
