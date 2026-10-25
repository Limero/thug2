// WIP DRAFT (non-matching) — hand reconstruction from the DOL
// REFRESHED 2026-10-07 (scaffold/flag/volatile re-sweep): 8.3045% -> 15.3979% `volatile` keyword(s) removed from the body
// family=m2c range=0x801A1C7C-0x801A2584 size=2312B
// FLAG: -mps-float
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "qb_constants.h"

typedef union { __ps_t p; f32 w[2]; } S;
typedef union { S s[8]; f32 f[16]; } Mat4;

typedef struct {
    char pad_00[0x18];
    s32 f_18;
    char pad_1C[0x20];
    f32 f_3C;
    s32 f_40;
    s32 f_44;
    f32 f_48;
    f32 f_4C;
    f32 f_50;
    char pad_54[4];
    f32 f_58;
    f32 f_5C;
    f32 f_60;
    char pad_64[4];
    s32 f_68;
    s32 f_6C;
    s32 f_70;
    char pad_74[0x1C];
    f32 f_90;
} Unk_801A1C7C;

extern f32 lbl_802AB1C8;
extern f32 lbl_802AB1CC;
extern s32 *lbl_80305EE4;
extern s32 lbl_80301A38;

s32 *fn_80024660(s32);
s32 *fn_800246AC(s32);
void fn_800AB3AC(void *, s32);
s32 fn_801A1BAC(void *, void *, void *);
s32 fn_800A398C(s32);
void fn_8012570C(s32, s32);
s32 fn_800244BC(s32);

s32 fn_801A1C7C(Unk_801A1C7C *arg0) {
    S V[20];
    S *pv;
    S *pv4;
    f32 a;
    f32 b;
    f32 c;
    f32 d;
    Mat4 *mm;
    S *v;
    s32 *p;
    s32 i;
    s32 ret;
    s32 e;

    pv = V;
    v = (S *)fn_80024660(arg0->f_18);
    mm = (Mat4 *)fn_800246AC(arg0->f_18);
    p = (s32 *)((char *)lbl_80305EE4 + 0x28);
    for (i = 0; i < 4; i++) {
        e = *(s32 *)((char *)*p++ + 0x1C);
        if (*(s32 *)((char *)e + 0x20) & 0x40) {
            fn_800AB3AC(arg0, 1);
        }
    }
    if (arg0->f_70 != 0) {
        f32 z;
        f32 o;

        z = lbl_802AB1C8;
        o = lbl_802AB1CC;
        V[0].w[0] = z;
        pv[0].w[1] = z;
        pv[1].w[0] = z;
        pv[1].w[1] = o;
        ret = fn_801A1BAC(arg0, (void *)pv, (void *)&V[2]);
        v[0].p = V[2].p;
        v[1].p = V[3].p;
        pv4 = &V[4];
        V[4].w[0] = z;
        pv4[1].w[1] = o;
        pv4[0].w[1] = z;
        pv4[1].w[0] = z;
        V[0].p = __builtin_ps_neg(V[0].p);
        pv[1].w[0] = -pv[1].w[0];
        a = V[0].w[0];
        b = V[0].w[1];
        c = V[1].w[1];
        V[6].w[0] = a * a;
        V[6].w[1] = b * b;
        d = pv[1].w[0];
        V[7].w[0] = d * d;
        V[8].w[0] = b * pv[1].w[0];
        V[9].w[0] = a * b;
        V[8].w[1] = pv[1].w[0] * a;
        V[10].w[1] = c * b;
        V[10].w[0] = c * a;
        V[11].w[0] = c * pv[1].w[0];
        mm->f[0] = o - 2.0f * (V[6].w[1] + V[7].w[0]);
        mm->f[4] = 2.0f * (V[11].w[0] + V[9].w[0]);
        mm->f[8] = 2.0f * (V[10].w[1] - V[8].w[1]);
        mm->f[12] = z;
        mm->f[16] = 2.0f * (V[11].w[0] - V[9].w[0]);
        mm->f[20] = o - 2.0f * (V[7].w[0] + V[6].w[0]);
        mm->f[24] = 2.0f * (V[10].w[0] + V[8].w[0]);
        mm->f[28] = z;
        mm->f[32] = 2.0f * (V[10].w[1] + V[8].w[1]);
        mm->f[36] = 2.0f * (V[10].w[0] - V[8].w[0]);
        mm->f[40] = o - 2.0f * (V[6].w[1] + V[6].w[0]);
        mm->f[44] = z;
        mm->s[6].p = V[4].p;
        mm->s[7].p = V[5].p;
        mm->f[15] = o;
    } else {
        V[0].w[0] = lbl_802AB1C8;
        pv[1].w[0] = lbl_802AB1C8;
        pv[1].w[1] = lbl_802AB1CC;
        pv[0].w[1] = lbl_802AB1C8;
        v[0].p = V[0].p;
        v[1].p = pv[1].p;
        mm->f[15] = lbl_802AB1CC;
        mm->f[0] = lbl_802AB1CC;
        mm->f[1] = lbl_802AB1C8;
        mm->f[2] = lbl_802AB1C8;
        mm->f[3] = lbl_802AB1C8;
        mm->f[4] = lbl_802AB1C8;
        mm->f[5] = lbl_802AB1CC;
        mm->f[6] = lbl_802AB1C8;
        mm->f[7] = lbl_802AB1C8;
        mm->f[8] = lbl_802AB1C8;
        mm->f[9] = lbl_802AB1C8;
        mm->f[10] = lbl_802AB1CC;
        mm->f[11] = lbl_802AB1C8;
        mm->f[12] = lbl_802AB1C8;
        mm->f[13] = lbl_802AB1C8;
        mm->f[14] = lbl_802AB1C8;
        if (arg0->f_3C == lbl_802AB1C8) {
            fn_8012570C(QB_CAMERA_FOV, 0);
        }
        ret = fn_800244BC(arg0->f_18);
    }
    return ret;
}
// PARKED 2026-10-03: 8.30% masked (48/578 words), object 740B vs
// symbol 2312B; 25.9% of the emitted prefix. What is now CORRECT (each measured,
// not guessed): the whole `arg0->f_70 != 0` branch (0x801A1CFC-0x801A1EA4) and
// the whole else branch (0x801A1EA8-0x801A1F38) are instruction-for-instruction
// identical to the want except register NUMBERS — including the volatile store
// order, the psq_l/ps_neg/psq_st round trip, the 9 V[6..11] products and all 12
// mm stores. Findings that mattered:
//  1) V must be a *direct local array* (`volatile S V[20]`), not a pointer, or
//     every access becomes base+disp off one register instead of `disp(sp)`.
//  2) a,b,c,d are real f32 LOCALS read from the volatile V — the want loads
//     V[0].x, V[0].y, V[1].y exactly once each (held in f11/f13/f10) while
//     V[1].x is re-read 5x; only 4 locals can produce that read pattern.
//  3) `mm` must be `volatile Mat4 *` or GCC reorders the else-branch f[14]
//     store to position 2 (proven: non-volatile gave 35 words, volatile 40).
//  4) `pv4 = &V[4]` is a real 7th pointer: it is the only way to get the want's
//     `addi r9,r1,0x28` + `0xc(r9)/4(r9)/8(r9)` triple (40 -> 48 words).
//  5) `mm->f[60]` in the old draft was a mis-decode: the want stores
//     `stfs f30,0x3c(r31)`, and 0x3c is f[15] of the 16-float matrix.
// BLOCKER (measured, not understood): GCC's hard-reg assignment for this body is
//  unreachable from the C source. Want: v=r26 pv=r27 arg0=r28 i=r29 p=r30 mm=r31,
//  and b=f13 (f12 reserved for the mm->f[0] value). Got: v=r26 i=r27 arg0=r28
//  pv=r29 mm=r30 p=r31, and b=f12 with f[0] materialised in f0. I proved the
//  allocno order is insensitive to local DECLARATION order (all 10-permutation
//  sweeps of pv/mm/v/p/i/a/b/c/ret/e gave byte-identical output) and to
//  initialisation STATEMENT order (4 variants identical) — it is
//  flow.c `local_allocate_registers` live-range/ref-count priority plus reload's
//  base choice, which I could not steer without brute-forcing, which the brief
//  forbids. The 4 stray f7<->f8 swaps and the 2-instruction drift at 0x801A1D20
//  come from that one cause.
// SECOND, HARDER BLOCKER: 0x801A1F3C-0x801A2564 (395 words, 68% of the symbol)
// is not in the draft at all. It is `if (f_40) { if (f_44 == 0xC588EEBC) ... else
// { fn_800A398C(lbl_80301A38); if (r3) { two 4x4-matrix dot-product blocks at
//  r3+0x78 guarded by f_68 / f_6c, then two ~180-word ps_madd0/ps_madd matrix
// builds } } }` — dense paired-single with no scalar anchor to decode from, and
// it needs the second half written before ANY score above ~30% is reachable.
// (Tried and rejected as regressions: named local for the f[0] value 48->48 with
// worse codegen, mm->f[0] moved to the 4th statement 48->46, dropping the loop
// temp `e` 48->20, hoisting z/o to function scope no change, `S *v` non-volatile
// no change.)
