// WIP DRAFT — PARKED 2026-10-04 (fn_80195B14 @ 0x80195B14, 640B).
//
// BEST MEASURED: masked **11.2%** (18/161 words), object 644B — i.e. ONE WORD
// longer than want.  The *previous* parked body (no `f32 dist`) measured 13.8%
// at exactly 640B, but that 640B was a COINCIDENCE: the `&p` hoist it carried
// (+1 word) exactly cancelled the `fmr f31,f0` pair it was missing (-2/+1).
// Drop the hoist and that body loses a word; drop `f32 dist` from THIS one and
// it is 640B with 138/160 diffs.  The body below is the structurally correct
// one: **CONTROL EXPERIMENT — replace the single argument `&p` by the literal
// `0` and this body compiles to 159 of want's 160 words (99.4%, EXACT size,
// frame 0x80, `stmw r28, 0x58`, `fmr f31,f0`, `fcmpu cr0, f31, f0`), with the
// single residual being `addi r3, r1, 0` where want has `addi r3, r1, 0x18`.**
// So there is exactly ONE thing left to fix, and it is not a semantic one.
//
// ---------------------------------------------------------------- semantics
// (all of this is established from want bytes, not guessed)
//   arg0->unk0x20 is the QB param block; three QB keys are used:
//     QB_FILM_TARGET (0xD262ED09) -> checksum -> fn_8009F498 -> object `m`
//     QB_MODEL      (0x286A8D26) -> GetChecksum_3(m,..)->[0x210] -> fn_800626E8
//     QB_MAX_DISTANCE_TO_TARGET (0x856FAB92) -> GetInteger -> limit
//   fn_800626E8 writes a 16-byte V4 (two __ps_t) at r1+0x08; the 16-byte copy
//   at r1+0x18 is then forced to `(v.z, 1.0f)` by a *scalar* stfs of
//   lbl_802AA100 (1.0f) into .hi.hi — that is why the local must be a
//   {__ps_t,__ps_t} struct with a float view on the second half (PSU), not two
//   plain __ps_t.
//   The matrix at m+0x78 is 4 columns of 16 bytes; fn_8006FA90(base,i) is just
//   `base + i*16` and is called EIGHT times (indices 0,0,1,1,2,2,3,3) — one per
//   .lo/.hi access, each written inline as `((V4*)fn_8006FA90(mtx,i))->lo/->hi`.
//   The op mix muls0,muls0,madds1,madds1,madds0,madds0,madds1,madds1 with the
//   multiplier switching p.lo/ps then p.hi/ps is reproduced exactly.
//   m+0x58 is a 16-byte world position (psq_l 88(r31) / 96(r31)); it is added to
//   the two computed halves and the 16-byte result is passed to
//   fn_800557B8(&p, 6.0f)  <- lbl_802AA104 is a REAL 2nd argument (f1 = 6.0f);
//   r4=3 there is leftover from the previous fn_8006FA90 call, not an argument.
//   `up = fn_80024660(fn_80141964(fn_801745B4(lbl_80305EAC)))` is a single
//   nested expression: r3 is threaded through all three calls, no reloads.
//   Distance: ps_sub / ps_sub / ps_mul / ps_merge00(zero) / ps_madds0 /
//   ps_sum0 / ps_rsqrte / ps_res, then `(f32)(f64)sp2C` compared with dot.hi.
//   lbl_802AA0B8 is the all-zero __ps_t pair used as ps_merge00's second source.
//   PROVEN house fact: ngccc/3.9.3's int->double magic constant is the double
//   2^52+2^31 = 4503601774854144.0, emitted as `xoris rX,rX,0x8000` +
//   `stw 0x43300000` (high) + `lfd` + `fsub <that literal>` (src/r2d_802AA0B8.c
//   already declares it as lbl_802AA108).  The literal is a *load*, not an
//   immediate, which is why `(f32)(f64)int` costs 8 stack bytes.
//
// ---------------------------------------------------------------- SOLVED this
// round: the distance operand (old blocker 3).  want keeps `dot.flt.hi` in f31
// across GetInteger:
//       psq_st f0,0x30(r1) ; lfs f0,0x30(r1) ; fmr f31,f0 ; bl GetInteger ...
//       fcmpu cr0, f31, f0
// while the old draft reloaded it afterwards into a caller-saved FPR (`lfs f13`).
// The fix is to make the source READ the lane before the call, by giving it a
// name:
//       f32 dist = dot.flt.hi;            /* <- the load that fixes the home */
//       GetInteger(...);
//       if (dist < (f32)(f64)sp2C) ret = 1;
// A value live across a call has to sit in a callee-saved FPR, so ngccc copies
// it into f31 and the comparison becomes exactly want's `fcmpu cr0, f31, f0`
// (NOT `fcmpu cr0, f0, f31` — so do not also swap the comparison operands).
// `f32 dist` is slotless: the frame does not grow.  Cost today: +1 word,
// because the old post-call `lfs` is gone but a 2-word `lfs`+`fmr` is added.
//
// ---------------------------------------------------------------- why parked
// ONE blocker left, and it is a ProDG-PASS artefact, not a C-shape problem:
// **`&p` is homed in a callee-saved GPR and hoisted instead of being
//  rematerialised into r3 at the call.**  Mechanism, read out of the RTL
//  (`ngccc -da` writes `.rtl`, `.addressof`, `.combine`, `.lreg`, `.mach`):
//
//   1. After `expand` (dump `.rtl`) each MEM gets its own address pseudo:
//        (set (reg:SI 100) (plus:SI (reg:SI 78) (const_int 16)))   ; p.lo base
//        (set (mem/s:PS (reg:SI 100) 0) (mem/s:PS (reg:SI 78) 0))  ; p.lo = v.lo
//        ...
//        (set (reg:SI 174) (plus:SI (reg:SI 78) (const_int 16)))  ; &p, at the call
//      so `&p` is its own pseudo, defined immediately before the call — the
//      perfect shape for want's rematerialised `addi r3, r1, 0x18`.
//   2. ProDG's own **`addressof` pass** (dump `.addressof`) rewrites the MEM
//      addresses back to `(plus r1 off)` and MERGES the two identical address
//      expressions: reg174 disappears and its use becomes reg100.  Verified by
//      counting occurrences per dump: reg174 present in `.rtl`, gone in
//      `.addressof`.
//   3. The survivor is the LOWEST-numbered pseudo of the pair, i.e. p.lo's
//      MEM base, whose def is at p's FIRST access — before all eight
//      `fn_8006FA90` calls.  `.lreg` then reports
//        "Register 100 used 2 times across 60 insns in block 1; set 1 time;
//         crosses 9 calls; pref GENERAL_REGS"
//      and local-alloc gives it a callee-saved GPR (r29), which drags the
//      whole colour map down one (`stmw r27, 0x64(r1)` instead of want's
//      `stmw r28, 0x58(r1)`, `li r27`/`mr r3,r27` instead of `r28`, and every
//      `0x20(r1)`-relative stack offset +8/+0x10).  `sched` then hoists the
//      definition `addi r29, r1, 0x18` all the way to the top of the `if (m)`
//      block, which shifts the whole body by one word and leaves a `mr r3, r29`
//      at the call instead of want's `addi r3, r1, 0x18`.
//   4. Measured threshold (delete matrix calls one at a time, keep everything
//      else): **1 call between p's first access and the `&p` use -> the pseudo
//      is rematerialised (`addi r3, r1, 0x18`, 3 callee-saved GPRs); 2 or more
//      -> it is homed (`addi r29, r1, 0x18` + `mr r3, r29`, 5 callee-saved).**
//      So this is not "the allocator ran out of registers" — there were r27/r28
//      free in the 1-call case; it is the call-crossing priority.
//
// WHY BLOCKER 2 (the frame) IS NOT INDEPENDENT — it is the SAME root cause.
// The old draft's `ret` accumulator was blamed for a 12-byte hole in the locals
// (frame 0x90 instead of 0x80, int->double temp at 0x58 instead of 0x50).  That
// is wrong.  Measured on the real body:
//     * arg = `&p`   + `s32 ret` accumulator  -> frame 0x90, `stmw r27, 0x64`
//     * arg = `0`     + `s32 ret` accumulator  -> frame 0x80, `stmw r28, 0x58`
//     * arg = `&p`   + early `return 0/1`      -> frame 0x80, `stmw r28, 0x58`
//     * arg = `0`     + early `return 0/1`      -> frame 0x80
// The hole needs BOTH the accumulator AND the homed address pseudo — it is the
// 5th call-crossing GPR pseudo, not the accumulator.  `s32 ret` is required (want
// has one epilogue with three predecessors) and is slotless on its own, and an
// `f32 dist` scalar is slotless too.  Killing the `&p` pseudo therefore fixes
// the frame, the GPR map, the stmw base and the locals offsets at once.
//
// WHY THE MERGE CANNOT BE BROKEN FROM C (all measured, do not re-grind):
//   * `&p` and p.lo's MEM base are the SAME rtx expression
//     `(plus <v's base pseudo> 16)`.  There is no C spelling of `&p` that is
//     not also an address of something in `p`, and want does `psq_l`/`psq_st`
//     on 0x18(0x18 = p.lo) eight times, so p.lo's base pseudo always exists.
//     PS-mode MEMs get an address pseudo; SF/SI-mode MEMs do NOT (verified in
//     `.rtl`: the `stfs` of 1.0f is `(mem/s:SF (plus (reg 78) 28))`, inline).
//     So the only escape would be a spelling in which 0x18 is never addressed
//     as a PS pair — and want addresses it as a PS pair 6 times.
//   * Decoys that all re-merge (each verified by the resulting `addi r29`):
//     named pointer `V4 *q; q = &p;` passed as the argument; `q` assigned at the
//     top of the block with ALL p accesses through `q->` and `&p` still passed
//     (addressof normalises through `q` and merges); `&p.lo`, `(V4*)&p.lo`,
//     `(char*)&p + 0`, `p[0]`/`V4 p[1]` decay, `&v` (worse: emits `vsel`/VMX),
//     `V4 p[2]`/`PSU p[2]`, two separate `PSU p_lo/p_hi` (also scalarises the
//     16-byte copy into `lwz`/`stw` and moves the locals), `p = v` whole-struct
//     copy, `V4 volatile p`, swapping the `v`/`p` declaration order (moves the
//     pseudo even EARLIER, to before the fn_800626E8 call), `register V4 *q
//     __asm__("r3")` + `q = &p` (doc 85 §2's arg-remat pin — does NOT bind,
//     reconfirming §6cs-2), `register s32 ret`, `s32 ret = 0` initialiser,
//     `ret = cond ? 1 : 0`, `ret` declared last, `dist` as a second `f32`.
//   * Flags, all neutral: `-fno-schedule-insns2` (hoist moves 1 insn earlier
//     only), `-fno-schedule-insns` (moves it to 0x80195B8C, still wrong),
//     `-fno-delayed-branch`, `-fno-gcse`, `-fno-thread-jumps`,
//     `-fno-strength-reduce`, `-fno-expensive-optimizations` (652B), `-O3`,
//     `-fsigned-char`.  `-fno-cse`/`-fno-crossjumping`/`-fno-if-conversion`/
//     `-fno-tree-pre`/`-fno-merge-constants` are rejected by cc1.
//
// ---------------------------------------------------------------- next levers
// (a) CLOSED 2026-10-08: cc1.exe has NO pass-disable switch. `strings`
//       finds bare "addressof" at 0x1B33C8 only inside the RTX-code-name table
//       (rtx_name[], between 'queued' and 'symbol_ref') and ".addressof" as the
//       -da dump filename; the f_options table has no such entry, so
//       `-fno-addressof` cannot exist (GCC 2.95 strips the `no-` prefix and
//       matches the remainder against the table). Do not re-grep the binary.
//   (a) `combine` runs AFTER `addressof` but BEFORE `local_alloc`, so if the
//       merged pseudo ever reached it with a single use it would propagate
//       `plus(r1,0x18)` into the `movsi r3` and delete the hoisted `addi`.
//       The block is the merge, so this is only reachable by disabling or
//       reordering ProDG's `addressof` pass — worth grepping the ngccc binary
//       for a pass flag before spending another round on C shapes.
//   (b) A compiler-temp shape that reads 0x18/0x20 through a scalar-only view
//       so no PS-mode MEM of `p` is ever formed.  The `stfs 1.0f` at 0x24
//       proves scalar lvalues of `p` cost no address pseudo, but the 8
//       psq_l/psq_st pairs cannot be expressed any other way.
//   (c) If a future round prefers a size-exact object: delete the
//       `f32 dist = dot.flt.hi;` line and compare against
//       `dot.flt.hi` directly — that is the previous 640B / 13.8% body.  It
//       still needs (a) plus the one-word `fmr f31, f0` pair.
//
// family=m2c range=0x80195B14-0x80195D94 size=640B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

// 8-byte paired single with a scalar view on its two halves.
typedef union {
    __ps_t ps;
    f32 f[2];
} PSU;

// The 16-byte value fn_800626E8 writes and fn_800557B8 takes.
typedef struct {
    PSU lo;
    PSU hi;
} V4;

extern s32 GetChecksum_2(CStruct *, s32, s32 *, s32);
extern void *fn_8009F498(s32);
extern CStruct *GetChecksum_3(void *, s32);
extern void fn_800626E8(void *, void *);
extern s32 fn_8006FA90(s32, s32);
extern s32 fn_800557B8(V4 *, f32);
extern void *fn_801745B4(void *);
extern void *fn_80141964(void *);
extern V4 *fn_80024660(void *);
extern s32 GetInteger(CStruct *, s32, s32 *, s32);

extern __ps_t lbl_802AA0B8; /* {0.0f, 0.0f} */
extern f32 lbl_802AA100;    /* 1.0f */
extern f32 lbl_802AA104;    /* 6.0f */
extern void *lbl_80305EAC;

s32 fn_80195B14(Unk_C7387A53 *arg0) {
    V4 v;              /* r1+0x08 : fn_800626E8 output */
    V4 p;              /* r1+0x18 : matrix result + world pos handed to 0x800557B8 */
    __ps_t t0, t1, t2; /* r1+0x38/0x40/0x48 : the three muls0/madds accumulators */
    s32 sp28;          /* r1+0x28 */
    s32 sp2C;          /* r1+0x2C */
    s32 ret;
    SN_PS_type dot;    /* r1+0x30 : 1/sqrt(dist^2) accumulator */
    f32 dist;          /* want keeps dot.flt.hi here (f31) across GetInteger */
    void *m;           /* r31 */
    V4 *mtx;           /* r30 = m + 0x78 */
    V4 *up;            /* player position, r1+0x68 of the return of 0x80024660 */

    ret = 0;
    GetChecksum_2(arg0->unk0x20, QB_FILM_TARGET, &sp28, 1);
    m = fn_8009F498(sp28);
    if (m != 0) {
        mtx = (V4 *)((char *)m + 0x78);
        fn_800626E8(&v, *(void **)((char *)GetChecksum_3(m, QB_MODEL) + 0x210));
        /* 16-byte copy, then force .w of the second half to 1.0f. */
        p.lo.ps = v.lo.ps;
        p.hi.ps = v.hi.ps;
        p.hi.f[1] = lbl_802AA100;

        /* 4x4 matrix times (x,y,zw): two separate calls per column, one per half. */
        t2 = __builtin_ps_muls0(((V4 *)fn_8006FA90((s32)mtx, 0))->lo.ps, p.lo.ps);
        t1 = __builtin_ps_muls0(((V4 *)fn_8006FA90((s32)mtx, 0))->hi.ps, p.lo.ps);
        t0 = __builtin_ps_madds1(((V4 *)fn_8006FA90((s32)mtx, 1))->lo.ps, p.lo.ps, t2);
        t2 = __builtin_ps_madds1(((V4 *)fn_8006FA90((s32)mtx, 1))->hi.ps, p.lo.ps, t1);
        t1 = __builtin_ps_madds0(((V4 *)fn_8006FA90((s32)mtx, 2))->lo.ps, p.hi.ps, t0);
        t0 = __builtin_ps_madds0(((V4 *)fn_8006FA90((s32)mtx, 2))->hi.ps, p.hi.ps, t2);
        p.lo.ps = __builtin_ps_madds1(((V4 *)fn_8006FA90((s32)mtx, 3))->lo.ps, p.hi.ps, t1);
        p.hi.ps = __builtin_ps_madds1(((V4 *)fn_8006FA90((s32)mtx, 3))->hi.ps, p.hi.ps, t0);

        /* transform into world space, then hand the point to 0x800557B8. */
        p.lo.ps = __builtin_ps_add(p.lo.ps, ((V4 *)((char *)m + 0x58))->lo.ps);
        p.hi.ps = __builtin_ps_add(p.hi.ps, ((V4 *)((char *)m + 0x58))->hi.ps);
        if (fn_800557B8(&p, lbl_802AA104) == 0) {
            up = fn_80024660(fn_80141964(fn_801745B4(lbl_80305EAC)));
            t0 = __builtin_ps_sub(((V4 *)((char *)m + 0x58))->lo.ps, up->lo.ps);
            t1 = __builtin_ps_sub(((V4 *)((char *)m + 0x58))->hi.ps, up->hi.ps);
            t0 = __builtin_ps_mul(t0, t0);
            t1 = __builtin_ps_merge00(t1, lbl_802AA0B8);
            dot.ps = __builtin_ps_madds0(t1, t1, t0);
            dot.ps = __builtin_ps_sum0(dot.ps, dot.ps, dot.ps);
            dot.ps = __builtin_ps_rsqrte(dot.ps);
            dot.ps = __builtin_ps_res(dot.ps);
            dist = dot.flt.hi;
            GetInteger(arg0->unk0x20, QB_MAX_DISTANCE_TO_TARGET, &sp2C, 1);
            if (dist < (f32)(f64)sp2C) {
                ret = 1;
            }
        }
    }
    return ret;
}