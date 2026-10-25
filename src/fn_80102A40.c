// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80102A40-0x80102AC8 (136B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 fn_80103198(s32, s32, s32);
void *fn_8007DF14(Unk_9D99273B *);
bool fn_80102A40(Unk_C7387A53 *arg0, Unk_9D99273B *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    s32 temp_r0;
    s32 temp_r11;

    temp_r11 = *(s32 *)((char *)(fn_8007DF14(arg1)) + 0xC);
    arg0->unk0x38 = (s32) (arg2 + arg0->unk0x38);
    arg0->unk0x30 = temp_r11;
    arg0->unk0x3C = 0;
    arg0->unk0xC = (s32) (arg0->unk0xC + arg4);
    temp_r0 = arg0->unk0x34 + arg5;
    arg0->unk0x34 = temp_r0;
    fn_80103198(temp_r0, arg5, arg6);
    return true;
}
