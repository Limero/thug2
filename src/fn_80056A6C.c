// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80056A6C-0x80056AC8 (92B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_800FF938(s32);
void fn_80056A6C(Unk_FFAD6788 *arg0) {
    s32 i;
    for (i = 0; i < (s32) arg0->unk0x158; i++) {
        fn_800FF938(arg0->unk0x15C + i * 0x10);
    }
}
