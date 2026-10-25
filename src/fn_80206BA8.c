// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80206BA8-0x80206C48 (160B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

void fn_80206BA8(Unk_C7387A53 *arg0) {
    extern s32 GetChecksum_3(Unk_6A70655D *, s32);
    arg0->unk0x24 = GetChecksum_3(*((void * *)&arg0->unk0xC), QB_INPUT);
    arg0->unk0x28 = GetChecksum_3(*((void * *)&arg0->unk0xC), QB_SKATERBALANCETRICK);
    arg0->unk0x2C = GetChecksum_3(*((void * *)&arg0->unk0xC), QB_SKATERCOREPHYSICS);
    arg0->unk0x30 = GetChecksum_3(*((void * *)&arg0->unk0xC), QB_SKATERFLIPANDROTATE);
    arg0->unk0x34 = GetChecksum_3(*((void * *)&arg0->unk0xC), QB_SKATERSTATE);
    arg0->unk0x38 = GetChecksum_3(*((void * *)&arg0->unk0xC), QB_STATSMANAGER);
}