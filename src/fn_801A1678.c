// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A1678-0x801A16C4 (76B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_8002DE6C(Unk_C7387A53 *);
s32 fn_801A1678(CScript *arg0) {
    if ((s32) arg0->unk0x24 != 0) {
        return 1;
    }
    if ((s32) arg0->unk0x1C != 0) {
        return 0;
    }
    return fn_8002DE6C((char *)arg0 + 0x40);
}
