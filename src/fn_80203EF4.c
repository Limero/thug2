// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80203EF4-0x80203F5C (104B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_3(void *, void *);
s32 fn_801745B4(s32);
extern f32 lbl_802AEEB4;
extern f32 lbl_802AEEB8;
extern char lbl_80305EAC[];
void fn_80203EF4(Unk_DB0E2BAB *arg0) {
    f32 temp_f0;

    arg0->unk0x20 = fn_801745B4(*(s32 *)&lbl_80305EAC);
    arg0->unk0x24 = GetChecksum_3(arg0->unk0xC, QB_PEDLOGIC);
    temp_f0 = lbl_802AEEB4 * lbl_802AEEB8;
    *((f32 *)&arg0->unk0x1C) = (f32) (temp_f0 * temp_f0);
}
