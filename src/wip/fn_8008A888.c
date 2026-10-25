// WIP DRAFT (non-matching) — hand-rebuilt from disasm; the m2c husk did not
// even compile (`sinf` called with 7 args).
// family=ps range=0x8008A888-0x8008B354 size=2764B
// extra_cflags: -mps-float
// INERT: not registered in splits.txt/configure.py — never compiled.
//
// PARKED 2026-10-05 (fn_8008A888): best measured 3.72% strict
// (tools/score_wip.py: want 2764B, got 2580B, 621/645 diffs, verdict DIFF).
// The body below is a complete, semantically faithful rebuild — every block
// of retail has a counterpart (QB command block, the two CrossProduct +
// two Normalize calls, the 3-entry colour lerp/clamp loop, the two
// pre-loop sinf/cosf accumulates, and the 6-call sinf/cosf ANG loop with its
// 12 PS accumulator updates) — and the int<->float conversion idiom is
// byte-shaped correctly (xoris/lis 0x4330/stw hi/stw lo/lfd/fsub/frsp/
// fctiwz/stfd/lwz, verified by probe).  It went from FAIL (did not compile,
// 0%) to this, so it is strictly better than what was here before.
//
// Residual (what is left, roughly in order of size):
//  1. FRAME: -0x268(r1) vs retail -0x248(r1); stmw r14 vs retail stmw r16,
//     and 5 stfd (f27..f31) vs retail's 7 (f25..f31).  Retail's local area is
//     0x08..0x1CF with two never-touched 36/56-byte holes (0xf4..0x117 and
//     0x190..0x1C7) that I cannot account for from the disassembly, so the
//     32 extra bytes of live locals I have cannot be trimmed blindly.  Every
//     stack-displacement in the body therefore differs.
//  2. The staging word pair lands at r1+0x1E8 rather than r1+0x1C8, and
//     retail REUSES that one 8-byte pair for both the int->f64 staging and
//     the fctiwz->s32 result, while ngccc gave me two slots (0x1E8/0x1F0).
//  3. ACC shape: retail emits `psq_l <scalar slot>; ps_mr fX,fY; ps_muls0 x2`
//     per operand.  Taking the operand as `(a)->ps` gives no ps_mr; taking it
//     as `(a)->f.x` gives the ps_mr but makes GCC scalarise `Vec2 s[]` and
//     spill extra f32 temporaries.  The scalar form was kept (it is both
//     closer in length and 3.72% vs 3.66%).
//  4. Retail reloads the colour bytes out of the frame (`lbz r0,1(r29)`) after
//     storing them; ngccc forwards the registers and emits an extra
//     `clrlwi rX,rX,0x18` per channel.
//  5. `crclr cr1eq` before `bl fn_8001F2D8` (1 word).  fn_8001F2D8 returns
//     void in retail (checked: its epilogue is plain `lmw/addi/blr`), and
//     declaring it f32/f64/__ps_t does not make ngccc emit the crclr.
//  6. The four accumulator vec3s at r1+0xA8/0xB8/0xC8/0xD8 and the s[] pair
//     array at 0x120 are correct in the first three; s[] is fragmented by
//     GCC to 0x128..0x180.
//
// Ruled out: a plain `(f32)(f64)(s32)` cast (ngccc synthesises its own private
// 2^52 pool, so the `lis` can never match retail's lbl_80296A50/58 — the
// word-pair union in I2F_S/I2F_U is required); making the staging union
// file-scope `static` instead of a local (loses r1-relative addressing,
// 1.09% -> 3.72% when made local); f32/f64 return types for fn_8001F2D8;
// the `__ps_t`-operand ACC (0.1% worse and 68 bytes shorter).  Not attempted:
// statement/store-order or flag permutation sweeps, and any inline asm.
//
// Decode notes:
//  * retail converts every int<->float in the lerp/clamp block through the
//    2^52 magic: `hi=0x43300000` + `lo=(s32)v ^ 0x80000000`, `lfd`, `fsub`
//    of lbl_80296A50 (2^52+2^31, signed) or lbl_80296A58 (2^52, unsigned),
//    `frsp`.  Probed: that exact word-pair union form is what ngccc turns
//    into `lis 0x4330 / stw hi / stw lo / lfd / fsub / frsp`; a plain
//    `(f32)(f64)(s32)` cast synthesises its own private pool instead, whose
//    address cannot match retail's.
//  * the four colour lerps/clamps and the six sinf/cosf calls dominate the
//    tail; the accumulator updates are __ps_t pair ops (hence -mps-float).
#include "qb_constants.h"
#include "dolphin/SN_PS.h"

extern const f32 lbl_80296A44; /* 0.0f                   */
extern const f32 lbl_80296A48; /* 1.0f                   */
extern const f64 lbl_80296A50; /* 2^52 + 2^31 (int->f64) */
extern const f64 lbl_80296A58; /* 2^52 (u32->f64)        */
extern const f32 lbl_80296A60; /* 255.0f                 */
extern const f32 lbl_80296A64; /* pi/180                 */
extern const f32 lbl_80296A68; /* 360.0f                 */
extern __ps_t lbl_8037B694;

/* ---- callees: arity taken from the promoted src/*.c bodies ---- */
void fn_800231C4(void *, void *, s32, s32, s32, s32);
void fn_8001E6F0(s32, s32, s32, s32, s32);
void fn_8001FAA4(s32, s32, s32, s32, s32);
void *fn_8001D440(void *, f32, f32, f32);
void *fn_8001D424(void *);
void PSVEC_CrossProduct(void *, void *, void *);
void PSVEC_Normalize(void *);
void fn_8001F2D8(s32, s32, s32, s32, s32);
void PSVECScale(void *, void *, f32);
void fn_8001F0A0(s32, s32, s32);
void fn_8001F0F8(f32, f32, f32);
void fn_8001F1D4(s32);
void fn_8001F0F4(void);
extern f32 sinf(f32);
extern f32 cosf(f32);

typedef union {
    struct {
        f32 x, y, z, w;
    } f;
    __ps_t ps[2];
} Vec4;

typedef union {
    struct {
        f32 x, y;
    } f;
    __ps_t ps;
} Vec2;

/* QB command word block built at r1+0x08 */
typedef struct {
    s32 f0x00; /* QB_PARTICLE */
    u8 f0x04;
    u8 f0x05;
    u8 f0x06;
    u8 pad0x07[0x19];
    s32 f0x20; /* self->unk0x180 — also fn_800231C4's 2nd arg */
    s16 f0x24; /* 0x60 / 0x61  */
    u8 f0x26;  /* self->unk0x178 */
    u8 f0x27;  /* self->unk0x179 */
    u8 pad0x28[4];
    u8 f0x2c; /* 0x80 */
    u8 f0x2d; /* 0x80 */
    u8 f0x2e; /* 0x80 */
    u8 f0x2f; /* 0xff */
    s16 f0x30; /* 0 */
    u8 pad0x32[4];
    u8 f0x36; /* 0 */
    u8 pad0x37[9];
} Cmd888;

/* the 0x30-byte per-entry vertex block at self->unk0x100 */
typedef struct {
    u8 pad0x00[0x18];
    f32 f18, f1c, f20, f24, f28, f2c;
} Pin888;

typedef struct {
    f32 x, y, z;
} V3;

typedef struct {
    u8 pad0x00[0x28];
    f32 unk0x28, unk0x2c, unk0x30;
    u8 pad0x34[0x34];
    f32 unk0x68, unk0x6c, unk0x70;
    u8 pad0x74[0x20];
    s32 unk0x94;
    u8 pad0x98[0x5c];
    f32 unk0xf4;
    u8 pad0xf8[0x8];
    Pin888 *unk0x100;
    u8 pad0x104[0xc];
    f32 unk0x110;
    s32 *unk0x114;
    s32 *unk0x118;
    s32 *unk0x11c;
    u8 pad0x120[0x4];
    V3 *unk0x124;
    u8 pad0x128[0xc];
    s32 unk0x134;
    u8 pad0x138[0x38];
    s32 unk0x170;
    u8 pad0x174[0x4];
    u8 unk0x178, unk0x179;
    u8 pad0x17a[2];
    f32 unk0x17c;
    s32 unk0x180;
} S_A888;

/* (f32)(f64)(s32)v, routed through the game's own 2^52+2^31 pool constant */
#define I2F_S(v) (g_dw.w.hi = 0x43300000, g_dw.w.lo = (v) ^ 0x80000000, (f32)(g_dw.d - lbl_80296A50))
/* (f32)(f64)(u32)v */
#define I2F_U(v) (g_dw.w.hi = 0x43300000, g_dw.w.lo = (v), (f32)(g_dw.d - lbl_80296A58))

#define ACC(acc, v, a, b)                                                       \
    do {                                                                        \
        Vec4 t_;                                                                \
        f32 sa_ = (a)->f.x;                                                     \
        f32 sb_ = (b)->f.x;                                                     \
        t_.ps[0] = __builtin_ps_muls0(__builtin_ps_muls0((v)->ps[0], sa_), sb_); \
        t_.ps[1] = __builtin_ps_muls0(__builtin_ps_muls0((v)->ps[1], sa_), sb_); \
        (acc)->ps[0] = __builtin_ps_add((acc)->ps[0], t_.ps[0]);                \
        (acc)->ps[1] = __builtin_ps_add((acc)->ps[1], t_.ps[1]);                \
    } while (0)

void fn_8008A888(S_A888 *self) {
    /* the int->f64 / f64->int staging word pair retail keeps at r1+0x1C8 */
    union {
        struct {
            s32 hi, lo;
        } w;
        f64 d;
    } g_dw;
    Cmd888 cmd;
    Vec4 va;
    Vec4 vb;
    Vec4 vc;
    Vec4 pos;
    Vec4 d1;
    Vec4 d2;
    Vec4 accA;
    Vec4 accB;
    Vec4 accC;
    Vec4 accD;
    s32 col[3];
    Vec2 s[14];
    f32 one;
    f32 zero;
    f32 full;
    f32 deg;
    f32 k2, k3, k4;
    f32 t;
    f32 g;
    s32 i;
    s32 n;
    Pin888 *pin;
    V3 *off;

    one = lbl_80296A48;
    zero = lbl_80296A44;
    full = lbl_80296A68;
    deg = lbl_80296A64;

    cmd.f0x00 = QB_PARTICLE;
    cmd.f0x04 = 1;
    cmd.f0x05 = 1;
    cmd.f0x06 = 2;
    cmd.f0x20 = self->unk0x180;
    cmd.f0x24 = (cmd.f0x20 != 0) ? 0x61 : 0x60;
    cmd.f0x26 = self->unk0x178;
    cmd.f0x27 = self->unk0x179;
    cmd.f0x2c = 0x80;
    cmd.f0x2d = 0x80;
    cmd.f0x2e = 0x80;
    cmd.f0x2f = 0xff;
    cmd.f0x30 = 0;
    cmd.f0x36 = 0;
    fn_800231C4(&cmd, &cmd.f0x20, 1, 1, 0, 0);
    fn_8001E6F0(0, 1, 4, 0, 0x7d);
    fn_8001FAA4(0, 0x3c, 0x3c, 0x3c, 0x3c);

    fn_8001D440(&va, zero, one, zero);
    fn_8001D424(&vb);
    fn_8001D424(&vc);
    PSVEC_CrossProduct(&vb, &lbl_8037B694, &va);
    PSVEC_CrossProduct(&vc, &vb, &lbl_8037B694);
    PSVEC_Normalize(&vb);
    PSVEC_Normalize(&vc);
    fn_8001F2D8(2, 9, 1, 0xb, 1);

    n = self->unk0x94;
    pin = self->unk0x100;
    off = self->unk0x124;
    for (i = 0; i < n; i++, pin++, off++) {
        s32 *p1;
        s32 *p2;
        s32 c1;
        s32 c2;
        s32 j;

        if (self->unk0x134 != 0) {
            pos.f.x = off->x;
            pos.f.y = off->y;
            pos.f.z = off->z;
        } else {
            pos.f.x = off->x + self->unk0x28;
            pos.f.y = off->y + self->unk0x2c;
            pos.f.z = off->z + self->unk0x30;
        }
        pos.f.w = one;

        t = pin->f28 / pin->f2c;
        PSVECScale(&vb, &d1, (pin->f20 - pin->f18) * t + pin->f18);
        PSVECScale(&vc, &d2, (pin->f24 - pin->f1c) * t + pin->f1c);

        g = self->unk0x110;
        d1.f.w = zero;
        d2.f.w = zero;
        if (g >= zero) {
            if (t < g) {
                t = t / g;
                p1 = self->unk0x114;
                p2 = self->unk0x118;
            } else {
                p1 = self->unk0x118;
                p2 = self->unk0x11c;
                t = (t - g) / (one - g);
            }
        } else {
            p1 = self->unk0x114;
            p2 = self->unk0x11c;
        }

        k2 = self->unk0xf4 * self->unk0x68;
        k3 = self->unk0xf4 * self->unk0x6c;
        k4 = self->unk0xf4 * self->unk0x70;
        for (j = 0; j < 3; j++) {
            u8 *d = (u8 *)&col[j];
            f32 r, gr, b;

            c1 = *p1++;
            c2 = *p2++;
            d[0] = (u8)((s32)(((u8 *)&c1)[0]) +
                         (s32)(I2F_S((s32)((u8 *)&c1)[0] - (s32)((u8 *)&c2)[0]) * t));
            d[1] = (u8)((s32)(((u8 *)&c1)[1]) +
                         (s32)(I2F_S((s32)((u8 *)&c1)[1] - (s32)((u8 *)&c2)[1]) * t));
            d[2] = (u8)((s32)(((u8 *)&c1)[2]) +
                         (s32)(I2F_S((s32)((u8 *)&c1)[2] - (s32)((u8 *)&c2)[2]) * t));
            d[3] = (u8)((s32)(((u8 *)&c1)[3]) +
                         (s32)(I2F_S((s32)((u8 *)&c1)[3] - (s32)((u8 *)&c2)[3]) * t));
            r = I2F_U(d[0]) * k2;
            gr = I2F_U(d[1]) * k3;
            b = I2F_U(d[2]) * k4;
            r = (r < zero) ? zero : ((r > lbl_80296A60) ? lbl_80296A60 : r);
            gr = (gr < zero) ? zero : ((gr > lbl_80296A60) ? lbl_80296A60 : gr);
            b = (b < zero) ? zero : ((b > lbl_80296A60) ? lbl_80296A60 : b);
            d[0] = (u8)(s32)r;
            d[1] = (u8)(s32)gr;
            d[2] = (u8)(s32)b;
        }

        accB = pos;
        s[0].f.x = sinf(zero);
        s[1].f.x = self->unk0x17c;
        s[2].f.x = cosf(zero);
        s[3].f.x = self->unk0x17c;
        ACC(&accB, &d1, &s[0], &s[1]);
        ACC(&accB, &d2, &s[2], &s[3]);

        if (self->unk0x170 > 0) {
            s32 cnt = self->unk0x170;
            s32 m;

            for (m = 0; m < cnt; m++) {
#define ANG(k)                                                                   \
    (full / (I2F_S(cnt) + I2F_S(cnt)) * I2F_S(k) * deg)
                s[4].f.x = sinf(ANG(2 * m + 1));
                s[5].f.x = self->unk0x17c;
                ACC(&accA, &d1, &s[4], &s[5]);
                s[6].f.x = cosf(ANG(2 * m + 1));
                s[7].f.x = self->unk0x17c;
                accD = pos;
                ACC(&accA, &d2, &s[6], &s[7]);
                s[8].f.x = sinf(ANG(2 * m + 2));
                s[9].f.x = self->unk0x17c;
                ACC(&accD, &d1, &s[8], &s[9]);
                s[10].f.x = cosf(ANG(2 * m + 2));
                s[11].f.x = self->unk0x17c;
                accC = pos;
                ACC(&accD, &d2, &s[10], &s[11]);
                s[12].f.x = sinf(ANG(2 * m + 1));
                s[13].f.x = cosf(ANG(2 * m + 1));
                ACC(&accC, &d2, &s[12], &s[13]);
                accB = accD;
#undef ANG
            }
        }
    }

    fn_8001F0A0(0xa0, 0, 6);
    fn_8001F0F8(accA.f.x, accA.f.y, accA.f.z);
    fn_8001F1D4(col[1]);
    fn_8001F0F8(accB.f.x, accB.f.y, accB.f.z);
    fn_8001F1D4(col[2]);
    fn_8001F0F8(accC.f.x, accC.f.y, accC.f.z);
    fn_8001F1D4(col[2]);
    fn_8001F0F8(accD.f.x, accD.f.y, accD.f.z);
    fn_8001F1D4(col[2]);
    fn_8001F0F8(pos.f.x, pos.f.y, pos.f.z);
    fn_8001F1D4(col[0]);
    fn_8001F0F8(accB.f.x, accB.f.y, accB.f.z);
    fn_8001F1D4(col[2]);
    fn_8001F0F4();
}