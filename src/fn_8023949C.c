// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8023949C-0x802394F8 (92B). Byte-identical.
#include "types.h"
#include "structs.h"
s32 fn_802439E0(void *, s32, s32 *);
s32 fn_80243C18(void *, s32, s32 *);
void fn_802392F0(Unk_673C6403 *, void *);
void fn_8023949C(Unk_673C6403 *arg0, s32 arg1) {
    s32 spC;
    s32 sp8;

    if (fn_802439E0(arg0->unk0x177C8, arg1, &sp8) != 0) {
        fn_802392F0(arg0, fn_80243C18(arg0->unk0x177C8, sp8, &spC));
    }
}
