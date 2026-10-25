// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800DBAE4-0x800DBB74 (144B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"

/* max-abs of two vec3s at +0x40/+0x44/+0x48 and +0x70/+0x74/+0x78, then the
   squared length of the sum, cached on the first call.
   The want uses lfs/stfs on all seven offsets and on the cached result at
   +0x90, so they are f32 — but the shared Unk_C101CE15 (the m2c field bag for
   this address family) declares 0x40/0x44/0x48/0x70/0x74/0x78 as s32.  Reading
   them through that bag makes every access an int<->float round trip: the
   object blows up to ~230 B for a 144 B symbol and the function scores 0%.
   Changing the shared header is NOT an option — 0x800D03DC/0x800D12DC use the
   same bag members as int flags and stop compiling, and 0x800DC680's shape
   regresses (8.25% -> 5.15%).  Keep this file-local f32 view. */
typedef struct {
    char pad0x0[0x40];
    f32 f40;
    f32 f44;
    f32 f48;
    char pad0x4C[0x24];
    f32 f70;
    f32 f74;
    f32 f78;
    char pad0x7C[0x10];
    s32 flag;   /* 0x8C */
    f32 cached; /* 0x90 */
} ObjDBAE4;

f32 fn_800DBAE4(ObjDBAE4 *arg0) {
    f32 var_f12;
    f32 temp_f13;
    f32 temp_f0;
    f32 *p;
    f32 temp_f0_2;
    f32 var_f1;
    f32 temp_f0_3;
    f32 temp_f1_2;
    f32 temp_f1;

    if (arg0->flag != 0) {
        return arg0->cached;
    }
    var_f12 = fabs(arg0->f44);
    temp_f13 = fabs(arg0->f40);
    if (temp_f13 > var_f12) {
        var_f12 = temp_f13;
    }
    temp_f0 = fabs(arg0->f48);
    if (temp_f0 > var_f12) {
        var_f12 = temp_f0;
    }
    p = &arg0->f70;
    var_f1 = fabs(p[2]);
    temp_f0_2 = fabs(p[1]);
    if (temp_f0_2 > var_f1) {
        var_f1 = temp_f0_2;
    }
    temp_f0_3 = fabs(arg0->f70);
    if (temp_f0_3 > var_f1) {
        var_f1 = temp_f0_3;
    }
    temp_f1_2 = var_f1 + var_f12;
    temp_f1 = temp_f1_2 * temp_f1_2;
    arg0->flag = 1;
    arg0->cached = temp_f1;
    return temp_f1;
}
