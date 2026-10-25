// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800677A8-0x800677E0 (56B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-schedule-insns
#include "types.h"
#include "structs.h"
s32 fn_80062DBC(Unk_EDE83D0E *);
extern char lbl_80294560[];
extern char lbl_80294578[];
void fn_800677A8(Unk_EDE83D0E * arg0) {
    arg0->unk0x20 = (s32)lbl_80294560;
    arg0->unk0x8 = (s32)lbl_80294578;
    fn_80062DBC(arg0);
}
