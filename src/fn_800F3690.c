// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F3690-0x800F36C8 (56B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
typedef struct {
    char pad0x88[0x88];
    s16 unk0x88;
    s32 unk0x8C;
} Rec_800F3690;
bool fn_800F3690(Unk_C7387A53 *arg0) {
    Rec_800F3690 *r = (Rec_800F3690 *)arg0->unk0x50;
    void (*fp)(void *);
    fp = (void (*)(void *))r->unk0x8C;
    fp((char *)arg0 + r->unk0x88);
    return false;
}
