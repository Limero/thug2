// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8012591C-0x80125954 (56B). Byte-identical.
#include "types.h"
#include "structs.h"
// FIXED: lbl_8029E480 extern + flipped NULL-first block - EXACT, M5.43
extern char lbl_8029E480[];
s32 fn_8012591C(s32 arg0, s32 arg1) {
    Unk_C7387A53 *temp_r3;

    temp_r3 = fn_80125480();
    if (temp_r3 == NULL) {
        return (s32)lbl_8029E480;
    }
    return temp_r3->unk0xC;
}
