// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8024C4D8-0x8024C5A0 (200B). Byte-identical.
#include "types.h"
#include "structs.h"
void memset(void *, s32, s32);
void fn_8024C4D8(Unk_5B449B03 *arg0, s32 arg1) {
    u16 w;
    u16 h;
    s32 stride;
    s32 wh;
    s32 p24;
    s32 p28;
    w = arg0->unk0x4;
    h = arg0->unk0x6;
    stride = (w * 8) & 0x7FFF0;
    wh = w * h;
    arg0->unk0x20 = arg1;
    *((s32 *)&arg0->unk0x8) = arg1 + (w << 5) + 0x80;
    p24 = arg1 + wh + 0x60;
    p28 = p24 + (wh >> 2) + 0x60;
    arg0->unk0xC = p24 + stride + 0x40;
    arg0->unk0x24 = p24;
    arg0->unk0x10 = p28 + stride + 0x40;
    arg0->unk0x28 = p28;
    memset(arg1, 0x10, wh);
    memset(arg0->unk0x24, 0x80,
           (arg0->unk0x4 * arg0->unk0x6) >> 2);
    memset(arg0->unk0x28, 0x80,
           (arg0->unk0x4 * arg0->unk0x6) >> 2);
}
