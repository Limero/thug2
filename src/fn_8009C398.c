// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8009C398-0x8009C3C8 (48B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_8009C398(Unk_C7387A53 *arg0, s32 arg1, f32 farg0, f32 farg1, f32 farg2) {
    s32 i;
    i = arg1 * 3;
    ((f32 *)arg0->unk0x28)[i] = farg0;
    ((f32 *)arg0->unk0x28)[i + 1] = farg1;
    ((f32 *)arg0->unk0x28)[i + 2] = farg2;
}
