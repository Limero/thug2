// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B9110-0x801B91DC (204B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"

typedef struct B9110 {
    char pad0[0xC];
    void *unk0xC;
    char pad10[0x14];
    s32 unk0x24;
    char pad28[0xBC];
    f32 unk0xE4;
} B9110;

s32 GetChecksum_3(s32, s32);
void fn_801B3220(s32, s32, s32, s32);
void fn_801B90FC(s32);
extern f32 lbl_802AC248;

bool fn_801B9110(B9110 *arg0) {
    if (!(*(s32 *)((char *)GetChecksum_3((s32)arg0->unk0xC, QB_MOTION) + 0x1C) & 0x100)) {
        if (arg0->unk0xE4 > lbl_802AC248) {
            *(f32 *)((char *)GetChecksum_3((s32)arg0->unk0xC, QB_MOTION) + 0x30) =
                arg0->unk0xE4;
        }
        if (*((s32 *)&arg0->unk0x24) & 4) {
            fn_801B3220((s32)arg0, QB_STATE_BAILGRIND, QB_SKATERPED_STATETABLE, 0);
        } else {
            fn_801B3220((s32)arg0, QB_STATE_BAIL, QB_SKATERPED_STATETABLE, 0);
        }
        fn_801B90FC((s32)arg0);
        return true;
    }
    return false;
}
