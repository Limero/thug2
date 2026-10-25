// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800B01CC-0x800B0208 (60B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"

typedef struct {
    char pad0x0[0x68];
    s16 unk0x68;
    char pad0x6A[0x2];
    s32 (*unk0x6C)(void *, s32);
} Rec_800B01CC;

void fn_800B01CC(Unk_C7387A53 *arg0) {
    Rec_800B01CC *r;

    r = *(Rec_800B01CC **)((char *)arg0 + 0x14);
    r->unk0x6C((char *)arg0 + r->unk0x68, *(s32 *)((char *)arg0 + 0x70) ^ 1);
}
