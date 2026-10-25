// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801C0944-0x801C09A0 (92B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
void fn_801C0A9C(Unk_DB0E2BAB * arg0);
void fn_801C0AE4(CScript * arg0);
s32 fn_801C0944(Unk_DB0E2BAB *arg0, u32 arg1) {
    switch (arg1) {
    case QB_WALKCAMERA_FLUSHREQUEST:
        fn_801C0A9C(arg0);
        break;
    case QB_WALKCAMERA_RESET:
        fn_801C0AE4(arg0);
        break;
    default:
        return 2;
    }
    return 1;
}
