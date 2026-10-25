// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801FE888-0x801FE990 (264B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"

typedef struct RunTimerCScript {
    char pad0x00[0x18];
    s32 unk0x18;
    char pad0x1C[0x2CC];
    s32 unk0x2E8;
} RunTimerCScript;

typedef struct RunTimer {
    char pad0x00[0x0C];
    RunTimerCScript *unk0x0C;
    char pad0x10[0x0C];
    s32 unk0x1C;
    f32 unk0x20;
    s16 unk0x24;
} RunTimer;

extern s32 lbl_80301A78;
extern f32 lbl_802AE8A4;
extern f32 lbl_802AE8B0;
extern f32 lbl_802AE8B4;
extern f32 fn_801417B8(RunTimerCScript *arg0, s32 arg1);
extern void fn_800A54AC(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, f32 arg6);

void fn_801FE888(RunTimer *arg0) {
    RunTimerCScript *temp_r11;
    f32 temp_f0;

    if (arg0->unk0x1C != 0) {
        arg0->unk0x1C = (arg0->unk0x20 > lbl_802AE8A4) ? 1 : 3;
        if (arg0->unk0x24 <= 7) {
            temp_f0 = (f32)(8 - arg0->unk0x24) * fn_801417B8(arg0->unk0x0C, QB_PHYSICS_RUNTIMER_DURATION) * lbl_802AE8B0;
            temp_f0 = (arg0->unk0x20 < temp_f0) ? arg0->unk0x20 : temp_f0;
            arg0->unk0x20 = temp_f0;
        }
        temp_r11 = arg0->unk0x0C;
        arg0->unk0x24 = (u16)arg0->unk0x24 + 1;
        fn_800A54AC(lbl_80301A78, QB_SHOWRUNTIMER, temp_r11->unk0x2E8 + QB_RUNTIMERCONTROLLER, temp_r11->unk0x18, 0, 0, lbl_802AE8B4);
    }
}
