// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80068998-0x800689D4 (60B). Byte-identical.
#include "types.h"
#include "structs.h"
void *fn_80068760();                                

void fn_80068998(void) {
    Unk_FFAD6788 *temp_r3;

    temp_r3 = fn_80068760();
    if (temp_r3 != NULL) {
        temp_r3->unk0x130 = 1;
        temp_r3->unk0x128 = (s32) (temp_r3->unk0x128 | 1);
    }
}
