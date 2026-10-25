// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80114638-0x8011478C (340B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

typedef struct {
    f32 theta;
    f32 phi;
    f32 radius;
    f32 size;
    s32 texture;
    s32 corona;
    char pad0x18[0x28];
    s32 enabled;
    char pad0x44[4];
} SunProps;

s32 GetFloat(CStruct *, s32, f32 *, s32);
s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
s32 ContainsFlag(CStruct *, s32);
void fn_80109AE4(SunProps *, s32);

bool ScriptSetSunProps(CStruct *arg0) {
    SunProps sun;
    s32 mask;
    s32 enabled;
    s32 disabled;

    mask = 0;
    if (GetFloat(arg0, QB_THETA, &sun.theta, 0) != 0)
        mask = 1;
    if (GetFloat(arg0, QB_PHI, &sun.phi, 0) != 0)
        mask |= 2;
    if (GetFloat(arg0, QB_RADIUS, &sun.radius, 0) != 0)
        mask |= 4;
    if (GetFloat(arg0, QB_SIZE, &sun.size, 0) != 0)
        mask |= 8;
    if (GetChecksum_2(arg0, QB_TEXTURE, &sun.texture, 0) != 0)
        mask |= 0x20;
    if (GetChecksum_2(arg0, QB_CORONA_TEXTURE, &sun.corona, 0) != 0)
        mask |= 0x40;
    enabled = ContainsFlag(arg0, QB_ENABLE);
    sun.enabled = enabled;
    if (enabled != 0) {
        mask |= 0x80;
    } else {
        disabled = ContainsFlag(arg0, QB_DISABLE);
        sun.enabled = disabled;
        if (disabled != 0) {
            sun.enabled = enabled;
            mask |= 0x80;
        }
    }
    fn_80109AE4(&sun, mask);
    return true;
}
