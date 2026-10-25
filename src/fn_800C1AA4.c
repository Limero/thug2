// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800C1AA4-0x800C1E60 (956B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 lbl_80299028;
extern f32 lbl_8029902C;
extern f32 lbl_80299030;
extern const f32 lbl_80299034;
s32 fn_80128978(s32, s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 GetFloat(CStruct *, s32, f32 *, s32);

void fn_800C1AA4(s32 arg0, Unk_5B4CBE2C *target, CStruct *script) {
    u32 sp8;

    if (fn_80128978(script, QB_STEERING) != 0) {
        GetChecksum_2(script, QB_STEERING, &sp8, 0);
        switch (sp8) {
        case QB_LEFT:
            target->unk0xB8 = 1;
            break;
        case QB_RIGHT:
            target->unk0xB8 = 2;
            break;
        case QB_FIXED:
            target->unk0xB8 = 0;
            break;
        }
    }
    if (fn_80128978(script, QB_DRIVE) != 0) {
        GetChecksum_2(script, QB_DRIVE, &sp8, 0);
        switch (sp8) {
        case QB_YES:
            target->unk0xBC = 1;
            break;
        case QB_NO:
            target->unk0xBC = 0;
            break;
        }
    }
    GetFloat(script, QB_SPRING_RATE, (char *)target + 0xD0, 0);
    GetFloat(script, QB_DAMPING_RATE, (char *)target + 0xD4, 0);
    GetFloat(script, QB_RADIUS, (char *)target + 0xC8, 0);
    if (fn_80128978(script, QB_MOMENT) != 0) {
        GetFloat(script, QB_MOMENT, (char *)target + 0xCC, 0);
        target->unk0xCC = lbl_80299028 / target->unk0xCC;
    }
    GetFloat(script, QB_UNKNOWN_0xD87D0183, (char *)target + 0xC4, 0);
    GetFloat(script, QB_STATIC_FRICTION, (char *)target + 0xE4, 0);
    GetFloat(script, QB_DYNAMIC_FRICTION, (char *)target + 0xE8, 0);
    GetFloat(script, QB_HANDBRAKE_THROTTLE_FRICTION, (char *)target + 0xEC, 0);
    GetFloat(script, QB_HANDBRAKE_LOCKED_FRICTION, (char *)target + 0xF0, 0);
    if (fn_80128978(script, QB_MIN_STATIC_GRIP_VELOCITY) != 0) {
        GetFloat(script, QB_MIN_STATIC_GRIP_VELOCITY, (char *)target + 0xD8, 0);
        target->unk0xD8 = target->unk0xD8 * lbl_8029902C * lbl_80299030 / lbl_80299034;
    }
    if (fn_80128978(script, QB_MAX_STATIC_GRIP_VELOCITY) != 0) {
        GetFloat(script, QB_MAX_STATIC_GRIP_VELOCITY, (char *)target + 0xDC, 0);
        target->unk0xDC = target->unk0xDC * lbl_8029902C * lbl_80299030 / lbl_80299034;
    }
    if (fn_80128978(script, QB_MIN_DYNAMIC_GRIP_VELOCITY) != 0) {
        GetFloat(script, QB_MIN_DYNAMIC_GRIP_VELOCITY, (char *)target + 0xE0, 0);
        target->unk0xE0 = target->unk0xE0 * lbl_8029902C * lbl_80299030 / lbl_80299034;
    }
    if (fn_80128978(script, QB_UNKNOWN_0x3BCCBADC) != 0) {
        GetFloat(script, QB_UNKNOWN_0x3BCCBADC, (char *)target + 0xF8, 0);
        target->unk0xF8 = target->unk0xF8 * lbl_80299030;
    }
    if (fn_80128978(script, QB_UNKNOWN_0x9439D144) != 0) {
        GetFloat(script, QB_UNKNOWN_0x9439D144, (char *)target + 0xFC, 0);
        target->unk0xFC = target->unk0xFC * lbl_80299030;
    }
}
