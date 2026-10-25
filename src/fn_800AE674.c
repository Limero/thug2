// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x800AE674-0x800AE8C4 (592B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// extra_cflags: -mps-float
#include "types.h"

typedef float sn_ps __attribute__((mode(PS)));

typedef union {
    sn_ps p[2];
    f32 f[4];
} Quat;

typedef struct {
    char pad0[0x1C];
    void *unk0x1C;
    char pad20[0x3448];
    s32 unk0x3468;
    char pad346C[0x14];
    f32 unk0x3480;
    f32 unk0x3484;
    char pad3488[0x30];
    s32 unk0x34B8;
} CutState;

typedef struct {
    char pad0[0x68];
    Quat quat;
    f32 mat[16];
} CamState;

extern f32 lbl_8029863C;
extern f32 lbl_80298640;
extern void *lbl_802FFE98;

void fn_80024610(void *);
void *fn_80024660(void *);
void *fn_800246AC(void *);
void fn_800AF6F8(void *, void *, void *);
void fn_8000F2F8(void *, s32);
s32 fn_8002AEF4(void *, s32, s32, f32, f32);
void fn_8000F320(void *);

void fn_800AE674(void *arg0, void *arg1) {
    Quat q;
    Quat r;
    Quat row3;
    f32 p[3][4];
    f32 *qp;
    f32 *rp3;
    Quat *out;
    f32 *m;
    f32 zero, one;

    if (*(s32 *)((char *)arg0 + 0x34B8) != 0) {
        qp = q.f;
        fn_80024610(arg1);
        out = (Quat *)fn_80024660(arg1);
        m = (f32 *)fn_800246AC(arg1);
        zero = lbl_8029863C;
        one = lbl_80298640;
        q.f[0] = zero;
        qp[1] = zero;
        qp[2] = zero;
        qp[3] = one;
        fn_800AF6F8(arg0, (void *)qp, (void *)&r);
        out->p[0] = r.p[0];
        out->p[1] = r.p[1];
        row3.f[0] = zero;
        rp3 = row3.f;
        rp3[1] = zero;
        rp3[2] = zero;
        rp3[3] = one;
        q.p[0] = __builtin_ps_neg(q.p[0]);
        qp[2] = -qp[2];
        p[0][0] = q.f[0] * q.f[0];
        p[0][1] = q.f[1] * q.f[1];
        p[0][2] = qp[2] * qp[2];
        p[1][0] = q.f[1] * qp[2];
        p[1][1] = qp[2] * q.f[0];
        p[1][2] = q.f[0] * q.f[1];
        p[2][0] = q.f[3] * q.f[0];
        p[2][1] = q.f[3] * q.f[1];
        p[2][2] = q.f[3] * qp[2];
        m[0] = one - 2.0f * (p[0][1] + p[0][2]);
        m[1] = 2.0f * (p[1][2] + p[2][2]);
        m[2] = 2.0f * (p[1][1] - p[2][1]);
        m[3] = zero;
        m[4] = 2.0f * (p[1][2] - p[2][2]);
        m[5] = one - 2.0f * (p[0][0] + p[0][2]);
        m[6] = 2.0f * (p[1][0] + p[2][0]);
        m[7] = zero;
        m[8] = 2.0f * (p[1][1] + p[2][1]);
        m[9] = 2.0f * (p[1][0] - p[2][0]);
        m[10] = one - 2.0f * (p[0][0] + p[0][1]);
        m[11] = zero;
        *(sn_ps *)(m + 12) = row3.p[0];
        *(sn_ps *)(m + 14) = row3.p[1];
        m[15] = one;
        if (*(s32 *)((char *)arg0 + 0x3468) == 0) {
            fn_8000F2F8(lbl_802FFE98, *(s32 *)((char *)lbl_802FFE98 + 0x154));
            fn_8002AEF4(*(void **)((char *)arg0 + 0x1C), (s32)arg1, 0,
                       *(f32 *)((char *)arg0 + 0x3480), *(f32 *)((char *)arg0 + 0x3484));
            fn_8000F320(lbl_802FFE98);
        }
    }
}
