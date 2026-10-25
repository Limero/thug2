// PARKED 2026-10-05: m2c DIFF 0.8% (0x130 frame, 9 saved FPRs, garbage
// body) -> **DIFF 12.4%** (`tools/ps_diff.py`, 484B object vs 512B want).
// Fully hand-reconstructed from the want; every semantic decision below is
// verified against the original bytes. family=m2c range=0x800F0870-0x800F0A70 size=512B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// extra_cflags: -mps-float
//
// WHAT IT IS: `ScriptQuaternionToMatrix(CStruct *ctx, Mat4 *out)` — 4x4 float
// matrix, 16-byte rows (m[4][4]). Reads the script's QB_ORIENTATION vector
// (3 floats) and builds the standard quaternion→rotation-matrix 3x3 in the
// top-left; the GetVector-fails arm writes the 4x4 IDENTITY (1.0f on the
// diagonal at +0x0/+0x14/+0x28/+0x3c). Constants: lbl_8029B30C = 0.0f,
// lbl_8029B310 = 1.0f, lbl_8029B314 = 2.0f, lbl_8029B2C0 = the {0,0} PS pair.
//
// SEMANTICS RECOVERED (all confirmed against want):
// * 1st arg is the script context, 2nd is the matrix (`mr r31, r4`; all 16
//   stores are `N(r31)`). m2c had one arg — that alone cost the whole body.
// * The quaternion local is initialised (0,0,0,1) in the order x,w,y,z — the
//   q.w=1.0f store is DEAD (overwritten by the sqrtf result) and want keeps it.
// * The PS block is the house idiom (cf. src/fn_800A07F0.c, fn_800A1230.c):
//     ps_mul / ps_merge00(<ps>, lbl_8029B2C0) / ps_madd / ps_sum0
//   fed from a `__ps_t`-typed first member, so want loads r1+8 as a PS PAIR
//   twice (`psq_l f0` and `psq_l f13`) and `psq_l f12, 0(r9)` for the zero
//   pair. The value read back is `dot.flt.hi` = r1+0x28 (NOT .lo).
//   Arithmetic: S = 2x² + y² (the ps_madd adds x*x twice) — reproduce as-is.
// * `if (S > 1.0f) S = 1.0f;` then `w = sqrtf(1.0f - S)` (want: `fmr f0,f13;
//   fcmpu; ble; fmr f13,f1; fsubs f1,f1,f13; bl sqrtf`).
// * len2 = w*w + (x*x + y*y + z*z)   — the source really nests it that way
//   (want: y² ; x²+y² ; z²+(x²+y²) ; w²+ that).
// * k = (len2 > 0.0f) ? 2.0f/len2 : 0.0f, then the 9 products are written
//   `x * (y * k)` — k innermost on the SECOND factor, so the want computes
//   x*k, y*k, z*k first and then x*(x*k), y*(y*k), ... Never write `k*(x*x+y*y)`
//   (no reassociation without fast-math, and it gives a different shape).
//
// SOLVED (worth keeping):
// * **The FPR-saving frame is reachable with a plain local.** want's prologue
//   is `stwu -0x48 / stfd f31,0x40 / stw r31,0x3c / stw r0,0x4c` and 0.0f
//   lives in f31 ACROSS the sqrtf call. A direct `lbl_8029B30C` reference is
//   rematerialised (got reloads it into f11 after the call → frame 0x38, no
//   `stfd f31`). The fix is a local `f32 zero = lbl_8029B30C;` **declared
//   inside the first block** (after the GetVector call): function-scope puts
//   the *address* pseudo in a callee-saved GPR instead (`lis r30; lfs f31,0(r30)`
//   + `stmw r30`) and adds 8 more frame bytes. With the block-scope local the
//   prologue is byte-identical and NO `volatile double _dummy` is needed (the
//   §4c +8 is supplied by the f31 save itself; adding the dummy on top gives
//   0x50, one word too many).
// * **The emitted store order is a permutation of the source order, and for
//   the 9 matrix stores that permutation is the SAME for every source order
//   tried: emitted = source[6,7,8,9,4,5,1,2,3]** (measured on three different
//   source orders — the scheduler does not move them back). want's emitted
//   order (m[0][1], m[0][2], m[1][2], m[2][2], m[0][0], m[1][1], m[1][0],
//   m[2][0], m[2][1]) is therefore reached from the source order
//   **m[1][0], m[2][0], m[2][1], m[0][0], m[1][1], m[0][1], m[0][2], m[1][2],
//   m[2][2]** — which is what this draft uses, and the 9 stores now come out
//   in exactly want's order. The 16-store identity arm does NOT follow a fixed
//   permutation (2 stores hoist), so its order below is only want's-emitted
//   order as source order; 14 of the 16 land in the right relative order.
//
// BLOCKER: the 9-statement arithmetic BLOCK is still 7 words short (484B vs
// 512B) and its product order differs. want's product/sum order is
//   x*k, y*k, z*k, 1.0f, a=x*xk, b=y*yk, c=z*zk, d=x*zk, a+b, e=w*zk,
//   g=w*xk, h=y*zk, i=w*yk, j=x*yk, a+c, b+c
// i.e. exactly the order of a source with those products in NAMED TEMPS
// (xk,yk,zk,a,b,c,d,s1,e,g,h,i,j,s2,s3 + 9 stores) — but writing it that way
// here does NOT reproduce it (sched2 reorders the pure-FP block anyway, and
// also produces one extra product). Also still open: want materialises
// address registers `r8 = &v` and `r11 = &q` (and uses r1+offset for the rest
// of each), which this draft does not; the `k` ternary lands in f0 and is
// copied to f10 in want but stays in one register here; and the want's
// `q.w = 1.0f` dead store is not sunk while every draft here sinks it below
// the PS block. Those are all register-allocation/scheduling artefacts of one
// 40-instruction block, not semantics — do not re-derive them from scratch.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern f32 lbl_8029B30C;
extern f32 lbl_8029B310;
extern f32 lbl_8029B314;
extern __ps_t lbl_8029B2C0;
extern s32 GetVector(CStruct *, s32, CStruct *, s32);
extern f32 sqrtf(f32);

typedef struct {
    f32 m[4][4];
} M4;
typedef struct {
    SN_PS_type xy;
    f32 z;
} V3;
typedef struct {
    f32 x, y, z, w;
} Q;

void fn_800F0870(CStruct *ctx, M4 *arg1) {
    V3 v;
    Q q;
    SN_PS_type dot;
    f32 s, k, len2, w;

    if (GetVector(ctx, QB_ORIENTATION, &v, 0) != 0) {
        f32 zero = lbl_8029B30C;

        q.x = zero;
        q.w = lbl_8029B310;
        q.y = zero;
        q.z = zero;
        dot.ps = __builtin_ps_mul(v.xy.ps, v.xy.ps);
        dot.ps = __builtin_ps_merge00(dot.ps, lbl_8029B2C0);
        q.x = v.xy.flt.hi;
        dot.ps = __builtin_ps_madd(v.xy.ps, v.xy.ps, dot.ps);
        q.y = v.xy.flt.lo;
        dot.ps = __builtin_ps_sum0(dot.ps, dot.ps, dot.ps);
        q.z = v.z;
        s = dot.flt.hi;
        if (s > lbl_8029B310)
            s = lbl_8029B310;
        w = sqrtf(lbl_8029B310 - s);
        q.w = w;
        len2 = w * w + (q.x * q.x + q.y * q.y + q.z * q.z);
        k = (len2 > zero) ? lbl_8029B314 / len2 : zero;
        arg1->m[1][0] = q.x * (q.y * k) + q.w * (q.z * k);
        arg1->m[2][0] = q.x * (q.z * k) - q.w * (q.y * k);
        arg1->m[2][1] = q.y * (q.z * k) + q.w * (q.x * k);
        arg1->m[0][0] = lbl_8029B310 - (q.y * (q.y * k) + q.z * (q.z * k));
        arg1->m[1][1] = lbl_8029B310 - (q.x * (q.x * k) + q.z * (q.z * k));
        arg1->m[0][1] = q.x * (q.y * k) - q.w * (q.z * k);
        arg1->m[0][2] = q.x * (q.z * k) + q.w * (q.y * k);
        arg1->m[1][2] = q.y * (q.z * k) - q.w * (q.x * k);
        arg1->m[2][2] = lbl_8029B310 - (q.x * (q.x * k) + q.y * (q.y * k));
    } else {
        arg1->m[0][0] = lbl_8029B310;
        arg1->m[3][3] = lbl_8029B310;
        arg1->m[3][2] = lbl_8029B30C;
        arg1->m[0][1] = lbl_8029B30C;
        arg1->m[0][2] = lbl_8029B30C;
        arg1->m[0][3] = lbl_8029B30C;
        arg1->m[1][0] = lbl_8029B30C;
        arg1->m[1][1] = lbl_8029B310;
        arg1->m[1][2] = lbl_8029B30C;
        arg1->m[1][3] = lbl_8029B30C;
        arg1->m[2][0] = lbl_8029B30C;
        arg1->m[2][1] = lbl_8029B30C;
        arg1->m[2][2] = lbl_8029B310;
        arg1->m[2][3] = lbl_8029B30C;
        arg1->m[3][0] = lbl_8029B30C;
        arg1->m[3][1] = lbl_8029B30C;
    }
}
