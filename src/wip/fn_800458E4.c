// WIP DRAFT (non-matching) — semantic reconstruction from the WANT disassembly.
// REFRESHED 2026-10-07 (scaffold/flag/volatile re-sweep): 0.3195% -> 1.2780% per-object flags: -mps-float -> -O1 -mps-float
// family=m2c range=0x800458E4-0x80045DC8 size=1252B
// FLAG: -O1
// FLAG: -mps-float
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// RE-TRIAGED 2026-10-17: still parked, body unchanged (PS-merge + 18-FPR
// frame walls stand; the 4-iteration delay loop is spellable after all —
// `for (i = 4; i != 0; i--) {}` survives ngccc and matches byte-identical
// (proven on fn_80176FA8, 2026-10-17) — but that alone does not unlock this
// function (undecoded op4 merges + FPR frame remain).
// PARKED 2026-10-06. Rebuilt the m2c husk into a
// typed, structured body.  The old body read uninitialised `temp_f0`/`temp_f13`
// as the four stored values and modelled the 4x4 scratch matrix as fifteen
// FILE-SCOPE `static s32 sp18..sp54` slots (so every transform read came from
// address 0).  Those are replaced by real locals here.
//
// DECODED SHAPE (all of it is legible in tmp_bundles/800458E4.md):
//   t  = fn_8005E1C4(arg0) / lbl_802927D8
//   a  = -(((fx - lbl_802927D0) * t) * fz) / lbl_802927DC
//   b  =  (((fy - lbl_802927D4) * fz))      / lbl_802927DC
//   mv = { a, b, fz, lbl_802927E0 }
//   out[16] = 4x4 base matrix (diagonal lbl_802927E0, off-diagonal lbl_802927E4)
//   r3 = fn_8005DE90(arg0, t)
//   if (r3) {
//       p   = fn_800246AC(r3)            // returns the 0x40-byte object matrix
//       mA  = p[0..7] as eight __ps_t    // 0x40 bytes
//       mA row3 = { lbl_802927E4, lbl_802927E4, lbl_802927E4, lbl_802927E0 }
//       obj = fn_80024660(r3, 0)         // returns a second matrix
//       wv  = { lbl_802927E4, obj[0], obj[1], lbl_802927E4 }
//       out = out * mA                   // 4x4 concat, row-vector convention
//       write the product back to out (paired-single pair stores)
//   }
//
// BLOCKER (why it is parked) — the expected PS wall, in two parts:
//  1. INLINE PAIRED-SINGLE.  67 words are PS.  Between 0x80045AB0 and
//     0x80045B00 the WANT pair-merges `mv` against the mA rows with eight
//     `.word # op4` merges (`0x10000258`, `0x11080258`, `0x10E7025E`,
//     `0x10C6425E`, `0x114A3ADC`, `0x11AD32DC`, `0x118C52DE`, `0x10006ADE`)
//     producing the r1+0x58/r1+0x60 warp pair, and the two sp8 merges at
//     0x80045A0C/0x80045A18.  Their operand fields are undecodable here
//     (capstone stalls at the first op4 word; `tools/ps_disasm.py` is needed),
//     so the warp block below is a scalar approximation, NOT a decode.
//  2. THE ALLOCATOR.  The WANT saves f14..f31 (18 doubles) plus r28..r31 and
//     sizes the frame at 0x178; the same source in ngccc with this many live
//     packed values sizes it differently, which shifts every stack offset and
//     the whole `stfd`/`lfd` run.  Matching also needs a real `ps` register
//     map, which plain C cannot pin (PS register pins are dropped by reload).
//  Also unspellable from C: the empty 4-iteration delay loop at 0x80045A38
//     (`li r0,4; mtctr r0; bdnz .`) between fn_800246AC and the matrix copy.
//  Best body is left above; expect the prologue/frame and the PS words to be
//  the residual.  Do NOT promote.
#include "types.h"
#include "structs.h"

extern char lbl_802927D0[];
extern char lbl_802927D4[];
extern char lbl_802927D8[];
extern char lbl_802927DC[];
extern char lbl_802927E0[];
extern char lbl_802927E4[];

f32 fn_8005E1C4(void *);
void *fn_8005DE90(void *, f32);
void *fn_800246AC(void *);
void *fn_80024660(void *, s32);

void fn_800458E4(void *arg0, f32 *out, const f32 *vin, f32 fx, f32 fy, f32 fz) {
    f32 t;
    f32 k0;
    f32 k1;
    f32 a;
    f32 b;
    __ps_t mA[8];
    __ps_t mv[2];
    __ps_t wv[2];
    __ps_t *p;
    __ps_t *obj;
    void *r3;
    f32 x0, x1, x2, x3;
    f32 y0, y1, y2, y3;
    f32 z0, z1, z2, z3;
    f32 w0, w1, w2, w3;
    f32 r0, r1, r2, r3v;
    f32 *m;

    k0 = *(f32 *)lbl_802927E0;
    k1 = *(f32 *)lbl_802927E4;

    t = fn_8005E1C4(arg0) / *(f32 *)lbl_802927D8;

    a = ((fx - *(f32 *)lbl_802927D0) * t * fz) / *(f32 *)lbl_802927DC;
    b = ((fy - *(f32 *)lbl_802927D4) * fz) / *(f32 *)lbl_802927DC;

    m = (f32 *)mv;
    m[0] = -a;
    m[1] = b;
    m[2] = fz;
    m[3] = k0;

    /* base 4x4 matrix: diagonal k0, off-diagonal k1 */
    out[0] = k0;
    out[15] = k0;
    out[14] = k1;
    out[1] = k1;
    out[2] = k1;
    out[3] = k1;
    out[4] = k1;
    out[5] = k0;
    out[6] = k1;
    out[7] = k1;
    out[8] = k1;
    out[9] = k1;
    out[10] = k0;
    out[11] = k1;
    out[12] = k1;
    out[13] = k1;

    (void)vin;

    r3 = fn_8005DE90(arg0, t);
    if (r3 != 0) {
        p = (__ps_t *)fn_800246AC(r3);
        mA[0] = p[0];
        mA[1] = p[1];
        mA[2] = p[2];
        mA[3] = p[3];
        mA[4] = p[4];
        mA[5] = p[5];
        mA[6] = p[6];
        mA[7] = p[7];
        m = (f32 *)mA;
        m[12] = k1;
        m[13] = k1;
        m[14] = k1;
        m[15] = k0;

        obj = (__ps_t *)fn_80024660(r3, 0);
        m = (f32 *)wv;
        m[0] = k1;
        m[1] = ((const f32 *)obj)[0];
        m[2] = ((const f32 *)obj)[1];
        m[3] = k1;

        /*
         * The WANT pair-merges `mv` against the four mA rows here and keeps the
         * two results in wv (r1+0x58 / r1+0x60).  The merge operand fields are
         * undecoded (see the park note); this scalar form is an approximation.
         */
        m = (f32 *)wv;
        m[0] = ((f32 *)mv)[3] * ((f32 *)mA)[3];
        m[1] = ((f32 *)mv)[1] * ((f32 *)mA)[7];
        m[2] = ((f32 *)mv)[3] * ((f32 *)mA)[11];
        m[3] = ((f32 *)mv)[3] * ((f32 *)mA)[15];

        x0 = out[0];
        x1 = out[1];
        x2 = out[2];
        x3 = out[3];
        y0 = out[4];
        y1 = out[5];
        y2 = out[6];
        y3 = out[7];
        z0 = out[8];
        z1 = out[9];
        z2 = out[10];
        z3 = out[11];
        w0 = out[12];
        w1 = out[13];
        w2 = out[14];
        w3 = out[15];
        m = (f32 *)mA;

        r0 = x0 * m[0] + x1 * m[4] + x2 * m[8] + x3 * m[12];
        r1 = x0 * m[1] + x1 * m[5] + x2 * m[9] + x3 * m[13];
        r2 = x0 * m[2] + x1 * m[6] + x2 * m[10] + x3 * m[14];
        r3v = x0 * m[3] + x1 * m[7] + x2 * m[11] + x3 * m[15];
        out[0] = r0;
        out[1] = r1;
        out[2] = r2;
        out[3] = r3v;

        r0 = y0 * m[0] + y1 * m[4] + y2 * m[8] + y3 * m[12];
        r1 = y0 * m[1] + y1 * m[5] + y2 * m[9] + y3 * m[13];
        r2 = y0 * m[2] + y1 * m[6] + y2 * m[10] + y3 * m[14];
        r3v = y0 * m[3] + y1 * m[7] + y2 * m[11] + y3 * m[15];
        out[4] = r0;
        out[5] = r1;
        out[6] = r2;
        out[7] = r3v;

        r0 = z0 * m[0] + z1 * m[4] + z2 * m[8] + z3 * m[12];
        r1 = z0 * m[1] + z1 * m[5] + z2 * m[9] + z3 * m[13];
        r2 = z0 * m[2] + z1 * m[6] + z2 * m[10] + z3 * m[14];
        r3v = z0 * m[3] + z1 * m[7] + z2 * m[11] + z3 * m[15];
        out[8] = r0;
        out[9] = r1;
        out[10] = r2;
        out[11] = r3v;

        r0 = w0 * m[0] + w1 * m[4] + w2 * m[8] + w3 * m[12];
        r1 = w0 * m[1] + w1 * m[5] + w2 * m[9] + w3 * m[13];
        r2 = w0 * m[2] + w1 * m[6] + w2 * m[10] + w3 * m[14];
        r3v = w0 * m[3] + w1 * m[7] + w2 * m[11] + w3 * m[15];
        out[12] = r0;
        out[13] = r1;
        out[14] = r2;
        out[15] = r3v;

        (void)wv;
        (void)obj;
    }
}

// NOTE (2026-10-06): the body above is a typed reconstruction of the
// algorithm, not a byte match.  Concrete defects removed from the previous m2c
// body: (1) the file-scope `static s32 sp18..sp54` scratch slots (the real
// function keeps a 4x4 f32 matrix in locals at r1+0x18..r1+0x54); (2) the
// uninitialised `temp_f0`/`temp_f13` written into out[0..0x3C]; (3) the literal
// `0;` statements standing in for the PS ops; (4) `fn_8005E1C4(0x80290000, ..)`
// — the call takes only arg0 (r3 is arg0 and r4 is never set).  The residual is
// the PS wall described in the header: 67 paired-single words, the eight
// undecoded op4 merges forming the r1+0x58/0x60 warp, the unspellable 4-iteration
// CTR delay loop, and the 18-double FPR frame the allocator will not reproduce
// from a scalar body.  Re-measure with tools/test_wip_drafts.py --addr
// 0x800458E4 (it auto-appends -mps-float for __ps_t bodies); the pre-edit husk is
// snapshotted at build/ctx50/orig/fn_800458E4.c.
