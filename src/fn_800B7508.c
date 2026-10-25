// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800B7508-0x800B7730 (552B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
typedef struct {
    char pad0x0[0x21];
    u8 startRGBA[4];
    u8 midRGBA[4];
    u8 endRGBA[4];
    char pad0x2D[3];
    f32 startRadius, midRadius, endRadius;
    f32 startIntensity, midIntensity, endIntensity;
    f32 midTime;
} T7508;
extern s32 GetFloat(CStruct *arg0, s32 arg1, f32 *arg2, s32 arg3);
extern s32 GetArray(CStruct *arg0, s32 arg1, s32 *arg2, s32 arg3);
extern s32 fn_801293FC(s32 arg0, s32 arg1);
void fn_800B7508(T7508 *arg0, CStruct *arg1) {
    s32 sp8;
    f32 t1;
    f32 t2;
    s32 t3;

    sp8 = 0;
    GetFloat(arg1, QB_STARTRADIUS, &arg0->startRadius, 1);
    GetFloat(arg1, QB_STARTINTENSITY, &arg0->startIntensity, 1);
    GetArray(arg1, QB_STARTRGBA, &sp8, 1);
    arg0->startRGBA[0] = (u8)fn_801293FC(sp8, 0);
    arg0->startRGBA[1] = (u8)fn_801293FC(sp8, 1);
    arg0->startRGBA[2] = (u8)fn_801293FC(sp8, 2);
    arg0->startRGBA[3] = (u8)fn_801293FC(sp8, 3);
    t1 = arg0->startRadius;
    t2 = arg0->startIntensity;
    t3 = *(s32 *)&arg0->startRGBA[0];
    arg0->midRadius = t1;
    arg0->endRadius = t1;
    arg0->midIntensity = t2;
    arg0->endIntensity = t2;
    *(s32 *)&arg0->midRGBA[0] = t3;
    *(s32 *)&arg0->endRGBA[0] = t3;
    arg0->midTime = -1.0f;
    GetFloat(arg1, QB_MIDTIME, &arg0->midTime, 0);
    GetFloat(arg1, QB_MIDRADIUS, &arg0->midRadius, 0);
    GetFloat(arg1, QB_MIDINTENSITY, &arg0->midIntensity, 0);
    if (GetArray(arg1, QB_MIDRGBA, &sp8, 0) != 0) {
        arg0->midRGBA[0] = (u8)fn_801293FC(sp8, 0);
        arg0->midRGBA[1] = (u8)fn_801293FC(sp8, 1);
        arg0->midRGBA[2] = (u8)fn_801293FC(sp8, 2);
        arg0->midRGBA[3] = (u8)fn_801293FC(sp8, 3);
    }
    GetFloat(arg1, QB_ENDRADIUS, &arg0->endRadius, 0);
    GetFloat(arg1, QB_ENDINTENSITY, &arg0->endIntensity, 0);
    if (GetArray(arg1, QB_ENDRGBA, &sp8, 0) != 0) {
        arg0->endRGBA[0] = (u8)fn_801293FC(sp8, 0);
        arg0->endRGBA[1] = (u8)fn_801293FC(sp8, 1);
        arg0->endRGBA[2] = (u8)fn_801293FC(sp8, 2);
        arg0->endRGBA[3] = (u8)fn_801293FC(sp8, 3);
    }
}
