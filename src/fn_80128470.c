// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80128470-0x801284EC (124B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
s32 fn_80127F60(s32 arg0, s32 arg1, s32 arg2, void *arg3);
void fn_80129570(s32 arg0, s32 arg1);
typedef struct Pt {
    s32 unk0x0;
    f32 unk0x4;
    f32 unk0x8;
} Pt;
bool fn_80128470(s32 arg0, s32 arg1, f32 *arg2, f32 *arg3, s32 arg4) {
    Pt *sp8;

    if (fn_80127F60(arg0, arg1, 5, &sp8) != 0) {
        *arg2 = sp8->unk0x4;
        *arg3 = sp8->unk0x8;
        return true;
    }
    if (arg4 != 0) {
        fn_80129570(arg0, 0);
    }
    return false;
}
