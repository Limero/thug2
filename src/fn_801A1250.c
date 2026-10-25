// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A1250-0x801A128C (60B). Byte-identical.
#include "types.h"
#include "structs.h"

void fn_8002AEF4(s32, s32, s32);

bool fn_801A1250(CScript *arg0, s32 arg1) {
    if (arg0->unk0x3C != 0) {
        fn_8002AEF4(arg0->unk0x3C, arg0->unk0x18, arg1);
    }
    return true;
}
