// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801F4DC8-0x801F4E0C (68B). Byte-identical.
#include "types.h"
#include "structs.h"
bool fn_801F4DC8(Unk_F64BBBF6 *arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3) {
    f32 temp_f0;
    f32 temp_f13;

    if ((((u8)arg0->unk0x2BA > 1U))
        && ((temp_f0 = arg0->unk0x140,
             temp_f13 = arg0->unk0x148,
             (temp_f0 < farg0) || (temp_f0 > farg2) || (temp_f13 < farg1)
                 || (temp_f13 > farg3)))) {
        return true;
    }
    return false;
}
