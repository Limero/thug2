// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800D7738-0x800D77FC (196B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

s32 GetVector(CStruct *, s32, void *, s32);
s32 ContainsFlag(CStruct *, s32);
void fn_80005C04(void *);
void fn_800D69A0(Unk_C8FEE62D *, CStruct *, void *);

extern f32 lbl_80299BE0;
extern f32 lbl_80299BE4;

void fn_800D7738(Unk_C8FEE62D *arg0, CStruct *arg1, s32 arg2) {
    f32 sp8[4];
    f32 *p = &sp8[0];

    sp8[0] = lbl_80299BE0;
    p[1] = lbl_80299BE0;
    p[2] = lbl_80299BE0;
    p[3] = lbl_80299BE4;
    GetVector(arg1, 0, p, 0);
    if (ContainsFlag(arg1, QB_FLAG_MAX_COORDS) != 0) {
        fn_80005C04(p);
    }
    if (arg2 == 0) {
        void *q = *(void **)((char *)arg0 + 0xC);

        *(__ps_t *)&sp8[0] = __builtin_ps_add(*(__ps_t *)&sp8[0], *(__ps_t *)((char *)q + 0x58));
        *(__ps_t *)&p[2] = __builtin_ps_add(*(__ps_t *)&p[2], *(__ps_t *)((char *)q + 0x60));
    }
    fn_800D69A0(arg0, arg1, p);
}
