// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800E0A7C-0x800E0AD4 (88B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

typedef struct {
    char pad0x0[0x30];
    s16 unk0x30;
    char pad0x32[0x2];
    s32 (*unk0x34)(void *, s32);
} VT_800E0A7C;

s32 fn_800E0A7C(CScript *arg0, s32 arg1, s32 arg2) {
    VT_800E0A7C *temp_r9;

    if (arg1 == QB_UNKNOWN_0xE357E3CB) {
        temp_r9 = *((VT_800E0A7C **)&arg0->unk0x18);
        temp_r9->unk0x34((char *)arg0 + temp_r9->unk0x30, arg2);
        return 1;
    }
    return 2;
}
