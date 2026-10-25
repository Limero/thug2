// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80069EB8-0x80069F1C (100B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
typedef struct Vt { char pad[0x38]; s16 off; char pad2[2]; void (*fn)(void *); } Vt;
typedef struct Obj {
    char pad0[0x48];
    f32 x;
    f32 y;
    f32 z;
    f32 w;
    char pad2[0x12C];
    s32 flag;
    char pad3[0x30];
    Vt *vt;
} Obj;
void fn_80069EB8(Obj *arg0, f32 *arg1) {
    if (arg0->flag != 0) {
        Vt *vt = arg0->vt;
        arg0->x = arg1[0];
        arg0->y = arg1[1];
        arg0->z = arg1[2];
        arg0->w = arg1[3];
        vt->fn((char *)arg0 + vt->off);
    }
}
