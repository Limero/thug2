// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x801B3514-0x801B3630 (284B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
typedef struct { f32 x, y, z, w; } vec3514;

s32 GetChecksum_3(Unk_6A70655D *, s32);
s32 fn_801B4E84(void *);
s32 fn_801B56C8(Unk_61ECF642 *);
void fn_801B52D0(Unk_0EAAF5DE *);
void fn_800D80F8(Unk_2A3EDACE *);
void fn_801B5A54(void *);
void fn_801B7484(Unk_0EAAF5DE *, Unk_EA529D06 *);
void fn_801B6004(void *);
s32 fn_800D9DB0(Unk_C7387A53 *);

void fn_801B3514(Unk_C7387A53 *arg0) {
    vec3514 cur;
    vec3514 out;
    s32 eq;

    if (arg0->unk0x24 & 2) {
        s32 handle;
        s32 t30;
        void *v;
        f32 *pf;

        handle = GetChecksum_3(*((void * *)&arg0->unk0xC), QB_MOTION);
        t30 = fn_801B4E84(arg0);
        if ((fn_801B56C8(arg0) == 0) && (t30 == 0)) {
            fn_801B52D0(arg0);
        }
        v = *((void * *)&arg0->unk0xC);
        ((__ps_t *)&cur)[0] = ((Unk_5F85C510 *)v)->unk0x58;
        pf = &cur.x;
        ((__ps_t *)pf)[1] = *((__ps_t *)&((Unk_31DE137E *)v)->unk0x60);
        fn_800D80F8(handle);
        fn_801B5A54(arg0);
        v = *((void * *)&arg0->unk0xC);
        eq = 0;
        if ((cur.x == *((f32 *)&((Unk_5F85C510 *)v)->unk0x58)) &&
            (pf[1] == *((f32 *)&((Unk_31DE137E *)v)->unk0x5C)) &&
            (pf[2] == *((f32 *)&((Unk_31DE137E *)v)->unk0x60))) {
            eq = pf[3] == *((f32 *)&((Unk_31DE137E *)v)->unk0x64);
        }
        if (eq == 0) {
            ((__ps_t *)&out)[1] = ((__ps_t *)pf)[1];
            ((__ps_t *)&out)[0] = ((__ps_t *)&cur)[0];
            fn_801B7484(arg0, &out);
        }
        fn_801B6004(arg0);
        fn_800D9DB0(handle);
    }
}
