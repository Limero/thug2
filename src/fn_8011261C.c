// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8011261C-0x801126DC (192B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

typedef union {
    s32 value;
    struct {
        u8 pad[3];
        u8 component;
    } bytes;
} ScriptColorValue;

typedef struct {
    u8 r;
    u8 g;
    u8 b;
    s8 a;
} PackedColor;

typedef struct {
    PackedColor color_arg;
    s32 index;
    ScriptColorValue red;
    ScriptColorValue green;
    ScriptColorValue blue;
    PackedColor color;
} LightColorFrame;

s32 GetInteger(CStruct *, s32, s32 *, s32);
s32 fn_80059318(s32, PackedColor *);

s32 ScriptSetLightDiffuseColor(CStruct *arg0) {
    LightColorFrame frame;
    ScriptColorValue *red_value;
    s32 green_value;
    s32 blue_value;
    PackedColor *color;

    GetInteger(arg0, QB_INDEX, &frame.index, 0);
    red_value = &frame.red;
    GetInteger(arg0, QB_R, &red_value->value, 0);
    GetInteger(arg0, QB_G, &frame.green.value, 0);
    GetInteger(arg0, QB_B, &frame.blue.value, 0);
    green_value = frame.green.value;
    blue_value = frame.blue.value;
    color = &frame.color;
    color->r = red_value->bytes.component;
    color->g = (u8)green_value;
    color->b = (u8)blue_value;
    color->a = (u8)-0x80;
    frame.color_arg = frame.color;
    return fn_80059318(frame.index, &frame.color_arg);
}
