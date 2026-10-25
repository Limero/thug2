// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8000F2F8-0x8000F320 (40B). Byte-identical.
#include "types.h"
#include "structs.h"
void fn_8000F2F8(Unk_9F352E7C *arg0, s32 arg1) {
    register void *r9 asm("r9");
    register s32 r11 asm("r11");
    r9 = arg0->unk0x110;
    r9 = (s32)r9 << 2;
    r9 = (s32)r9 + (s32)arg0;
    r9 = (s32)r9 + 0xD0;
    arg0->unk0xCC = (s32)r9;
    ((CStruct *)r9)->unk0x0 = arg1;
    r11 = arg0->unk0x110 + 1;
    arg0->unk0x110 = r11;
}
