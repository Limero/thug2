// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800ABAB0-0x800ABAF8 (72B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void PauseMusic(s32);
void fn_800ABAB0(Unk_6849630D *arg0, f32 farg0) {
    volatile double _dummy;
    PauseMusic(1);
    *(f32 *)((char *)arg0 + 0x3484) = farg0;
    arg0->unk0x347C = 1;
}
