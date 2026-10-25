// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8013B4B8-0x8013B4FC (68B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8013B4B8(Unk_C7387A53 *arg0) {
    void *temp_r3;
    Unk_89391A04 *temp_r11;

    temp_r3 = *((void * *)&arg0->unk0x20);
    (((Unk_77675BCD *)temp_r3)->unk0x1804)++;
    temp_r11 = ((Unk_77675BCD *)temp_r3)->unk0x2300;
    ((void (*)(void *))temp_r11->unk0x14)(temp_r3 + temp_r11->unk0x10);
}
