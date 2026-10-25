// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80244858-0x802448E4 (140B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_80240B0C(Unk_F96D0DC8 *, s32, s32, s32, s32, s32, s32);
void *fn_80244858(Unk_09BB4394 *arg0) {
    Unk_F96D0DC8 *temp_r29;

    temp_r29 = (char *)arg0 + 1;
    __asm__("" : "+r"(temp_r29));
    fn_80240B0C(temp_r29, 0, 0, 0, 0, 0, 0);
    *((s32 *)&arg0->unk0xC) = 0;
    arg0->unk0x8 = 0xFF;
    arg0->unk0x7 = 0xFF;
    arg0->unk0xA = 0;
    arg0->unk0x9 = 0;
    arg0->unk0x14 = 0;
    arg0->unk0x1 = 0;
    temp_r29->unk0x1 = 0;
    temp_r29->unk0x2 = 0;
    temp_r29->unk0x3 = 0;
    temp_r29->unk0x4 = 0;
    temp_r29->unk0x5 = 0;
    *((s32 *)&arg0->unk0x10) = 0;
    return arg0;
}
