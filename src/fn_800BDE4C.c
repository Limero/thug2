// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800BDE4C-0x800BDF64 (280B). Byte-identical.
// extra_cflags: -mps-float
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
s32 GetVector(CStruct *, s32, CStruct *, s32);
void fn_800BA64C(Unk_60E57DDC * arg0);

// Local alias over the script-motion region of the object (Unk_C7387A53's
// 0x118..0x158). Each frame the QB node (arg1) supplies "Pos"/"Vel"/
// "RotVel" vectors — 4 f32 lanes each, i.e. two __ps_t lane-pairs — that
// are accumulated into the matching members here. Members are named by
// their absolute byte offset (same convention as the shared class), and
// under -mps-float a __ps_t member access IS the game's psq_l/ps_add/
// psq_st pair op, so no width is lost vs the raw cast form.
typedef struct {
    char pad0x0[0x118];
    __ps_t unk0x118;   // QB_POS lanes 0
    __ps_t unk0x120;   // QB_POS lanes 1
    __ps_t unk0x128;   // QB_VEL lanes 0
    __ps_t unk0x130;   // QB_VEL lanes 1
    char pad0x138[0x10];
    __ps_t unk0x148;   // QB_ROTVEL lanes 0
    __ps_t unk0x150;   // QB_ROTVEL lanes 1
} ObjMotion;

bool fn_800BDE4C(Unk_C7387A53 *arg0, CStruct *arg1) {
    __attribute__((aligned(16))) char sp8[16];
    __ps_t *d;
    if (GetVector(arg1, QB_VEL, (s32 *)sp8, 0)) {
        ObjMotion *m = (ObjMotion *)arg0;
        m->unk0x128 = m->unk0x128 + ((__ps_t *)sp8)[0];
        d = (__ps_t *)arg0->unk0xC;
        m->unk0x130 = m->unk0x130 + ((__ps_t *)sp8)[1];
        d[23] = m->unk0x128;
        d[24] = m->unk0x130;
    }
    if (GetVector(arg1, QB_ROTVEL, (s32 *)sp8, 0)) {
        ObjMotion *m = (ObjMotion *)arg0;
        m->unk0x148 = m->unk0x148 + ((__ps_t *)sp8)[0];
        m->unk0x150 = m->unk0x150 + ((__ps_t *)sp8)[1];
    }
    if (GetVector(arg1, QB_POS, (s32 *)sp8, 0)) {
        ObjMotion *m = (ObjMotion *)arg0;
        m->unk0x118 = m->unk0x118 + ((__ps_t *)sp8)[0];
        d = (__ps_t *)arg0->unk0xC;
        m->unk0x120 = m->unk0x120 + ((__ps_t *)sp8)[1];
        d[11] = m->unk0x118;
        d[12] = m->unk0x120;
    }
    fn_800BA64C(arg0);
    return true;
}
