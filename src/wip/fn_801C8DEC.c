// WIP DRAFT (non-matching) — hand-rebuilt from the want disassembly, 2026-10-04.
// family=m2c range=0x801C8DEC-0x801C9404 size=1560B
// extra_cflags: -mps-float
// PARKED at best measured 28/390 masked words (7.2%, up from the m2c stub's
// 1.3% / 5 words), object 1568B vs want 1560B (was 1040B).
//
// WHAT THIS IS NOW (a genuine, near-complete reconstruction, not the m2c stub):
// the whole 1560B body is present and the *semantics* of every block is
// recovered — the (f32)(f64)int 2^52 idiom, the signed `% 20`, the
// ps_mul/ps_merge00/ps_madd/ps_sum0 "length^2 of a 3-vector" webs, the
// rsqrte+res+muls0 normalisations, the (dot+1)*0.5 angle term, the
// idx/cnt ring-buffer store + summing loop, the three (f32)(f64)i divisions,
// the fn_8014030C vec4 in/out, and the trailing length<=120 CObject tail.
// The 6-prologue words (stwu -0x1c8, mflr, stfd f30 0x1b8, stfd f31 0x1c0,
// stmw r27 0x1a4, stw r0 0x1cc) now match byte-for-byte, and the PS op
// *sequence* matches op-for-op (ps_sub / ps_mul / ps_merge00(lbl_802ACD30) /
// ps_madd / ps_sum0 / ps_rsqrte / ps_muls0 / ps_mul / ps_res).
//
// REMAINING BLOCKER: register allocation + stack-slot numbering. The want
// assigns arg0->r31, cur->r30, mgr->r29, cnt->r27 (r28 left as scratch) and
// puts every long-lived __ps_t at *specific* offsets (0x18,0x20,0x28,0x30,
// 0x38,0x40,0x48,0x50,0x58,0x60 and 0x128..0x158) with one store + one
// reload each; this body gets a rotated GPR set (arg0->r30, mgr->r28,
// cur->r31) and a different slot map, so ~85% of words differ even though
// the instruction streams agree. Reproducing that needs the original's exact
// local-declaration list/order (which ngccc turns into slots) and, for the
// register assignment, the `register __ps_t x __asm__("frN")` pins +
// empty-`__asm__` barriers that the house style uses for PS functions
// (see matched src/fn_801B19DC.c) — banned for this pass. Verified negative:
//   * `volatile` on every __ps_t (all 17) — correct psq_st/psq_l traffic but
//     5 callee-saved FPRs (f27..f31) instead of 2 => prologue 9 words, size
//     1560B but only 2.8%.
//   * plain (non-volatile) __ps_t locals — ngccc keeps them in PS register
//     pairs, so d0/d1 + e0/e1 end up in callee-saved f28/f29 and f30/f31
//     across fn_8014030C => prologue 7-9 words.
//   * The 2-saved-FPR prologue only appears when the first two
//     `if (dot > 0.0f)` tests compare against the *variable* f31v (which
//     holds lbl_802ACDF8 from before the call to fn_8021D758) instead of the
//     literal — that is what makes f31 callee-saved and reproduces the
//     want's `fcmpu cr0, f13, f31`.
//   * `if (sp178 <= lbl_802ACE20)` compiles to fcmpu+cror+bns (3 words); the
//     want's fcmpu+bgt needs `if (!(sp178 > lbl_802ACE20))`.
//
// TOOLS NOTE: tools/want_dis.py / tools/ps_disasm.py STALL at 0x801C8F2C
// because capstone 5.0.7 cannot decode `e1bf0030` (stw r29,0x30(r1)); this
// function is 100% undisassemblable with the stock tools unless capstone is
// run with skipdata=True. Worth a recipes-file note.
//
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

extern char lbl_80305F9C[];
extern f32 lbl_802ACDF4;
extern f32 lbl_802ACDF8;
extern f32 lbl_802ACE08;
extern f32 lbl_802ACE0C;
extern f32 lbl_802ACE10;
extern f32 lbl_802ACE20;
extern char lbl_8029F480[];
extern __ps_t lbl_802ACD30;

void *fn_8021B55C(void *, s32);
void *fn_80219698(void *);
void *fn_8021D358(void *, u16);
s32 fn_8013F74C(void *);
void *fn_8013E034(void *, void *);
void *fn_8021D758(void *);
f32 fn_8014030C(s32, s32, void *, void *);
void fn_8010794C(void *);
void fn_80107AB4(void *, void *, void *);
void fn_80107A80(void *, s32, s32);
s32 fn_80107B20(void *, s32, s32);
void fn_801C84E8(void *, void *, void *);
void CObject_RemoveRefLink(void *, void *);

typedef union { __ps_t p; f32 w[2]; } PS;
typedef struct { PS a; f32 b; PS c; } V4;

typedef struct So_801C8DEC { char pad[0x20B4]; s32 v; } So_801C8DEC;

typedef struct Obj_801C8DEC {
    char pad0x0[0xC];
    void *unk0xC;
    char pad0x10[0x20];
    __ps_t v30[4];
    char pad0x50[0x20];
    f32 a70[20];
    f32 aC0[20];
    f32 a110[20];
    char pad0x160[0x140];
    s32 cnt;
    f32 scale;
} Obj_801C8DEC;

typedef struct Sk_801C8DEC {
    char pad0x0[0x58];
    __ps_t v58;
    f32 f5C;
    __ps_t v60;
    char pad0x68[0x20];
    __ps_t v88;
    char pad0x94[0x4];
    __ps_t v98;
} Sk_801C8DEC;

typedef struct Q_801C8DEC { s32 f[54]; } Q_801C8DEC;

void fn_801C8DEC(Obj_801C8DEC *arg0) {
    void *mgr = *(void **)lbl_80305F9C;
    void *cur = fn_8021B55C(mgr, 0);
    u32 cnt = (s32)(arg0->scale * lbl_802ACDF4);
    u32 value;
    So_801C8DEC *o;
    Q_801C8DEC sp28;
    void *p;
    void *sp68;
    void *sp110;
    V4 out;
    volatile __ps_t d0, d1, e0, e1, n0, n1, s0, s1;
    __ps_t t0, t1, i1, i2, i3, dotv, lenv, A, B;
    __ps_t tmp, inv;
    PS u;
    volatile PS sp160, sp168, sp170;
    volatile f32 sp13C, sp144, sp15C;
    f32 sp178;
    f32 f30v, f31v, f6v, f7v, f8v;
    s32 i, idx, sp100, spF0;

    if (fn_80219698(mgr) != 0) {
        o = *(So_801C8DEC **)((char *)fn_8021D358(mgr, *(u16 *)((char *)arg0->unk0xC + 0x1A)) + 0x1C);
        value = (fn_8013F74C(o) == 0) ? o->v : 0;
    } else {
        sp28.f[1] = 0;
        sp28.f[2] = (s32)lbl_8029F480;
        o = fn_8013E034(cur, &sp28);
        value = (fn_8013F74C(o) == 0) ? o->v : 0;
        sp28.f[2] = (s32)lbl_8029F480;
    }

    if (cnt == 0) {
        f30v = lbl_802ACDF8;
    } else {
        f30v = (f32)(f64)(value - cnt) / (f32)(f64)cnt;
        if (f30v < lbl_802ACDF8) {
            f30v = lbl_802ACDF8;
        }
    }

    idx = arg0->cnt % 20;
    d0 = arg0->v30[0];
    d0 = d0 - arg0->v30[2];
    d1 = arg0->v30[1];
    d1 = d1 - arg0->v30[3];
    e0 = d0;
    e1 = d1;
    f31v = lbl_802ACDF8;
    p = fn_8021D758(mgr);
    if (p != 0 && *(s32 *)((char *)p + 0x18) != 0) {
        A = *(__ps_t *)((char *)p + 0xD0);
        B = *(__ps_t *)((char *)p + 0xD8);
        n0 = d0;
        n1 = d1;
        tmp = B * B;
        tmp = __builtin_ps_merge00(tmp, lbl_802ACD30);
        tmp = __builtin_ps_madd(A, A, tmp);
        tmp = __builtin_ps_sum0(tmp, tmp, tmp);
        u.p = tmp;
        if (u.w[0] > f31v) {
            inv = __builtin_ps_rsqrte(tmp);
            i1 = inv;
            A = __builtin_ps_muls0(A, inv);
            sp13C = lbl_802ACE08;
            B = B * i1;
        }
        tmp = n1 * n1;
        tmp = __builtin_ps_merge00(tmp, lbl_802ACD30);
        tmp = __builtin_ps_madd(n0, n0, tmp);
        tmp = __builtin_ps_sum0(tmp, tmp, tmp);
        u.p = tmp;
        if (u.w[0] > f31v) {
            inv = __builtin_ps_rsqrte(tmp);
            i2 = inv;
            n0 = __builtin_ps_muls0(n0, inv);
            sp144 = lbl_802ACE08;
            n1 = n1 * i2;
        }
        tmp = B * n1;
        tmp = __builtin_ps_merge00(tmp, lbl_802ACD30);
        tmp = __builtin_ps_madd(A, n0, tmp);
        dotv = __builtin_ps_sum0(tmp, tmp, tmp);
        f31v = (*(volatile f32 *)&dotv + lbl_802ACE08) * lbl_802ACE0C;
    } else {
        f31v = lbl_802ACDF8;
    }

    tmp = d1 * d1;
    tmp = __builtin_ps_merge00(tmp, lbl_802ACD30);
    tmp = __builtin_ps_madd(d0, d0, tmp);
    tmp = __builtin_ps_sum0(tmp, tmp, tmp);
    lenv = __builtin_ps_res(__builtin_ps_rsqrte(tmp));
    arg0->a70[idx] = *(volatile f32 *)&lenv / (f32)(f64)cnt * lbl_802ACE10;
    arg0->aC0[idx] = f30v;
    arg0->a110[idx] = f31v;
    arg0->cnt++;
    f7v = lbl_802ACDF8;
    f8v = lbl_802ACDF8;
    f6v = lbl_802ACDF8;
    for (i = 0; i < arg0->cnt; i++) {
        if (i > 19) {
            break;
        }
        f7v += arg0->a70[i];
        f8v += arg0->aC0[i];
        f6v += arg0->a110[i];
    }

    sp160.w[0] = f7v / (f32)(f64)i;
    sp168.w[0] = (f8v / (f32)(f64)i) * (f6v / (f32)(f64)i);

    tmp = d1 * d1;
    tmp = __builtin_ps_merge00(tmp, lbl_802ACD30);
    tmp = __builtin_ps_madd(d0, d0, tmp);
    tmp = __builtin_ps_sum0(tmp, tmp, tmp);
    u.p = tmp;
    if (u.w[0] > lbl_802ACDF8) {
        inv = __builtin_ps_rsqrte(tmp);
        i3 = inv;
        d0 = __builtin_ps_muls0(d0, inv);
        sp15C = lbl_802ACE08;
        d1 = d1 * i3;
    }

    d0 = __builtin_ps_muls0(d0, sp160.p);
    d1 = __builtin_ps_muls0(d1, sp160.p);
    e0 = __builtin_ps_muls0(d0, sp168.p);
    e1 = __builtin_ps_muls0(d1, sp168.p);
    A = ((Sk_801C8DEC *)arg0->unk0xC)->v58 + e0;
    B = ((Sk_801C8DEC *)arg0->unk0xC)->v60 + e1;
    n0 = A;
    n1 = B;
    out.a.p = A;
    out.b = ((Sk_801C8DEC *)arg0->unk0xC)->f5C;
    out.c.p = B;

    sp170.w[0] = fn_8014030C(0x8024D49B, 1, arg0->unk0xC, &out);
    n1 = __builtin_ps_muls0(((Sk_801C8DEC *)arg0->unk0xC)->v98, sp170.p);
    n0 = __builtin_ps_muls0(((Sk_801C8DEC *)arg0->unk0xC)->v88, sp170.p);
    d1 = arg0->v30[1];
    d1 = d1 + n1;
    d0 = arg0->v30[0];
    d0 = d0 + n0;
    s1 = ((Sk_801C8DEC *)arg0->unk0xC)->v60 + n1;
    s0 = ((Sk_801C8DEC *)arg0->unk0xC)->v58 + n0;
    fn_8010794C(&sp68);

    t1 = e1 - s1;
    t0 = e0 - s0;
    tmp = t1 * t1;
    tmp = __builtin_ps_merge00(tmp, lbl_802ACD30);
    tmp = __builtin_ps_madd(t0, t0, tmp);
    tmp = __builtin_ps_sum0(tmp, tmp, tmp);
    lenv = __builtin_ps_res(__builtin_ps_rsqrte(tmp));
    sp178 = *(volatile f32 *)&lenv;
    if (!(sp178 > lbl_802ACE20)) {
        fn_80107AB4(&sp68, &e0, &s0);
        fn_80107A80(&sp68, 0x10, 0);
        if (fn_80107B20(&sp68, 1, 0) != 0) {
            fn_801C84E8(arg0, &sp100, &spF0);
        }
    }
    if (sp110 != 0) {
        CObject_RemoveRefLink(sp110, &sp110);
        sp110 = 0;
    }
}
