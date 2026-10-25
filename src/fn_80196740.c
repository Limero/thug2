// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80196740-0x801967A8 (104B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// Identification: tiny setter — forwards +0x53C to fn_80126E28 and stores
// lbl_802AA5F8 / (f32)arg2 at +0x534 (normalized field).
#include "types.h"
#include "structs.h"

extern f32 lbl_802AA5F8;

void fn_80126E28(Unk_5AA7B5D7 *, Unk_5AA7B5D7 *);

void fn_80196740(Unk_3F93CF38 *arg0, Unk_5AA7B5D7 *arg1, s32 arg2) {
    fn_80126E28(*((s32 *)&arg0->unk0x53C), arg1);
    arg0->unk0x534 = lbl_802AA5F8 / (f32)arg2;
}
