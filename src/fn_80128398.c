// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x80128398-0x80128424 (140B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
void fn_80129570(s32 arg0, s32 arg1);
#include "structs.h"
s32 fn_80127F60(s32, s32, s32, s32);
extern f32 lbl_8029E600;
typedef struct { f32 w, x, y, z; } WV;
// GetVector @ 0x80128398
bool GetVector(CStruct *arg0, s32 arg1, CStruct *arg2, s32 arg3) {
    WV *sp8;
    f32 vl, vx, vy, vz;

    if (fn_80127F60(arg0, arg1, 6, &sp8) != 0) {
        vl = lbl_8029E600;
        vx = sp8->x;
        vy = sp8->y;
        vz = sp8->z;
        *((f32 *)&arg2->unk0x0) = vx;
        *((f32 *)&arg2->unk0x4) = vy;
        *((f32 *)&arg2->unk0x8) = vz;
        *((f32 *)&arg2->unk0xC) = vl;
        return true;
    }
    if (arg3 != 0) {
        fn_80129570(arg0, 0);
    }
    return false;
}
