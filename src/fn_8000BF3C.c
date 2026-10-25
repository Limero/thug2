// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000BF3C-0x8000BF80 (68B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_8000C410();                                  

void fn_8000BF3C(Unk_FFAD6788 *arg0) {
    s32 temp_r9;

    if (fn_8000C410() != 3) {
        temp_r9 = arg0->unk0xE0;
        arg0->unk0xE0 = 0;
        arg0->unk0xDC = temp_r9;
    }
}
