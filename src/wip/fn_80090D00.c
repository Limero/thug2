// WIP DRAFT (non-matching) — hand-reconstructed from the want disassembly
// (the m2c husk emitted ~90 `0;` no-ops for the paired-single body and had the
// wrong frame / wrong declared types throughout).
// family=m2c range=0x80090D00-0x80091360 size=1632B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// extra_cflags: -mps-float
//
// ---------------------------------------------------------------------------
// PARKED 2026-10-05 (w2): DIFF, 15.24% reloc-masked (41/269 words), object
// 1076B vs want 1632B.  The m2c husk this replaces measured DIFF 5.91%
// (11/186, 748B) — its "score" was pure luck in an unshifted prologue, since
// 74 of its 90 `0;` statements never compiled to anything.
//   tools/score_wip.py 0x80090D00 src/wip/fn_80090D00.c            -> 15.24%
//   tools/want_got.py 0x80090D00                                    -> see note
//   tools/test_wip_drafts.py --addr 0x80090D00                      -> DIFF
//
// WHAT IS NOW BYTE-EXACT (all 41 masked words)
//   * the WHOLE prologue + scalar head, 0x80090D00..0x80090D9C (40 words):
//     frame 0x170, the five `stfd f27..f31` + `stmw r30` + `stw r0` in the
//     want's order, `li r30,0`, the v34 *= lbl_80296F14 multiply, Mem_Alloc,
//     the `mulli r0,r0,0x14` / `add` / `addi -0x14` pointer arithmetic, the
//     fn_8005CF80 lookup with its `or./beq/lwz 0xc/stw 0x258` guard, and the
//     `bl fn_80081794`.  Getting here needed: (a) a function-local struct with
//     CORRECT field types (0x18..0x3C are f32; 0x25C/0x25D are u8; 0x1D8..0x214
//     are f32; 0x260/0x290 are 6x8-byte slots) — the shared `CScript` has
//     several of these as s32, which alone cost ~7 words; (b) 6 `PSVal`-union
//     scalars so the local pool is exactly 0x08..0x137 and the frame lands on
//     0x170 (union/array locals are address-taken, so cc1 keeps the 8 write-only
//     slots the want keeps — see fn_80090958's park note (1)); (c) C-level
//     `register ... __asm__("fr27".."fr31")` / `("r30")` pins so cc1 allocates
//     the same callee-saved set (the retail holds those five FPRs across the two
//     branches and uses r30 for the two zero stores); (d) moving
//     `arg0->v1C0 = 0` to AFTER the Mem_Alloc block — the want's store emission
//     order for 0x1C0/0x1C4/0x1C8/0x1CC/0x1D0/0x1D4 is
//     1C8,1C4,1C0,1D4,1CC,1D0.
//   * frame/offset facts decoded and confirmed: locals 0x08..0x137 (6 pairs
//     pool + 16 pairs rec + 17 PSVal scale slots), GPR saves 0x140/0x144,
//     FPR saves 0x148..0x16F, LR 0x174.
//
// THE RECONSTRUCTED SEMANTICS (all confirmed against the want)
//   arg0 (Attractor): 0x18/0x1C/0x20/0x24/0x28/0x2C are f32 locals fed into
//   the pool's .hi lanes; 0x38/0x3C give x and its partner, t = x*0x3C*K18;
//   0xA8..0x107 = six 8-byte "src" slots `a`, 0xD8..0x107 = six 8-byte slots
//   `b` that seed the local pool; 0x168 = flag; 0x260..0x2BF = `m`, the six
//   8-byte "m" slots; 0x290..0x2BF = `out`.
//   pool q[0..5] = {b.p0, (b.p1.x, arg0->0x24), b.p2, (b.p3.x, arg0->0x28),
//   b.p4, (b.p5.x, arg0->0x2C)} — the want does six 8-byte psq copies and then
//   three 4-byte `.hi` overwrites, exactly a `union { __ps_t p[6]; struct{f32
//   lo,hi;} w[6]; }`.
//   if (arg0->0x168): c = K1C/((t*x)*(x-t)); twelve PSVal scale slots written
//   (kt,kx,kxx,ktt,kc,kc2 then the same six again at 0xF0..0x127 — the second
//   set is WRITE-ONLY in the retail, kept only because the union is
//   address-taken); then 16 `rec[]` pairs built from ps_sub/ps_muls0.
//   else: 1/x into two slots (0xE8 write-only, 0x120), rec[0..5] = copies of
//   q.p[0]/b.p2/b.p4, rec[2].lo = rec[3].hi = rec[4].lo = rec[4].hi = K20.
//   then the pool is REFILLED from `a` + 0x18/0x1C/0x20 and rec[0..3] are
//   copied to out.p[2..5]; three 1.5 slots (0x128/0x130/0x138) are written;
//   out.p[0..5] = ps_sub(P[i], ps_muls0(m.p[k], 1.5)) with
//   P = {q.p0,q.p0,rec[0],rec[1],rec[6],rec[3]} and k = {0,1,3,2,4,5};
//   out.p[1].hi/.p[3].hi/.p[5].hi = {q.p1.hi, rec[1].hi, rec[3].hi} -
//   {m.p0.hi, m.p1.hi, m.p2.hi} * 1.5;  then `bl fn_80090958` and the 16
//   constant stores at 0x1D8..0x20C.
//
// Gekko paired-single A-FORM FIELD LAYOUT (re-derived from probe compiles this
// run; capstone mislabels these as VMX, so decode by hand):
//   bits 31..26 opcode(4) | 25..21 frD | 20 .. 19..16 frA | 15..11 frC |
//   10..6 frB | 5 Rc-ish | 4..0 XO.   GCC emits frC (not frB) as the 2nd
//   source of ps_sub/ps_add/ps_div and frB as the 2nd source of
//   ps_mul/ps_muls0/ps_muls1.  XO: 0=ps_merge*, 4=ps_div, 8=ps_sub, 10=ps_add,
//   14=ps_sel, 16=ps_res(b5=1,B=0)/ps_neg(b5=0,B=1)/ps_abs(b5=0,B=8),
//   18=ps_mul, 20=ps_sum0(b5=0)/ps_rsqrte(b5=1), 22=ps_sum1, 24=ps_muls0 /
//   ps_msub(b5=1), 26=ps_muls1 / ps_madd(b5=1), 28=ps_madds0/ps_nmsub,
//   30=ps_madds1/ps_nmadd.  The one op that had no SN_PS.h spelling is
//   xo=16, b5=0, B=2, A=src, D=dst  ==  a PS pair MOVE (`ps_mr`); confirmed
//   against the byte-exact src/fn_8006AC08.c (0x8006ac9c/0x8006acac are its
//   `s.ps = d` copies).  GCC 2.95 does NOT emit an op4 for a plain `d = a`
//   __ps_t copy — it uses a scalar `fmr` — so these `ps_mr`s only appear when
//   the source is reading a PSVal union member whose .hi was never written.
//
// REMAINING BLOCKER: cc1 FPR colouring + list scheduling inside the paired-
// single body.  The very first divergence is at 0x80090DA0: the want's pool
// prologue loads b.p[0] first (load order 0,1,3,5,2,4, with two pool base
// registers r10/r11 from `addi r11,r1,8` + `mr r10,r11`), this body emits the
// same six psq_l/psq_st pairs but in load order 1,3,5,0,2,4 from ONE base and
// 29 words instead of 31.  Rewriting the source's pool order to 0,1,3,5,2,4
// does NOT change the emitted order (measured) — GCC re-normalises it.  That
// 2-word shift then moves both 31-word if/else arms and the 100-word tail, so
// everything past 0x80090D9C is misaligned even where the semantics agree.
// This is the same class of wall as fn_80090958 (DIFF 22.4% after a full run).
//
// RULED OUT THIS RUN (all measured)
//   * keeping the old `// FLAG: -fno-rerun-cse-after-loop` -> 12.18% (it was
//     load-bearing for the husk's shape, harmful here); dropped.
//   * `-fno-crossjumping` -> ngccc cc1 rejects the option.
//   * source pool order 0,1,3,5,2,4 / 0..5 / 1,3,5,0,2,4 -> all 15.24%, the
//     emitted order is scheduler-chosen, not source-chosen.
//   * `arg0->v1C0 = 0` before the alloc (8.15%), after the pointer stores
//     (9.26%, kept), and v1C4/v1C8 swapped -> the want's store emission order
//     needs v1C0 last of the three int stores.
//   * fusing the `sc0..sc4` f27..f31 scalars away -> loses the five `stfd`
//     saves and the whole 10-word prologue (measured 0.39% at 1028B).
//   * the shared `CScript` from structs.h -> v34 read as s32 (lwz not
//     lfs), v25C/0x25D as s32 (stw not stb), 0x1D8..0x214 as s32 (stw not
//     stfs); every one is a word the want gets right.
// ---------------------------------------------------------------------------
// extra_cflags: -mps-float
#include "types.h"
#include "mem.h"
#include "structs.h"
#include "dolphin/SN_PS.h"

extern f32 lbl_80296F14;
extern f32 lbl_80296F18;
extern f32 lbl_80296F1C;
extern f32 lbl_80296F20;
extern f32 lbl_80296F24;
extern s32 lbl_80366478;
s32 fn_80081794(s32);
s32 fn_8005CF80(Unk_9994C3F5 *, s32);

typedef union {
    __ps_t p;
    struct {
        f32 lo;
        f32 hi;
    } w;
} PSVal;

typedef union {
    __ps_t p[6];
    struct {
        f32 lo;
        f32 hi;
    } w[6];
} SixW;

typedef union {
    PSVal s[17];
    __ps_t p[17];
} Scales;

typedef struct {
    char pad0x00[0x18];
    f32 v18;
    f32 v1c;
    f32 v20;
    f32 v24;
    f32 v28;
    f32 v2c;
    char pad0x30[4];
    f32 v34;
    f32 v38;
    f32 v3c;
    char pad0x40[0x68];
    SixW a;
    SixW b;
    char pad0x108[0x40];
    s32 v148;
    char pad0x14C[3];
    u8 v14F;
    char pad0x150[4];
    s32 v154;
    char pad0x158[0x10];
    s32 v168;
    char pad0x16C[0x54];
    s32 v1C0;
    s32 v1C4;
    s32 v1C8;
    s32 v1CC;
    s32 v1D0;
    s32 v1D4;
    f32 v1D8;
    f32 v1DC;
    f32 v1E0;
    f32 v1E4;
    f32 v1E8;
    f32 v1EC;
    f32 v1F0;
    f32 v1F4;
    f32 v1F8;
    f32 v1FC;
    f32 v200;
    f32 v204;
    f32 v208;
    f32 v20C;
    f32 v210;
    f32 v214;
    char pad0x218[0x40];
    s32 v258;
    u8 v25C;
    u8 v25D;
    char pad0x25E[2];
    SixW m;
    SixW out;
} Attractor;

void fn_80090D00(Attractor *arg0) {
    SixW q;
    PSVal rec[16];
    Scales ks;
    __ps_t *r;
    register f32 sc0 __asm__("fr27");
    register f32 sc1 __asm__("fr28");
    register f32 sc2 __asm__("fr29");
    register f32 sc3 __asm__("fr30");
    register f32 sc4 __asm__("fr31");
    register s32 zero __asm__("r30");
    f32 x, t, c;
    void *p;
    s32 v;
    f32 f11;

    zero = 0;
    arg0->v1C4 = 5;
    arg0->v1C8 = zero;
    arg0->v34 = arg0->v34 * lbl_80296F14;
    p = Mem_Alloc(0x64);
    arg0->v1D4 = (s32)p;
    arg0->v1CC = (s32)p;
    arg0->v1D0 = (s32)p + (arg0->v1C4 * 0x14) - 0x14;
    arg0->v1C0 = zero;
    v = fn_8005CF80(lbl_80366478, arg0->v154);
    if (v != 0) {
        arg0->v258 = *(s32 *)(v + 0xC);
    }
    arg0->v25C = (u8)fn_80081794(arg0->v148);
    arg0->v25D = arg0->v14F;

    x = arg0->v38;
    t = x * arg0->v3c * lbl_80296F18;
    q.p[0] = arg0->b.p[0];
    q.p[1] = arg0->b.p[1];
    q.p[3] = arg0->b.p[3];
    q.p[5] = arg0->b.p[5];
    q.p[2] = arg0->b.p[2];
    q.p[4] = arg0->b.p[4];
    q.w[1].hi = arg0->v24;
    q.w[3].hi = arg0->v28;
    q.w[5].hi = arg0->v2c;
    r = q.p;

    if (arg0->v168 != 0) {
        c = lbl_80296F1C / ((t * x) * (x - t));
        ks.s[3].w.lo = t;
        ks.s[4].w.lo = x;
        ks.s[0].w.lo = x * x;
        ks.s[1].w.lo = t * t;
        ks.s[5].w.lo = c;
        ks.s[2].w.lo = c;
        ks.s[9].w.lo = t;
        ks.s[10].w.lo = x;
        ks.s[6].w.lo = x * x;
        ks.s[7].w.lo = t * t;
        ks.s[11].w.lo = c;
        ks.s[8].w.lo = c;

        rec[10].p = __builtin_ps_sub(arg0->b.p[4], r[0]);
        rec[14].p = __builtin_ps_sub(arg0->b.p[2], r[0]);
        rec[11].p = __builtin_ps_sub(arg0->b.p[5], ks.p[5]);
        rec[9].p = __builtin_ps_sub(arg0->b.p[3], ks.p[6]);
        rec[15].p = __builtin_ps_sub(arg0->b.p[3], ks.p[10]);
        rec[13].p = __builtin_ps_sub(arg0->b.p[1], ks.p[10]);
        rec[12].p = __builtin_ps_muls0(arg0->b.p[2], ks.p[10]);
        rec[8].p = __builtin_ps_muls0(arg0->b.p[4], ks.p[9]);
        rec[0].p = __builtin_ps_muls0(arg0->b.p[2], ks.p[0]);
        rec[1].p = __builtin_ps_muls0(arg0->b.p[1], ks.p[0]);
        rec[2].p = ks.p[10];
        rec[3].p = __builtin_ps_muls0(rec[0].p, ks.p[11]);
        rec[4].p = ks.p[10];
        rec[5].p = ks.p[10];
        rec[6].p = ks.p[10];
        rec[7].p = __builtin_ps_muls0(rec[0].p, ks.p[11]);
    } else {
        ks.s[12].w.lo = lbl_80296F1C / x;
        rec[6].p = r[0];
        rec[7].p = r[0];
        rec[0].p = arg0->b.p[2];
        rec[4].p = arg0->b.p[2];
        rec[1].p = arg0->b.p[4];
        rec[5].p = arg0->b.p[4];
        rec[2].w.lo = lbl_80296F20;
        rec[3].w.hi = lbl_80296F20;
        rec[4].w.lo = lbl_80296F20;
        rec[4].w.hi = lbl_80296F20;
        ks.s[13].w.lo = lbl_80296F1C / x;
    }

    arg0->out.p[1] = r[0];
    arg0->out.p[0] = r[0];
    r[0] = arg0->a.p[1];
    r[3] = arg0->a.p[3];
    q.w[3].hi = arg0->v1c;
    r[4] = arg0->a.p[5];
    q.w[5].hi = arg0->v20;
    q.w[1].hi = arg0->v18;
    arg0->out.p[2] = rec[0].p;
    arg0->out.p[3] = rec[1].p;
    arg0->out.p[4] = rec[2].p;
    arg0->out.p[5] = rec[3].p;
    r[0] = arg0->a.p[0];
    r[2] = arg0->a.p[2];
    r[4] = arg0->a.p[4];

    sc3 = rec[1].w.hi;
    sc4 = rec[3].w.hi;
    ks.s[16].w.lo = lbl_80296F24;
    ks.s[14].w.lo = lbl_80296F24;
    ks.s[15].w.lo = lbl_80296F24;
    arg0->out.p[0] = __builtin_ps_sub(r[0], __builtin_ps_muls0(arg0->m.p[0], ks.p[14]));
    arg0->out.p[1] = __builtin_ps_sub(r[0], __builtin_ps_muls0(arg0->m.p[1], ks.p[14]));
    arg0->out.p[2] = __builtin_ps_sub(rec[0].p, __builtin_ps_muls0(arg0->m.p[3], ks.p[15]));
    arg0->out.p[3] = __builtin_ps_sub(rec[1].p, __builtin_ps_muls0(arg0->m.p[2], ks.p[15]));
    arg0->out.p[4] = __builtin_ps_sub(rec[6].p, __builtin_ps_muls0(arg0->m.p[4], ks.p[16]));
    arg0->out.p[5] = __builtin_ps_sub(rec[3].p, __builtin_ps_muls0(arg0->m.p[5], ks.p[16]));
    sc0 = arg0->m.w[0].hi * lbl_80296F24;
    f11 = q.w[1].hi - sc0;
    arg0->out.w[0].hi = f11;
    sc1 = arg0->m.w[1].hi * lbl_80296F24;
    f11 = sc3 - sc1;
    arg0->out.w[1].hi = f11;
    sc2 = arg0->m.w[2].hi * lbl_80296F24;
    f11 = sc4 - sc2;
    arg0->out.w[2].hi = f11;
    fn_80090958(arg0);
    arg0->v1D8 = lbl_80296F1C;
    arg0->v214 = lbl_80296F1C;
    arg0->v210 = lbl_80296F20;
    arg0->v1DC = lbl_80296F20;
    arg0->v1E0 = lbl_80296F20;
    arg0->v1E4 = lbl_80296F20;
    arg0->v1E8 = lbl_80296F20;
    arg0->v1EC = lbl_80296F1C;
    arg0->v1F0 = lbl_80296F20;
    arg0->v1F4 = lbl_80296F20;
    arg0->v1F8 = lbl_80296F20;
    arg0->v1FC = lbl_80296F20;
    arg0->v200 = lbl_80296F1C;
    arg0->v204 = lbl_80296F20;
    arg0->v208 = lbl_80296F20;
    arg0->v20C = lbl_80296F20;
}
// RE-TRIAGE 2026-10-12: PS-wall stands (1632B hand recon, 15%); no body change.
