// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801C50A0-0x801C50FC (92B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern void fn_801C52EC(Unk_DB0E2BAB * arg0);
extern void fn_801C5510(Unk_DB0E2BAB * arg0);

s32 fn_801C50A0(Unk_DB0E2BAB *arg0, s32 arg1) {
    switch (arg1) {
    case QB_SKATERPHYSICSCONTROL_SWITCHWALKINGTOSKATING:
        fn_801C52EC(arg0);
        break;
    case QB_SKATERPHYSICSCONTROL_SWITCHSKATINGTOWALKING:
        fn_801C5510(arg0);
        break;
    default:
        return 2;
    }
    return 1;
}
