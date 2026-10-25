// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800670E0-0x80067118 (56B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-schedule-insns
#include "types.h"
#include "structs.h"
void fn_80062DBC(void *);
extern char lbl_802943C8[];
extern char lbl_802943E0[];
void fn_800670E0(Unk_C8FEE62D *arg0) {
    arg0->unk0x20 = (s32)lbl_802943C8;
    arg0->unk0x8 = (s32)lbl_802943E0;
    fn_80062DBC(arg0);
}
