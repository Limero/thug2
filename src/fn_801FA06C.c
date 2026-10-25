// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801FA06C-0x801FA0C0 (84B). Byte-identical.
#include "types.h"
#include "structs.h"
bool fn_801FA06C(Unk_C7387A53 *arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3) {
    Unk_DB0E2BAB *var_r9;
    f32 temp_f0;
    f32 *var_r11;

    var_r9 = *((s32 * *)&arg0->unk0xC);
    while (var_r9 != NULL) {
        temp_f0 = *((f32 *)&var_r9->unk0x8);
        {
            register char *mid __asm__("r11");
            __asm__("" : "=r"(mid) : "r"((char *)var_r9 + 8));
            if ((temp_f0 < farg0) || (temp_f0 > farg2) ||
                (((Unk_5EF41E38 *)mid)->unk0x8 < farg1) || (((Unk_5EF41E38 *)mid)->unk0x8 > farg3)) {
                return true;
            }
        }
        var_r9 = *((s32 * *)&var_r9->unk0x24);
    }
    return false;
}
