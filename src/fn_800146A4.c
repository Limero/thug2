// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800146A4-0x800146E0 (60B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct Slot {
    char pad0x0[0x14];
    s32 state;
    char pad0x18[0xE4];
} Slot;

extern Slot lbl_80314330[3];

void fn_800146A4(void *arg0) {
    Slot *slot = lbl_80314330;
    s32 *field = &slot->state;
    Slot *entry = slot;
    s32 count = 3;

    do {
        if (arg0 == entry) {
            *field = 0;
            return;
        }
        field = (s32 *)((char *)field + 0xFC);
        entry++;
    } while (--count != 0);
}
