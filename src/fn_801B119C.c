// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B119C-0x801B11CC (48B). Byte-identical.
#include "types.h"
#include "structs.h"
extern char lbl_802ABE10[];

// WANT: no r4 setup at the bl -> per-caller 1-arg proto (recipe 87).
void fn_80033560(void *);
void fn_801B119C(Unk_C8FEE62D *arg0) {
    arg0->unk0x14 = (s32)lbl_802ABE10;
    fn_80033560(arg0);
}
