// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A3910-0x801A397C (108B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_3(s32, s32);
void fn_801A3910(CStruct *arg0, Unk_6A70655D *arg1) {
    arg0->unk0x4 = arg1;
    arg0->unk0x8 = GetChecksum_3(arg1, QB_SKATERBALANCETRICK);
    arg0->unk0xC = GetChecksum_3(arg0->unk0x4, QB_SKATERSCORE);
    arg0->unk0x10 = GetChecksum_3(arg0->unk0x4, QB_INPUT);
}