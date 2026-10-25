// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800DDDC0-0x800DDE00 (64B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_800DDDC0(Unk_31DE137E *arg0) {
    void *temp_r11;
    Unk_89391A04 *temp_r9;

    temp_r11 = arg0->unk0x1C;
    if (temp_r11 != NULL) {
        temp_r9 = ((Unk_9994C3F5 *)temp_r11)->unk0x8;
        ((void (*)(void *))temp_r9->unk0x24)(temp_r11 + temp_r9->unk0x20);
    }
}
