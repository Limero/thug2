// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8003E0B8-0x8003E104 (76B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_8005C414(void *, s32, f32, f32, f32);
bool fn_8003E0B8(void *arg0, Unk_C7387A53 *arg1) {
    if ((s32) arg1->unk0x20 != 0) {
        fn_8005C414(arg0, 0, *((f32 *)&arg1->unk0x24), *((f32 *)&arg1->unk0x28), *((f32 *)&arg1->unk0x2C));
        return true;
    }
    return false;
}
