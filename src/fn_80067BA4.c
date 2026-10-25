// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80067BA4-0x80067BDC (56B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-schedule-insns
#include "types.h"
#include "structs.h"
s32 fn_80062DBC(Unk_EDE83D0E *);
extern char lbl_80294670[];
extern char lbl_80294688[];
void fn_80067BA4(Unk_EDE83D0E * arg0) {
    arg0->unk0x20 = (s32)lbl_80294670;
    arg0->unk0x8 = (s32)lbl_80294688;
    fn_80062DBC(arg0);
}
