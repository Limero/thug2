// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800EDF68-0x800EDFC0 (88B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern s32 GetChecksum_3(Unk_6A70655D *, s32);
extern void fn_800EE918(CScript *);
void fn_800EDF68(Unk_31DE137E *arg0) {
    *((s32 *)&arg0->unk0xB8) = GetChecksum_3(arg0->unk0xC, QB_VEHICLE);
    arg0->unk0xBC = GetChecksum_3(arg0->unk0xC, QB_SOUND);
    fn_800EE918(arg0);
}
