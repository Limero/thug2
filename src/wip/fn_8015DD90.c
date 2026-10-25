// WIP DRAFT — ScriptGetSkaterVelocity full build, plain C only.
// family=m2c range=0x8015DD90-0x8015E868 size=2776B
// FLAG: -mps-float
//
// RE-TRIAGED 2026-10-19: sweep still DIFF — the 192B-short slow-path wall
// stands, no incremental path. Parked as-is.
// PARKED 2026-10-05 (w_8015DD90): best measured 8.05% DIFF (tools/score_wip.py
// 0x8015DD90 <this file> -mps-float), object 2584 B vs the 2776 B symbol — still
// 192 B / 48 words SHORT, so the masked score is not a meaningful closeness
// number yet (AGENTS §6es). Everything below is now semantically retail-exact;
// see AGENTS-recipes.md / docs/parkings for the residual analysis.
//
// RESIDUAL: the whole gap is the SLOW path (`speed <= 100`) 4x4 product.
// Retail reloads all 8 operands per statement (16 x 8 = 128 lfs + 17 fmuls,
// ~14 words/statement); this body emits only ~86 lfs there because GCC CSEs the
// `fr.rot2[]` / `fr.init[]` operands across the 16 statements (they are direct
// struct members, and the `stfs` to fr.tmp2[] provably cannot alias them).
// The fast-path product matches retail's shape because retail reaches rot1
// through the *returned pointer* of fn_80003EB0 (register r3), which GCC
// cannot prove non-aliasing.
//
// CLOSEST ALTERNATIVE MEASURED (kept out because the masked score drops):
//   b = ((f32 *)fr.pp0)[0]; a = ((f32 *)fr.pp1)[0]; ...   (opaque-pointer
//   access via the two struct slots) restores the reload count and lands the
//   object at 2772 B (only 4 B off) but then the frame becomes 0x1f8 (retail
//   0x1f0, GPR save 0x1bc vs 0x1b4, fctiwz temp 0x1b0 vs 0x1a8) and the whole
//   stream re-aligns worse: 5.77%.
//
// RULED OUT: (a) `register __ps_t *p27 __asm__("r27")` pin — gives retail's
//   stmw r27..r31 but pushes the frame to 0x1f8 and scores 6.03%; (b) rewriting
//   the matrices as PS-typed unions/pointers (V2/V4, `__ps_t *initp`) — ngccc
//   ICEs at expmed.c:1115, and the union form alone costs 89 lfs (over-CSE,
//   2524 B, 1.74%); (c) padding the Frame struct to move the fctiwz temp — it
//   is a compiler-generated DImode slot that always lands *last*, so growing
//   the struct moves it the wrong way; (d) a 4-byte trailing struct member to
//   close the 428-vs-424 local-area gap — GCC never allocates a user local
//   after that temp.
//
// SEMANTIC FIXES LANDED (all verified against the retail bytes):
//  * tmp2 is rot2 x smat (tmp2[4i+j] = sum_k rot2[4i+k]*smat[4k+j], smat =
//    &fr.init[8]) — the m2c draft had smat x rot2^T and got every index wrong.
//  * the rotate's 4th term is vel[1].hi (w, the second half of the 0xC0 psq),
//    not 1.0; its 2nd term is vel[0].hi, which the code zeroed at 0x8015DE84.
//  * fr.rot1[0..3] is overwritten from fr.rot1[4..7] before vel[0]/vel[1] are
//    taken from rot1[2]/rot1[3] (retail 0x8015E2F8).
//  * the slow path loads skater+0x98/+0xA0 into fr.init[0..3] (not fr.vel)
//    and the three QB_SCALED_* reads come from fr.init[0..2].
//  * the 8 skater matrix copies must be PS-typed lvalues
//    (`((__ps_t *)&fr.init[8])[k] = ...`), else GCC splits them into lwz/stw.
//  * the identity matrix is 16 explicit `fr.init[k] = ...` stores bracketed by
//    `for (ctr = 0; ctr < 4; ctr++) { }` — that spelling reproduces retail's
//    `li r0,4; mtctr r0; ...; bdnz .-0` degenerate loops AND the 16-store order.
//  * lbl_802A821C/lbl_802A8218 must be long-lived locals (`zero`/`one`), or
//    GCC re-loads them at every use instead of holding f27/f28 across the 5
//    calls; lbl_802A8220/24 stay direct global reads (retail reloads those).
//  * Frame is 0x170 B with `skew` at +0x150, `scale` +0x154, the two s32
//    rot2/smat pointers at +0x158/+0x15c, speedps +0x160, normps +0x168; that
//    puts the frame at r1+8 and the fctiwz int temp at 0x1a8 like retail.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern f32 lbl_802A8218;
extern f32 lbl_802A821C;
extern f32 lbl_802A8220;
extern f32 lbl_802A8224;
extern __ps_t lbl_802A8048;
s32 GetFloat(CStruct *, s32, f32 *, s32);
void AddInteger(CStruct *, s32, s32);
void *fn_80003EB0(void *, f32);
typedef union { __ps_t ps; f32 f[2]; } PSU;
struct Frame {
    __ps_t vel[2];
    f32 init[16];
    f32 rot1[16];
    f32 tmp1[16];
    f32 rot2[16];
    f32 tmp2[16];
    f32 skew;
    f32 scale;
    void *pp0;
    void *pp1;
    __ps_t speedps;
    __ps_t normps;
};
bool ScriptGetSkaterVelocity(CStruct *arg0, Unk_EFC8CFAD *arg1) {
    struct Frame fr;
    PSU sum;
    PSU rsq;
    __ps_t *p30;
    __ps_t *p27;
    f32 x;
    f32 y;
    f32 z;
    f32 w;
    f32 v;
    f32 zero;
    f32 one;
    void *skater;
    void *tmp;
    int ctr;
    f32 a;
    f32 b;
    f32 c;
    f32 d;
    f32 e;
    f32 f;
    f32 g;
    f32 h;
    skater = (void *)arg1->unk0xBC;
    if (skater != 0) {
        zero = lbl_802A821C;
        one = lbl_802A8218;
        fr.vel[0] = *((__ps_t *)((char *)skater + 0xB8));
        p30 = &fr.vel[0];
        fr.vel[1] = *((__ps_t *)((char *)skater + 0xC0));
        y = ((f32 *)p30)[1];
        p27 = p30;
        z = ((f32 *)p30)[2];
        x = *(f32 *)&fr.vel[0];
        fr.scale = one;
        fr.skew = zero;
        GetFloat(arg0, QB_SKEW_ANGLE, &fr.skew, 0);
        AddInteger(arg1->unk0x18, QB_VEL_X, (s32)x);
        AddInteger(arg1->unk0x18, QB_VEL_Y, (s32)y);
        AddInteger(arg1->unk0x18, QB_VEL_Z, (s32)z);
        GetFloat(arg0, QB_SCALE, &fr.scale, 0);
        ((f32 *)&fr.vel[0])[1] = zero;
        sum.ps = __builtin_ps_madd(fr.vel[0], fr.vel[0],
                __builtin_ps_merge00(__builtin_ps_mul(fr.vel[1], fr.vel[1]), lbl_802A8048));
        sum.ps = __builtin_ps_sum0(sum.ps, sum.ps, sum.ps);
        rsq.ps = __builtin_ps_rsqrte(sum.ps);
        fr.speedps = __builtin_ps_res(rsq.ps);
        if (*(f32 *)&fr.speedps > lbl_802A8220) {
            if (sum.f[0] > zero) {
                fr.normps = __builtin_ps_rsqrte(p27[0]);
                fr.vel[1] = __builtin_ps_muls0(p27[0], fr.normps);
                ((f32 *)&fr.normps)[1] = one;
                fr.vel[0] = __builtin_ps_mul(p27[0], fr.normps);
            }
            if (fr.skew != zero) {
                for (ctr = 0; ctr < 4; ctr++) {
                }
                v = fr.skew * lbl_802A8224;
                fr.init[0] = one; fr.init[1] = zero; fr.init[2] = zero; fr.init[3] = zero;
                fr.init[4] = zero; fr.init[5] = one; fr.init[6] = zero; fr.init[7] = zero;
                fr.init[8] = zero; fr.init[9] = zero; fr.init[10] = one; fr.init[11] = zero;
                fr.init[12] = zero; fr.init[13] = zero; fr.init[14] = zero; fr.init[15] = one;
                for (ctr = 0; ctr < 4; ctr++) {
                }
                fn_80003EB0((void *)fr.rot1, v);
                b = fr.rot1[0]; a = fr.init[0]; d = fr.rot1[4]; c = fr.init[1];
                f = fr.rot1[8]; e = fr.init[2]; h = fr.rot1[12]; g = fr.init[3];
                fr.tmp1[0] = a*b+c*d+e*f+g*h;
                b = fr.rot1[1]; a = fr.init[0]; d = fr.rot1[5]; c = fr.init[1];
                f = fr.rot1[9]; e = fr.init[2]; h = fr.rot1[13]; g = fr.init[3];
                fr.tmp1[1] = a*b+c*d+e*f+g*h;
                b = fr.rot1[2]; a = fr.init[0]; d = fr.rot1[6]; c = fr.init[1];
                f = fr.rot1[10]; e = fr.init[2]; h = fr.rot1[14]; g = fr.init[3];
                fr.tmp1[2] = a*b+c*d+e*f+g*h;
                b = fr.rot1[3]; a = fr.init[0]; d = fr.rot1[7]; c = fr.init[1];
                f = fr.rot1[11]; e = fr.init[2]; h = fr.rot1[15]; g = fr.init[3];
                fr.tmp1[3] = a*b+c*d+e*f+g*h;
                b = fr.rot1[0]; a = fr.init[4]; d = fr.rot1[4]; c = fr.init[5];
                f = fr.rot1[8]; e = fr.init[6]; h = fr.rot1[12]; g = fr.init[7];
                fr.tmp1[4] = a*b+c*d+e*f+g*h;
                b = fr.rot1[1]; a = fr.init[4]; d = fr.rot1[5]; c = fr.init[5];
                f = fr.rot1[9]; e = fr.init[6]; h = fr.rot1[13]; g = fr.init[7];
                fr.tmp1[5] = a*b+c*d+e*f+g*h;
                b = fr.rot1[2]; a = fr.init[4]; d = fr.rot1[6]; c = fr.init[5];
                f = fr.rot1[10]; e = fr.init[6]; h = fr.rot1[14]; g = fr.init[7];
                fr.tmp1[6] = a*b+c*d+e*f+g*h;
                b = fr.rot1[3]; a = fr.init[4]; d = fr.rot1[7]; c = fr.init[5];
                f = fr.rot1[11]; e = fr.init[6]; h = fr.rot1[15]; g = fr.init[7];
                fr.tmp1[7] = a*b+c*d+e*f+g*h;
                b = fr.rot1[0]; a = fr.init[8]; d = fr.rot1[4]; c = fr.init[9];
                f = fr.rot1[8]; e = fr.init[10]; h = fr.rot1[12]; g = fr.init[11];
                fr.tmp1[8] = a*b+c*d+e*f+g*h;
                b = fr.rot1[1]; a = fr.init[8]; d = fr.rot1[5]; c = fr.init[9];
                f = fr.rot1[9]; e = fr.init[10]; h = fr.rot1[13]; g = fr.init[11];
                fr.tmp1[9] = a*b+c*d+e*f+g*h;
                b = fr.rot1[2]; a = fr.init[8]; d = fr.rot1[6]; c = fr.init[9];
                f = fr.rot1[10]; e = fr.init[10]; h = fr.rot1[14]; g = fr.init[11];
                fr.tmp1[10] = a*b+c*d+e*f+g*h;
                b = fr.rot1[3]; a = fr.init[8]; d = fr.rot1[7]; c = fr.init[9];
                f = fr.rot1[11]; e = fr.init[10]; h = fr.rot1[15]; g = fr.init[11];
                fr.tmp1[11] = a*b+c*d+e*f+g*h;
                b = fr.rot1[0]; a = fr.init[12]; d = fr.rot1[4]; c = fr.init[13];
                f = fr.rot1[8]; e = fr.init[14]; h = fr.rot1[12]; g = fr.init[15];
                fr.tmp1[12] = a*b+c*d+e*f+g*h;
                b = fr.rot1[1]; a = fr.init[12]; d = fr.rot1[5]; c = fr.init[13];
                f = fr.rot1[9]; e = fr.init[14]; h = fr.rot1[13]; g = fr.init[15];
                fr.tmp1[13] = a*b+c*d+e*f+g*h;
                b = fr.rot1[2]; a = fr.init[12]; d = fr.rot1[6]; c = fr.init[13];
                f = fr.rot1[10]; e = fr.init[14]; h = fr.rot1[14]; g = fr.init[15];
                fr.tmp1[14] = a*b+c*d+e*f+g*h;
                b = fr.rot1[3]; a = fr.init[12]; d = fr.rot1[7]; c = fr.init[13];
                f = fr.rot1[11]; e = fr.init[14]; h = fr.rot1[15]; g = fr.init[15];
                fr.tmp1[15] = a*b+c*d+e*f+g*h;
                ((__ps_t *)fr.init)[0] = ((__ps_t *)fr.tmp1)[0];
                ((__ps_t *)fr.init)[1] = ((__ps_t *)fr.tmp1)[1];
                ((__ps_t *)fr.init)[2] = ((__ps_t *)fr.tmp1)[2];
                ((__ps_t *)fr.init)[3] = ((__ps_t *)fr.tmp1)[3];
                ((__ps_t *)fr.init)[4] = ((__ps_t *)fr.tmp1)[4];
                ((__ps_t *)fr.init)[5] = ((__ps_t *)fr.tmp1)[5];
                ((__ps_t *)fr.init)[6] = ((__ps_t *)fr.tmp1)[6];
                ((__ps_t *)fr.init)[7] = ((__ps_t *)fr.tmp1)[7];
                w = ((f32 *)&fr.vel[1])[1];
                fr.rot1[4] = *(f32 *)&p27[0]*fr.init[0] + ((f32 *)&p27[0])[1]*fr.init[4] +
                             ((f32 *)&p27[1])[0]*fr.init[8] + w*fr.init[12];
                fr.rot1[5] = *(f32 *)&p27[0]*fr.init[1] + ((f32 *)&p27[0])[1]*fr.init[5] +
                             ((f32 *)&p27[1])[0]*fr.init[9] + w*fr.init[13];
                fr.rot1[6] = *(f32 *)&p27[0]*fr.init[2] + ((f32 *)&p27[0])[1]*fr.init[6] +
                             ((f32 *)&p27[1])[0]*fr.init[10] + w*fr.init[14];
                fr.rot1[7] = *(f32 *)&p27[0]*fr.init[3] + ((f32 *)&p27[0])[1]*fr.init[7] +
                             ((f32 *)&p27[1])[0]*fr.init[11] + w*fr.init[15];
                ((__ps_t *)fr.rot1)[0] = ((__ps_t *)fr.rot1)[2];
                ((__ps_t *)fr.rot1)[1] = ((__ps_t *)fr.rot1)[3];
                fr.vel[0] = ((__ps_t *)fr.rot1)[2];
                fr.vel[1] = ((__ps_t *)fr.rot1)[3];
            }
            AddInteger(arg1->unk0x18, QB_SCALED_X, (s32)(*(f32 *)&fr.vel[0] * fr.scale));
            AddInteger(arg1->unk0x18, QB_SCALED_Y, (s32)(((f32 *)&fr.vel[0])[1] * fr.scale));
            AddInteger(arg1->unk0x18, QB_SCALED_Z, (s32)(*(f32 *)&fr.vel[1] * fr.scale));
        } else {
            ((__ps_t *)fr.init)[0] = *((__ps_t *)((char *)skater + 0x98));
            ((__ps_t *)fr.init)[1] = *((__ps_t *)((char *)skater + 0xA0));
            if (fr.skew != zero) {
                for (ctr = 0; ctr < 4; ctr++) {
                }
                v = fr.skew * lbl_802A8224;
                ((__ps_t *)&fr.init[8])[0] = *((__ps_t *)((char *)skater + 0x78));
                ((__ps_t *)&fr.init[9])[1] = *((__ps_t *)((char *)skater + 0x80));
                ((__ps_t *)&fr.init[10])[2] = *((__ps_t *)((char *)skater + 0x88));
                ((__ps_t *)&fr.init[11])[3] = *((__ps_t *)((char *)skater + 0x90));
                ((__ps_t *)&fr.init[12])[4] = *((__ps_t *)((char *)skater + 0x98));
                ((__ps_t *)&fr.init[13])[5] = *((__ps_t *)((char *)skater + 0xA0));
                ((__ps_t *)&fr.init[14])[6] = *((__ps_t *)((char *)skater + 0xA8));
                ((__ps_t *)&fr.init[15])[7] = *((__ps_t *)((char *)skater + 0xB0));
                for (ctr = 0; ctr < 4; ctr++) {
                }
                fr.pp0 = fn_80003EB0((void *)fr.rot2, v);
                fr.pp1 = (void *)&fr.init[8];
                b = fr.rot2[0]; a = fr.init[8]; d = fr.rot2[1]; c = fr.init[12];
                f = fr.rot2[2]; e = fr.init[16]; h = fr.rot2[3]; g = fr.init[20];
                fr.tmp2[0] = a*b+c*d+e*f+g*h;
                b = fr.rot2[0]; a = fr.init[9]; d = fr.rot2[1]; c = fr.init[13];
                f = fr.rot2[2]; e = fr.init[17]; h = fr.rot2[3]; g = fr.init[21];
                fr.tmp2[1] = a*b+c*d+e*f+g*h;
                b = fr.rot2[0]; a = fr.init[10]; d = fr.rot2[1]; c = fr.init[14];
                f = fr.rot2[2]; e = fr.init[18]; h = fr.rot2[3]; g = fr.init[22];
                fr.tmp2[2] = a*b+c*d+e*f+g*h;
                b = fr.rot2[0]; a = fr.init[11]; d = fr.rot2[1]; c = fr.init[15];
                f = fr.rot2[2]; e = fr.init[19]; h = fr.rot2[3]; g = fr.init[23];
                fr.tmp2[3] = a*b+c*d+e*f+g*h;
                b = fr.rot2[4]; a = fr.init[8]; d = fr.rot2[5]; c = fr.init[12];
                f = fr.rot2[6]; e = fr.init[16]; h = fr.rot2[7]; g = fr.init[20];
                fr.tmp2[4] = a*b+c*d+e*f+g*h;
                b = fr.rot2[4]; a = fr.init[9]; d = fr.rot2[5]; c = fr.init[13];
                f = fr.rot2[6]; e = fr.init[17]; h = fr.rot2[7]; g = fr.init[21];
                fr.tmp2[5] = a*b+c*d+e*f+g*h;
                b = fr.rot2[4]; a = fr.init[10]; d = fr.rot2[5]; c = fr.init[14];
                f = fr.rot2[6]; e = fr.init[18]; h = fr.rot2[7]; g = fr.init[22];
                fr.tmp2[6] = a*b+c*d+e*f+g*h;
                b = fr.rot2[4]; a = fr.init[11]; d = fr.rot2[5]; c = fr.init[15];
                f = fr.rot2[6]; e = fr.init[19]; h = fr.rot2[7]; g = fr.init[23];
                fr.tmp2[7] = a*b+c*d+e*f+g*h;
                b = fr.rot2[8]; a = fr.init[8]; d = fr.rot2[9]; c = fr.init[12];
                f = fr.rot2[10]; e = fr.init[16]; h = fr.rot2[11]; g = fr.init[20];
                fr.tmp2[8] = a*b+c*d+e*f+g*h;
                b = fr.rot2[8]; a = fr.init[9]; d = fr.rot2[9]; c = fr.init[13];
                f = fr.rot2[10]; e = fr.init[17]; h = fr.rot2[11]; g = fr.init[21];
                fr.tmp2[9] = a*b+c*d+e*f+g*h;
                b = fr.rot2[8]; a = fr.init[10]; d = fr.rot2[9]; c = fr.init[14];
                f = fr.rot2[10]; e = fr.init[18]; h = fr.rot2[11]; g = fr.init[22];
                fr.tmp2[10] = a*b+c*d+e*f+g*h;
                b = fr.rot2[8]; a = fr.init[11]; d = fr.rot2[9]; c = fr.init[15];
                f = fr.rot2[10]; e = fr.init[19]; h = fr.rot2[11]; g = fr.init[23];
                fr.tmp2[11] = a*b+c*d+e*f+g*h;
                b = fr.rot2[12]; a = fr.init[8]; d = fr.rot2[13]; c = fr.init[12];
                f = fr.rot2[14]; e = fr.init[16]; h = fr.rot2[15]; g = fr.init[20];
                fr.tmp2[12] = a*b+c*d+e*f+g*h;
                b = fr.rot2[12]; a = fr.init[9]; d = fr.rot2[13]; c = fr.init[13];
                f = fr.rot2[14]; e = fr.init[17]; h = fr.rot2[15]; g = fr.init[21];
                fr.tmp2[13] = a*b+c*d+e*f+g*h;
                b = fr.rot2[12]; a = fr.init[10]; d = fr.rot2[13]; c = fr.init[14];
                f = fr.rot2[14]; e = fr.init[18]; h = fr.rot2[15]; g = fr.init[22];
                fr.tmp2[14] = a*b+c*d+e*f+g*h;
                b = fr.rot2[12]; a = fr.init[11]; d = fr.rot2[13]; c = fr.init[15];
                f = fr.rot2[14]; e = fr.init[19]; h = fr.rot2[15]; g = fr.init[23];
                fr.tmp2[15] = a*b+c*d+e*f+g*h;
                ((__ps_t *)&fr.init[8])[0] = ((__ps_t *)fr.tmp2)[0];
                ((__ps_t *)&fr.init[8])[1] = ((__ps_t *)fr.tmp2)[1];
                ((__ps_t *)&fr.init[8])[2] = ((__ps_t *)fr.tmp2)[2];
                ((__ps_t *)&fr.init[8])[3] = ((__ps_t *)fr.tmp2)[3];
                ((__ps_t *)&fr.init[8])[4] = ((__ps_t *)fr.tmp2)[4];
                ((__ps_t *)&fr.init[8])[5] = ((__ps_t *)fr.tmp2)[5];
                ((__ps_t *)&fr.init[8])[6] = ((__ps_t *)fr.tmp2)[6];
                ((__ps_t *)&fr.init[8])[7] = ((__ps_t *)fr.tmp2)[7];
                ((__ps_t *)fr.init)[0] = ((__ps_t *)fr.tmp2)[0];
                ((__ps_t *)fr.init)[1] = ((__ps_t *)fr.tmp2)[1];
            }
            AddInteger(arg1->unk0x18, QB_SCALED_X, (s32)(fr.init[0] * fr.scale));
            AddInteger(arg1->unk0x18, QB_SCALED_Y, (s32)(fr.init[1] * fr.scale));
            AddInteger(arg1->unk0x18, QB_SCALED_Z, (s32)(fr.init[2] * fr.scale));
        }
        return true;
    }
    return false;
}
