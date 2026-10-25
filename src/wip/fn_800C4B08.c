// WIP DRAFT (non-matching) — hand-rebuilt from tools/ps_disasm.py  (M8.xx session)
// REFRESHED 2026-10-07 (FPR-pin RETARGET sweep): 7.5000% -> 18.0723%
//   the `lim` pin was retargeted fr9 -> fr28 (nothing else touched).  fr-pin REMOVAL
//   had been swept; retargeting had not.  Checked NOT size-exact before or after.  §6hk.
// REFRESHED 2026-10-07 (scaffold/flag/volatile re-sweep): 6.8750% -> 7.5000% `volatile` keyword(s) removed from the body
// family=ps range=0x800C4B08-0x800C4D88 size=640B
// FLAG: -mps-float
//
// VERDICT 2026-09-27: DIFF. want 640B/160 insns, got 632B/158 insns,
// masked 11/160 = 6.9% (tools/diff_near.py / want_got.py -mps-float).
// The old header's "PARKED (10.8%): WANT body dominated by paired-single ops
// (psq_l/ps_merge10/ps_mul/ps_madd/ps_sum0/ps_mr) - known unmatchable PS idiom
// gap" was WRONG and has been deleted. Every opcode-4 word in WANT decodes to a
// standard, emittable Gekko PS A-form op — mul=xo5 25, sub=20, add=21, madd=29,
// muls0=12, sum0=10, merge00/01/10 = xo5 16 with sub-op 16/17/18 (XO10 528/560/592),
// ps_mr = xo5 8 / XO10 72, psq_l/st = opcode 4/59. NONE is a doc-06 XO5=6/7 or
// doc-29 VMX wall. The old 10.8% came from the m2c body being a statics-DCE husk
// (stack slots modelled as file-scope `static s32 spN`), not from an emission
// gap; this file is a full disasm-faithful rebuild and every PS op in WANT is
// now reproduced with __builtin_ps_* only (no inline-asm instruction templates).
//
// WHAT NOW MATCHES EXACTLY: stwu -0x80 / stmw r24,0x60 / stw r0,0x84 prologue and
// the whole epilogue; the 0x08..0x5F frame layout (V[0..10] = 11 x 8-byte union
// slots, V[6]/V[7] @0x38/0x40 used only by the fn_8003EF4C out-param block);
// the complete PS opcode SEQUENCE of both math blocks (mul/merge00/madd/sum0 and
// merge10/mul/merge00/sub/merge10/mr); both callee signatures read off the
// disasm (fn_800C494C reads only r3/r4/r5 -> 3-arg f32; fn_8003EF4C is a 4-byte
// blr stub -> arity from the call site); the -0x9C->0xFF64FFFF constant pair.
//
// RESIDUAL (all allocator/scheduling, not semantics):
//  (1) loop-invariant motion: ngccc 2.95 hoists `mulli r10,r24,0x28` and
//      `r11 = arg2+r6+0xD60` out of the outer loop into the preheader, while WANT
//      re-computes them at 0x800C4B60/B7C every iteration. NOT reachable from any
//      source shape tried (do-while, goto state machine, reordering).
//  (2) the outer latch: WANT tests the counter IN PLACE
//      (`cmpwi r3,0; addi r3,-1; bne`); every C spelling of `i-- != 0` /
//      `--i != 0` / `--i != -1` makes gcc build a pre-decremented induction copy
//      and emit `mr rX,rY; cmpwi rX,-1; bne` (one insn longer). The inner latch
//      DOES match (`--j != -1` gives exactly `cmpwi; addi; bne`).
//  (3) FPR/GPR colouring inside the two PS math blocks (e.g. WANT's
//      `fsubs f0,f0,f13` three times vs got f0/f8, f0/f13, f0/f11) and the
//      psq_st/lfs interleave around the epsilon chain.
//  (4) `ok` lands in r6 (want r12); and the 1.0f / 72.0f `lfs` + `stfs` pair in
//      block B is scheduled differently (want: stfs 0x54 after the second
//      ps_sub; got: stfs 0x58 immediately after the lfs).
//  8-byte size deficit: GOT is 2 instructions short (632 vs 640) — the two
//  missing words are one extra `mr` in the outer latch plus one net difference
//  around the two PS blocks.
//
// REGISTER PINS USED (disclosed, per the "last resort" rule): six
// `register s32 pNN __asm__("rNN")` GPR pins (r24=arg5, r25=arg2+arg4*0x68+0xD38,
// r28=arg3, r29=arg4, r30=arg0, r31=arg1) and two FPR pins
// (`register f32 eps __asm__("fr10")`, `register f64 lim __asm__("f64")`).
// WITHOUT them gcc saves only r27-r31 (frame 0x78, stmw r27) and puts eps/lim in
// f9/f8; the GPR pins alone took the masked score 3.80% -> 6.92% by fixing
// stwu -0x80 / stmw r24,0x60, the FPR pins 6.92% -> 8.18% by fixing
// `fcmpu cr0,f0,f10`. A named `char *pk` for lbl_80299118 (to remove the extra
// `addi r9,r27,0`) then traded 8.18% -> 6.96% for one fewer emitted instruction;
// both are kept because the emitted instruction count is the honest measure and
// the masked % is positional (a shorter body always looks worse at the tail).
// Dead ends recorded so they are not retried: inlining the V[] reads into the
// epsilon `&&` chain, nesting the three epsilon tests, and the goto state
// machine for the outer loop (all scored 5.06%).
//
// INERT: not registered in splits.txt/configure.py. Object has NO .rodata, so
// the §4n FP-pool promote blocker does not apply. .rela.text carries only
// REL14/REL24/ADDR16_HA+LO against lbl_80299114/118/120/124, fn_800C494C,
// fn_8003EF4C — i.e. the shape would link, it simply is not byte-exact.
#include "types.h"
#include "structs.h"

extern f32 lbl_80299114;
extern f32 lbl_80299120;
extern f32 lbl_80299124;
extern char lbl_80299118[];

f32 fn_800C494C(void *, void *, void *);
s32 fn_8003EF4C(s32, s32, s32, s32, s32);

typedef union { __ps_t p; f32 w[2]; } S;

/* File-local layouts. The shared Unk_C7387A53 has pad0x10[0x10] + s32 unk0x20,
   which would make the vector loads fctiwz+stw instead of psq_l/psq_st. */
typedef struct { char pad0x0[0x10]; __ps_t v10; __ps_t v18; f32 v20; } A_t;
typedef struct { char pad0x0[0x1350]; s32 unk0x1350; } O_t;
typedef struct { char pad0x0[0x1A38]; s32 unk0x1A38; } B_t;

s32 fn_800C4B08(O_t *arg0, A_t *arg1, B_t *arg2, s32 arg3, s32 arg4, s32 arg5) {
    S V[11];
    register s32 p24 __asm__("r24");
    register s32 p25 __asm__("r25");
    register s32 p28 __asm__("r28");
    register s32 p29 __asm__("r29");
    register s32 p30 __asm__("r30");
    register s32 p31 __asm__("r31");
    s32 i;
    s32 r6;
    s32 r7;
    s32 r11;
    s32 r10;
    s32 r8;
    char *pk;
    s32 j;
    s32 flag;
    s32 ok;
    register f32 eps __asm__("fr10");
    register f64 lim __asm__("fr28");
    __ps_t a;
    __ps_t b;
    __ps_t c;
    __ps_t d;
    __ps_t e;
    __ps_t f;
    __ps_t g;
    __ps_t h;
    __ps_t m;
    __ps_t t;
    __ps_t u;
    __ps_t v;
    __ps_t w;
    __ps_t y;
    f32 t0;
    f32 t1;
    f32 t2;
    f32 t3;
    f32 z;
    f32 zz;

    p30 = (s32)arg0;
    p31 = (s32)arg1;
    i = arg2->unk0x1A38;
    p28 = arg3;
    p29 = arg4;
    p24 = arg5;
    if (i == 0) {
        return 0;
    }
    i -= 1;
    r6 = i * 0x68;
    r7 = (s32)arg2 + r6 + 0xD38;
    p25 = (s32)arg2 + p29 * 0x68 + 0xD38;
    do {
        if (i != p29) {
            r10 = p25 + p24 * 0x28 + 0x10;
            r11 = (s32)arg2 + r6 + 0xD60;
            r8 = (s32)&V[0];
            pk = lbl_80299118;
            eps = lbl_80299114;
            lim = *(f64 *)lbl_80299118;
            j = 1;
            do {
                V[0].p = *(__ps_t *)arg1;
                ok = 0;
                flag = 0;
                *(__ps_t *)(r8 + 8) = *(__ps_t *)((char *)arg1 + 8);
                V[2].p = *(__ps_t *)r11;
                V[3].p = *(__ps_t *)(r11 + 8);
                t0 = V[0].w[0];
                t1 = V[2].w[0];
                t2 = V[0].w[1];
                t3 = V[2].w[1];
                z = V[0].w[2];
                zz = V[2].w[2];
                if ((__builtin_fabsf(t0 - t1) < eps) &&
                    (__builtin_fabsf(t2 - t3) < eps) &&
                    (__builtin_fabsf(z - zz) < eps)) {
                    flag = 1;
                }
                if (flag != 0) {
                    d = arg1->v18;
                    m = *(__ps_t *)(r7 + 0x58);
                    c = *(__ps_t *)pk;
                    d = __builtin_ps_mul(d, m);
                    b = arg1->v10;
                    e = *(__ps_t *)(r7 + 0x50);
                    d = __builtin_ps_merge00(d, c);
                    b = __builtin_ps_madd(b, e, d);
                    b = __builtin_ps_sum0(b, b, b);
                    V[8].p = b;
                    t0 = V[8].w[0];
                    t1 = t0;
                    if (t1 < lim) {
                        ok = 1;
                    }
                }
                if (ok != 0) {
                    f = *(__ps_t *)r10;
                    g = *(__ps_t *)(r10 + 8);
                    a = arg1->v10;
                    h = arg1->v18;
                    u = __builtin_ps_merge10(f, g);
                    u = __builtin_ps_mul(u, a);
                    v = __builtin_ps_merge10(a, h);
                    w = __builtin_ps_mul(f, v);
                    t = __builtin_ps_merge00(a, h);
                    g = __builtin_ps_merge00(g, f);
                    g = __builtin_ps_mul(g, t);
                    w = __builtin_ps_sub(w, u);
                    t = __builtin_ps_merge00(w, w);
                    V[9].p = t;
                    zz = lbl_80299120;
                    y = __builtin_ps_merge10(g, g);
                    g = __builtin_ps_sub(g, y);
                    V[10].w[0] = zz;
                    u = __builtin_ps_merge10(w, g);
                    t = V[9].p;
                    arg1->v10 = u;
                    e = t;
                    arg1->v18 = e;
                    V[4].p = u;
                    V[5].p = e;
                    arg1->v20 = fn_800C494C((void *)p30, (void *)p31, (s32)p28);
                    if (*(s32 *)(p30 + 0x1350) != 0) {
                        V[10].w[0] = lbl_80299124;
                        f = V[10].p;
                        h = arg1->v10;
                        g = arg1->v18;
                        y = f;
                        h = __builtin_ps_muls0(h, y);
                        e = *(__ps_t *)arg1;
                        f = *(__ps_t *)((char *)arg1 + 8);
                        g = __builtin_ps_muls0(g, y);
                        V[6].p = h;
                        V[7].p = g;
                        u = __builtin_ps_add(e, h);
                        w = __builtin_ps_add(f, g);
                        V[4].p = u;
                        V[5].p = w;
                        fn_8003EF4C((s32)p31, (s32)&V[4], 0xFF64FFFF,
                                    0xFF64FFFF, 1);
                    }
                    return 1;
                }
                r11 -= 0x28;
            } while (--j != -1);
        }
        r7 -= 0x68;
        r6 -= 0x68;
    } while (i-- != 0);
    return 0;
}
