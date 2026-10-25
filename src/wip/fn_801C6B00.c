// WIP DRAFT (non-matching) — hand-reconstructed from the want bytes (m2c's
// body decoded this function's semantics but emitted nothing usable).
// family=m2c range=0x801C6B00-0x801C6F88 size=1160B
// extra_cflags: -mps-float
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// BEST MEASURED: object is SIZE-EXACT (1160 B == want) at 20.0% masked
// (58/290 words; 2026-10-04 round, was 19.7%). The 18-word prologue (stwu
// -0x1d0 / mflr / stfd f27..f31 @0x1a8.. / stmw r28 @0x198 / stw r0 @0x1d4 /
// addi r30 / mr r31 / mr r3 / li r28) and the whole 13-word epilogue are
// byte-identical to the want. Body now also lands on want's store ORDER in
// block 1 (see STORE ORDER below).
//
// WHAT THE FUNCTION IS (fully derived, this part is reusable):
//   * a 0xC0-byte trace matrix (fn_8010794C) at frame+0x28; fn_80107AB4(&m,
//     &v8, &v18) fills its two 16-byte vectors, fn_80107A80(&m,0x10,0) sets
//     its u16s at +0x54/+0x56, fn_80107B20(&m,1,0) raycasts and fills
//     m+0x88/0x90 (V1), m+0x98/0xA0 (V2), an f32 at +0x80 and a u16 at +0x58,
//     and returns the hit flag. Its callees set m+0xA8 (the CObject ref that
//     CObject_RemoveRefLink clears in the tail).
//   * v8 = objQuat*QB(Physics_Ground_Snap_Up) + obj->unk0x58,
//     v18 = objQuat*(-200.0f) + obj->unk0x58, objQuat = {obj+0x88, obj+0x90}
//     (both scalars are stored with a SCALAR stfs and read back as a PAIR:
//      `SN_PS_type s; s.flt.hi = <f32 expr>;` then `ps_muls0(q, s.ps)`).
//   * the PS length/dot idiom is the house one (see src/fn_800A07F0.c):
//     sum0(ps_madd(d, d, merge00(ps_mul(e, e), lbl_802ACD30))) then
//     rsqrte+res; lbl_802ACD30 is a {0.0f,0.0f} pair inside a 0x2C-byte
//     STRING object (0x802ACD30..0x5B) so it must be `extern __ps_t`.
//   * lbl_802ACD6C=0.0f, 0x6C+4=0x70=-200.0f, 0x74=DEG2RAD, 0x78=0.001f,
//     0x7C=-1.0f, 0x80=1.0f.
//   * QB hashes: Physics_Ground_Snap_Up 0xE4D79235,
//     Wall_Non_Skatable_Angle 0x3EEDE4D3, Ground_stick_angle_forward
//     0x4138283E, Physics_Ground_Snap_Down 0x899BA3D0.
//
// WHY PARKED (remaining blocker + what was measured/negative):
//   * BLOCKER 1 — the 4th callee-saved GPR (r29 = arg0->unk0xC). The r29 lead
//     is NOT asm-only (see 2026-10-04 below): `register Skater *obj
//     __asm__("r29")` reproduces `lwz r29,0xc(r31)` @0x801C6B38 and all three
//     `mr r5,r29` byte-exactly. What fails is the FRAME: obj then needs a 5th
//     callee-saved GPR, the frame goes 0x1D8 and `stmw r27`. Root cause found:
//     want has exactly FOUR cross-call GPRs — r28=result, r29=obj, r30=&fr.m
//     (later reused for the lbl_802ACD30 page address), r31=arg0. This body
//     spends the 5th on `&fr.p118`: it keeps the call-crossing address in r30
//     (`addi r30,r1,0x118` hoisted before the first fn_800058CC, then
//     `mr r3,r30`), while want REMATERIALISES it straight into the argument
//     register right after that call (`addi r3,r1,0x118` @0x801C6DA0). That
//     single decision cascades: it steals r30 from the rodata page address,
//     which pushes the const address to r28 and `result` to r27, i.e. +1 GPR.
//     NEGATIVE: swapping the two fn_800058CC calls, `volatile` on p118/p120,
//     `(void*)` casts, a non-const 2nd parameter, and -fno-schedule-insns /
//     -fno-schedule-insns2 / -fno-thread-jumps / -fno-gcse all leave the r30
//     form in place. It is the one thing here that looks unreachable in C.
//   * BLOCKER 2 — the two `ps_mr f12,f11` scalar copies in block 1
//     (0x801C6B74/0x801C6BA8). Solved as a SOURCE SHAPE, not asm: see
//     "NON-ESCAPING SLOTS" below — but only by moving s138..s168 out of the
//     escaping Frame struct, which costs +24 B of object size, so it cannot
//     be banked until BLOCKER 1 frees a register.
//   * want re-tests `cmpwi r28,0` for the tail `if (result)`; this body keeps
//     cr0 alive across fn_80004518 (`cmpwi r28,0` + `mfcr r30` at the head of
//     the wall-test then-branch, a second `mfcr r30` on the else path,
//     `mtcrf 0x80,r30` before the join's `beq`; +3 words net). Guard
//     spellings `!= 0 {}`, plain `if (r)`, `== 0 {} else {}` and a `goto`
//     form are all byte-identical.
//   * want hoists `addi r4,r1,0xd0` (the 2nd argument of the tail
//     CObject_RemoveRefLink) ABOVE `cmpwi r3,0`; this body emits it after the
//     call — a 3-word cost in the last block.
//   * all scheduling flags are no-ops here (-fno-sched-interblock,
//     -fno-sched-spec, -fno-thread-jumps, -fno-expensive-optimizations:
//     byte-identical); -fno-schedule-insns2 (17.2%), -fno-gcse (10.0%) and
//     -fno-rerun-cse-after-loop (10.0%) all LOWER the score.
//
// 2026-10-04 ROUND (three findings, all reusable):
//   * STORE ORDER (banked, +0.3 pts and the reason the body is now 20.0%):
//     when a PS product feeds BOTH a caller-visible vector and a struct temp
//     (`v8.xy` and `pE8` in block 1), write the product into the STANDALONE
//     accumulator and store VECTOR-FIRST, TEMP-SECOND:
//         acc.ps = __builtin_ps_muls0(obj->q88.ps, fr.s138.ps);
//         fr.v8.xy.ps = acc.ps;   fr.pE8.ps = acc.ps;
//     The older spelling (struct temp first, then `fr.v8.xy.ps = fr.pE8.ps`)
//     makes cc1 emit `psq_st pE8` BEFORE `psq_st v8.xy`; with the accumulator
//     the order is want's. Group 2 then matches want's store order EXACTLY
//     (v18.xy, pE8, v18.zw, pF0) and group 1 is 3 of 4 (pF0/v8.zw swapped).
//     Not a plain statement-order lever: swapping the last two statements of
//     group 1 does NOT move the two stores (scheduler, not expander).
//   * NON-ESCAPING SLOTS (recipes §7q, extended): §7q's rule that a reload
//     copy (`fmr`/`ps_mr`) needs a standalone local whose address never escapes
//     ALSO governs `__builtin_ps_muls0` operands, not just `x = dot.flt.hi`.
//     Moving s138/s140/s148/s150/s158/s160/s168 out of the Frame struct into
//     standalone `SN_PS_type` locals makes cc1 emit want's copies verbatim:
//     2 x `ps_mr` in block 1, 2 x `ps_mr` in the else branch, and the five
//     `fmr f27,f0` / `fmr f29,f11` / `fmr f31,f11` / `fmr f30,f0` / `fmr f31,f0`
//     scalar-copy pairs -> 13 copies vs want's 14 (6 without the move). Frame
//     and slot offsets are unchanged (still 0x1D0, s138 @0x138 ... s168 @0x168).
//     COST: object 1184 B (+24). CAVEAT: ALL SEVEN must leave the struct —
//     moving only s138/s140 relocates them to 0x160/0x168 (§7q's "4-byte local
//     sorts before an 8-byte one"), which breaks the 0x138/0x140 slots.
//   * The obj/r29 lead IS reachable in plain C via a GPR register pin
//     (`register Skater *obj __asm__("r29");` + `obj = arg0->unk0xC;` placed
//     after the fn_8010794C call, so the load stays where want has it).
//     Result: 13.1% — the 3 `mr r5,r29` + the `lwz r29,0xc(r31)` are exact,
//     but the `stwu -0x1D8` / `stmw r27` prologue mismatch costs more than
//     the four words it wins, so the pin is NOT banked. See BLOCKER 1 for why
//     the frame cannot stay 0x1D0 with five callee-saved GPRs.
//
// FRAME LEVERS (measured; re-deriving these is the expensive part):
//   * ONE aggregate local holding the whole frame in want's slot order is
//     what pins the local area to exactly 0x190. But GCC SRA's PS-typed
//     struct members back into independent locals, so the accumulator must
//     stay OUTSIDE the struct (plain `SN_PS_type acc`); as a struct field it
//     gets a slot and the frame becomes 0x1D8.
//   * `la`/`lb` (plain f32 copies of s148.flt.hi / s150.flt.hi, read right
//     after their `psq_st`) are what forces FIVE callee-saved FPRs. Without
//     them GCC reloads both from the stack, saves only f29-f31 and the frame
//     drops to 0x1C8.
//   * `volatile` on exactly {v8, v18, p108, p128} is what makes the object
//     LENGTH 1160: none of them -> 1132 B (7 words short), all of them ->
//     1204 B (11 long). Semantically defensible: v8/v18/p108/p128 all have
//     their address taken or a dead store in the want.
//   * `rad = lbl_802ACD74;` must be a statement BEFORE the wall-test `if`
//     (not inside the `||` comma-expression), else the f28/f29 colours of
//     `rad` and `lb` swap (+1.4 points).
#include "types.h"
#include "qb_constants.h"

typedef struct {
    SN_PS_type xy, zw;
} Vec4;

typedef struct {
    SN_PS_type o[4];
    char pad0x20[0x34];
    u16 unk0x54;
    u16 unk0x56;
    u16 unk0x58;
    char pad0x5A[0x2E];
    SN_PS_type unk0x88;
    SN_PS_type unk0x90;
    SN_PS_type unk0x98;
    SN_PS_type unk0xA0;
    void *unk0xA8;
    char pad0xAC[0x14];
} Mtx;

typedef struct Skater_s {
    char pad0x0[0xC];
    struct Skater_s *unk0xC;
    char pad0x10[0x40];
    SN_PS_type unk0x50;
    SN_PS_type unk0x58;
    SN_PS_type unk0x60;
    SN_PS_type unk0x68;
    char pad0x70[0x8];
    void *unk0x78;
    char pad0x7C[0x4];
    SN_PS_type unk0x80;
    SN_PS_type unk0x88;
    SN_PS_type unk0x90;
    SN_PS_type unk0x98;
    SN_PS_type unk0xA0;
} Skater;

typedef struct {
    volatile Vec4 v8;   /* +0x008 (passed by address to fn_80107AB4) */
    volatile Vec4 v18;  /* +0x018 (idem) */
    Mtx m;              /* +0x028 .. +0x0E7 (the 0xC0-byte trace matrix) */
    SN_PS_type pE8;     /* +0x0E8 */
    SN_PS_type pF0;     /* +0x0F0 */
    SN_PS_type pF8;     /* +0x0F8 (in-arg of fn_800058CC) */
    SN_PS_type p100;    /* +0x100 */
    volatile SN_PS_type p108;  /* +0x108 (out-arg of fn_800058CC: written) */
    SN_PS_type p110;    /* +0x110 */
    SN_PS_type p118;    /* +0x118 (out-arg of fn_800058CC) */
    SN_PS_type p120;    /* +0x120 */
    volatile SN_PS_type p128;  /* +0x128 (dead store in want) */
    SN_PS_type p130;    /* +0x130 (dead store in want) */
    SN_PS_type s138;    /* +0x138 */
    SN_PS_type s140;    /* +0x140 */
    SN_PS_type s148;    /* +0x148 */
    SN_PS_type s150;    /* +0x150 */
    SN_PS_type s158;    /* +0x158 */
    SN_PS_type s160;    /* +0x160 */
    SN_PS_type s168;    /* +0x168 */
} Frame;

extern __ps_t lbl_802ACD30;
extern f32 lbl_802ACD6C;
extern f32 lbl_802ACD70;
extern f32 lbl_802ACD74;
extern f32 lbl_802ACD78;
extern f32 lbl_802ACD7C;
extern f32 lbl_802ACD80;

void fn_8010794C(Mtx *);
void fn_80107AB4(Mtx *, volatile Vec4 *, volatile Vec4 *);
void fn_80107A80(Mtx *, s32, s32);
s32 fn_80107B20(Mtx *, s32, s32);
void fn_800058CC(void *, const void *);
void fn_80004518(void *, s32);
void CObject_RemoveRefLink(void *, void *);
f32 fn_8014030C(u32, s32, void *);
f32 fn_8012570C(u32, s32);
f32 acosf(f32);
f32 cosf(f32);
f32 sinf(f32);
f32 tanf(f32);

void fn_801C6B00(struct Skater_s *arg0) {
    Frame fr;
    s32 result;
    u16 flags;
    f32 rad, ta, tb, tc, fd, fe, ff, fg;
    f32 la, lb;
    SN_PS_type acc;

    result = 0;
    fn_8010794C(&fr.m);

    fr.s138.flt.hi = fn_8014030C(QB_PHYSICS_GROUND_SNAP_UP, 1, arg0->unk0xC);
    acc.ps = __builtin_ps_muls0(arg0->unk0xC->unk0x88.ps, fr.s138.ps);
    fr.v8.xy.ps = acc.ps;
    fr.pE8.ps = acc.ps;
    acc.ps = __builtin_ps_muls0(arg0->unk0xC->unk0x90.ps, fr.s138.ps);
    fr.v8.zw.ps = acc.ps;
    fr.pF0.ps = acc.ps;
    fr.s140.flt.hi = lbl_802ACD70;
    acc.ps = __builtin_ps_muls0(arg0->unk0xC->unk0x88.ps, fr.s140.ps);
    fr.v18.xy.ps = acc.ps;
    fr.pE8.ps = acc.ps;
    acc.ps = __builtin_ps_muls0(arg0->unk0xC->unk0x90.ps, fr.s140.ps);
    fr.v18.zw.ps = acc.ps;
    fr.pF0.ps = acc.ps;
    fr.v8.xy.ps = __builtin_ps_add(fr.v8.xy.ps, arg0->unk0xC->unk0x58.ps);
    fr.v8.zw.ps = __builtin_ps_add(fr.v8.zw.ps, arg0->unk0xC->unk0x60.ps);
    fr.v18.xy.ps = __builtin_ps_add(fr.v18.xy.ps, arg0->unk0xC->unk0x58.ps);
    fr.v18.zw.ps = __builtin_ps_add(fr.v18.zw.ps, arg0->unk0xC->unk0x60.ps);

    fn_80107AB4(&fr.m, &fr.v8, &fr.v18);
    fn_80107A80(&fr.m, 0x10, 0);
    if (fn_80107B20(&fr.m, 1, 0) != 0) {
        fr.pE8.ps = __builtin_ps_sub(arg0->unk0xC->unk0x58.ps, fr.m.unk0x88.ps);
        fr.pF0.ps = __builtin_ps_sub(arg0->unk0xC->unk0x60.ps, fr.m.unk0x90.ps);
        acc.ps = __builtin_ps_merge00(__builtin_ps_mul(fr.pF0.ps, fr.pF0.ps), lbl_802ACD30);
        acc.ps = __builtin_ps_madd(fr.pE8.ps, fr.pE8.ps, acc.ps);
        fr.s148.ps = __builtin_ps_sum0(acc.ps, acc.ps, acc.ps);
        acc.ps = __builtin_ps_merge00(__builtin_ps_mul(arg0->unk0xC->unk0x90.ps, fr.pF0.ps), lbl_802ACD30);
        acc.ps = __builtin_ps_madd(arg0->unk0xC->unk0x88.ps, fr.pE8.ps, acc.ps);
        fr.s150.ps = __builtin_ps_sum0(acc.ps, acc.ps, acc.ps);
        fr.s148.ps = __builtin_ps_rsqrte(fr.s148.ps);
        fr.s148.ps = __builtin_ps_res(fr.s148.ps);
        la = fr.s148.flt.hi;
        lb = fr.s150.flt.hi;

        rad = lbl_802ACD74;
        flags = fr.m.unk0x58;
        if (((flags ^ 1) & 1) || ((flags & 0xE) != 8) ||
            (fr.m.unk0x98.flt.lo < sinf(fn_8012570C(QB_WALL_NON_SKATABLE_ANGLE, 1) * rad))) {
            if (lb < lbl_802ACD78) {
                fr.pF8.ps = __builtin_ps_add(fr.m.unk0x88.ps, fr.m.unk0x98.ps);
                fr.p100.ps = __builtin_ps_add(fr.m.unk0x90.ps, fr.m.unk0xA0.ps);
                arg0->unk0xC->unk0x58.ps = fr.pF8.ps;
                arg0->unk0xC->unk0x60.ps = fr.p100.ps;
            }
        } else {
            result = 1;
            fr.pF8.ps = fr.m.unk0x98.ps;
            fr.p100.ps = fr.m.unk0xA0.ps;
            fr.p108.ps = arg0->unk0xC->unk0x98.ps;
            fr.p110.ps = arg0->unk0xC->unk0xA0.ps;
            fr.p118.ps = arg0->unk0xC->unk0x98.ps;
            fr.p120.ps = arg0->unk0xC->unk0xA0.ps;
            acc.ps = __builtin_ps_merge00(__builtin_ps_mul(fr.p110.ps, fr.p100.ps), lbl_802ACD30);
            acc.ps = __builtin_ps_madd(fr.p108.ps, fr.pF8.ps, acc.ps);
            fr.s158.ps = __builtin_ps_sum0(acc.ps, acc.ps, acc.ps);
            ta = fr.s158.flt.hi;
            fn_800058CC(&fr.p108, &fr.pF8);
            fn_800058CC(&fr.p118, &arg0->unk0x60);
            acc.ps = __builtin_ps_merge00(__builtin_ps_mul(fr.p110.ps, fr.p120.ps), lbl_802ACD30);
            acc.ps = __builtin_ps_madd(fr.p108.ps, fr.p118.ps, acc.ps);
            fr.s160.ps = __builtin_ps_sum0(acc.ps, acc.ps, acc.ps);
            tb = fr.s160.flt.hi;
            tc = cosf(fn_8014030C(QB_GROUND_STICK_ANGLE_FORWARD, 1, arg0->unk0xC) * rad);
            if (ta > lbl_802ACD6C && tb > lbl_802ACD6C && tb < tc) {
                result = 0;
            } else if (lb > lbl_802ACD6C) {
                fd = tb;
                if (tb > lbl_802ACD80) {
                    fd = lbl_802ACD80;
                }
                fe = fd;
                if (fd < lbl_802ACD7C) {
                    fe = lbl_802ACD7C;
                }
                fe = acosf(fe);
                fr.p130.ps = __builtin_ps_sub(arg0->unk0xC->unk0x60.ps, arg0->unk0x58.ps);
                fr.p128.ps = __builtin_ps_sub(arg0->unk0xC->unk0x58.ps, arg0->unk0x50.ps);
                acc.ps = __builtin_ps_merge00(
                    __builtin_ps_mul(arg0->unk0x58.ps, arg0->unk0x58.ps), lbl_802ACD30);
                acc.ps = __builtin_ps_madd(fr.p128.ps, fr.p128.ps, acc.ps);
                acc.ps = __builtin_ps_sum0(acc.ps, acc.ps, acc.ps);
                acc.ps = __builtin_ps_rsqrte(acc.ps);
                fr.s168.ps = __builtin_ps_res(acc.ps);
                ff = fr.s168.flt.hi;
                ff = ff * tanf(fe);
                fg = fn_8014030C(QB_PHYSICS_GROUND_SNAP_DOWN, 1, arg0->unk0xC);
                if (ff < fg) {
                    ff = fg;
                }
                if (la > ff) {
                    result = 0;
                }
            }
            if (result != 0) {
                arg0->unk0x60.ps = fr.pF8.ps;
                arg0->unk0x68.ps = fr.p100.ps;
                arg0->unk0xC->unk0x88.ps = fr.pF8.ps;
                arg0->unk0xC->unk0x90.ps = fr.p100.ps;
                fn_80004518((char *)arg0->unk0xC + 0x78, 1);
            }
        }
        if (result != 0) {
            arg0->unk0xC->unk0x58.ps = fr.m.unk0x88.ps;
            arg0->unk0xC->unk0x60.ps = fr.m.unk0x90.ps;
        }
    }
    if (fr.m.unk0xA8 != 0) {
        CObject_RemoveRefLink(fr.m.unk0xA8, &fr.m.unk0xA8);
        fr.m.unk0xA8 = 0;
    }
}
