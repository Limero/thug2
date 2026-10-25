// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800ADCD4-0x800ADD64 (144B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_80013E2C(s32);
void fn_800AC884(s32, s32);
bool fn_800ADCD4(Unk_4A70D538 *arg0) {
    if (arg0->unk0x8 != 0) {
        return true;
    }
    if (arg0->unk0x34B8 != 0) {
        if (fn_80013E2C(arg0->unk0x4) == 0) {
            return false;
        }
        fn_800AC884((s32)arg0, 1);
        arg0->unk0x8 = 1;
        return true;
    }
    if (arg0->unk0x4 != 0) {
        if (fn_80013E2C(arg0->unk0x4) == 0) {
            return false;
        }
    }
    return true;
}
