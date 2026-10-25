// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801317C0-0x8013183C (124B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_8012ED7C(CStruct *);
s32 fn_80130D24(void *, s32);
void fn_8012F360(Unk_15EF4A35 *);
void fn_8012F4DC(Unk_FFAD6788 *);
void fn_801317C0(s32 arg0) {
    void *temp_r30;
    Unk_FFAD6788 *var_r31;

    var_r31 = fn_8012ED7C(NULL);
    if (var_r31 != NULL) {
        do {
            temp_r30 = fn_8012ED7C(var_r31);
            if ((var_r31->unk0xCC < 0) && (fn_80130D24(var_r31, arg0) != 0)) {
                fn_8012F360(var_r31);
                fn_8012F4DC(var_r31);
            }
            var_r31 = temp_r30;
        } while (var_r31 != NULL);
    }
}
