// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B2978-0x801B29F8 (128B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void *GetChecksum_3(Unk_6A70655D * arg0, s32 arg1);
s32 fn_800D64DC(CScript * arg0);

bool fn_801B2978(Unk_AA1A1735 *arg0) {
    Unk_130D31C8 *src;
    void *temp_r30;

    temp_r30 = GetChecksum_3((void *)*((s32 *)&arg0->unk0xC), QB_MOTION);
    if (temp_r30 != NULL && fn_800D64DC(temp_r30) != 0) {
        src = (__ps_t *)fn_800D64DC(temp_r30);
        arg0->unk0xD0 = src->unk0x80;
        arg0->unk0xD8 = src->unk0x88;
    } else {
        register void *def __asm__("r9");

        def = arg0->unk0xC;
        arg0->unk0xD0 = ((Unk_DF2324A8 *)def)->unk0x58;
        arg0->unk0xD8 = ((Unk_DF2324A8 *)def)->unk0x60;
    }
    return true;
}
