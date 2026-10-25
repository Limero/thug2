// WIP DRAFT (non-matching) — hand reconstruction (2026-10-03)
// family=manual range=0x800EB8F8-0x800EBA28 size=304B
// extra_cflags: -mps-float
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// RECONSTRUCTION NOTES
// -------------------
// want is pure Gekko paired-single (psq_l/ps_muls0/ps_add/ps_mr) + 2 scalar f32
// tail ops. Frame 0x80, stmw r27@0x6c, LR@0x84. Semantics (all verified by
// hand against the want's 76 words):
//
//   h = fn_800EBA28(arg0, arg1, &v08);      // arg0 of fn_800EBA28 is UNUSED
//   if (!h) return 0;                      // callee never reads r3
//   if (!fn_800EBA28(arg0, arg2, &v18))    // 2nd call: 3rd arg re-uses &v18
//        *arg1 = *arg2;                    //   copy both ps pairs
//   else {
//        t = fn_800144C8(); k = lbl_8029ACE0;
//        u0 = muls0(h[0xB8], t); u1 = muls0(h[0xC0], t);
//        w0 = muls0(u0, k);    w1 = muls0(u1, k);
//        v28[0] = add(arg1[0], w0); v28[1] = add(arg1[1], w1);
//        v28[2..5] = w0, w1, u0, u1;        // DEAD in the want (never re-read)
//        if (fn_800EBA28(arg0, &v28, &v18))
//             *arg1 = v08; arg1->y += lbl_8029ACE4;
//        else
//             *arg1 = v28;                 // copies p0->+0, p1->+8
//   }
//   return h;
//
// Local layout the want implies (all offsets reproduced by this draft):
//   sp+0x08 v08(16)  sp+0x18 v18(16)  sp+0x28 v28(6x ps = 48)
//   sp+0x58 PSU t (8B, written by a 4-byte stfs at +0, read by an 8-byte psq_l)
//   sp+0x60 PSU k (same shape)
//
// Two codegen facts this draft exploits (see AGENTS-recipes.md "PSU locals"):
//  - an 8-byte `union { __ps_t ps; struct { f32 a, b; } f; }` assigned through
//    its +0 f32 member and read back as `.ps` emits stfs<off+0> + psq_l<off>,
//    exactly like the want's two scalar-fed ps locals;
//  - the four dead 8-byte stores only survive if the aggregate's address
//    escapes, hence one 6-member struct at sp+0x28 whose address is the 4th
//    call's 2nd argument (that is also why `addi r4,r1,0x28` in the want).
//
// STATUS 2026-10-03: NEAR 75.0% masked, object 304B == symbol
// 304B. Frame, save area, callee-saved register assignment (r28=arg0,
// r31=arg1, r30=arg2, r27=&v18, r29=return), ALL five branch targets (verified
// via the REL14/REL24 section addends: 0x34/0x64/0x118/0x11c/0xf4), every
// frame displacement and every store address already match. Residual = 19
// words of pure list-schedule order / FPR choice inside the ps window
// (0x800EB970-0x800EB9AC and 0x800EB9F4-0x800EBA08): the want interleaves the
// `pa[0]`/`pa[1]` psq_l with the two `ps_muls0` and reloads t/dt late, we hoist
// all four multiplies first. See PARKED note at end of file.
#include "types.h"
#include "structs.h"

extern f32 lbl_8029ACE0;
extern f32 lbl_8029ACE4;
extern s32 fn_800EBA28(const void *a0, const void *a1, void *out);
extern f32 fn_800144C8(void);

typedef union {
    __ps_t ps;
    struct {
        f32 a;
        f32 b;
    } f;
} PSU;

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} V4;

typedef struct {
    __ps_t v0;
    __ps_t v1;
} V2;

typedef struct {
    __ps_t p0;
    __ps_t p1;
    __ps_t p2;
    __ps_t p3;
    __ps_t p4;
    __ps_t p5;
} V6;

typedef struct {
    char pad0[184];
    __ps_t vB8;
    __ps_t vC0;
} HANDLE;

s32 fn_800EB8F8(s32 *arg0, V4 *arg1, V4 *arg2) {
    V2 v08;
    V2 v18;
    V6 v28;
    PSU t;
    PSU k;
    s32 temp;
    HANDLE *h;
    __ps_t u0, u1, w0, w1;
    __ps_t *pa;
    __ps_t *pa2;

    temp = fn_800EBA28(arg0, arg1, &v08);
    if (temp == 0) {
        return 0;
    }
    h = (HANDLE *)temp;
    pa = (__ps_t *)arg1;
    pa2 = (__ps_t *)arg2;
    if (fn_800EBA28(arg0, arg2, &v18) != 0) {
        goto big;
    }
    pa[0] = pa2[0];
    pa[1] = pa2[1];
    goto done;
big:
    t.f.a = fn_800144C8();
    u0 = __builtin_ps_muls0(h->vB8, t.ps);
    k.f.a = lbl_8029ACE0;
    u1 = __builtin_ps_muls0(h->vC0, t.ps);
    w0 = __builtin_ps_muls0(u0, k.ps);
    w1 = __builtin_ps_muls0(u1, k.ps);
    v28.p0 = __builtin_ps_add(pa[0], w0);
    v28.p1 = __builtin_ps_add(pa[1], w1);
    v28.p2 = w0;
    v28.p3 = w1;
    v28.p4 = u0;
    v28.p5 = u1;
    if (fn_800EBA28(arg0, (void *)&v28, &v18) != 0) {
        goto do_v08;
    }
    pa[0] = v28.p0;
    pa[1] = v28.p1;
    goto done;
do_v08:
    pa[0] = v08.v0;
    pa[1] = v08.v1;
    arg1->y += lbl_8029ACE4;
done:
    return temp;
}
// PARKED 2026-10-03: 75.0% 304B/304B. Body above is a complete,
// hand-verified semantic reconstruction: frame 0x80 + stmw r27@0x6c + LR@0x84,
// callee-saved assignment (r28=arg0, r31=arg1, r30=arg2, r27=&v18, r29=ret),
// all five branch targets (read from the REL14/REL24 section addends, not from
// capstone), every stack displacement and every store address all match the
// want; 57 of 76 words are byte-identical. The residual 19 words are a pure
// list-schedule lock inside the paired-single window (0x800EB970-0x800EB9AC,
// 0x800EB9F4-0x800EBA08): the want interleaves the two independent
// `psq_l arg1+0/+8` loads BETWEEN the two `ps_muls0` and re-loads its two
// scalar-fed ps locals late, while cc1 hoists all four multiplies to the front
// of the window regardless of statement order. Proven not fixable by
// reordering the four multiply statements (all four orders measured; only the
// `u0,u1,w0,w1` order preserves the want's store run, and that is the one
// kept), by `register __ps_t __asm__("frN")` FPR pins (byte-identical output),
// by `volatile` on the y-update load, or by `-fno-schedule-insns2` /
// `-fno-expensive-optimizations` (both neutral-to-worse; `-fno-schedule-insns`
// = 51%). ngccc's PS-window scheduler, not the C semantics, owns this residual.
// 2026-10-22: 96.1% (was 75.0%): `k.f.a = lbl_8029ACE0` sits between the two `ps_muls0` (u0 first),
// so the literal load lands between the u0 and u1 multiplies. Residual: 3 words at the
// do_v08 tail (`psq_l`/`psq_st`/`lfs` rotation); `arg1->y +=` before or between the
// `pa[i] = v08` copies measures 89.5% / 92.1%.
