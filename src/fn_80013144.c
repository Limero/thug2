// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80013144-0x80013180 (60B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_80013180(Unk_C7387A53 *);
extern char lbl_802908D8[];
void *fn_80013144(Unk_C7387A53 *arg0) {
    arg0->unk0x3C = (s32)lbl_802908D8;
    fn_80013180(arg0);
    return arg0;
}
