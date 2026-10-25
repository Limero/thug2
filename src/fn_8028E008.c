// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8028E008-0x8028E038 (48B). Byte-identical.
// extra_cflags: -msdata=eabi, -G4
// FLAG: -msdata=eabi -G4
// Dispatcher thunk — forwards nonzero arg to the handler registered in the
// .sdata slot lbl_803CA324 (r13 SDA21 form, resolved at link vs _SDA_BASE_).
// ProDG ngccc object. Promoted via the sda_verify route (AGENTS.md 5q).
#include "types.h"

typedef s32 (*cb_t)(s32);
extern cb_t lbl_803CA324;

s32 fn_8028E008(s32 arg0) {
    if (arg0 != 0) {
        arg0 = lbl_803CA324(arg0);
    }
    return arg0;
}
