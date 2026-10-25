// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801A397C-0x801A3A08 (140B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -fno-schedule-insns
#include "types.h"
#include "qb_constants.h"

typedef struct {
    u8 pad0[0x28];
    f32 unk28;
    f32 unk2c;
    u8 pad1[4];
    f32 unk34;
    f32 unk38;
    f32 unk3c;
    s32 unk40;
    u8 pad2[0x10];
    s32 unk54;
    s32 unk58;
} Unk_A397C;

s32 Script_GetInteger(s32, s32);
void Script_RunScript(s32, s32, s32, s32, s32);
extern f32 lbl_802AB734;

void fn_801A397C(Unk_A397C *arg0) {
    f32 temp_f0;

    if (Script_GetInteger(QB_BALANCE_CHECK, 0) != 0) {
        Script_RunScript(QB_RESET_BALANCE_INDICATOR, 0, 0, 0, 0);
    }
    temp_f0 = lbl_802AB734;
    arg0->unk58 = 0;
    arg0->unk38 = temp_f0;
    arg0->unk54 = -1;
    arg0->unk3c = temp_f0;
    arg0->unk28 = temp_f0;
    arg0->unk2c = temp_f0;
    arg0->unk34 = temp_f0;
    arg0->unk40 = 0;
}
