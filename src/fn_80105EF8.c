// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80105EF8-0x80105F70 (120B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

// file-local view of the vtable at arg1->unk0xC: the `this` adjustment is a signed
// 16-bit field, the method pointer a plain s32. No inline asm, no barriers, no pins.
typedef struct Vt_80105EF8 {
    char pad0x0[0xB0];
    s16 unk0xB0;
    s32 unk0xB4;
} Vt_80105EF8;

void fn_80105EF8(Unk_5CB48605 *arg0, Unk_C7387A53 *arg1) {
    Vt_80105EF8 *temp_r9;
    s32 *base_24;
    s32 *base_20;
    s32 temp_r11;
    s32 ret;

    temp_r9 = (Vt_80105EF8 *)arg1->unk0xC;
    ret = ((s32 (*)(void *, void *))temp_r9->unk0xB4)((char *)arg1 + temp_r9->unk0xB0, arg1);
    base_24 = (s32 *)((char *)arg0 + 0x24);
    base_20 = (s32 *)((char *)arg0 + 0x20);
    base_24[arg0->unk0xFC0 * 2] = ret;
    temp_r11 = arg0->unk0xFC0;
    base_20[temp_r11 * 2] = (s32)arg1;
    arg0->unk0xFC0 = temp_r11 + 1;
    arg0->unk0xFC4 = arg0->unk0xFC4 + 1;
}
