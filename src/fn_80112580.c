// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80112580-0x8011261C (156B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

s32 GetInteger(CStruct *, s32, s32 *, s32);
__ps_t *fn_800592F8(s32);
void fn_80005BA4(CStruct *);
void fn_8012772C(CStruct *, s32, f32);

typedef union {
    __ps_t p[2];
    f32 f[4];
} LightVec;

bool ScriptGetLightDirection(CStruct *pParams, CScript *pScript) {
    s32 sp18;
    LightVec sp8;
    __ps_t *light;
    __ps_t *dst;
    f32 heading;
    f32 pitch;

    GetInteger(pParams, QB_INDEX, &sp18, 0);
    light = fn_800592F8(sp18);
    dst = sp8.p;
    dst[0] = light[0];
    dst[1] = light[1];
    fn_80005BA4((CStruct *)dst);
    heading = sp8.f[1];
    pitch = sp8.f[0];
    fn_8012772C((CStruct *)pScript->unk0x18, QB_HEADING, heading);
    fn_8012772C((CStruct *)pScript->unk0x18, QB_PITCH, pitch);
    return true;
}
