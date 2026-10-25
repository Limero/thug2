// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8013183C-0x801318C8 (140B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8013183C(s32);
s32 fn_8012ED7C(CStruct *);
void fn_8012F360(Unk_15EF4A35 *);
void fn_8012F4DC(Unk_FFAD6788 *);
void fn_8013183C(s32 arg0) {
    void *temp_r30;
    Unk_FFAD6788 *var_r31;

    var_r31 = fn_8012ED7C(NULL);
    if (var_r31 != NULL) {
        do {
            temp_r30 = fn_8012ED7C(var_r31);
            if (((s32) var_r31->unk0xCC < 0) && (((s32) var_r31->unk0xD4 == arg0) || ((s32) var_r31->unk0xB0 == arg0) || ((s32) var_r31->unk0xD0 == arg0))) {
                fn_8012F360(var_r31);
                fn_8012F4DC(var_r31);
            }
            var_r31 = temp_r30;
        } while (var_r31 != NULL);
    }
}
