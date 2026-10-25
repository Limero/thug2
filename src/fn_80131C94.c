// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80131C94-0x80131D18 (132B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_8012ED7C(s32);
s32 fn_8012F044(CStruct *o);
void fn_8012EE64(Unk_FFAD6788 *o, s32 v);
void fn_80131C94(void) {
    Unk_FFAD6788 *temp_r30;
    Unk_FFAD6788 *var_r31;

    var_r31 = fn_8012ED7C(0);
    if (var_r31 != 0) {
        do {
            temp_r30 = fn_8012ED7C(var_r31);
            if ((fn_8012F044(var_r31) == 0) && ((s32)var_r31->unk0xCC >= 0) &&
                ((s32)var_r31->unk0xE0 == 0) && (var_r31 != 0)) {
                fn_8012EE64(var_r31, 3);
            }
            var_r31 = temp_r30;
        } while (var_r31 != 0);
    }
}
