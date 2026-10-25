// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8002DDAC-0x8002DDE8 (60B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

typedef struct {
    char pad0[0x18];
    f32 f18;
    f32 f1C;
    f32 f20;
    char pad1[4];
    s32 u28;
} S2DDAC;

void fn_8002DDAC(S2DDAC *arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    *arg2 = arg0->f1C;
    if (arg0->u28 == 0) {
        *arg1 = arg0->f18;
        *arg3 = arg0->f20;
    } else {
        *arg1 = arg0->f20;
        *arg3 = arg0->f18;
    }
}
