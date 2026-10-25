// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80066E68-0x80066EA0 (56B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-schedule-insns
#include "types.h"
#include "structs.h"
s32 fn_80062DBC(Unk_EDE83D0E *);
extern char lbl_80294340[];
extern char lbl_80294358[];
void fn_80066E68(Unk_EDE83D0E * arg0) {
    arg0->unk0x20 = (s32)lbl_80294340;
    arg0->unk0x8 = (s32)lbl_80294358;
    fn_80062DBC(arg0);
}
