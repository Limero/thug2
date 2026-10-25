// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800ABB34-0x800ABCA8 (372B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
typedef struct Vec4 { f32 x; f32 y; f32 z; f32 w; } Vec4;
s32 GetStructure_2(CStruct *, s32, CStruct **, s32);
s32 GetInteger(CStruct *, s32, s32 *, s32);
void *fn_800ABB34(Vec4 *out, CStruct *arg1, s32 arg2) {
    CStruct *sp8;
    s32 sp10, sp14, sp18, spC;
    sp8 = NULL;
    if (GetStructure_2(arg1, arg2, &sp8, 0) != 0) {
        spC = 1;
        GetInteger(sp8, QB_USE_DEFAULT_SCALE, &spC, 0);
        if (spC == 0) {
            GetInteger(sp8, QB_X, &sp10, 1);
            GetInteger(sp8, QB_Y, &sp14, 1);
            GetInteger(sp8, QB_Z, &sp18, 1);
            out->x = (f32)sp10 / 100.0f;
            out->y = (f32)sp14 / 100.0f;
            out->z = (f32)sp18 / 100.0f;
            out->w = 1.0f;
            goto end;
        }
    }
    out->x = 1.0f;
    out->y = 1.0f;
    out->z = 1.0f;
    out->w = 1.0f;
end:
    return out;
}
