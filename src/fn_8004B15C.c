// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8004B15C-0x8004B1C0 (100B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_8004B270(Unk_9E4B1D7B *, s32);
s32 fn_80040BE8(s32);
s32 fn_8004C66C(Unk_9E4B1D7B *);
void fn_8004B15C(Unk_9E4B1D7B *arg0) {
    if (arg0->unk0x4C != 0) {
        fn_8004B270(arg0, 1);
        fn_80040BE8(arg0->unk0x4C);
        fn_8004B270(arg0, 0);
        if (arg0->unk0x5C4 > 0) {
            fn_8004C66C(arg0);
        }
    }
}
