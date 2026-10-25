// WIP DRAFT — hand-rewritten from the want disassembly (NOT m2c output).
// family=m2c range=0x80096884-0x80096BE8 size=868B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// ---------------------------------------------------------------------------
// PARKING NOTE (2026-10-04, 2nd pass): NEAR **99.08%**, object exactly 868B.
// 215 of 217 words are byte-identical. Only two words of the final
// `fn_8001D39C(&L.mtx, &L.tmp)` argument setup differ, and they are
// *value-identical* (both compute 0x8037C038). The want forms r3 from the
// frame pointer with a 0x38 displacement at 0x80096BA8 and copies r31 to r4
// at 0x80096BAC. The current output instead copies r31 to r4 at 0x80096BA8
// and copies the live r22 to r3 at 0x80096BAC.
// i.e. want REMATERIALISES `&L.mtx` from the frame pointer for that call while
// reusing the live callee-saved copy (r22 = &L.mtx, set in the prologue by
// `mr r22, r26`) that the very next instruction (`stw r22, 0xa8(r30)`) needs.
// See "REMAINING BLOCKER" at the bottom for the full negative-result list.
//
// WHAT CLOSED THE GAP SINCE 70.5% (the single lever, measured twice):
//   `&lbl_8037B7E8 + 0x48` must be written as *base pointer + member*, never
//   as a direct field reference. ngccc FOLDS `&sym + off` into a single
//   `lis`/`addi` pair whenever the address expression is built from the
//   symbol itself, but DECOMPOSES it into `lis; addi(base); addi(base,off)`
//   as soon as a *variable* holds the base. Proof (isolated probe, -O2 -G0
//   -mcpu=750 -fno-common):
//       Blk *f2(void) { return (Blk *)&G + 3; };        -> lis G+72@ha; la;
//       Blk *f3(void) { Blk *b = (Blk *)&G; return b+3; } -> lis G@ha; la G; addi 72;
//   so `s2 = &lbl_8037B7E8.m48.b[0]` (got 4 setup words) becomes
//   `CamB *cb = &lbl_8037B7E8; s2 = &cb->m48.b[0];` (want 5).
//   TWO *separate, block-scoped* `CamB *cb = &lbl_8037B7E8` are needed --
//   one wrapping loop 2 only, one opened after the three `vw[]` stores and
//   left open to `}` so it also covers `PSMTXCopy`/`mp`/fn_800173CC/fn_8001737C
//   (that second one is what makes r30 = &lbl_8037B7E8 live across the five
//   tail calls instead of being re-materialised at each use, and it moves
//   `lis r30` from the end of the tail to just before the `vw` stores, which
//   is exactly want's order). A FUNCTION-scope `CamB *cb` costs an extra
//   callee-saved GPR (r23) and shifts the whole allocation; the block scope
//   is load-bearing.
//   Also measured: declaring `L.mtx` as `Mtx` instead of the `MatU` union and
//   fixing the `fn_8001D440`/`scale` prototypes to `f32 *` / `void *` removes
//   all compiler warnings without changing a single word.
// ---------------------------------------------------------------------------
// WHAT WAS FIXED (each measured):
//  * `f32 tanf(f32); f32 sqrtf(f32);` MUST be declared. types.h has no math.h,
//    so with implicit `int` returns ngccc builds every FP expression in
//    double + `fctiwz`/`xoris`/`frsp` helpers and the object is 1248B. This
//    alone was most of the 380B over-generation.
//  * arg0 is a PSX `Mtx` (3 x Vec4 @ 0x00/0x10/0x20); arg1 is a Vec3. The
//    local basis built from them is a `Mtx` whose .w slots carry
//    arg1.x/.y/.z (r0=-m.r0, r1=+m.r1, r2=-m.r2, translation in the w column).
//  * m2c had the basis field mapping shifted by one slot; the store offsets
//    are 0x0,0x4,0x8 / 0x10,0x14,0x18 / 0x20,0x24,0x28 for the vectors and
//    0xc,0x1c,0x2c for the translation, and they are emitted last.
//  * The two `w / sqrtf(...)` rows must re-read `lbl_8037B5E8.t0` / `.t1` from
//    memory (3 reloads total, not 1) — plain global reads do that for free.
//  * The second quotient needs its own C variable, otherwise ngccc coalesces
//    it with the first and emits `fdivs f2,f1,f30` where want reuses the
//    dead farg1 register: `fdivs f30,f1,f30`.
//  * Locals must be ONE address-taken struct (basis r1+0x08, mtx r1+0x38,
//    sc r1+0x68, tmp r1+0x78) plus a 20-byte pad: 0xB4 bytes puts the GPR save
//    area at r1+0xC0 and the frame at 0x100 with `stmw r22`. Declared as four
//    separate locals the frame came out 0xE8 and only 9 GPRs were saved.
//  * A *named* pointer for the basis (`pb = &L.basis`) homes r1+8 into r29 for
//    the 12 stores (a bare `&L.basis` rematerializes into r1-relative
//    displacements) — same lever as docs/parkings/36.
//  * `Vec4 *a1 = (Vec4 *)arg0 + 1; Vec4 *a2 = (Vec4 *)arg0 + 2;` inside a
//    NESTED `{ }` scope is what produces want's `addi r9,r28,0x20` /
//    `addi r11,r28,0x10` row bases. At function scope ngccc hoists both into
//    the prologue, which makes them live across all six calls, costs two more
//    callee-saved GPRs and inflates the frame to 0x108. Inside a block they
//    are materialised late, in volatile regs, exactly like the want.
//  * One shared `s32 v;` for all six words of a 0x18-stride copy block is what
//    produces want's interleaved `lwz r0,X(src); stw r0,X(dst)` through a
//    SINGLE temp register. Written as `d->wN = s->wN` ngccc hoists all six
//    loads above the stores and burns six temps (r9,r11,r10,r8,r7) — same
//    instruction count, all 17 loop words wrong.
//  * Loop 1 reuses the dying `&lbl_8037B7E8` register (want `addi r24,r24,0x48`)
//    and loop 3 reuses `r29 = &basis`; three separate pointer/counter
//    variable sets are needed for that (shared ones cost 2-4 extra words).
//
// REMAINING BLOCKER (2 words, value-identical): the last
// `fn_8001D39C(&L.mtx, &L.tmp)`. want passes `&L.mtx` as a FRESH frame
// reference `addi r3, r1, 0x38`; got passes the live callee-saved copy
// `mr r3, r22`. 2026-10-08 ROOT-CAUSED WITH THE `-da` RTL DUMPS: the shared
// pseudo is created by **gcse** (`.gcse` dump: `(insn 626 (set (reg:SI 244)
// (reg:SI 105)) REG_EQUAL (plus (reg 31) 56))`), and both the last call's arg0
// and the late store then read it. want's shape needs the call's arg0 to be its
// own single-use pseudo so reload has no live register to copy from and
// rematerialises the address. 10 further variants measured, all worse — pins
// r22-at-store 95.39 %, r22-for-both-stores 3.69 %, r26 1.84 %, unpinned `pm`
// assigned early 88.02 % / late 99.08 % (copy-propagated away),
// `(Mtx *)((char *)&L.basis + 0x30)` 99.08 % (cse folds it back), via `pb`
// 39.63 %. Full writeup: AGENTS-recipes.md §7m-4. Both are 0x8037C038 and the following `stw r22, 0xa8(r30)`
// (which want still does) proves r22 == &L.mtx throughout. Mechanism is cse
// failing to unify that one occurrence of the address with the prologue
// `addi r26, r1, 0x38` (cse cannot use r22 as the value's reg, since after
// `bl 0x8001d010` it has lost track of `mr r22, r26`), so reload has to
// rematerialise from the frame pointer. want does that at exactly one of the
// five `&L.mtx` occurrences and got at none of them. Tried and measured, all
// still 99.08% (2 words): a `MatU *pm = &L.mtx` local used for the calls /
// for the stores / for both / declared before or after `pb` (all 88%, the
// pseudo's creation order moves `&L.mtx` from r26 to r31 and `arg1` from r25
// to r26); the last call's arg1 through such a local; a block-scoped local
// for arg2; arg1 as `&L.mtx.m` (union member) or `(void *)&L.mtx`; the member
// declared as `MatU` instead of `Mtx`; a second decl at the same offset via
// `union { struct {MatU basis; MatU mtx; ...} a; struct {MatU z0; MatU z1; ...} b; }`
// (proves cse keys on the rtx address, not the DECL); swapping the store and
// the call in source (98.2%, ngccc sinks the store up across the `bl`);
// UPDATE 2026-10-18: not a toolchain-version artifact — the identical
// 215/217 residual reproduces on all five ProDG releases (3.5/3.5b140/
// 3.7/3.8.1/3.9.3, same 2 words), so no per-object mw_version override
// helps. Flag probes all no-ops at 215/217: -fno-regmove,
// -fno-function-cse, -fno-cse-follow-jumps, -fno-cse-skip-blocks,
// -fno-force-mem, -fno-rerun-loop-opt, -fno-defer-pop, -fno-thread-jumps
// (-fno-cprop-registers/-fno-reload-cse/-fno-rename-registers/
// -fno-if-conversion/-fno-merge-constants do not exist in this cc1).
// -fno-schedule-insns2 perturbs the tail (store/call swap +2 diffs);
// -fno-rerun-cse-after-loop destroys the frame. Still needs a C-level
// de-unification of the last call's &L.mtx from the gcse pseudo.
// UPDATE 2026-10-18: `fn_8001D39C(pb + 1, &L.tmp)` (address via pb instead of
// &L.mtx) globally perturbs regalloc (DIFF, +12B: r26/r29/r31 homes shift) --
// cse keys on the address so the spelling change moves the whole web, not just
// the tail. `// FLAG: -fno-expensive-optimizations` on the current body:
// 97.7% (worse; recipe-165 shape needs the paired proto flip, N/A here since
// the callee proto is already verified from its own first insns).
// A narrow block-scope
// `{ Mtx *q = &L.mtx; fn_8001D39C(q, &L.tmp); }` for last-call arg0 only
// (2026-10-10, still 99.1% — cse folds q into the shared pseudo); moving the `cb` block's
// boundary earlier (H4b, 99.08%); routing the late store through a block
// local (`{ Mtx *pm = &L.mtx; fn_8001D39C(&L.mtx,&L.tmp); cb->mp = pm; }`,
// 99.08% with byte-identical output to base); last-call arg0 as
// `(Mtx *)((char *)&L + 0x38)` (7.3% — the char arithmetic perturbs the
// whole function, not just the tail). Late-homing the r22 copy was ruled
// out without compiling: the prologue `mr r22,r26` exists without any
// explicit variable, so an explicit late-assigned local can only add code. Earlier pass also ruled out: a function
// scope `CamB *cb` used at both ends (breaks the prologue), swapping the d/s
// assignment order, shared vs separate loop pointers/counters, and
// -fno-schedule-insns2 / -fno-gcse / -fno-expensive-optimizations (57.1% /
// 1.8% / 71.0%). Related: docs/parkings/46 (0x18-stride copy loop), 36
// (home vs rematerialize), 73 (hi16 reload register set).
// ---------------------------------------------------------------------------
//
// RE-AUDITED 2026-10-20: the `addi r3,r1,0x38` / `mr r4,r31` transposition
// stands. -fno-sched-spec, -fno-delayed-branch, -fno-peephole and
// -fno-strength-reduce are bit-identical; -fno-schedule-insns 6.0%,
// -fno-schedule-insns2 82.5%. Unmasked check: no wrong-symbol immediate.
#include "types.h"

f32 tanf(f32);
f32 sqrtf(f32);

typedef struct { f32 x, y, z; } Vec3;
typedef struct { f32 x, y, z, w; } Vec4;
typedef struct { Vec4 r[3]; } Mtx;
typedef struct { s32 w0, w1, w2, w3, w4, w5; } Blk;
typedef struct { Blk b[2]; } Mat;
typedef union { Mtx m; Mat i; } MatU;

/* lbl_8037B5E8: projection tan/clip scalars + three cached matrices. */
typedef struct {
    u8 pad0[0x2C];
    Mat m614;
    Mat m644;
    Mat m674;
    u8 pad1[0x30];
    f32 vw[3];
    Mat m6e0;
    f32 t0;
    f32 t1;
    f32 n0;
    f32 n1;
    f32 n2;
    f32 n3;
    f32 az;
    f32 bz;
} CamA;

/* lbl_8037B7E8: the camera object the frustum is installed into. */
typedef struct {
    u8 pad0[0x48];
    Mat m48;
    u8 pad1[0x30];
    Mtx *mp;
} CamB;

extern CamA lbl_8037B5E8;
extern CamB lbl_8037B7E8;
extern f32 lbl_8029749C;
extern f32 lbl_802974A0;
extern f32 lbl_802974A4;
extern f32 lbl_802974A8;
extern f32 lbl_802974AC;
extern f32 lbl_803018AC;
extern f32 lbl_803018B0;

s32 fn_8001D010(void *);
void fn_800173D0(CamB *, f32, f32, f32, f32);
void fn_8001737C(CamB *);
void fn_800173CC(CamB *);
void fn_8001D39C(void *, void *);
void fn_8001D440(f32 *, f32, f32, f32);
void scale(void *, f32 *, s32);
void PSMTXCopy(void *, void *);

void fn_80096884(Mtx *arg0, Vec3 *arg1, f32 farg0, f32 farg1, f32 farg2) {
    struct {
        MatU basis;
        Mtx mtx;
        f32 sc[4];
        MatU tmp;
        s32 pad[5];
    } L;
    MatU *pb = &L.basis;
    f32 t, q, q2, nb, na, w, c;
    Blk *d1, *s1, *d2, *s2, *d3, *s3;
    s32 n1, n2, n3;
    s32 v;

    fn_8001D010(&L.mtx);
    t = 2.0f * tanf(farg0 * lbl_8029749C);
    q = t / farg1;
    nb = lbl_803018B0;
    na = lbl_803018AC;
    lbl_8037B5E8.bz = nb;
    lbl_8037B5E8.az = na;
    lbl_8037B5E8.t0 = t;
    lbl_8037B5E8.t1 = -q;
    fn_800173D0(&lbl_8037B7E8, t, q, -na, 2.0f * -nb);

    farg0 = farg0 * lbl_802974A0;
    t = tanf(farg0 * lbl_802974A4);
    q2 = t / farg1;
    w = lbl_802974A8;
    lbl_8037B5E8.t0 = t;
    lbl_8037B5E8.t1 = -q2;
    lbl_8037B5E8.n0 = w / sqrtf(w / (t * t) + w);
    lbl_8037B5E8.n1 = w / sqrtf(w / (lbl_8037B5E8.t1 * lbl_8037B5E8.t1) + w);
    lbl_8037B5E8.n2 = w / sqrtf(lbl_8037B5E8.t0 * lbl_8037B5E8.t0 + w);
    lbl_8037B5E8.n3 = w / sqrtf(lbl_8037B5E8.t1 * lbl_8037B5E8.t1 + w);

    {
        Vec4 *a1 = (Vec4 *)arg0 + 1;
        Vec4 *a2 = (Vec4 *)arg0 + 2;

        pb->m.r[0].x = -arg0->r[0].x;
        pb->m.r[0].y = -arg0->r[0].y;
        pb->m.r[0].z = -arg0->r[0].z;
        pb->m.r[1].x = a1->x;
        pb->m.r[1].y = a1->y;
        pb->m.r[1].z = a1->z;
        pb->m.r[2].x = -a2->x;
        pb->m.r[2].y = -a2->y;
        pb->m.r[2].z = -a2->z;
        pb->m.r[0].w = arg1->x;
        pb->m.r[1].w = arg1->y;
        pb->m.r[2].w = arg1->z;
    }
    fn_8001D39C(&L.mtx, &L.basis);
    lbl_8037B7E8.mp = &L.mtx;
    fn_8001737C(&lbl_8037B7E8);

    d1 = &lbl_8037B5E8.m644.b[0];
    s1 = &lbl_8037B7E8.m48.b[0];
    n1 = 0x30;
    do {
        n1 -= 0x18;
        v = s1->w0;
        d1->w0 = v;
        v = s1->w1;
        d1->w1 = v;
        v = s1->w2;
        d1->w2 = v;
        v = s1->w3;
        d1->w3 = v;
        v = s1->w4;
        d1->w4 = v;
        v = s1->w5;
        s1++;
        d1->w5 = v;
        d1++;
    } while (n1 != 0);

    {
        CamB *cb = &lbl_8037B7E8;

        d2 = &lbl_8037B5E8.m614.b[0];
        s2 = &cb->m48.b[0];
        n2 = 0x30;
        do {
            n2 -= 0x18;
            v = s2->w0;
            d2->w0 = v;
            v = s2->w1;
            d2->w1 = v;
            v = s2->w2;
            d2->w2 = v;
            v = s2->w3;
            d2->w3 = v;
            v = s2->w4;
            d2->w4 = v;
            v = s2->w5;
            s2++;
            d2->w5 = v;
            d2++;
        } while (n2 != 0);
    }

    d3 = &lbl_8037B5E8.m674.b[0];
    s3 = &L.basis.i.b[0];
    n3 = 0x30;
    do {
        n3 -= 0x18;
        v = s3->w0;
        d3->w0 = v;
        v = s3->w1;
        d3->w1 = v;
        v = s3->w2;
        d3->w2 = v;
        v = s3->w3;
        d3->w3 = v;
        v = s3->w4;
        d3->w4 = v;
        v = s3->w5;
        s3++;
        d3->w5 = v;
        d3++;
    } while (n3 != 0);

    c = lbl_802974AC;
    lbl_8037B5E8.vw[0] = c;
    lbl_8037B5E8.vw[1] = c;
    lbl_8037B5E8.vw[2] = c;
    {
        CamB *cb = &lbl_8037B7E8;

        PSMTXCopy(&cb->m48, &lbl_8037B5E8.m6e0);

        fn_8001D440(&L.sc[0], farg2, farg2, farg2);
        fn_8001D39C(&L.tmp, &L.basis);
        scale(&L.tmp, &L.sc[0], 1);
        fn_8001D39C(&L.mtx, &L.tmp);
        cb->mp = &L.mtx;
        fn_800173CC(cb);
        fn_8001737C(cb);
    }
}
