// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800D70D8-0x800D7270 (408B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern f32 lbl_80299BC4;
extern f32 lbl_80299BC8;

s32 GetVector(CStruct *, s32, void *, s32);
s32 ContainsFlag(CStruct *, s32);
void fn_80005C04(void *);
void fn_80005B74(f32 *);
void fn_80004B4C(void *, void *);
void fn_80003830(void *, f32, f32, f32);
void fn_800D6FF0(Unk_1536F9AE *, CStruct *, void *);

void fn_800D70D8(Unk_1536F9AE *arg0, CStruct *arg1) {
    f32 sp8[4];
    f32 sp18[16];
    f32 *p = &sp8[0];

    sp8[0] = lbl_80299BC4;
    p[1] = lbl_80299BC4;
    p[2] = lbl_80299BC4;
    p[3] = lbl_80299BC8;
    if (GetVector(arg1, QB_RELATIVE, p, 0) != 0) {
        if (ContainsFlag(arg1, QB_FLAG_MAX_COORDS) != 0) {
            p[2] = -p[2];
            fn_80005C04(p);
        }
        fn_80005B74(p);
        {
            f32 *q = &sp18[0];
            char *c;
            s32 i;

            i = 4;
            c = *(char **)((char *)arg0 + 0xC);
            c += 0x78;
            do {
                i -= 1;
            } while (i != 0);
            ((__ps_t *)sp18)[0] = ((__ps_t *)c)[0];
            ((__ps_t *)sp18)[1] = ((__ps_t *)c)[1];
            ((__ps_t *)sp18)[2] = ((__ps_t *)c)[2];
            ((__ps_t *)sp18)[3] = ((__ps_t *)c)[3];
            ((__ps_t *)sp18)[4] = ((__ps_t *)c)[4];
            ((__ps_t *)sp18)[5] = ((__ps_t *)c)[5];
            ((__ps_t *)sp18)[6] = ((__ps_t *)c)[6];
            ((__ps_t *)sp18)[7] = ((__ps_t *)c)[7];
            fn_80004B4C(q, sp8);
            fn_800D6FF0(arg0, arg1, q);
        }
        return;
    }
    if (GetVector(arg1, QB_ABSOLUTE, p, 0) != 0) {
        if (ContainsFlag(arg1, QB_FLAG_MAX_COORDS) != 0) {
            p[2] = -p[2];
            fn_80005C04(p);
        }
        fn_80005B74(p);
        {
            f32 *q = &sp18[0];

            fn_80003830(q, sp8[0], sp8[1], p[2]);
            fn_800D6FF0(arg0, arg1, q);
        }
    }
}
