// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001ADC8-0x8001AE04 (60B). Byte-identical.
#include "types.h"
#include "structs.h"
void dvd_file_read(s32, s32, s32, s32);
// dvd_file_getcharacter @ 0x8001ADC8
s8 dvd_file_getcharacter(Unk_C7387A53 *arg0) {
    u8 sp8;

    sp8 = -1U;
    dvd_file_read(arg0, &sp8, 1, 0);
    return (s8) sp8;
}
