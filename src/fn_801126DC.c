// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801126DC-0x8011281C (320B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

typedef struct {
    char pad0x00[0x18];
    s32 unk0x18;
} Sc;

typedef union {
    struct {
        u8 r;
        u8 g;
        u8 b;
        s8 a;
    } bytes;
    s32 value;
} Color;

void fn_80059284(s32 *arg0, ...);
s32 fn_8005934C(s32 *arg0, s32 arg1, ...);
void AddInteger(s32 arg0, s32 arg1, u8 arg2);

bool ScriptGetLightCurrentColor(CStruct *arg0, Sc *arg1) {
    Color col;
    Color *p;
    s32 v0;
    s32 v1;
    s32 v2;

    p = &col;
    p->bytes.r = 0;
    p->bytes.a = -128;
    p->bytes.g = 0;
    p->bytes.b = 0;
    fn_80059284(&v0);
    p->value = v0;
    AddInteger(arg1->unk0x18, QB_AMBIENT_RED, p->bytes.r);
    AddInteger(arg1->unk0x18, QB_AMBIENT_GREEN, p->bytes.g);
    AddInteger(arg1->unk0x18, QB_AMBIENT_BLUE, p->bytes.b);
    fn_8005934C(&v1, 0);
    p->value = v1;
    AddInteger(arg1->unk0x18, QB_RED_0, p->bytes.r);
    AddInteger(arg1->unk0x18, QB_GREEN_0, p->bytes.g);
    AddInteger(arg1->unk0x18, QB_BLUE_0, p->bytes.b);
    fn_8005934C(&v2, 1);
    p->value = v2;
    AddInteger(arg1->unk0x18, QB_RED_1, p->bytes.r);
    AddInteger(arg1->unk0x18, QB_GREEN_1, p->bytes.g);
    AddInteger(arg1->unk0x18, QB_BLUE_1, p->bytes.b);
    return true;
}
// RE-TRIAGE 2026-10-12: re-verified 97.50% (78/80) size-exact, same addi/stb swap at 0x801126FC/0x80112700. Doc-15 interleave wall stands; no new lever (arg must stay a frame-address addi, so the r3-pin recipe cannot apply); no body change.
