// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8026A024-0x8026A058 (52B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -msdata=eabi -G4
// vprintf(fmt, args): loads the MSL printf state (.sdata lbl_803CA420 via
// r13) and dispatches to fn_8026BC98. Suggested rename: vprintf.
#include "types.h"
#include "structs.h"

extern s32 fn_8026BC98(Unk_C7387A53 *, char *, void *);
extern s32 lbl_803CA420;

void vprintf(void *fmt, void *args) {
    s32 p;

    p = lbl_803CA420;
    fn_8026BC98(((Unk_1D62F22E_2 *)p)->unk0x8, fmt, args);
}
