// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801BA360-0x801BA3AC (76B). Byte-identical.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetChecksum_3(Unk_6A70655D *, void *);
s32 fn_801BA360(Unk_6A70655D *);
s32 fn_801C1F6C(void *, f32);
bool fn_801BA360(Unk_6A70655D *arg0) {
    s32 temp_r3;

    temp_r3 = GetChecksum_3(arg0->unk0xC, QB_SKATERSOUND);
    if (temp_r3 != 0) {
        fn_801C1F6C(temp_r3, *((f32 *)&arg0->unk0xE8));
    }
    return true;
}
