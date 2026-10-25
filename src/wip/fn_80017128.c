// WIP DRAFT (non-matching) — hand semantic reconstruction (matrix-stack setup).
// family=m2c range=0x80017128-0x8001737C size=596B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// PARKED 2026-10-06: body re-modeled from the WANT (supersedes the m2c output
// at 5.3%, which had a gross pointer-arithmetic bug — arg0 was typed `f32 *`,
// so `arg0 + 0x48` scaled to +0x120 and `arg0 + 0xC0` to +0x300). Fixes:
//   * arg0 is a byte-addressed game object: float fields +0xAC / +0xB0, int
//     fields +0x108 / +0x10C, an int flag +0xBC, and sub-objects at +0x48
//     (fed to fn_8001F738 / PSMTX_Concat) and +0xC0 (fed to GX_SetProjection);
//   * callees use the real promoted prototypes (rotateX/rotateY/translate/
//     scale/PSMTX_Concat/PSMTX_Inverse/PSMTX_MultVec/PSVEC_Add/fn_8001D39C/
//     fn_8001D440/fn_8001F738/GX_SetProjection), not ad-hoc casts;
//   * two 0x30-byte matrices live at sp+8 (A) and sp+0x38 (B); fn_8001D440
//     writes a 3-float out at sp+0x68.
// Constants: lbl_80290C28 = 0.0f (f31), lbl_80290C2C = 1.0f (f30).
//
// NOT byte-verified (no compiler in this slice). Expected residual: stack-slot
// assignment for A/B/tmp, the `(f32)(u32)` int->float double-magic (0x4330 /
// the +0xc30 double constant) that GCC 2.95 emits for the two ratio numerators,
// fneg/store interleave for A[3]/A[7]/A[0xB], and FPR colouring. Same doc-15 /
// regalloc family as the other p_matrix callers; needs a compiler pass to
// calibrate, not more blind spellings.
#include "types.h"

extern f32 lbl_80290C28;
extern f32 lbl_80290C2C;
extern f32 lbl_8031E664[3];
extern f32 lbl_8031E670[3];
extern f32 lbl_8031E67C[3];
extern f32 lbl_8031E688[12];
extern f32 lbl_8031E6B8[12];
extern f32 lbl_8031E6E8[12];
extern f32 lbl_8031E718[12];

void rotateX(void *, s32, f32);
void rotateY(void *, s32, f32);
void translate(void *, f32 *, s32);
void scale(void *, f32 *, s32);
void PSMTX_Concat(void *, void *, void *);
void PSMTX_Inverse(void *, void *);
void PSMTX_MultVec(s32, void *, void *);
void PSVEC_Add(void *, void *);
void fn_8001D39C(void *, void *);
void *fn_8001D440(f32 *, f32, f32, f32);
void fn_8001F738(void *, s32);
void GX_SetProjection(void *, s32);

typedef struct {
    f32 A[12];
    f32 B[12];
    f32 tmp[3];
} Locals;

void fn_80017128(char *arg0, f32 *arg1) {
    Locals l;
    f32 zero;
    f32 one;
    f32 *v;
    f32 *a;

    zero = lbl_80290C28;
    one = lbl_80290C2C;
    v = lbl_8031E664;
    a = lbl_8031E67C;

    v[0] = zero;
    v[1] = zero;
    v[2] = zero;
    rotateX(lbl_8031E688, 0, a[0]);
    rotateY(lbl_8031E6B8, 0, a[1]);
    PSMTX_Concat(lbl_8031E718, lbl_8031E688, lbl_8031E6B8);
    PSMTX_Inverse(lbl_8031E6B8, lbl_8031E718);
    PSMTX_MultVec((s32)lbl_8031E6B8, v, v);
    PSVEC_Add(lbl_8031E670, v);
    translate(lbl_8031E6E8, lbl_8031E670, 0);
    PSMTX_Concat(lbl_8031E6E8, lbl_8031E718, lbl_8031E6E8);

    fn_8001D39C(l.A, arg1);
    fn_8001D39C(l.B, arg1);

    l.A[3] = -l.A[3];
    l.A[7] = -l.A[7];
    l.A[0xB] = -l.A[0xB];
    l.A[0] = one;  l.A[1] = zero; l.A[2] = zero;
    l.A[4] = zero; l.A[5] = one;  l.A[6] = zero;
    l.A[8] = zero; l.A[9] = zero; l.A[0xA] = one;
    l.B[0xB] = zero;
    l.B[3] = zero;
    l.B[7] = zero;
    PSMTX_Concat(l.A, l.B, l.A);
    PSMTX_Concat(l.A, lbl_8031E6E8, l.A);

    if (*(s32 *)(arg0 + 0xBC) == 1) {
        fn_8001D39C(l.B, arg0);
        fn_8001D440(l.tmp,
                    (f32)(*(u32 *)(arg0 + 0x108)) / *(f32 *)(arg0 + 0xAC),
                    (f32)(*(u32 *)(arg0 + 0x10C)) / *(f32 *)(arg0 + 0xB0),
                    one);
        scale(l.B, l.tmp, 2);
        PSMTX_Concat(arg0 + 0x48, l.B, l.A);
    } else {
        PSMTX_Concat(arg0 + 0x48, arg0, l.A);
    }
    fn_8001F738(arg0 + 0x48, 0);
    GX_SetProjection(arg0 + 0xC0, *(s32 *)(arg0 + 0xBC));
}
