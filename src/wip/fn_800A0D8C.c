// === PARKED (2026-10-01) — NEAR 78.6% (44/56 words), size EXACT 224B ===
//
// WHAT THIS IS: vec3 normalize. arg0->0xF0/0xF8 are two PS pairs (x,y / z,w);
// length^2 via the SNAPS dot idiom merge00(b*b, zero_pair) + madd(a,a,·) +
// sum0(t,t,t) (== 3t in this compiler's model); guarded by `> 0.0f`, then
// inv = rsqrte(len2), a = muls0(a, inv), inv = (inv, 1.0f), b = b * inv.
// Result pushed as QB_X/QB_Y/QB_Z on arg2->0x18 via fn_8012772C.
//
// LOAD-BEARING FIXES (in order of value):
//  1. `__ps_t` (mode(PS)) locals + `__builtin_ps_*` + per-object -mps-float.
//     All 12 psq/ps_* opcodes then emit, frame 0x28 + 3 pair slots (8/10/18).
//  2. Lane access needs the SNAPS union: reading a float out of a plain
//     `__ps_t` ICEs cc1 3.9.3 at expmed.c:1115 — must be `SP {__ps_t ps;
//     struct {f32 hi, lo;};}`.
//  3. Locals must live in ONE struct whose address escapes (`Loc loc; Loc *L
//     = &loc;`). Without the escape GCC register-allocates the PS locals, and
//     the *store* of the second pair degrades to a GPR block copy
//     (lwz/lwz/stw/stw) instead of psq_l+psq_st. The escape also creates the
//     `addi r31,r1,8` frame base want uses for the sp+0x10 slot.
//  4. SOURCE ORDER: `L->b.ps = <load>` must come BEFORE the `b*b` statement.
//     Reversed, GCC CSEs the two 0xF8 loads into one and the object loses a
//     word (220B vs 224B -> masked score collapses).
//
// STILL MISSING (12 words, all reload/regalloc ties, no opcode/structure diff):
//  * idx 13/15/17: want re-anchors r9 for lbl_80297B90 right after the pair
//    load (so `mr r30,r5` sits between them); here the 0.0 load is scheduled
//    two slots early, forcing a second anchor (r11) and shifting `mr r30,r5`.
//  * idx 24-33 (the if-body): want does `ps_rsqrte f13,f0` (dst = the dead
//    fcmpu operand) and `ps_muls0 f0,f11,f13`; here the rsqrte updates f0 in
//    place and the muls0 takes f13, which also drags the `lfs 1.0f` above both
//    psq_sts (want: below them, into the just-freed f0).
//  * idx 40: `lfs f1, 0xc(r1)` (want) vs `lfs f1, 4(r31)` — find_reload_base
//    picked the FP base for one of the two sp+0x8 pair-element reads; want uses
//    r1 for sp+0x8/0xc/0x18/0x1c and r31 only for sp+0x10.
//
// TRIED (all measured, all leave the same 12 words): ~20 source shapes —
// plain-SP vs struct locals, 3 separate address-taken locals, declaration
// reorder, nested/single-statement PS chains, temps for the rsqrte/muls0
// results, comma-expression in the if condition, lim/d temps, statement
// reorder inside the if, volatile source + volatile loads (gives 3 loads,
// worse). Flags: -fno-schedule-insns (26), -fno-schedule-insns2 (23),
//  -fno-expensive-optimizations (13), -fno-gcse / -fno-sched-interblock /
//  -fno-thread-jumps / -fno-cse-follow-jumps / -fno-rerun-cse-after-loop /
//  -fno-strength-reduce / -fno-branch-count-reg / -fno-delayed-branch (all 12).
//  Register pins are unavailable: `register __ps_t x __asm__("f0")` is rejected
//  ("invalid register name `f0' for register variable").
//
// NOT TRIED: a -mcpu/-mabi or "big/small GQR" rebuild of the local layout.
// TRIED 2026-10-19: copying the QB_X/Y/Z scalars into separate f32 locals
// before the calls (the first half of the old NOT TRIED) -> DIFF (extra
// loads/spills, whole tail shifts). Reverted to the 78.6% body.
//
// NOTE (tools bug, not mine): tools/want_got.py auto-adds -mps-float only for
// `__ps_t`, not for `__builtin_ps_` — it prints "want == got: None" for this
// draft. test_wip_drafts.py handles both.
// === PARKED END ===

// family=m2c range=0x800A0D8C-0x800A0E6C size=224B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "qb_constants.h"

typedef union {
    __ps_t ps;
    struct {
        f32 hi, lo;
    } flt;
} SP;

typedef struct {
    char pad0x0[0xf0];
    f32 x, y, z, w;
} VecSrc;

typedef struct {
    char pad0x0[0x18];
    s32 *u;
} CScript;

typedef struct {
    SP a, b, inv;
} Loc;

extern __ps_t lbl_80297B28;
extern f32 lbl_80297B90;
extern f32 lbl_80297B94;
extern void fn_8012772C(s32, u32, f32);

s32 fn_800A0D8C(VecSrc *arg0, s32 arg1, CScript *arg2) {
    Loc loc;
    Loc *L = &loc;
    SP dot;

    L->a.ps = *(__ps_t *)&arg0->x;
    L->b.ps = *(__ps_t *)&arg0->z;
    dot.ps = __builtin_ps_merge00(*(__ps_t *)&arg0->z * *(__ps_t *)&arg0->z, lbl_80297B28);
    dot.ps = __builtin_ps_madd(L->a.ps, L->a.ps, dot.ps);
    dot.ps = __builtin_ps_sum0(dot.ps, dot.ps, dot.ps);
    if (dot.flt.hi > lbl_80297B90) {
        L->inv.ps = __builtin_ps_rsqrte(dot.ps);
        L->a.ps = __builtin_ps_muls0(L->a.ps, L->inv.ps);
        L->inv.flt.lo = lbl_80297B94;
        L->b.ps = L->b.ps * L->inv.ps;
    }
    fn_8012772C(arg2->u, QB_X, L->a.flt.hi);
    fn_8012772C(arg2->u, QB_Y, L->a.flt.lo);
    fn_8012772C(arg2->u, QB_Z, L->b.flt.hi);
    return 1;
}