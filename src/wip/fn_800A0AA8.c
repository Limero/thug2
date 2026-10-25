// WIP DRAFT (non-matching) — hand-rebuilt from the 0x800A0AA8 want disasm
// (25.3% -> 35.0%). Semantics fully recovered: see recipes §6fy2.
// family=m2c range=0x800A0AA8-0x800A0D8C size=740B
// extra_cflags: -mps-float
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// Recovered: arg0 = a 10-double object with xy pairs at +0x58/0x60, 0x68/0x70,
// 0x78/0x80, 0x88/0x90, 0x98/0xA0 (fn_800A08C0 names 0x58/0x60 acc0/acc1 and
// 0x78..0xA0 the six "per-round scale inputs"); arg1 = the QB data block.
// 4 GetFloat(QB_LENGTH/HEIGHT/DISTANCE/SHIFT) each scaled by lbl_80297B88,
// then x = m58 + m88*h + m98*d + m78*sh and y = m60 + m90*h + mA0*d + m80*sh
// (all six products, both partial sums and the final point are also spilled to
// the local object's +0xC0..+0x118, and the final point to +0x00/+0x10/+0xC0).
// ContainsFlag(QB_SIDE) -> += (m78,m80)*length; QB_DOWN -> -= (m88,m90)*length;
// else -> += (m98,mA0)*length. Then fn_80107B20(&loc,1,0) + the ref-link tail.
#include "types.h"
#include "qb_constants.h"

extern const f32 lbl_80297B84;
extern const f32 lbl_80297B88;
extern const f32 lbl_80297B8C;

typedef union {
    f32 f;
    __ps_t p;
} U;

typedef struct {
    volatile __ps_t x;
    volatile __ps_t y;
} Pt;

typedef struct {
    Pt p00;
    Pt p10;
    char pad0x20[0x88];
    void *fA8;
    char pad0xAC[0x14];
    volatile __ps_t fC0;
    volatile __ps_t fC8;
    volatile __ps_t fD0;
    volatile __ps_t fD8;
    volatile __ps_t fE0;
    volatile __ps_t fE8;
    volatile __ps_t fF0;
    volatile __ps_t fF8;
    volatile __ps_t f100;
    volatile __ps_t f108;
    volatile __ps_t f110;
    volatile __ps_t f118;
} Loc;

typedef struct {
    char pad0x00[0x58];
    __ps_t f58;
    __ps_t f60;
    char pad0x68[0x10];
    __ps_t f78;
    __ps_t f80;
    __ps_t f88;
    __ps_t f90;
    __ps_t f98;
    __ps_t fA0;
} Mat;

void fn_8010794C(Loc *);
s32 GetFloat(void *, s32, f32 *, s32);
s32 ContainsFlag(void *, s32);
s32 fn_80107B20(Loc *, s32, void *);
void CObject_RemoveRefLink(void *, void *);

s32 fn_800A0AA8(Mat *m, void *qb) {
    Loc L;
    f32 v0;
    f32 v1;
    f32 v2;
    f32 v3;
    U h;
    U d;
    U sh;
    U l1;
    U l2;
    U l3;
    __ps_t a;
    __ps_t b;
    __ps_t c;
    __ps_t e;
    __ps_t g;
    __ps_t i;
    __ps_t tx;
    __ps_t ty;
    f32 s;
    s32 t;

    fn_8010794C(&L);
    v0 = lbl_80297B84;
    GetFloat(qb, QB_LENGTH, &v0, 0);
    s = lbl_80297B88;
    v0 *= s;
    v1 = lbl_80297B84;
    GetFloat(qb, QB_HEIGHT, &v1, 0);
    v1 *= s;
    v2 = lbl_80297B8C;
    GetFloat(qb, QB_DISTANCE, &v2, 0);
    v2 *= s;
    v3 = lbl_80297B8C;
    GetFloat(qb, QB_SHIFT, &v3, 0);
    v3 *= s;
    h.f = v1;
    d.f = v2;
    sh.f = v3;
    a = __builtin_ps_muls0(m->f88, h.p);
    b = __builtin_ps_muls0(m->f90, h.p);
    c = __builtin_ps_muls0(m->f98, d.p);
    e = __builtin_ps_muls0(m->fA0, d.p);
    i = __builtin_ps_muls0(m->f80, sh.p);
    g = __builtin_ps_muls0(m->f78, sh.p);
    tx = __builtin_ps_add(m->f58, a);
    ty = __builtin_ps_add(m->f60, b);
    L.fE0 = tx;
    L.fE8 = ty;
    L.fF0 = a;
    L.fF8 = b;
    L.f100 = c;
    L.f108 = e;
    L.f118 = i;
    tx = __builtin_ps_add(tx, c);
    ty = __builtin_ps_add(ty, e);
    L.fD0 = tx;
    L.fD8 = ty;
    L.f110 = g;
    tx = __builtin_ps_add(tx, g);
    ty = __builtin_ps_add(ty, i);
    L.p10.x = tx;
    L.p10.y = ty;
    L.fC0 = tx;
    L.fC8 = ty;
    L.p00.x = tx;
    L.p00.y = ty;
    if (ContainsFlag(qb, QB_SIDE) != 0) {
        l1.f = v0;
        i = __builtin_ps_muls0(m->f80, l1.p);
        g = __builtin_ps_muls0(m->f78, l1.p);
        L.fC8 = i;
        L.fC0 = g;
        tx = __builtin_ps_add(L.p10.x, g);
        ty = __builtin_ps_add(L.p10.y, i);
    } else if (ContainsFlag(qb, QB_DOWN) != 0) {
        l2.f = v0;
        i = __builtin_ps_muls0(m->f90, l2.p);
        g = __builtin_ps_muls0(m->f88, l2.p);
        L.fC8 = i;
        L.fC0 = g;
        tx = __builtin_ps_sub(L.p10.x, g);
        ty = __builtin_ps_sub(L.p10.y, i);
    } else {
        l3.f = v0;
        i = __builtin_ps_muls0(m->fA0, l3.p);
        g = __builtin_ps_muls0(m->f98, l3.p);
        L.fC8 = i;
        L.fC0 = g;
        tx = __builtin_ps_add(L.p10.x, g);
        ty = __builtin_ps_add(L.p10.y, i);
    }
    L.p10.x = tx;
    L.p10.y = ty;
    t = fn_80107B20(&L, 1, 0);
    if (t != 0) {
        if (L.fA8 != 0) {
            CObject_RemoveRefLink(L.fA8, &L.fA8);
            L.fA8 = 0;
        }
        return 1;
    }
    if (L.fA8 != 0) {
        CObject_RemoveRefLink(L.fA8, &L.fA8);
    }
    L.fA8 = t;
    return 0;
}
// PARKED 2026-10-03: 34.97% masked, object 732 B vs symbol 740 B
// (8 B / 2 words SHORT), 0 flags beyond -mps-float, 0 pins, 0 barriers, 0 asm.
// Proved blockers, both measured (recipes §6fy2 has the full tables):
//  (1) LENGTH. want's if/else chain is 46 instructions: each arm keeps its own
//      volatile reads of L.p10.x/L.p10.y and the arms tail-merge only
//      {muls0,muls0,psq_st,psq_st,ps_add,ps_add} (SIDE jumps into a common block
//      that the DOWN-flag fall-through also reaches). ngccc instead cross-jumps
//      the whole SIDE arm onto the DOWN-flag fall-through block, so the shared
//      tail carries the two volatile loads once -> exactly 2 words fewer. Every
//      source shape that gets want's split (duplicate the L.p10 tail store per
//      arm, non-volatile p00/p10, extra temps) scores lower.
//  (2) REGISTER ALLOCATION / sched2 in the main block. 124/185 instructions now
//      have the right mnemonic but only 64 are byte-equal. want pins the six
//      products in f9,f8,f7,f6,f11,f10 with the accumulators in f13/f0 and the
//      ps_muls0 second operand in f12; ngccc hoists the first two ps_adds above
//      the remaining ps_muls0s and recycles product registers (f13,f10,f12,f0,
//      f8,f7; accumulators f6/f7). Resistant (byte-identical or worse) to 6
//      declaration orders of the __ps_t temporaries, ps_add operand swap,
//      d.f/sh.f store swap, a renamed union typedef, hoisting the accumulator
//      loads, and -fno-schedule-insns / -fno-schedule-insns2 (25.8%/28.4%).
//      So the residual is an RTL source-shape difference, not a flag or an
//      ordering axis. Same class as recipes §6bu2's sched2 look-ahead wall.
// Semantics are believed correct and fully documented in the header comment, so
// a future attempt should start from THIS body and only chase (1)+(2).
