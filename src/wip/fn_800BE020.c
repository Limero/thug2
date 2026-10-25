// PARKED 2026-10-03 (a19):
//   verdict DIFF 31.7% (want 832B / got 832B, exact size), unchanged from the
//   2026-09-27 baseline in *score*, but TWO REAL SEMANTIC BUGS WERE FIXED this
//   round (see below) - the committed body is now semantically right, it just
//   still does not schedule/register-allocate the way retail does.
//   reproduce:
// LEAF_TMPDIR=<scratch> tools/venv/bin/python tools/test_wip_drafts.py --addr 0x800BE020
//
// FIXED THIS ROUND (both read straight off the disassembly, not guessed):
//  A. The quaternion rescale block was operating on the WRONG PAIRS. It did
//     {q0,q1} then {q1,q2} (i.e. `&self->q[1]`), which double-scales q1 and
//     leaves q3 unscaled. Retail (0x800BE230-0x800BE24C) loads
//     `psq_l f0,312(r31)` (=&q[0]) and `psq_l f13,320(r31)` (=&q[2]), does ONE
//     `ps_mr f12,f11` broadcast, `ps_muls0` on both, then both stores. So the
//     second statement must be `*(__ps_t *)&self->q[2] = ...muls0(q[2], sp[4])`.
//     This was worth -1 instruction (got 832->828) and is the only honest
//     reading of retail.
//  B. The last two `__ps_t` copies must read `self->obj->f0B8/f0C0`, not the
//     local `obj`. Retail reloads the pointer at 0x800BE334 (`lwz r9,0xc(r31)`)
//     and only then does `psq_l f0,184(r9)`. Writing `self->obj` there lets
//     `obj` die at the end of the then-branch, which is what frees r30 for
//     `mm[k]` inside the Sheppard branch and for `&self->q[0]` at 0x800BE1F8.
//     (Side effect: got now loads obj into r29 instead of r24, and its save
//     set became r25-r31, so the epilogue `lmw` regressed by one word while the
//     tail block gained three.)
//
// REMAINING DIFF (in descending size):
//  1. obj's home is r29 (want r30) and `&sp[0]` is never hoisted: want has
//     `addi r24, r1, 8` in the *prologue* and uses r24 for both `mr r3` at the
//     two calls and `stfsx`/`psq_l`, whereas got folds `addi r3, r1, 8` at each
//     call site and materialises `addi r11, r1, 8` inside the else-branch for
//     the indexed stores. One extra instruction, but it also shifts the whole
//     save set (want `stmw r24,0x28` / `lmw r24,0x28`, got r25-r31).
//  2. Quaternion-sum block: want has ZERO `fmr`s and re-loads q[0..3] from a
//     base register (`addi r30,r31,0x138` then `lfs f13,0(r30)` ...), got keeps
//     the four q values live and emits 4-5 `fmr`s (f9<-f0, f3<-f12, f8<-f11,
//     f10<-f13). A named `f32 *q = self->q` was tried -> 30.8% / 828B, WORSE.
//  3. The 9 result stores: want uses `addi r11, r31, 0x158` + `stfs fX, off(r11)`
//     (offsets 0/4/8/0x10/0x14/0x18/0x20/0x24/0x28); got uses r31 + full
//     displacement (0x158..0x180). All 9 mismatch on the base/displacement.
//  4. `sc` lands in f11 (want f31). See "RULED OUT" for the experiment.
//  5. Three `lfsx` in the Sheppard branch compute the right address but with
//     the A/B base-vs-index fields swapped (e.g. want `lfsx f0, r30, r27`,
//     got `lfsx f0, r27, r30`) - an encoding-level choice, and in the
//     `(ri[j] + rj[i])` / `(ri[k] + rk[i])` adds the two operands land in
//     swapped destination registers.
//
// RULED OUT THIS ROUND (do not retry):
//  * `sq = lbl_80298E80 / sq;` (one variable reused for the scale, which is what
//    retail's `fmuls f13,f31,f0` then `fdivs f31,f0,f31` implies): reproduces
//    retail's else-branch SHAPE exactly - `fmuls` before `fdivs` in the same
//    order - but the whole object drops to 824B (4 words short) and 30.3%.
//    So the in-place fdivs is real, and something else it enables is 4 words
//    too small. Interesting lead, not a win.
//  * `f32 *q = self->q` used for fn_80036304 + every q[] read and the __ps_t
//    casts: 30.8% / 828B.
//  * The muls0 pair-index fix alone (without fix B) also scores 27.9%, because
//    the extra `lwz` of fix B is what restores the 832B size. Keep BOTH.
//
// MOST PROMISING NEXT IDEA: fix the size first. Retail is 832B; the current body
// is 832B only by coincidence (one word too many in the else-branch, one word
// too few in the quaternion block). Getting rid of the stray `addi r11, r1, 8`
// (residual 1) while making the quaternion block one word longer - e.g. by
// getting the q values re-loaded from a base register instead of kept live in
// f9/f3/f8/f10 - should make the two halves realign and unlock ~40 more
// matching words at once.
// WIP DRAFT (non-matching) - quaternion normalize + Sheppard axis extraction
// family=m2c range=0x800BE020-0x800BE360 size=832B
// INERT: not registered in splits.txt/configure.py - never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// HAND REBUILT from ps_disasm. VERDICT 2026-09-27: DIFF - 66/208 masked words
// (31.7%), want 832B / got 832B (EXACT size), prologue+epilogue byte-exact
// (stwu -0x50 / mflr / stfd f31,0x48(r1) / stmw r24,0x28(r1) / stw r0,0x54(r1)
// / mr r31,r3 ... lwz r0,0x54(r1) / mtlr / lmw r24,0x28(r1) / lfd f31,0x48(r1)
// / addi r1,r1,0x50 / blr). Up from 13/207 (6.3%) at the start of the round.
//
// SOLVED THIS ROUND (verified at the instruction level):
//  * The normalize block is  __builtin_ps_muls0(pair, f32scalar)  - NOT
//    __builtin_ps_mul with a pre-built splat pair. cc1 lowers the 2-arg form to
//    exactly retail's PS triple  ps_splat(XO=8,C=2) + 2x ps_muls0(XO=12).
//    The scalar must come from a MEMORY slot (an array element `sp[4]`, not a
//    plain local): a register local gives ps_mr+2x muls0, a *parameter* gives
//    just 2x muls0, `volatile f32` gives 2x lfs (all same score, wrong shape).
//    Capstone prints all three as `.word # op4`; the A-form layout is
//    OPCD|D(6-10)|A(11-15)|B(16-20)|C(21-25)|XO(26-30)|Rc and XO=8's C field is
//    a sub-op magic (1=neg 4=nabs 8=abs, 2=the splat form) - calibrated by
//    assembling one __builtin_ps_* per TU and reading back the encodings.
//  * Sheppard vp[j]/vp[k] were SWAPPED in the m2c baseline. Correct:
//    vp[j]=(ri[j]+rj[i])*sc, vp[k]=(ri[k]+rk[i])*sc, sp[3]=(rk[j]-rj[k])*sc.
//  * The 0x50 frame comes from EIGHT callee-saved GPRs, not from the 4c FPR
//    frame dummy: `f32(*mm)[4]` + `mm[i][i]` strength-reduces to `mulli i,0x14`,
//    but three NAMED row pointers (ri=mm[i], rj, rk) reproduce retail's
//    slwi/slwi/add/lfsx and add the 2 extra saved regs. A `volatile double`
//    also gives 0x50 but with only r26-r31 saved - wrong span.
//  * Constants are 0.0f/1.0f/0.5f/2.0f at lbl_80298E78/7C/80/84 (verified in
//    .rodata2), each reached via one `lis r9,-0x7fd6` anchor + folded
//    displacement; all four symbols exist in symbols.txt.
//  * self layout: q[] is at 0x138 - the m2c draft's `char _p134[4]` pad pushed
//    it to 0x13C and shifted every downstream load by 4.
//  * File-local struct with the TRUE member types is required (the shared
//    Unk_* classes are all s32 here): obj+0x78 is a 3x4 f32 matrix, obj+0x58/60
//    and +0xB8/C0 are f32 pairs moved with __ps_t.
//
// PRECISE RESIDUAL (named classes, not a blanket "regalloc"):
//  1. obj's home is r24 (want r30) and &sp[0] is rematerialized per call site
//     (want: one r24 home hoisted into the prologue). Pre-REGALLOC allocation
//     choices given the web set. `register s32 __asm__("r30")` on obj, used at
//     every deref, was tried: 23.1%, WORSE. A named `f32 *spp` base: 6.3%.
//     NO register pin is used in the committed body.
//  2. Consequence of (1): with r30 free, GCC materializes the lbl_80298E80
//     anchor in r30 (lis+lfs) and RELOADS it after the bl, where want keeps one
//     scratch r9 anchor rematerialized per use -> +1 insn, then-branch shifts.
//  3. `sc` (the 1/len scale) lands in f11, want has f31; fn_8002C904's fsubs
//     register assignment is f12/f13/f0 where want has f13/f0/f12.
//  4. Sheppard branch: `lfsx` operand ROLES are swapped at 3 sites - want has
//     the row pointer in rA and the scaled column in rB, got the reverse.
//     Probed GCC 2.95 directly: `f32 *a = m[i]; a[j]` gives the want order but
//     `a[j] + b[i]` yields one of each, so this is a per-site allocation
//     artifact, not a source spelling.
//  5. muls0 block interleaving: want does one broadcast, BOTH pair loads, BOTH
//     muls, BOTH stores; got interleaves and needs two broadcasts.
//  6. Quaternion block: 4 spurious `fmr`s (r9<-f0, f3<-f12, f8<-f11, f10<-f13)
//     from the q-value web split, and the 9 output stores use r31 + full
//     displacement where want uses a single r11 = self+0x158 base with small
//     displacements. A named `f32 *o` output base was tried: frame 0x58,
//     stmw r23, 8.2% - WORSE.
// Non-fixes recorded so they are not re-tried: hard register pins, the named
// sp/output base pointers, `volatile` scalar, sc-before-call in the then
// branch, and the `out[11]` struct member all regress.
// FLAG: -mps-float
#include "types.h"

typedef struct {
    char _p000[0x58];
    f32 f058[2];
    f32 f060[2];
    char _p068[0x10];
    f32 m[12];
    char _p0A8[0x10];
    f32 f0B8[2];
    f32 f0C0[2];
} BE0_Obj;

typedef struct {
    char _p000[0x0C];
    BE0_Obj *obj;
    char _p010[0x104];
    s32 f114;
    f32 f118[2];
    f32 f120[2];
    f32 f128[2];
    f32 f130[2];
    f32 q[4];
    char _p148[0x10];
    f32 r158;
    f32 r15C;
    f32 r160;
    char _p164[4];
    f32 r168;
    f32 r16C;
    f32 r170;
    char _p174[4];
    f32 r178;
    f32 r17C;
    f32 r180;
} BE0_Self;

extern f32 lbl_80298E78;
extern f32 lbl_80298E7C;
extern f32 lbl_80298E80;
extern f32 lbl_80298E84;

void fn_8002C8FC(f32 *, f32);
void fn_8002C904(f32 *, f32, f32, f32);
f32 fn_80036304(f32 *);
f32 sqrtf(f32);

s32 fn_800BE020(BE0_Self *self) {
    f32 sp[5];
    BE0_Obj *obj;
    f32 (*mm)[4];
    f32 *ri;
    f32 *rj;
    f32 *rk;
    s32 i;
    s32 j;
    s32 k;
    f32 x;
    f32 y;
    f32 z;
    f32 mag;
    f32 sq;
    f32 sc;
    f32 n;
    f32 a;
    f32 b;
    f32 c;
    f32 xx;
    f32 yy;
    f32 zz;
    f32 az;
    f32 wa;
    f32 wa2;
    f32 bc;
    f32 wb;
    f32 ab;

    obj = self->obj;
    self->f114 = 1;
    *(__ps_t *)&self->f118[0] = *(__ps_t *)&obj->f058[0];
    *(__ps_t *)&self->f120[0] = *(__ps_t *)&obj->f060[0];
    mm = (f32 (*)[4])((char *)obj + 0x78);
    x = obj->m[0];
    y = obj->m[5];
    z = obj->m[10];
    mag = x + y + z;
    if (mag > lbl_80298E78) {
        sq = sqrtf(mag + lbl_80298E7C);
        fn_8002C8FC(sp, sq * lbl_80298E80);
        sc = lbl_80298E80 / sq;
        fn_8002C904(sp,
                    (obj->m[9] - obj->m[6]) * sc,
                    (obj->m[2] - obj->m[8]) * sc,
                    (obj->m[4] - obj->m[1]) * sc);
    } else {
        i = 0;
        if (y > x) {
            i = 1;
        }
        {
            f32 *r0 = mm[i];
            if (z > r0[i]) {
                i = 2;
            }
        }
        j = (i + 1) % 3;
        k = (j + 1) % 3;
        ri = mm[i];
        rj = mm[j];
        rk = mm[k];
        sq = sqrtf((ri[i] - (rj[j] + rk[k])) + lbl_80298E7C);
        sc = lbl_80298E80 / sq;
        sp[i] = sq * lbl_80298E80;
        sp[j] = (ri[j] + rj[i]) * sc;
        sp[k] = (ri[k] + rk[i]) * sc;
        sp[3] = (rk[j] - rj[k]) * sc;
    }
    *(__ps_t *)&self->q[2] = *(__ps_t *)&sp[2];
    *(__ps_t *)&self->q[0] = *(__ps_t *)&sp[0];
    sq = sqrtf(fn_80036304(self->q));
    if (sq > lbl_80298E78) {
        sp[4] = lbl_80298E7C / sq;
        *(__ps_t *)&self->q[0] = __builtin_ps_muls0(*(__ps_t *)&self->q[0], sp[4]);
        *(__ps_t *)&self->q[2] = __builtin_ps_muls0(*(__ps_t *)&self->q[2], sp[4]);
    }
    n = self->q[1] * self->q[1];
    n = n + self->q[0] * self->q[0];
    n = n + self->q[2] * self->q[2];
    n = n + self->q[3] * self->q[3];
    if (n > lbl_80298E78) {
        sc = lbl_80298E84 / n;
    } else {
        sc = lbl_80298E78;
    }
    a = self->q[0] * sc;
    b = self->q[1] * sc;
    c = self->q[2] * sc;
    xx = self->q[0] * a;
    yy = self->q[1] * b;
    zz = self->q[2] * c;
    az = self->q[0] * c;
    wa = self->q[3] * c;
    wa2 = self->q[3] * a;
    bc = self->q[1] * c;
    wb = self->q[3] * b;
    ab = self->q[0] * b;
    self->r15C = ab - wa;
    self->r158 = lbl_80298E7C - (yy + zz);
    self->r160 = az + wb;
    self->r170 = bc - wa2;
    self->r180 = lbl_80298E7C - (xx + yy);
    self->r16C = lbl_80298E7C - (xx + zz);
    self->r168 = ab + wa;
    self->r178 = az - wb;
    self->r17C = bc + wa2;
    *(__ps_t *)&self->f128[0] = *(__ps_t *)&self->obj->f0B8[0];
    *(__ps_t *)&self->f130[0] = *(__ps_t *)&self->obj->f0C0[0];
    return 1;
}
