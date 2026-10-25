// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800636F4-0x8006374C (88B). Byte-identical.
#include "types.h"
#include "structs.h"

void fn_8012EE64(Unk_069CE08E *, s32);
s32 fn_801309EC(void);
void fn_800636F4(Unk_FFAD6788 *arg0) {
    s32 temp_r3;
    s32 field;

    field = arg0->unk0x104;
    if (field != 0) {
        temp_r3 = fn_801309EC();
        if (temp_r3 == 0) {
            field = arg0->unk0x104;
            if (field != 0) {
                fn_8012EE64(field, 3);
            }
            arg0->unk0x104 = temp_r3;
        }
    }
}
