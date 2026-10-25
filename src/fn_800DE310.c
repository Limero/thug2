// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800DE310-0x800DE354 (68B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
extern void *lbl_80301A38;
typedef struct {
    char pad0x0[0x28];
    s16 unk0x28;
    s32 unk0x2C;
} DE310_t;
void fn_800DE310(s32 arg0) {
    void *temp_r11;
    DE310_t *temp_r9;

    temp_r11 = lbl_80301A38;
    temp_r9 = *(DE310_t **)((char *)temp_r11 + 0x2C);
    ((s32 (*)(void *, s32, s32))temp_r9->unk0x2C)((char *)temp_r11 + temp_r9->unk0x28, *(s32 *)((char *)arg0 + 0xC), -0x3E8);
}
