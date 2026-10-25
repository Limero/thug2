// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800F2334-0x800F2384 (80B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
//
// Identification: scripted-animation channel setter on a cine-cam/action
// object: copies the 3-word (0x30/0x34/0x38) payload from arg0 into the
// target struct via fn_800F3674 (plain 3-store setter), then conditionally
// (flag @0x3C) refreshes via fn_800F2324. Suggested rename:
// CineSetChannel3.
#include "types.h"
#include "structs.h"
s32 fn_800F2324(Unk_C7387A53 *);
s32 fn_800F3674(Unk_C8FEE62D *, void *, void *, void *);
void fn_800F2334(Unk_C7387A53 *arg0, Unk_C8FEE62D *arg1) {
    fn_800F3674(arg1, arg0->unk0x30, arg0->unk0x34, arg0->unk0x38);
    if ((s32) arg0->unk0x3C != 0) {
        fn_800F2324(arg0);
    }
}
