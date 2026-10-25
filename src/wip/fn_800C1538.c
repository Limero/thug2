// family=m2c range=0x800C1538-0x800C1AA4 size=1388B
// FLAG: -mps-float
//
// REBUILD 2026-10-07. From-scratch transcription of the
// retail instruction stream (build/b34pkt/fn_800C1538.psdiff.txt +
// .diff.txt), replacing the previous m2c/fill_wip_drafts statics husk.
// Everything below is derived from the WANT column, NOT from the old draft.
//
// ============================ FUNCTION IDENTITY ============================
// "quaternion -> rotation matrix + quaternion, with persistent state".
//   arg0->f40..f4C is a QUATERNION (x,y,z,w = a,b,c,d).
//   L   = x*x + y*y + z*z + w*w              (4-term, left-assoc)
//   s   = (L > 0.0f) ? 2.0f / L : 0.0f       (scale)
//   arg0->m[3][4] @0x70 = the rotation matrix of that quaternion:
//       m00 = 1 - (y*sy + z*sz)        m01 = x*sy - w*sz     m02 = x*sz + w*sy
//       m10 = x*sy + w*sz              m11 = 1 - (x*sx + z*sz)  m12 = y*sz - w*sx
//       m20 = x*sz - w*sy              m21 = y*sz + w*sx     m22 = 1 - (x*sx + y*sy)
//     with sx = x*s, sy = y*s, sz = z*s.  (Verified against every emitted
//     fmuls/fmadds/fsubs in 0x15A0..0x1618 -- the old draft's L was
//     `x*x + y + z*z + w*w`, i.e. it dropped y*y and added a linear y; that is
//     NOT what retail computes.  Retail's first FPR op at 0x1568 is
//     `fmuls f0,f0,f0` on the value loaded from 0x44 == y*y.)
//   arg0->fA0..fAC @0xA0 = (0,0,0,1)  (emission order A0, AC, A4, A8)
//
// ============================ CONTROL FLOW =================================
//   if (m11 > 0.999f)                       { i12C = 0; return; }   // 0x166C
//   flag = 0;                                                      // li r11,0 @0x1554
//   if (dot(arg0->wB[0..2]) < 300.0f*300.0f)      // ps dot, low lane
//    if (dot(arg0->wC[0..2]) < (pi/4)*(pi/4))
//     if (arg0->f1340 > 0.0f)
//      if (m11 < 0.25f)
//       if (arg0->i120 == 0 || m11 < 0.0f)      // 0x1DC beq + 0x1E4 bge (merged)
//        if (arg0->i328 != 0) flag = 1;         // li r11,1 @0x1F4
//   if (arg0->i12C == 0) {                                          // 0x1730
//       if (flag == 0) return;                                      // 0x1A88
//       arg0->f30 = 0;   arg0->f3C = 1;                             // 0x1668 block
//       arg0->f34 = 0;   arg0->f38 = 0;
//       arg0->f50 = 0;   arg0->f5C = 1;
//       arg0->f58 = 0;   arg0->f54 = 0;
//       arg0->i12C = 1;
//       arg0->i130 = lbl_80303150 + Tmr_GetTime();
//   }
//   if ((u32)((lbl_80303150 + Tmr_GetTime()) - arg0->i130) > 0x14B4U) {
//       arg0->i12C = 0; return; }                                   // 0x17B8
//   if ((u32)((lbl_80303150 + Tmr_GetTime()) - arg0->i130) <= 0x12BU) return;
//
//   4-iteration self-targeting countdown window (doc-30) at 0x17E0, whose
//   "body" is the four r1 base-pointer rematerialisations
//     addi r30,r1,8 / addi r10,r1,0x18 / addi r29,r1,0x48 / addi r23,r1,0xe0
//   -> in C they are the leading `pmv/po/pva` pointer inits after the loop.
//
//   mv[4][4] @r1+0x08 is built from the matrix's row 2 and its column 2:
//       mv[2][2..3] = m[2][2..3];  mv[2][1] = 0;  mv[2][0..1] = m[2][0..1];
//       dot = |(mv20,mv21,mv22)|^2 (PS low lane)
//       if (dot > 0.0f) { n = ps_rsqrte(dot);
//                         buf = n; buf.hi = 1.0f;
//                         mv[2][0..1] = ps_muls0(mv[2][0..1], n);
//                         mv[2][2..3] = ps_mul(m[2][2..3], buf); }
//   then, in emission order 0x1878:
//       mv[1][2]=0; mv[2][0]=0; mv[2][1]=1; mv[1][3]=1;
//       mv[0][0]=mv[2][2]; mv[0][1]=0; mv[0][2]=-mv[2][0]; mv[0][3]=1;
//   (note mv[1][0]/mv[1][1] are NEVER written -- mv[1][0] has no store at
//    all, so it is not in the source; the old draft's `pmv[1][0]=zero` and
//    `pmv[1][1]=one` do not exist in retail.)
//   fn_80007B94(&out); fn_80007BFC(&out, &arg0->m, mv);
//   t = (fn_800144C8() * 3.0f) / out.f90;  if (t > 1.0f) t = 1.0f;
//   fn_800086B0(&out, &arg0->m, t);
//
//   trace = m00 + m11 + m22;
//   if (trace > 0.0f) {
//       len = sqrtf(trace + 1.0f);  inv = 0.5f / len;
//       fn_8002C8FC(vA, len * 0.5f);
//       fn_8002C904(vA, (m21-m12)*inv, (m02-m20)*inv, (m10-m01)*inv);
//   } else {
//       idx = (m11 > m00) ? 1 : 0;  if (m22 > m[idx][idx]) idx = 2;
//       j = (idx+1)%3;  k = (j+1)%3;
//       len = sqrtf(m[idx][idx] - (m[j][j] + m[k][k]) + 1.0f);
//       inv = 0.5f / len;
//       vA[idx] = len * 0.5f;
//       vA[j]   = (m[j][idx] + m[idx][j]) * inv;
//       vA[k]   = (m[k][idx] + m[idx][k]) * inv;
//       vA[3]   = (m[k][j]   - m[j][k])   * inv;
//   }
//   *(ps *)&arg0->f48 = *(ps *)&vA[2];     // emitted first
//   *(ps *)&arg0->f40 = *(ps *)&vA[0];
//
// ============================ STACK FRAME (exact) ==========================
//   -0x150 stwu | 0x140 stfd f30 | 0x148 stfd f31 | 0x11c stmw r23 (9 GPR:
//   r23..r31, so r23=vA, r24=&m, r29=&out, r30=mv, r31=arg0)
//   mv[4][4] @0x08 (0x40B) | Out1538 @0x48 (0x98B, f90 at +0x90 -> 0xD8)
//   vA[4] @0xE0 (0x10B) | psbuf[3] @0xF0 (0x18B: 0xF0/0xF8 = the two gate
//   dots, 0x100 = the rsqrte pair, 0x104 = its high lane forced to 1.0f).
//   Declared in exactly that order so ngccc lays the slots out ascending.
//
// ============================ UNKNOWNS =====================================
// The packet omits the 16 words whose got/want bytes coincided; three of them
// are inside the flag block (0x1E4, 0x1EC, 0x1F0) and one at 0x3F4 (`mr r3,r23`
// before the fn_8002C8FC call, inferred), one at 0x2D8 (a `psq_st` of the
// arg0+0x90 pair into mv[2][0..1], inferred from the 0x2C8 load/0x2F4 reload).
// The flag-block reconstruction (beq->0x1720 / bge->0x1730 / cmpwi+beq->0x1730)
// is the only 3-instruction shape that both consumes the 0x1E8/0x1F4 anchors
// and merges at 0x1730.
// ===========================================================================
#include "types.h"

typedef float sn_ps __attribute__((mode(PS)));

typedef struct {
    u8  pad000[0x30];
    f32 f30, f34, f38, f3C;
    f32 f40, f44, f48, f4C;   /* quaternion x,y,z,w */
    f32 f50, f54, f58, f5C;
    u8  pad060[0x10];
    f32 m[3][4];              /* 0x70 rotation matrix */
    f32 fA0, fA4, fA8, fAC;
    f32 wB[4];                /* 0xB0 */
    f32 wC[4];                /* 0xC0 */
    u8  pad0D0[0x50];
    s32 i120;                 /* 0x120 */
    u8  pad124[8];
    s32 i12C;                 /* 0x12C */
    s32 i130;                 /* 0x130 */
    u8  pad134[0x1F4];
    s32 i328;                 /* 0x328 */
    u8  pad32C[0x1014];
    f32 f1340;                /* 0x1340 */
} T1538;

typedef struct { u8 pad0[0x90]; f32 f90; u8 pad1[4]; } Out1538;

extern f32 lbl_80299004;    /* 0.0    */
extern f32 lbl_80299008;    /* 2.0    */
extern f32 lbl_8029900C;    /* 1.0    */
extern f32 lbl_80299010;    /* 0.999  */
extern f32 lbl_80299014;    /* 300.0  */
extern f32 lbl_80299018;    /* pi/4   */
extern f32 lbl_8029901C;    /* 0.25   */
extern f32 lbl_80299020;    /* 3.0    */
extern f32 lbl_80299024;    /* 0.5    */
extern f32 lbl_80298F18[2]; /* {0.0, 0.0} */
extern s32 lbl_80303150;
extern s32 Tmr_GetTime(void);          /* 0-arg: retail overwrites r3 first */
extern void fn_80007B94(void *);
extern void fn_80007BFC(void *, void *, void *);
extern f32 fn_800144C8(void);
extern void fn_800086B0(void *, void *, f32);
extern f32 sqrtf(f32);
extern void fn_8002C8FC(f32 *, f32);
extern void fn_8002C904(f32 *, f32, f32, f32);

void fn_800C1538(T1538 *arg0) {
    f32 mv[4][4];
    Out1538 out;
    f32 vA[4];
    __ps_t psbuf[3];
    /* ---- FRAME PAD (earlier measurement fix) ----------------------------
       MEASURED: stwu -0x138 / stfd f31,0x130 / stmw r24,0x110 vs
       retail stwu -0x150 / stfd f30,0x140 + stfd f31,0x148 / stmw r23,0x11c.
       The whole body came out exactly ONE INSTRUCTION (4 bytes) ahead of
       retail (G at +0x1550 held what W has at +0x1554), i.e. the only
       missing prologue word is retail's `stfd f30`.

       Frame arithmetic, derived from the two prologues (mine vs retail):
         gp_save_offset = 0x10 + L        (L = total declared locals)
         frame          = gp_off + gp_size + fp_size
       mine: 0x110 = 0x10 + 0x100, frame 0x110+0x20+0x08 = 0x138   <- measured
       want: 0x11c = 0x10 + 0x10C, frame 0x11c+0x24+0x10 = 0x150  <- retail
       => the rebuilt body is 0x0C bytes of locals SHORT of retail.  Every
       r1-relative access in the whole retail function is accounted for and
       the last one is at +0x104 (psbuf[2].hi), so retail's extra 12 bytes sit
       at r1+0x108..0x113 and are never referenced: they are spilled 4-byte
       temporaries from retail's own source (the sibling m2c draft produces
       them incidentally from its many named f32/s32 locals).  A `volatile`
       pad is the project's documented frame-size knob (AGENTS.md section 5
       `_dummy` mechanism, recipes section 5) and is allocation-forced even
       when unused.  8 + 4 = 0x0C, declared LAST so it lands above psbuf. */
    volatile double _dummy;
    volatile double _dummy4;
    volatile f32 _dummy8;
    /* ^ MEASUREMENT FIX . With the register set
       (1 saved FPR = f31, 7 saved GPRs = r25..r31) the emitted prologue was
       `stwu -0x148` where retail has `-0x150`, i.e. exactly 8 bytes short.
       Frame arithmetic from the two prologues:
         gp_save_offset = 0x10 + L      L = total declared local bytes
         frame          = gp_off + gp_size + fp_size
       earlier: 0x124 = 0x10 + L -> L = 0x114; 0x114 + 0x1c + 0x08 = 0x148.
       retail : 0x11c = 0x10 + L -> L = 0x10C; 0x10C + 0x24 + 0x10 = 0x150.
       So +8 bytes of locals makes `stwu` read -0x150 whatever the saved set
       is (12 -> 20 bytes of pads).  NOTE the pads are declared LAST, above
       psbuf (which ends at r1+0x104), so no live local moves.

       RETAIL'S FULL PROLOGUE is still NOT reproduced: retail also saves a
       SECOND callee-saved FPR (f30) and TWO more callee-saved GPRs (r23, r24)
       -   W: stfd f30,0x140 / stfd f31,0x148 / stmw r23,0x11c
           G: stfd f31,0x140  /                    stmw r25,0x124
       Both gaps are REMATERIALISATION decisions of cc1 2.95, not source
       shapes this body can express:
        (b1) f30 holds the late 0.0f (`lis/lfs f30` at 0x1808, used six times
             0x181C/0x1844/0x187C/0x1888/0x18A4/0x1910).  The body DOES keep
             it in the named local `z0` and uses `z0` at every one of those
             sites, but cc1 gives the pseudo a REG_EQUAL constant and
             rematerialises the pool load at each use instead of keeping the
             register live across the fn_80007B94/BFC/144C8/086B0 calls, so
             no `stfd f30` is emitted.  Blocking remat in pure C is not
             possible (the project's own `"+f"` barrier idiom is inline asm,
             which is banned); recorded as a wall, not a residual.
        (b2) r23/r24 hold the addresses of vA and &arg0->m across the calls;
             cc1 folds `addi rX,r1,const` / `addi rX,r31,0x70` back to each
             use, so only 7 GPRs are saved.  Same class of wall. */

    f32 L, s, a, b, c, d, sa, sb, sc, len, inv, lim;
    /* Retail keeps a SECOND long-lived 0.0f in a callee-saved FPR (f30,
       loaded at 0x800C1808 -- i.e. right here, after the 4-count window --
       and used at 0x181C/0x1844/0x187C/0x1888/0x18A4/0x1910, so its live
       range spans the fn_80007B94/BFC/144C8/086B0 calls).  The other 0.0f
       (f31, loaded at 0x15D4) dies at 0x1718, before any call.  Writing the
       constant inline everywhere makes cc1 rematerialise it per use and save
       only one callee-saved FPR; holding the late one in a named local is
       what earns the `stfd f30` word the frame above is sized for. */
    f32 z0;
    s32 flag, elapsed, idx, jx, kx;
    f32 *v;
    f32 (*m)[4];
    f32 (*pmv)[4];
    f32 *po;
    f32 *pva;
    __ps_t v01, w;

    v = (f32 *)&arg0->f40;

    /* ---------- quaternion -> scale + rotation matrix (0x1554..0x1660) ---- */
    L = arg0->f40 * arg0->f40 + arg0->f44 * arg0->f44
      + arg0->f48 * arg0->f48 + arg0->f4C * arg0->f4C;
    s = (L > lbl_80299004) ? (lbl_80299008 / L) : lbl_80299004;

    m = arg0->m;
    a = v[0];
    b = v[1];
    c = v[2];
    sa = a * s;
    d = v[3];
    sb = b * s;
    sc = c * s;
    /* retail's emission order for the nine stores is exactly the source order
       (the compiler interleaves each product with its store); these are the
       nine in retail's order 0x88,0x74,0x78,0x70,0x84,0x98,0x80,0x90,0x94. */
    m[1][2] = b * sc - d * sa;
    m[0][1] = a * sb - d * sc;
    m[0][2] = a * sc + d * sb;
    m[0][0] = lbl_8029900C - (b * sb + c * sc);
    m[1][1] = lbl_8029900C - (a * sa + c * sc);
    m[2][2] = lbl_8029900C - (a * sa + b * sb);
    m[1][0] = a * sb + d * sc;
    m[2][0] = a * sc - d * sb;
    m[2][1] = b * sc + d * sa;

    arg0->fA0 = lbl_80299004;
    arg0->fAC = lbl_8029900C;
    arg0->fA4 = lbl_80299004;
    arg0->fA8 = lbl_80299004;

    if (arg0->m[1][1] > lbl_80299010) {
        arg0->i12C = 0;
        return;
    }

    /* ---------- gates (0x1664..0x1730) ------------------------------------ */
    flag = 0;
    *(sn_ps *)&psbuf[0] = __builtin_ps_sum0(
        __builtin_ps_madd(*(sn_ps *)&arg0->wB[0], *(sn_ps *)&arg0->wB[0],
                          __builtin_ps_merge00(
                              __builtin_ps_mul(*(sn_ps *)&arg0->wB[2],
                                               *(sn_ps *)&arg0->wB[2]),
                              *(sn_ps *)lbl_80298F18)),
        *(__ps_t *)&psbuf[0], *(__ps_t *)&psbuf[0]);
    if (*(f32 *)&psbuf[0] < lbl_80299014 * lbl_80299014) {
        *(sn_ps *)&psbuf[1] = __builtin_ps_sum0(
            __builtin_ps_madd(*(sn_ps *)&arg0->wC[0], *(sn_ps *)&arg0->wC[0],
                              __builtin_ps_merge00(
                                  __builtin_ps_mul(*(sn_ps *)&arg0->wC[2],
                                                   *(sn_ps *)&arg0->wC[2]),
                                  *(__ps_t *)&psbuf[0])),
            *(__ps_t *)&psbuf[1], *(__ps_t *)&psbuf[1]);
        if (*(f32 *)&psbuf[1] < lbl_80299018 * lbl_80299018) {
            if (arg0->f1340 > lbl_80299004) {
                if (arg0->m[1][1] < lbl_8029901C) {
                    if (arg0->i120 == 0 || arg0->m[1][1] < lbl_80299004) {
                        if (arg0->i328 != 0) {
                            flag = 1;
                        }
                    }
                }
            }
        }
    }

    if (arg0->i12C == 0) {
        if (flag == 0) {
            return;
        }
        arg0->f30 = lbl_80299004;
        arg0->f3C = lbl_8029900C;
        arg0->f34 = lbl_80299004;
        arg0->f38 = lbl_80299004;
        arg0->f50 = lbl_80299004;
        arg0->f5C = lbl_8029900C;
        arg0->f58 = lbl_80299004;
        arg0->f54 = lbl_80299004;
        arg0->i12C = 1;
        arg0->i130 = lbl_80303150 + Tmr_GetTime();
    }
    elapsed = (lbl_80303150 + Tmr_GetTime()) - arg0->i130;
    if ((u32)elapsed > 0x14B4U) {
        arg0->i12C = 0;
        return;
    }
    elapsed = (lbl_80303150 + Tmr_GetTime()) - arg0->i130;
    if ((u32)elapsed <= 0x12BU) {
        return;
    }

    /* ---- 0x17E0: the doc-30 self-targeting 4-count window.  Its four
       "instructions" are the r1 base pointers used below, so the C form is
       an empty 4-iteration loop followed by the pointer inits. */
    {
        s32 spin;
        for (spin = 0; spin < 4; spin++) {
        }
    }
    pmv = mv;
    po = (f32 *)&out;
    pva = vA;
    z0 = lbl_80299004;   /* retail: lis/lfs f30 right after the 4-count window */

    /* ---- 0x1800: row/column 2 of the matrix, normalised ---------------- */
    *(sn_ps *)&pmv[2][2] = *(__ps_t *)&arg0->m[2][2];
    pmv[2][1] = z0;
    *(sn_ps *)&pmv[2][0] = *(__ps_t *)&arg0->m[2][0];
    w = *(__ps_t *)&arg0->m[2][2];
    v01 = *(__ps_t *)&pmv[2][0];
    *(sn_ps *)&psbuf[0] = __builtin_ps_sum0(
        __builtin_ps_madd(v01, v01,
                          __builtin_ps_merge00(__builtin_ps_mul(w, w),
                                               *(__ps_t *)&psbuf[1])),
        *(__ps_t *)&psbuf[0], *(__ps_t *)&psbuf[0]);
    if (*(f32 *)&psbuf[0] > z0) {
        psbuf[2] = __builtin_ps_rsqrte(*(sn_ps *)&psbuf[0]);
        ((f32 *)&psbuf[2])[1] = lbl_8029900C;
        *(sn_ps *)&pmv[2][0] = __builtin_ps_muls0(v01, *(__ps_t *)&psbuf[2]);
        *(sn_ps *)&pmv[2][2] = __builtin_ps_mul(w, *(__ps_t *)&psbuf[2]);
    }

    /* ---- 0x1878: fill the view matrix (retail's order) ------------------ */
    /* FIX: the earlier body wrote r1+0x20/0x28/0x2c/0x24, i.e. it put
       two of these four stores in the mv[2] ROW at 0x28/0x2c -- the very slots
       the rsqrte arm just wrote (0x1864 `psq_st f0,0x28(r1)`, 0x1874
       `psq_st f13,0x30(r1)`).  The retail disassembly stores the row as
       r1+0x18, 0x1c, 0x20, 0x24 = mv[1][0..3] = {0,1,0,1} in THIS emission
       order: 0x187C [1][0]=f30(0), 0x1888 [1][2]=f30(0), 0x188C [1][3]=f31(1),
       0x1890 [1][1]=f31(1).  (mv[2][1] is never set to 1.0f anywhere in
       retail: the 1.0f lane of the rsqrte pair is written to r1+0x104 and
       reaches the matrix only through the 0x1874 ps_mul into mv[2][2..3].) */
    pmv[1][0] = z0;
    pmv[1][2] = z0;
    pmv[1][3] = lbl_8029900C;
    pmv[1][1] = lbl_8029900C;
    pmv[0][0] = pmv[2][2];
    pmv[0][1] = z0;
    pmv[0][2] = -pmv[2][0];
    pmv[0][3] = lbl_8029900C;

    fn_80007B94(po);
    fn_80007BFC(po, m, pmv);
    lim = (fn_800144C8() * lbl_80299020) / out.f90;
    if (lim > lbl_8029900C) {
        lim = lbl_8029900C;
    }
    fn_800086B0(po, m, lim);

    /* ---- 0x1978: matrix -> quaternion ----------------------------------- */
    L = m[0][0] + m[1][1] + m[2][2];
    if (L > z0) {   /* retail 0x1910: fcmpu cr0,f0,f30 -- same f30 as the fill */
        len = sqrtf(L + lbl_8029900C);
        inv = lbl_80299024 / len;
        fn_8002C8FC(vA, len * lbl_80299024);
        fn_8002C904(vA, (m[2][1] - m[1][2]) * inv,
                        (m[0][2] - m[2][0]) * inv,
                        (m[1][0] - m[0][1]) * inv);
    } else {
        idx = 0;
        if (m[1][1] > m[0][0]) {
            idx = 1;
        }
        if (m[2][2] > m[idx][idx]) {
            idx = 2;
        }
        jx = (idx + 1) % 3;
        kx = (jx + 1) % 3;
        len = sqrtf(m[idx][idx] - (m[jx][jx] + m[kx][kx]) + lbl_8029900C);
        inv = lbl_80299024 / len;
        vA[idx] = len * lbl_80299024;
        vA[jx] = (m[jx][idx] + m[idx][jx]) * inv;
        vA[kx] = (m[kx][idx] + m[idx][kx]) * inv;
        vA[3] = (m[kx][jx] - m[jx][kx]) * inv;
    }
    *(sn_ps *)&arg0->f48 = *(sn_ps *)&vA[2];
    *(sn_ps *)&arg0->f40 = *(sn_ps *)&vA[0];
}

// ---------------------------------------------------------------------------
// SUPERSEDED BODY (m2c husk) — earlier findings preserved verbatim below.
// The body above replaced it (worker rebuild + measured-diff repair loop,
// 2); keep these notes, they are still the local lore.
// ---------------------------------------------------------------------------
// WIP DRAFT (non-matching) — hand-reconstructed from the retail disassembly
// (the previous m2c/fill_wip_drafts body was a statics-DCE husk: 14.1%,
//  frame -0x60, all stack slots modelled as file-scope statics).
// FLAG: -mps-float
//
// VERDICT 2026-09-27: DIFF, masked 4.6% (16/347 words), 341 insns / 1364 B
//   vs retail 347 insns / 1388 B.  STRUCTURE IS NOW EXACT where it was hopeless:
//   - the whole 7-instruction prologue is byte-identical to retail:
//     stwu r1,-0x150(r1) / mflr r0 / stfd f30,0x140(r1) / stfd f31,0x148(r1) /
//     stmw r23,0x11c(r1) / stw r0,0x154(r1) / mr r31,r3
//   - callee-saved GPR count 9 (r23..r31) and FPR count 2 (f30,f31) == retail
//   - all 6 callee signatures read off the retail prologues: fn_80124F44 is
//     0-arg s32 (it overwrites r3 before reading it), fn_80007B94 1-arg void,
//     fn_80007BFC 3-arg void, fn_800144C8 0-arg f32, fn_800086B0 (ptr,ptr,f32)
//     void, sqrtf 1-arg f32; fn_8002C8FC/904 are 2-line 4-float stores
//   - real stack locals, all at retail offsets: f32 mv[4][4] @0x08 (0x40B,
//     &mv escapes to fn_80007BFC so retail's dead row-1 stores survive DCE),
//     Out1538 @0x48 (0x98B), f32 vA[4] @0xE0, the two dot-product PS slots
//     @0xF0/0xF8, the rsqrt PS pair @0x100 (its HIGH lane is overwritten with
//     1.0f by retail at 0x104, which is why the final multiply is
//     M[2][2] * {1/len, 1.0f})
//   - the three paired-single dot products compile to real Gekko PS.  Hand-
//     decoded the A-form once and it is reproducible: operand order is
//     (fD,fA,fC,fB); ps_mul fD = frA*frC; ps_madd fD = frA*frC + frB;
//     ps_merge00 fD = {frA.lo, frB.lo}; ps_sum0 fD = {frA.lo+frB.hi, frC.hi}.
//     Each is a 3-term dot x*x+y*y+z*z whose 4th float is zeroed by the
//     merge00 against lbl_80298F18 = (0.0f,0.0f) -- i.e. arg0+0xB0/+0xB4/+0xB8,
//     arg0+0xC0/+0xC4/+0xC8 and M[2][0..2] are 3-vectors with a padded 4th.
//   - the argmax/%3 arm is branchy (li 0; ble; li 1) and uses the
//     slwi/slwi/add/lfsx 2-D row-base + column-offset addressing
//
// The masked score is offset-dominated here (one wrong prologue word zeroes
// the whole byte-offset compare), so 4.6% badly understates convergence: a
// mnemonic-sequence diff puts 292 of 347 retail instructions in matching
// positions, the largest exact runs being 50 @0x800C1968, 28 @0x800C1784,
// 26 @0x800C16E8, 23 @0x800C1650, 13 @0x800C18EC and 13 @0x800C16B0.
//
// RESIDUAL (precise, largest first):
//  1. doc-30 `bdnz $` self-targeting spin, 0x800C17E0-0x800C17FC:
//     `li r0,4; addi r24,r31,0x70; mtctr r0; addi r30/r10/r29/r23; bdnz .`.
//     Retail's four address computes sit INSIDE the countdown window and the
//     branch targets ITSELF.  A plain `for (i=0;i<4;i++){}` emits
//     `li r0,4; mtctr r0; bdnz <forward>` (measured), and
//     docs/parkings/30 records displacement 0 as unreachable from plain C on
//     all five ProDG builds.  The only known fix is a literal `bdnz $`
//     volatile-asm window (docs/parkings/solved/30) -- an asm instruction
//     template, deliberately not used here.  3 insns + 4 mis-placed addis.
//  2. Matrix block 0x800C15A0-0x800C1660: retail holds a/b/c/d in
//     f13/f9/f11/f6 (one load each) and emits its 9 stores in source order.
//     got re-loads 0x4C per product (5 extra `lfs`) and rotates the 9-store
//     run.  Making `d` a named local kills the reloads but costs one extra
//     callee-saved FPR (frame -0x160, stmw@0x124): with the current source
//     shape an exact frame and correct reloads are mutually exclusive.
//  3. rodata constants: retail folds @l into the lfs displacement and
//     re-materialises per use (`lis r9,-0x7fd6; lfs f11,-0x6ffc(r9)`); got
//     hoists the full address (`lis rX,0; lfs fY,0(rX)`).  Same insn count,
//     different ADDR16_HA/LO reloc shape (recipe 53 wants the typed extern,
//     which is already used here -- the hoist is GCSE, not the decl).
//  4. rsqrte arm: retail saves the reciprocal to r1+0x100 and reloads it
//     (`ps_mr; psq_st 256(r1); ...; psq_l f12,256(r1)`) between the two
//     normalises; got keeps it live in an FPR.  Also the two dot results both
//     land on r1+0xF0 instead of 0xF0/0xF8.
//  5. Clamp/sqrt copies: retail keeps an explicit copy
//     (`fmr f0,f1; fcmpu cr0,f1,f31; ble; fmr f0,f31; fmr f1,f0` and
//     `fmr f31,f1`); got folds one of them away, shifting ~6 words in the
//     last third, and the pmv[0][*] store block differs by 2 slots.
//
// No inline-asm instruction templates and no register pins were used.
//
// PARKED 2026-10-07: 4.61% masked, .text 1364B vs retail 1388B.
// Attempted this round: routed a/b/c/d through a real base pointer
// `v = (f32 *)&arg0->f40;` (v[0..3]) instead of the folded `p[0x10..0x13]`
// member forms, to reproduce want's 0x0024 `addi r11,r31,0x40` + the
// `lfs f13,0(r11)` / `lfs f9,4(r11)` / `lfs f11,8(r11)` / `lfs f6,0xc(r11)`
// loads (got had all four r31-relative).  This is a pure addressing-base
// change (same statements, same types), the documented
// `T *ptr = &obj->field;` lever, not a cast.
// WHY IT IS STILL PARKED (first divergence is at 0x001C, before the matrix):
//   * want's L-sum is a 3-fmadd chain whose reused register is f0 = arg0->f44
//     (`fmadds f12,f12,f12,f0` = f40*f40 + f44, then f48, then
//     `fmadds f12,f0,f0,f13` = f44*f44 + ...), i.e. the retail source seeds the
//     accumulator from f44 and squares it LAST.  got loads f40 first (f0) and
//     produces f44*f44 + f40 + f48*f48 + f40*f40 — the two forms are not the
//     same value, so this is a *source-statement order* difference, not merely
//     scheduling.  Trying to reorder it blind is exactly the permutation search
//     the brief forbids; it needs the surrounding constant-materialisation
//     shape settled first.
//   * the rodata constants are hoisted by got into callee-saved f30/f31
//     (`lis r11,0` at 0x001C + `lfs f31,0(r11)` at 0x003C, `lfs f30,0(r9)` at
//     0x0048), while retail re-materialises them per use inside the branch
//     arm (`lfs f0,-0x6ff8(r9)` at 0x0058, `lfs f11,-0x6ffc(r9)` at 0x003C AND
//     again `lfs f31,-0x6ffc(r9)` at 0x009C).  Because the retail prologue
//     genuinely saves f30/f31 (they are used later), the `zero`/`one` locals
//     are NOT simply removable — the correct source shape for the constant
//     webs is unknown, and every guess risks breaking the byte-identical
//     7-word prologue that this draft currently gets right.
//   * remaining walls are unchanged and documented above: the doc-30
//     `bdnz $` self-targeting window at 0x800C17E0 (unreachable from plain C
//     per docs/parkings/30), the 9-store rotation in the matrix block, the
//     d-vector reload count vs callee-saved FPR budget, and the rsqrte-arm
//     stack spill to r1+0x100/0x104.
// Net: the addressing-base fix is kept (it is strictly more faithful), but the
// masked score cannot be moved to 100% without the L-sum statement order and
// the constant-web shape, both of which need measured iteration, not guesses.
// No inline-asm instruction templates and no register pins were used.
