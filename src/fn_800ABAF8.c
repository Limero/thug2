// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800ABAF8-0x800ABB34 (60B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
s32 PauseMusic(s32);
void fn_800ABAF8(Unk_0771A7B9 *arg0, f32 farg0) {
    arg0->unk0x347C = 1;
    *(f32 *)&arg0->unk0x3494 = farg0;
    arg0->unk0x3490 = arg0->unk0x3484;
    PauseMusic(1);
}
