// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8001AB78-0x8001ABC4 (76B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 dvd_file_read_anywhere(s32, s32, s32, s32);
// dvd_file_fill_cache @ 0x8001AB78
void dvd_file_fill_cache(Unk_C7387A53 *arg0) {
    s32 temp_r3;

    temp_r3 = dvd_file_read_anywhere((char *)arg0 + 0x28, (char *)arg0 + 4, 0x20, arg0->unk0x74);
    arg0->unk0x70 = temp_r3;
    arg0->unk0x74 = (s32) (arg0->unk0x74 + temp_r3);
}
