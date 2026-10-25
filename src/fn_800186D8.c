// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800186D8-0x80018748 (112B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct {
    s32 unk0x0;
    s32 unk0x4;
    s32 unk0x8;
} Entry;

typedef struct {
    Entry entries[5];
    u16 unk0x3C;
    u16 unk0x3E;
} Ring;

// enqueue @ 0x800186D8
void enqueue(Ring *arg0, Entry *arg1) {
    u16 temp_r11;

    temp_r11 = arg0->unk0x3C;
    if (temp_r11 == 5) {
        arg0->unk0x3E = 0;
        arg0->unk0x3C = 0;
    } else {
        arg0->unk0x3C = (temp_r11 + 1) % 5;
    }
    *(Entry *) ((char *) arg0 + arg0->unk0x3C * 0xC) = *arg1;
}
