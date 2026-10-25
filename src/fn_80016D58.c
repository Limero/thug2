// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80016D58-0x80016DBC (100B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
typedef struct Ent {
    char pad0[8];
    s32 unk0x8;
    s32 unk0xC;
} Ent;
extern Ent lbl_802FFF80[];
s32 GX_GetTexBufferSize(u16, u16, s32, s32, s32);
void fn_80016D58(s32 arg0, s32 arg1, s32 arg2) {
    Ent *e = &lbl_802FFF80[arg0];
    s32 v3 = (arg2 == 1) ? (e->unk0x8 >> 1) : e->unk0x8;

    GX_GetTexBufferSize((u16)v3, (u16)((arg2 == 1) ? (e->unk0xC >> 1) : e->unk0xC), arg1, 0, 0);
}
