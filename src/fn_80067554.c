// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80067554-0x8006758C (56B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-schedule-insns
#include "types.h"
#include "structs.h"
s32 fn_80062DBC(Unk_EDE83D0E *);
extern char lbl_802944D8[];
extern char lbl_802944F0[];
void fn_80067554(Unk_EDE83D0E * arg0) {
    arg0->unk0x20 = (s32)lbl_802944D8;
    arg0->unk0x8 = (s32)lbl_802944F0;
    fn_80062DBC(arg0);
}
