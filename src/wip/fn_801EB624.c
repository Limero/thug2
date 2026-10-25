// WIP DRAFT (non-matching) — hand-rebuilt from disasm (group G)
// PARKED (G, 2nd pass): 17.3% - GPR-web coloring + scratch-fill slides.
// 2nd-pass retry applied the fn_801E1224 win (copy-back RHS as typed
// __ps_t pair reads `((__ps_t volatile *)&fr.out[0])[k]` + matrix-#2 true
// pair order [0,1,2,3,4,7,5,6]) -> only +0.2%: the dominant residue is the
// saved-reg map (my 7 webs vs want 5) displacing every line, same
// window-vs-map coupling documented in fn_801E1224's park block — there the
// map resisted rawm-local/r9-pin/anonymous-deref variants alike. Don't
// re-grind without a new lever for THAT coupling.
// Structure is fully rebuilt and correct: frame 0xF8 + stmw r27 + 6x stfd
// f26-f31 prologue, guard tree (ctl->0x74 / ctl->0x98 / return), sinf/cosf
// (SDK syms at 0x80271170/0x80271070), fn_8012570C(0x38505EF3,1)*lbl_802AD8C0
// (negated in path 2), TWO empty mtctr/bdnz$ spin windows (li r0,4) reproduced
// with volatile asm wedges, window-1 PS rotation block via __builtin_ps_mul /
// ps_madds0 / ps_msub / ps_merge01 on __ps_t pairs {cos,K},{sin,K} at
// r1+0x98/0xA0 (all opcode-4 words decode emittable; no XO5=6/7/8 walls),
// two full 16-dot-product matrix multiplies (want #1 uses DIRECT derefs,
// #2 caches N columns in saved FPRs — modeled with frN pins v00/v01/v10/v11/
// v20/v21 -> f26/f29/f27/f30/f31/f28), psq pair copy-backs (#2 emits pairs
// in order 0,1,2,3,4,6?,... want #2 order is [72,80,88,96,104,128,112,120]).
// Tried: volatile out[] to force store-all/reload-all (kept), mbase raw-vs-
// derived web split via second volatile read of arg0->0xC (best), single-var
// reassignment (mixed forms), tp pin to r9 (rotated everything, reverted),
// "+r" barrier at reassignment (-10%, reverted). Residue: my compile needs
// 7 saved-GPR webs vs want 5 (stmw r26 vs r27; arg0 lands r26/r31 vs r29)
// which shifts every displacement line, plus ±1 load-slot fill slides inside
// each product row. Same family as fn_801E1224 (sibling, same session).
// family=m2c range=0x801EB624-0x801EBDD8 size=1972B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// extra_cflags: -mps-float
// SEARCHED 2026-09-11 (tools/store_order_search.py): store/assignment block(s) re-ordered (reversed / ascending / descending); score now 37.7% ([4]rev->37.7%).
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern f32 lbl_802AD8C0;
extern f32 lbl_802AD8C4;
extern f32 sinf(f32);
extern f32 cosf(f32);
extern f32 fn_8012570C(s32 hash, s32 flag);
extern void *fn_80003EB0(Unk_DB0E2BAB * arg0, f32 farg1);

void fn_801EB624(Unk_7258DEBD *arg0) {
    struct fr_s {
        char mat[0x40];
        volatile f32 out[16];
        void *t1;
        void *dst;
        void *t2;
        void *dst2;
        __ps_t ck;
        __ps_t sn;
    } fr;
    Unk_C7387A53 *ctl;
    f32 var_f31;
    Unk_DB0E2BAB *mbase;
    Unk_548A6C04 *mbase0;
    Unk_DB0E2BAB *nbase;
    void **p1;
    void **p2;
    Unk_DB0E2BAB *tp;
    register f32 v00 __asm__("fr26");
    register f32 v01 __asm__("fr29");
    f32 v02;
    f32 v03;
    register f32 v10 __asm__("fr27");
    register f32 v11 __asm__("fr30");
    f32 v12;
    f32 v13;
    register f32 v20 __asm__("fr31");
    register f32 v21 __asm__("fr28");
    f32 v22;
    f32 v23;
    f32 v30;
    f32 v31;
    f32 v32;
    f32 v33;

    ctl = *((s32 * *)&arg0->unk0x15A0);
    if (ctl->unk0x74 != 0) {
        var_f31 = fn_8012570C(QB_RAIL_JUMP_ANGLE, 1) * lbl_802AD8C0;
    } else if (ctl->unk0x98 != 0) {
        var_f31 = -(fn_8012570C(QB_RAIL_JUMP_ANGLE, 1) * lbl_802AD8C0);
    } else {
        return;
    }

    mbase0 = *((char * *)&arg0->unk0xC);
    ((f32 volatile *)&fr.sn)[0] = sinf(var_f31);
    nbase = (char *)arg0 + 0x20;
    p1 = (void **)&fr.t1;
    ((f32 volatile *)&fr.ck)[0] = cosf(var_f31);
    ((f32 volatile *)&fr.ck)[1] = lbl_802AD8C4;
    __asm__ volatile("li 0,4\n\tmtctr 0" ::: "ctr", "r0");
    p2 = (void **)&fr.t2;
    ((f32 volatile *)&fr.sn)[1] = lbl_802AD8C4;

    {
        __ps_t ckv = *(__ps_t volatile *)&fr.ck;
        __ps_t a = mbase0->unk0xB8;
        __ps_t b = mbase0->unk0xC0;
        __ps_t m0 = __builtin_ps_mul(a, ckv);
        __ps_t snv = *(__ps_t volatile *)&fr.sn;
        __ps_t m1 = __builtin_ps_mul(a, snv);
        __ps_t s0 = __builtin_ps_madds0(snv, m0, b);
        __ps_t ck2 = *(__ps_t volatile *)&fr.ck;
        __ps_t g0 = __builtin_ps_merge01(s0, a);
        __ps_t s1 = __builtin_ps_msub(ck2, b, m1);
        __ps_t g1;
        mbase0->unk0xB8 = g0;
        g1 = __builtin_ps_merge01(s1, b);
        mbase0->unk0xC0 = g1;
    }

    mbase = *((char * volatile *)&arg0->unk0xC) + 0x78;
    __asm__ volatile("bdnz $" ::: "ctr");

    fr.t1 = fn_80003EB0(&fr.mat[0], var_f31);
    __asm__ volatile("li 0,4\n\tmtctr 0" ::: "ctr", "r0");
    p1[1] = mbase;
    tp = fr.t1;
    fr.out[0] = *((f32 *)&tp->unk0x0) * *((f32 *)&mbase->unk0x0) +
                *((f32 *)&tp->unk0x4) * *((f32 *)&mbase->unk0x10) +
                *((f32 *)&tp->unk0x8) * *((f32 *)&mbase->unk0x20) +
                *((f32 *)&tp->unk0xC) * *((f32 *)&mbase->unk0x30);
    fr.out[1] = *((f32 *)&tp->unk0x0) * *((f32 *)&mbase->unk0x4) +
                *((f32 *)&tp->unk0x4) * *((f32 *)&mbase->unk0x14) +
                *((f32 *)&tp->unk0x8) * *((f32 *)&mbase->unk0x24) +
                *((f32 *)&tp->unk0xC) * *((f32 *)&mbase->unk0x34);
    fr.out[2] = *((f32 *)&tp->unk0x0) * *((f32 *)&mbase->unk0x8) +
                *((f32 *)&tp->unk0x4) * *((f32 *)&mbase->unk0x18) +
                *((f32 *)&tp->unk0x8) * *((f32 *)&mbase->unk0x28) +
                *((f32 *)&tp->unk0xC) * *((f32 *)&mbase->unk0x38);
    fr.out[3] = *((f32 *)&tp->unk0x0) * *((f32 *)&mbase->unk0xC) +
                *((f32 *)&tp->unk0x4) * *((f32 *)&mbase->unk0x1C) +
                *((f32 *)&tp->unk0x8) * *((f32 *)&mbase->unk0x2C) +
                *((f32 *)&tp->unk0xC) * *((f32 *)&mbase->unk0x3C);
    fr.out[4] = *((f32 *)&tp->unk0x10) * *((f32 *)&mbase->unk0x0) +
                *((f32 *)&tp->unk0x14) * *((f32 *)&mbase->unk0x10) +
                *((f32 *)&tp->unk0x18) * *((f32 *)&mbase->unk0x20) +
                *((f32 *)&tp->unk0x1C) * *((f32 *)&mbase->unk0x30);
    fr.out[5] = *((f32 *)&tp->unk0x10) * *((f32 *)&mbase->unk0x4) +
                *((f32 *)&tp->unk0x14) * *((f32 *)&mbase->unk0x14) +
                *((f32 *)&tp->unk0x18) * *((f32 *)&mbase->unk0x24) +
                *((f32 *)&tp->unk0x1C) * *((f32 *)&mbase->unk0x34);
    fr.out[6] = *((f32 *)&tp->unk0x10) * *((f32 *)&mbase->unk0x8) +
                *((f32 *)&tp->unk0x14) * *((f32 *)&mbase->unk0x18) +
                *((f32 *)&tp->unk0x18) * *((f32 *)&mbase->unk0x28) +
                *((f32 *)&tp->unk0x1C) * *((f32 *)&mbase->unk0x38);
    fr.out[7] = *((f32 *)&tp->unk0x10) * *((f32 *)&mbase->unk0xC) +
                *((f32 *)&tp->unk0x14) * *((f32 *)&mbase->unk0x1C) +
                *((f32 *)&tp->unk0x18) * *((f32 *)&mbase->unk0x2C) +
                *((f32 *)&tp->unk0x1C) * *((f32 *)&mbase->unk0x3C);
    fr.out[8] = *((f32 *)&tp->unk0x20) * *((f32 *)&mbase->unk0x0) +
                *((f32 *)&tp->unk0x24) * *((f32 *)&mbase->unk0x10) +
                *((f32 *)&tp->unk0x28) * *((f32 *)&mbase->unk0x20) +
                *((f32 *)&tp->unk0x2C) * *((f32 *)&mbase->unk0x30);
    fr.out[9] = *((f32 *)&tp->unk0x20) * *((f32 *)&mbase->unk0x4) +
                *((f32 *)&tp->unk0x24) * *((f32 *)&mbase->unk0x14) +
                *((f32 *)&tp->unk0x28) * *((f32 *)&mbase->unk0x24) +
                *((f32 *)&tp->unk0x2C) * *((f32 *)&mbase->unk0x34);
    fr.out[10] = *((f32 *)&tp->unk0x20) * *((f32 *)&mbase->unk0x8) +
                 *((f32 *)&tp->unk0x24) * *((f32 *)&mbase->unk0x18) +
                 *((f32 *)&tp->unk0x28) * *((f32 *)&mbase->unk0x28) +
                 *((f32 *)&tp->unk0x2C) * *((f32 *)&mbase->unk0x38);
    fr.out[11] = *((f32 *)&tp->unk0x20) * *((f32 *)&mbase->unk0xC) +
                 *((f32 *)&tp->unk0x24) * *((f32 *)&mbase->unk0x1C) +
                 *((f32 *)&tp->unk0x28) * *((f32 *)&mbase->unk0x2C) +
                 *((f32 *)&tp->unk0x2C) * *((f32 *)&mbase->unk0x3C);
    fr.out[12] = *((f32 *)&tp->unk0x30) * *((f32 *)&mbase->unk0x0) +
                 *((f32 *)&tp->unk0x34) * *((f32 *)&mbase->unk0x10) +
                 *((f32 *)&tp->unk0x38) * *((f32 *)&mbase->unk0x20) +
                 *((f32 *)&tp->unk0x3C) * *((f32 *)&mbase->unk0x30);
    fr.out[13] = *((f32 *)&tp->unk0x30) * *((f32 *)&mbase->unk0x4) +
                 *((f32 *)&tp->unk0x34) * *((f32 *)&mbase->unk0x14) +
                 *((f32 *)&tp->unk0x38) * *((f32 *)&mbase->unk0x24) +
                 *((f32 *)&tp->unk0x3C) * *((f32 *)&mbase->unk0x34);
    fr.out[14] = *((f32 *)&tp->unk0x30) * *((f32 *)&mbase->unk0x8) +
                 *((f32 *)&tp->unk0x34) * *((f32 *)&mbase->unk0x18) +
                 *((f32 *)&tp->unk0x38) * *((f32 *)&mbase->unk0x28) +
                 *((f32 *)&tp->unk0x3C) * *((f32 *)&mbase->unk0x38);
    fr.out[15] = *((f32 *)&tp->unk0x30) * *((f32 *)&mbase->unk0xC) +
                 *((f32 *)&tp->unk0x34) * *((f32 *)&mbase->unk0x1C) +
                 *((f32 *)&tp->unk0x38) * *((f32 *)&mbase->unk0x2C) +
                 *((f32 *)&tp->unk0x3C) * *((f32 *)&mbase->unk0x3C);

    ((__ps_t volatile *)mbase)[0] = ((__ps_t volatile *)&fr.out[0])[0];
    ((__ps_t volatile *)mbase)[1] = ((__ps_t volatile *)&fr.out[0])[1];
    ((__ps_t volatile *)mbase)[2] = ((__ps_t volatile *)&fr.out[0])[2];
    ((__ps_t volatile *)mbase)[3] = ((__ps_t volatile *)&fr.out[0])[3];
    ((__ps_t volatile *)mbase)[4] = ((__ps_t volatile *)&fr.out[0])[4];
    ((__ps_t volatile *)mbase)[5] = ((__ps_t volatile *)&fr.out[0])[5];
    ((__ps_t volatile *)mbase)[6] = ((__ps_t volatile *)&fr.out[0])[6];
    ((__ps_t volatile *)mbase)[7] = ((__ps_t volatile *)&fr.out[0])[7];
    __asm__ volatile("bdnz $" ::: "ctr");

    v01 = *((f32 *)&nbase->unk0x4);
    v11 = *((f32 *)&nbase->unk0x14);
    v30 = *((f32 *)&nbase->unk0x30);
    v20 = *((f32 *)&nbase->unk0x20);
    v00 = *((f32 *)&nbase->unk0x0);
    v10 = *((f32 *)&nbase->unk0x10);
    tp = fr.t2;
    p2[1] = nbase;
    fr.t2 = fn_80003EB0(&fr.mat[0], var_f31);
    fr.out[0] = *((f32 *)&tp->unk0x0) * v00 +
                *((f32 *)&tp->unk0x4) * v10 +
                *((f32 *)&tp->unk0x8) * v20 +
                *((f32 *)&tp->unk0xC) * v30;
    v21 = *((f32 *)&nbase->unk0x24);
    v31 = *((f32 *)&nbase->unk0x34);
    v12 = *((f32 *)&nbase->unk0x18);
    v02 = *((f32 *)&nbase->unk0x8);
    fr.out[1] = *((f32 *)&tp->unk0x0) * v01 +
                *((f32 *)&tp->unk0x4) * v11 +
                *((f32 *)&tp->unk0x8) * v21 +
                *((f32 *)&tp->unk0xC) * v31;
    v22 = *((f32 *)&nbase->unk0x28);
    v32 = *((f32 *)&nbase->unk0x38);
    v13 = *((f32 *)&nbase->unk0x1C);
    v03 = *((f32 *)&nbase->unk0xC);
    fr.out[2] = *((f32 *)&tp->unk0x0) * v02 +
                *((f32 *)&tp->unk0x4) * v12 +
                *((f32 *)&tp->unk0x8) * v22 +
                *((f32 *)&tp->unk0xC) * v32;
    v23 = *((f32 *)&nbase->unk0x2C);
    v33 = *((f32 *)&nbase->unk0x3C);
    fr.out[3] = *((f32 *)&tp->unk0x0) * v03 +
                *((f32 *)&tp->unk0x4) * v13 +
                *((f32 *)&tp->unk0x8) * v23 +
                *((f32 *)&tp->unk0xC) * v33;
    fr.out[4] = *((f32 *)&tp->unk0x10) * v00 +
                *((f32 *)&tp->unk0x14) * v10 +
                *((f32 *)&tp->unk0x18) * v20 +
                *((f32 *)&tp->unk0x1C) * v30;
    fr.out[5] = *((f32 *)&tp->unk0x10) * v01 +
                *((f32 *)&tp->unk0x14) * v11 +
                *((f32 *)&tp->unk0x18) * v21 +
                *((f32 *)&tp->unk0x1C) * v31;
    fr.out[6] = *((f32 *)&tp->unk0x10) * v02 +
                *((f32 *)&tp->unk0x14) * v12 +
                *((f32 *)&tp->unk0x18) * v22 +
                *((f32 *)&tp->unk0x1C) * v32;
    fr.out[7] = *((f32 *)&tp->unk0x10) * v03 +
                *((f32 *)&tp->unk0x14) * v13 +
                *((f32 *)&tp->unk0x18) * v23 +
                *((f32 *)&tp->unk0x1C) * v33;
    fr.out[8] = *((f32 *)&tp->unk0x20) * v00 +
                *((f32 *)&tp->unk0x24) * v10 +
                *((f32 *)&tp->unk0x28) * v20 +
                *((f32 *)&tp->unk0x2C) * v30;
    fr.out[9] = *((f32 *)&tp->unk0x20) * v01 +
                *((f32 *)&tp->unk0x24) * v11 +
                *((f32 *)&tp->unk0x28) * v21 +
                *((f32 *)&tp->unk0x2C) * v31;
    fr.out[10] = *((f32 *)&tp->unk0x20) * v02 +
                 *((f32 *)&tp->unk0x24) * v12 +
                 *((f32 *)&tp->unk0x28) * v22 +
                 *((f32 *)&tp->unk0x2C) * v32;
    fr.out[11] = *((f32 *)&tp->unk0x20) * v03 +
                 *((f32 *)&tp->unk0x24) * v13 +
                 *((f32 *)&tp->unk0x28) * v23 +
                 *((f32 *)&tp->unk0x2C) * v33;
    fr.out[12] = *((f32 *)&tp->unk0x30) * v00 +
                 *((f32 *)&tp->unk0x34) * v10 +
                 *((f32 *)&tp->unk0x38) * v20 +
                 *((f32 *)&tp->unk0x3C) * v30;
    fr.out[13] = *((f32 *)&tp->unk0x30) * v01 +
                 *((f32 *)&tp->unk0x34) * v11 +
                 *((f32 *)&tp->unk0x38) * v21 +
                 *((f32 *)&tp->unk0x3C) * v31;
    fr.out[14] = *((f32 *)&tp->unk0x30) * v02 +
                 *((f32 *)&tp->unk0x34) * v12 +
                 *((f32 *)&tp->unk0x38) * v22 +
                 *((f32 *)&tp->unk0x3C) * v32;
    fr.out[15] = *((f32 *)&tp->unk0x30) * v03 +
                 *((f32 *)&tp->unk0x34) * v13 +
                 *((f32 *)&tp->unk0x38) * v23 +
                 *((f32 *)&tp->unk0x3C) * v33;

    ((__ps_t volatile *)nbase)[0] = ((__ps_t volatile *)&fr.out[0])[0];
    ((__ps_t volatile *)nbase)[1] = ((__ps_t volatile *)&fr.out[0])[1];
    ((__ps_t volatile *)nbase)[2] = ((__ps_t volatile *)&fr.out[0])[2];
    ((__ps_t volatile *)nbase)[3] = ((__ps_t volatile *)&fr.out[0])[3];
    ((__ps_t volatile *)nbase)[4] = ((__ps_t volatile *)&fr.out[0])[4];
    ((__ps_t volatile *)nbase)[7] = ((__ps_t volatile *)&fr.out[0])[7];
    ((__ps_t volatile *)nbase)[5] = ((__ps_t volatile *)&fr.out[0])[5];
    ((__ps_t volatile *)nbase)[6] = ((__ps_t volatile *)&fr.out[0])[6];
}
