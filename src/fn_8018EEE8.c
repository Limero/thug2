// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8018EEE8-0x8018EF54 (108B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_80305EAC[];
s32 fn_801745B4(void *arg0);
Unk_31DE137E *GetChecksum_3(Unk_6A70655D *arg0, s32 arg1);
s32 fn_801EFAB4(Unk_31DE137E *o);
s32 fn_8018EEE8(Unk_C7387A53 *arg0) {
    Unk_6A70655D *temp_r31;
    Unk_31DE137E *chk;

    temp_r31 = (Unk_6A70655D *)fn_801745B4((void *)*(s32 *)&lbl_80305EAC);
    chk = GetChecksum_3(temp_r31, QB_SKATERENDRUN);
    switch (arg0->unk0x28) {
    case 1:
        return fn_801EFAB4(chk);
    case 0:
        return ((u32)arg0->unk0x70 & 0x01000000u) >> 24;
    default:
        return 0;
    }
}
