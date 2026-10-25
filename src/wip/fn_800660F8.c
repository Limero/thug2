// PARKED 2026-10-03 (b05): DIFF ~1.9% (baseline was FAIL - did not compile).
// reproduce: LEAF_TMPDIR=<scratch> tools/venv/bin/python tools/test_wip_drafts.py --addr 0x800660F8
//   got .text = 1868B vs want 1852B (4 words long). The prologue frame now matches
//   EXACTLY (stwu r1,-0xe0 / mflr / stfd f29,f30,f31 @0xc8,0xd0,0xd8 / stw LR @0xe4),
//   i.e. local-slot layout and callee-saved-FPR count are solved. What is left is
//   scheduling + register allocation.
//
// THE FAIL (one line, and it was the whole baseline):
//   m2c emitted a bare `sqrtf()` with no argument -> ngccc 'too few arguments to
//   function sqrtf' (hard error, no .o). It is `sqrtf(fn_80036304(acc))`:
//   fn_80036304 RETURNS f32 - proven because its result in f1 is the immediate
//   operand of `bl sqrtf` at 0x800665DC with no reload in between (a call clobbers
//   f1, so f1 must be that call's return value).  Also fn_80060E84 / fn_8006239C /
//   fn_8005FD68 were undeclared (implicit decls) and fn_8006239C had 10 phantom
//   args; the want shows exactly 5 (node, r, g, b, a) in r3..r7, no crclr.
//
// SOLVED (reusable):
//   * Local-slot rule here: 64-byte aggregate at the bottom (Mat4 m @0x08), then
//     4-byte slots in REVERSE declaration order -> s58@0x58, pc@0x54, cr@0x50,
//     cb@0x4c, ca@0x48. That order is what walked the frame 0x100 -> 0xc0 -> 0xe0.
//   * Float literals live across calls MUST be written inline at each use site
//     (*(f32 *)lbl_80294184 etc). Hoisting them into f32 locals made ngccc keep 7
//     FPRs live -> frame 0x100. The want keeps only f29 (1.0f, used by the quat
//     matrix); every other constant is rematerialised with lfs fX,0x418x(r21).
//   * fn_80036304 returning f32 also explains the dead `mr r10, r23` at 0x800665E4.
//   * int->double->float lowerings are automatic and reference the CRT pool
//     (lbl_80294188 = 2^52+2^31 for SIGNED, lbl_80294190 = 2^52 for UNSIGNED), so
//     `(f32)(f64)x` reproduces xoris/lfd/fsub/frsp with the right pool symbol as
//     long as x's signedness is right. Signed: (u8)b-(u8)a and i&3. Unsigned
//     (no xoris, 2^52): the u8 channel in the clamp step.
//   * The >= test on the colour lerp is `arg0->f110 >= 0.0f` (NOT a zero copy).
//   * Colours are packed s32 words read byte-wise; that is what forces the
//     stw-to-slot / lbz-from-slot shape (Col struct + .r fields gets rlwinm'd).
//
// RULED OUT / STILL MISSING (in order of expected value):
//  1. EIGHT PAIRED-SINGLE WORDS at 0x800665F8 through 0x80066614 unimplemented.
//     Decoded with the paired-single diff decoder: a pair load of f13 from 88(r1)
//     plus an indexed pair load of f0 from r27 plus r30 feed a pair move into f12;
//     f0 is scaled by f12 and stored indexed back to r27 plus r30; then f13 is
//     pair-loaded from 8(r31), scaled by f12, and pair-stored back to 8(r31).
//     i.e. the `if (len > 0)` body scales acc->xy and cr.rg by 1/len as PS pairs,
//     not 4 scalar f32 `*=` (what I wrote). NOTE 0x5c is never written so lane 1
//     of the multiplier is garbage - the original probably has a latent ap->y bug.
//     Needs __ps_t (include/dolphin/SN_PS.h has ps_lx/ps_muls0/ps_mr/psq_lx).
//  2. EIGHT DEAD `mr rN, r9` at 0x800662D8-0x80066300 (r3,r4,r5,r6,r7,r8,r11,r30
//     all = the *cb word). r3..r7 look like arg setup for fn_8006239C but every one
//     is clobbered before the bl. Cause unknown - probably the original's colour
//     locals were reached through a pointer.
//  3. First identity-matrix init emits as 0x0c,0x08,0x10,0x40,0x14,0x18,...,0x34,
//     0x38,0x3c,0x44 with `cmpw r25,r0` sunk into the middle of the store run; the
//     SECOND (in-loop) init emits in plain source order 0x08..0x44. I use one
//     source order for both (0x0c,0x08,0x10,0x44,0x14,...,0x3c,0x40) - the first
//     one needs the 0x40/0x44 pair swapped and the latch sunk at slot 4.
//  4. Register assignment: want uses r14=pool, r15=&m, r16=o12, r17=&ca, r18=&cb,
//     r19=&cr, r20=&m[3], r21=pool, r22..r27=offsets, r28=&m, r29=arg0, r26=0x43300000.
//     Mine picks arg0 into r31 not r29 and starts `stmw r15` not `stmw r14`.
//  5. The first-loop guard folds in my build (cmpwi r0,0; beq) but not in the want
//     (cmplw r9,r0; bge). The want keeps the already-loaded n94 in r9 for BOTH
//     tests, so the source holds n94 in a variable across the if (ngccc 2.95 does
//     not propagate ==0 into the branch); everything later re-loads 0x94(r29).
//     NOT TRIED: a plain local risks a new stack slot and the frame is exact now.
//  6. r10 (= p100+o30) is rebuilt in the want (mr r10,r23; add r10,r10,r0) for the
//     three `lfs f0,0x18(r10)` uses of the 0x18 field, while 0x28/0x2C go through
//     the walking pointer r24 - so the source has BOTH `SrcBone *s` and
//     `p100[o30]`-shaped expressions. I use the same expression for both.
//
// NEXT IDEA: #1 is the only remaining *semantic* hole; write it with __ps_t and
// re-measure before touching store order again.
////// WIP DRAFT (non-matching) — C body generated by tools/fill_wip_drafts.py
// family=m2c range=0x800660F8-0x80066834 size=1852B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// SEARCHED 2026-09-11 (tools/store_order_search.py): store/assignment block(s) re-ordered (reversed / ascending / descending); score now 0.8% ([3]rev->0.7% [17]rev->0.8% [15]rev->0.8%).
// UPDATED 2026-09-15 (e): 1.0% -> 1.1%. raw address literal -> registered lbl_ symbol: MWCC emits lis+ori for a literal constant but lis+addi for a symbol address. tools/raw_sym_scan.py automated the A/B; keep the best body.
// extra_cflags: -mps-float
#include "types.h"

extern char lbl_80294180[];
extern char lbl_80294184[];
extern char lbl_80294198[];
extern char lbl_8029419C[];
extern char lbl_802941A0[];

void fn_80060E84(void *, s32);
void fn_8006239C(void *, u32, u32, u32, u32);
f32 fn_80036304(void *);
void fn_8005FD68(void *, void *, s32, s32);
f32 sqrtf(f32);

typedef struct { f32 x, y, z, w; } Quat;
typedef struct { f32 m[4][4]; } Mat4;
typedef struct { f32 x, y, z; } Vec3;
typedef struct { u8 r, g, b, a; } Col;

/* 0x30-byte per-bone record; arg0->p100 points at the array */
typedef struct {
    Quat q;
    f32 pad10;
    f32 pad14;
    f32 w;        /* 0x18 */
    f32 pad1c;
    f32 pad20;
    f32 pad24;
    f32 n28;      /* 0x28 */
    f32 n2c;      /* 0x2C */
} SrcBone;

typedef struct {
    u8 pad0[0x68];
    f32 f68, f6C, f70;
    u8 pad1[0x20];
    s32 n94;
    u8 pad2[0x5C];
    f32 fF4;
    u8 pad3[0x08];
    SrcBone *p100;
    u8 pad4[0x0C];
    f32 f110;
    s32 *p114, *p118, *p11C;
    u8 pad5[0x04];
    Vec3 *p124;
    u8 pad6[0x4C];
    s32 n174;
    Quat *p178;
    u8 pad7[0x04];
    s32 *p180;
} Node;

void fn_800660F8(Node *arg0) {
    Mat4 m;
    f32 s58;
    u32 pc;
    Col cr;
    s32 cb;
    s32 ca;

    s32 ctr;
    s32 i;
    s32 k180;
    s32 k100;
    s32 k178;
    s32 k124;
    SrcBone *bp;
    Quat *ap;

    f32 one, t, f3, qf;
    s32 ea;
    f32 A, B, C, aa, bb, dd, ee, ff, gg, hh, jj;

    if (arg0->n94 == 0) {
        i = 0;
        k180 = 0;
        while ((u32)arg0->n94 < (u32)arg0->n174) {
            i++;
            fn_80060E84(arg0->p180[k180], 0);
            k180++;
        }
    } else {
        i = arg0->n94 - 1;
        k180 = arg0->n94 - 1;
        while ((u32)i < (u32)arg0->n174) {
            i++;
            fn_80060E84(arg0->p180[k180], 0);
            k180++;
        }

        ctr = 4;
        do {
            ctr -= 1;
        } while (ctr != 0);

        one = *(f32 *)lbl_80294180;
        i = 0;
        m.m[0][1] = *(f32 *)lbl_80294184;
        m.m[0][0] = one;
        m.m[0][2] = *(f32 *)lbl_80294184;
        m.m[3][3] = one;
        m.m[0][3] = *(f32 *)lbl_80294184;
        m.m[1][0] = *(f32 *)lbl_80294184;
        m.m[1][1] = one;
        m.m[1][2] = *(f32 *)lbl_80294184;
        m.m[2][0] = *(f32 *)lbl_80294184;
        m.m[2][1] = *(f32 *)lbl_80294184;
        m.m[2][2] = one;
        m.m[2][3] = *(f32 *)lbl_80294184;
        m.m[3][0] = *(f32 *)lbl_80294184;
        m.m[3][1] = *(f32 *)lbl_80294184;
        m.m[3][2] = *(f32 *)lbl_80294184;

        bp = arg0->p100;
        if (i >= arg0->n94) {
            return;
        }
        for (k124 = 0, k100 = 0, k178 = 0, k180 = 0; i < arg0->n94; ) {
            fn_80060E84(arg0->p180[k180], 1);

            qf = arg0->f110;
            f3 = bp->n28 / bp->n2c;
            if (qf >= *(f32 *)lbl_80294184) {
                if (f3 < qf) {
                    f3 = f3 / qf;
                    ca = *(s32 *)arg0->p114;
                    cb = *(s32 *)arg0->p118;
                } else {
                    ca = *(s32 *)arg0->p118;
                    cb = *(s32 *)arg0->p11C;
                    f3 = (f3 - qf) / (one - qf);
                }
            } else {
                ca = *(s32 *)arg0->p114;
                cb = *(s32 *)arg0->p11C;
            }

            *((u8 *)&cr) = (u8) ca
                + (s32)((f32)(f64)((u8) cb - (u8) ca) * f3);
            *((u8 *)&cr + 1) = (u8)(*(s32 *)((char *)&ca + 1)
                + (s32)((f32)(f64)(*(s32 *)((char *)&cb + 1)
                - *(s32 *)((char *)&ca + 1)) * f3));
            *((u8 *)&cr + 2) = (u8)(*(s32 *)((char *)&ca + 2)
                + (s32)((f32)(f64)(*(s32 *)((char *)&cb + 2)
                - *(s32 *)((char *)&ca + 2)) * f3));
            *((u8 *)&cr + 3) = (s8)(*(s32 *)((char *)&ca + 3)
                + (s32)((f32)(f64)(*(s32 *)((char *)&cb + 3)
                - *(s32 *)((char *)&ca + 3)) * f3));

            t = arg0->fF4 * arg0->f68 * (f32)(f64)cr.r;
            if (t < *(f32 *)lbl_80294184) {
                t = *(f32 *)lbl_80294184;
            } else if (t > *(f32 *)lbl_80294198) {
                t = *(f32 *)lbl_80294198;
            }
            cr.r = (u8)(s32)t;

            t = arg0->fF4 * arg0->f6C * (f32)(f64)cr.g;
            if (t < *(f32 *)lbl_80294184) {
                t = *(f32 *)lbl_80294184;
            } else if (t > *(f32 *)lbl_80294198) {
                t = *(f32 *)lbl_80294198;
            }
            cr.g = (u8)(s32)t;

            t = arg0->fF4 * arg0->f70 * (f32)(f64)cr.b;
            if (t < *(f32 *)lbl_80294184) {
                t = *(f32 *)lbl_80294184;
            } else if (t > *(f32 *)lbl_80294198) {
                t = *(f32 *)lbl_80294198;
            }
            cr.b = (u8)(s32)t;

            pc = *(u32 *)&cr;
            fn_8006239C(arg0->p180[k180], pc >> 24, (pc >> 16) & 0xFF,
                        (pc >> 8) & 0xFF, pc & 0xFF);

            ap = arg0->p178 + k178;
            ap->x += arg0->p100[k100].q.x;
            ap->y += arg0->p100[k100].q.y;
            ap->z += arg0->p100[k100].q.z;
            ap->w += arg0->p100[k100].q.w;

            qf = sqrtf(fn_80036304(ap));
            if (qf > *(f32 *)lbl_80294184) {
                qf = one / qf;
                s58 = qf;
                ap->x *= qf;
                ap->y *= qf;
                cr.r *= qf;
                cr.g *= qf;
            }

            m.m[0][0] = one;
            m.m[0][1] = *(f32 *)lbl_80294184;
            m.m[1][0] = *(f32 *)lbl_80294184;
            m.m[3][3] = one;
            m.m[0][3] = *(f32 *)lbl_80294184;
            m.m[1][1] = *(f32 *)lbl_80294184;
            m.m[1][2] = one;
            m.m[2][0] = *(f32 *)lbl_80294184;
            m.m[2][1] = *(f32 *)lbl_80294184;
            m.m[2][2] = *(f32 *)lbl_80294184;
            m.m[2][3] = *(f32 *)lbl_80294184;
            m.m[3][0] = one;
            m.m[3][1] = *(f32 *)lbl_80294184;
            m.m[3][2] = *(f32 *)lbl_80294184;
            m.m[3][3] = *(f32 *)lbl_80294184;

            t = ap->w * ap->w + ap->z * ap->z + ap->x * ap->x + ap->y * ap->y;
            if (t > *(f32 *)lbl_80294184) {
                t = *(f32 *)lbl_8029419C / t;
            } else {
                t = *(f32 *)lbl_80294184;
            }

            A = ap->x * t;
            B = ap->y * t;
            C = ap->z * t;
            aa = ap->x * A;
            bb = ap->y * B;
            dd = ap->x * C;
            ee = ap->w * C;
            ff = ap->w * A;
            gg = ap->y * C;
            hh = ap->w * B;
            jj = ap->x * B;

            m.m[0][1] = jj - ee;
            m.m[0][2] = dd + hh;
            m.m[1][2] = gg - ff;
            m.m[0][0] = one - bb;
            m.m[1][1] = one - aa;
            m.m[2][2] = one - (aa + bb);
            m.m[1][0] = jj + ee;
            m.m[2][0] = dd - hh;
            m.m[2][1] = gg + ff;

            m.m[3][0] = arg0->p124[k124].x;
            m.m[3][1] = arg0->p124[k124].y;
            m.m[3][2] = arg0->p124[k124].z;
            m.m[3][3] = one;

            ea = i;
            if (ea < 0) {
                ea = ea + 3;
            }
            ea = i - (ea & ~3);
            t = (f32)(f64)ea * *(f32 *)lbl_802941A0;
            m.m[0][0] = m.m[0][0] * (arg0->p100[k100].w - t);
            m.m[1][3] = m.m[1][3] * (arg0->p100[k100].w - t);
            m.m[3][0] = m.m[3][0] * (arg0->p100[k100].w - t);

            fn_8005FD68(arg0->p180[k180], &m, 1, 0);

            i++;
            k124++;
            k100++;
            k178++;
            bp++;
            k180++;
        }
    }
}
