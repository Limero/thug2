// WIP DRAFT (non-matching) — hand-rebuilt from DOL disassembly 2026-09-27
// family=m2c range=0x800C6860-0x800C6EC0 size=1632B
//
// VERDICT 2026-09-27: DIFF. masked 4.7% (was 0.7% for the m2c baseline).
// object 259 insns vs retail 408 insns (1036B vs 1632B). NOT promotable.
// The old header claimed "PARKED (2.9%)" — that number was stale (re-measured
// the committed m2c body at 0.7% with tools/score_body.py).
//
// Recovered and verified instruction-by-instruction against the DOL:
//   * the entry guard, and the value-context fcmpu-cr7 / mfcr / rlwinm. 0x1d
//     bool (probe-confirmed: `s32 r; r = (a < b);` emits that exact triple, and
//     the d1A8 test belongs INSIDE the `if (flag)` arm so flag==0 falls
//     straight through, matching want's `beq 0x800C68CC`)
//   * the TRUE arg0 layout (the shared Unk_4877B8EF class mistypes 16 of the
//     float fields as s32) — a file-local typedef, not a header edit
//   * the 2.0/len2 normaliser (0.0f guard, not a >0 test) and the 3x3 adjugate
//     store block, in want's exact store order
//   * the 122500.0f / 0.3f fn_800086B0 blend pair, with the long-lived 0.0f
//     local (retail f31) that keeps the fsubs/fadds from being folded away
//   * the sqrtf + fn_8002C8FC/2C904 tail incl. the (i+1)%3/(i+2)%3
//     diagonal walk, and the fdivs-before-the-call operand order
//   * all six callee signatures, audited from each callee's own prologue
//     (fn_80007B94 is a 0-arg body; m2c had invented 6 args)
//
// NOT recovered: 0x800C69F8..0x800C6C38 — 144 instructions of Gekko
// paired-single vec2 math. op4 XO5 census = {8,10,12,16,20,25,26,29}: every
// value is standard emittable PS, so this is NOT a doc-29 VMX wall and NOT the
// doc-06 XO5=6/7 wall. m2c had modelled the region as file-scope statics, so
// it DCEs and nothing is emitted for it. That region owns 4 of the 9 callee-
// saved GPRs (r23/r24/r29/r30 are its stack bases) and ~264B of the locals
// area, which is why the frame/save count cannot match until it is written.
// Precise residual at EOF.
#include "types.h"
#include "structs.h"

/* TRUE arg0 layout. The shared Unk_4877B8EF class types 0x74/0x78/0x80/0x84/
 * 0x88/0x90/0x94/0x98/0xA0/0xB0/0x134/0x158/0x19C/0x1A0/0x1A4/0x133C as s32;
 * retail lfs/stfs every one of them, so all are f32 here. Declaring this
 * file-locally (not in structs.h) is what un-blocks the float loads. */
typedef struct C6860 {
    char pad00[0x40];
    f32 m40, m44, m48, m4C;          /* source matrix row 0 (0x40..0x4F)   */
    char pad50[0x20];
    f32 r70, r74, r78;               /* destination matrix row 0           */
    char pad7C[4];
    f32 r80, r84, r88;               /* row 1                              */
    char pad8C[4];
    f32 r90, r94, r98;               /* row 2                              */
    char pad9C[4];
    f32 a0, a4, a8, aC;              /* 0xA0..0xAC                         */
    f32 b0;                          /* 0xB0                               */
    char padB4[4];
    f32 b8;                          /* 0xB8                               */
    char padBC[0x70];
    s32 c12C;                        /* lwz 0x12C                          */
    char pad130[4];
    f32 c134;                        /* lfs 0x134                          */
    char pad138[0x20];
    f32 c158;                        /* lfs 0x158                          */
    char pad15C[0x40];
    f32 d19C, d1A0, d1A4;            /* lfs 0x19C/0x1A0/0x1A4             */
    s32 d1A8;                        /* lwz 0x1A8                          */
    char pad1AC[0x1190];
    f32 d133C;                       /* lfs 0x133C                         */
} C6860;

/* .rodata2 float pool, values read back from the DOL:
 *   0x80299154 = 0.0f        0x80299158 = 2.0f        0x8029915C = 1.0f
 *   0x80299160 = -1.0f       0x80299164 = 122500.0f  0x80299168 = 0.3f
 *   0x8029916C = 0.5f                                                      */
extern f32 lbl_80299154;
extern f32 lbl_80299158;
extern f32 lbl_8029915C;
extern f32 lbl_80299160;
extern f32 lbl_80299164;
extern f32 lbl_80299168;
extern f32 lbl_8029916C;

/* Callee signatures audited from each callee's own prologue:
 *   0x80007B94  leaf, reads no arg reg  -> 0-arg body, 1-arg proto (the
 *               dead-arg form that still materialises r3, per recipe §6t-3)
 *   0x80007BFC  (r3, r4, r5)
 *   0x800086B0  (r3, r4, f1)
 *   0x80270CA4  f32 (f1)                       -> f32
 *   0x8002C8FC  stfs f1,0xc(r3)                -> (f32 *, f32), void
 *   0x8002C904  stfs f3,8 / f1,0 / f2,4        -> (f32 *,f32,f32,f32), void */
void fn_80007B94(void *);
void fn_80007BFC(void *, void *, void *);
void fn_800086B0(void *, void *, f32);
f32 sqrtf(f32);
void fn_8002C8FC(f32 *, f32);
void fn_8002C904(f32 *, f32, f32, f32);

void fn_800C6860(C6860 *o) {
    f32 *v;                          /* (f32 *)(o + 0x70) -> r10, copy r24 */
    f32 *w, *w2;                     /* (f32 *)(o + 0x40) -> r11           */
    f32 *p;                          /* f32[4] out        -> r23            */
    f32 *m, *m2;                     /* callee-arg copies                   */
    f32 *scratch;                    /* 16-byte callee out -> r30           */
    f32 t0, t1, t2, t3;              /* outer test     f0 f12 f13           */
    f32 u0, u1, u2, u3;              /* inner len2 sum f13 f12 f0 f11       */
    f32 sc;                          /* 2.0/len2 or 0.0 -> f0              */
    f32 A, B, C;                     /* v[i]*sc         f5 f12 f0           */
    f32 g0, g1, g2;                  /* v[i]*A/B/C      f8 f9 f13           */
    f32 h0, h1, h2, h3, h4, d3;      /*                  f6 f1 f10 f7       */
    f32 k0, k1;                      /*                  f11 f4             */
    f32 a70, a84, a98;               /* 0x70/0x84/0x98   f11 f12 f10        */
    f32 c130;                        /* 0x133C                             */
    f32 f1v, hlf, sc2;
    f32 zf;                          /* lbl_80299154 = 0.0f, live in f31   */
    f32 psSinkA, psSinkB;           /* paired-single arm sinks (unrecon.)   */
    f32 zo;                          /* lbl_8029915C = 1.0f                 */
    s32 flag;                        /* r8, the fcmpu/mfcr/rlwinm. bool     */
    s32 i, j, k;
    f32 pbuf[4];
    f32 scratchbuf[4];
    f32 pairbuf[2];

    if (o->c12C != 0) {
        return;
    }
    if (o->c134 > lbl_80299154) {
        return;
    }
    t0 = o->b8;
    t1 = o->b0;
    t2 = o->d19C;
    t0 = t0 * t0;
    t1 = t1 * t1 + t0;
    t2 = t2 * t2;
    flag = (t1 < t2);
    /* want: rlwinm. r8,...; beq 0x800C68CC  -> the 0x1A8 test lives INSIDE the
     * flag arm, and flag==0 falls straight through into the body. */
    if (flag) {
        if (o->d1A8 == 0) {
            return;
        }
    }

    v = (f32 *)((char *)o + 0x70);
    u0 = o->m44;
    u1 = o->m40;
    u0 = u0 * u0;
    u2 = o->m48;
    u1 = u1 * u1 + u0;
    u3 = o->m4C;
    u2 = u2 * u2 + u1;
    t3 = u3 * u3 + u2;
    if (t3 > lbl_80299154) {
        sc = lbl_80299158 / t3;
    } else {
        sc = lbl_80299154;
    }

    /* 3x3 adjugate of (row0 * sc), stored back into the matrix at o+0x70.
     * retail re-reads row0 through a fresh base (r11) rather than reusing the
     * u1..u3 values, hence the second pointer. */
    w2 = (f32 *)((char *)o + 0x40);
    A = w2[0] * sc;
    d3 = w2[3];
    B = w2[1] * sc;
    C = w2[2] * sc;
    zo = lbl_8029915C;
    g0 = w2[0] * A;
    g1 = w2[1] * B;
    zf = lbl_80299154;
    g2 = w2[2] * C;
    h0 = w2[0] * C;
    k1 = g0 + g1;
    h1 = d3 * C;
    h2 = d3 * A;
    h3 = w2[1] * C;
    h4 = d3 * B;
    k0 = w2[0] * B;

    v[1] = k0 - h1;
    v[2] = h0 + h4;
    v[6] = h3 - h2;
    v[0] = zo - (g1 + g2);
    v[5] = zo - (g0 + g2);
    v[10] = zo - k1;
    v[4] = k0 + h1;
    v[8] = h0 - h4;
    v[9] = h3 + h2;
    o->a0 = zf;
    o->a4 = zf;
    o->a8 = zf;
    o->aC = zo;
    for (i = 0; i < 4; i++) {
    }

    /* 0x800C69F8 / 0x800C6A6C / 0x800C6ADC: the two paired-single vec2 arms and
     * their merge point, selected by `flag` (beq 0x800C6A6C on flag==0).
     * NOT reconstructed — see the header note.  The sink assignments exist only
     * so the arms keep the second use of `flag` that forces ngccc to materialise
     * the fcmpu-cr7/mfcr/rlwinm. bool instead of folding it to `blt`. */
    if (flag) {
        psSinkA = zo;
    } else {
        psSinkB = zo;
    }

    scratch = scratchbuf;
    p = pbuf;
    m = v;
    m2 = pairbuf;
    fn_80007B94(scratch);
    fn_80007BFC(scratch, m, m2);

    t0 = o->b8;
    t1 = o->b0;
    t0 = t0 * t0;
    t2 = lbl_80299164;
    t1 = t1 * t1 + t0;
    if (t1 > t2) {
        a70 = o->d1A0;
        f1v = o->d1A4 * o->c158;
        c130 = o->d133C;
        if (c130 < a70) {
            a70 = c130;
        }
        fn_800086B0(scratch, m, ((f1v - zf) * ((a70 - zf) / (t2 - zf))) + zf);
    } else {
        f1v = o->d1A4 * lbl_80299168 * o->c158;
        c130 = o->d133C;
        a70 = o->d1A0;
        if (c130 < a70) {
            a70 = c130;
        }
        fn_800086B0(scratch, m, ((f1v - zf) * ((a70 - zf) / (t2 - zf))) + zf);
    }

    a70 = o->r70;
    a84 = o->r84;
    a98 = o->r98;
    f1v = a70 + a84 + a98;
    if (f1v > lbl_80299154) {
        sc2 = sqrtf(f1v + lbl_8029915C);
        hlf = sc2;
        t0 = lbl_8029916C;
        hlf = t0 / hlf;
        fn_8002C8FC(p, sc2 * t0);
        fn_8002C904(p, (o->r94 - o->r88) * hlf,
                    (o->r78 - o->r90) * hlf, (o->r80 - o->r74) * hlf);
    } else {
        i = 0;
        if (a84 > a70) {
            i = 1;
        }
        if (a98 > v[i * 5]) {
            i = 2;
        }
        j = (i + 1) % 3;
        k = (i + 2) % 3;
        sc2 = sqrtf((v[i * 5] - (v[j * 5] + v[k * 5])) + lbl_8029915C);
        hlf = lbl_8029916C / sc2;
        p[i] = sc2 * lbl_8029916C;
        p[j] = (v[4 * j + i] + v[4 * i + j]) * hlf;
        p[k] = (v[4 * k + i] + v[4 * i + k]) * hlf;
        hlf = (v[4 * k + j] - v[4 * j + k]) * hlf;
        p[3] = hlf;
    }
}

// RESIDUAL (exact, for a future pass — 259/408 insns emitted):
//  (1) 0x800C69F8..0x800C6C38 — 144 insns of Gekko paired-single vec2 math.
//      op4 XO5 census over the region = {8,10,12,16,20,25,26,29} only, i.e.
//      ps_mul(25) / ps_madd(29) / ps_sum0(10) / ps_muls0(12) / ps_sub(20) /
//      ps_rsqrte(26) / merge-family(16, selector in bits 10-6) / a mode-2
//      unary(8) — all standard PS, emittable from __ps_t with a per-object
//      `-mps-float`. Operands are stack pairs at sp+0x8,0x18,0x20,0x28,0x30,
//      0x38,0x48,0x50,0x110,0x118 and the zero pair lbl_80298F18 (0.0f,0.0f),
//      loaded via `psq_l`/`psq_st` at I=0. The two arms are selected by the
//      entry `flag` (beq 0x800C6A6C) and merge at 0x800C6ADC. Nothing is
//      emitted for it today, which is the whole 149-insn size gap.
//  (2) Prologue: got `stwu -0x50 / stfd f31,0x48 / stmw r27,0x34` (5 saved
//      GPRs) vs want `stwu -0x158 / stfd f31,0x150 / stmw r23,0x12c`
//      (9 saved GPRs). 4 of the 9 (r23,r24,r29,r30) are the PS region's stack
//      bases and ~264B of the locals area belong to it, so (1) gates this.
//  (3) Head FPR colouring: want `lfs f0,0xb8; lfs f12,0xb0; lfs f13,0x19c`
//      (f0 = the b8 term, f12 = the b0 accumulator) and holds the 0.0f pool
//      constant in f10; ngccc emits `lfs f0,0xb0; lfs f13,0xb8; lfs f10,0x19c`
//      and holds it in f8. Identical RTL — this is local-alloc order, and three
//      semantically-identical source orderings (swap the first two loads, move
//      the 0x19c square first) all score identically, so it is not reachable
//      by source shape. It should fall out once (1) puts the real float web
//      back, because the allocator's free-list state depends on it.
//  (4) want re-reads row0 through the r11 base (`lfs f11,0(r11)`) instead of
//      folding onto the earlier `lfs f12,0x40(r31)`; a distinct second pointer
//      variable (w2) does not defeat the fold, and no `volatile`/barrier form
//      was found that does not also perturb the store order.
//  (5) The 9 adjugate stores come out rotated by 6 relative to want's
//      (want 0x74,0x78,0x88,0x70,0x84,0x98,0x80,0x90,0x94); the source order
//      IS want's order, so this is a store-scheduling artifact of ngccc filling
//      the wait slots for the three `zo - (...)` subtractions. Reordering the
//      source only trades one rotation for another.
//  (6) The `if (flag) psSinkA = zo; else psSinkB = zo;` pair is scaffolding
//      only: the second use of `flag` is what stops ngccc if-converting the
//      value-context bool back into a plain `blt`. Delete both arms together
//      with the flag's `if` arm when (1) is written.

