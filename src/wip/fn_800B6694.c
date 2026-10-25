// PARKED 2026-10-01: 88.55% -> 88.55% (no improvement; residual is a
// single `sched` window — see ADDENDUM at the bottom for the new proof
// that it is NOT source-reachable, and for the levers measured this round)
// family=m2c range=0x800B6694-0x800B68A0 size=524B
//
// WIP DRAFT (non-matching) — hand-rebuilt from the DOL disassembly 2026-09-27,
// head/tail rework 2026-09-29 (82.4% -> 88.55%).
//
// RETAIL 0x800B6694, size 0x20C (524B), 131 insns, void return.
// VERDICT: NEAR 88.55% (15/131 words differ). Compiled object == retail SIZE
// (524B), the whole frame, prologue, epilogue, all 10 bl call sites, the
// 3-way fn_800B62EC dispatch, the shared fctiwz conversion slot, the whole
// script-message tail AND the entire float store run now match. The whole
// residual is ONE block: the 21-word constant-load / register-colour preamble
// at 0x800B66B0-0x800B6700 (see RESIDUAL below).
//
// 2026-09-29 WIN (+6.1 points, two independent levers — see AGENTS §6cc):
//  A. `vp[3] = *(volatile f32 *)&lbl_802988F0;`  (the 1.0f constant load)
//     ngccc's sched pass hoists ALL `extern f32` constant loads to the top of
//     the entry block, so all five constants are simultaneously live and the
//     allocator needs 5 distinct FPRs with no reuse. A VOLATILE load is not
//     schedulable, so it stays at its statement; because the fmuls has
//     retired the 0.1f register by then, the allocator REUSES it for the 1.0f
//     — exactly retail's `lfs f0, -0x7710(r11)` after `fmuls f1,f1,f0`.
//     82.4 -> 83.2, and with the store-run order below 88.55.
//  B. `st.a0C = (s8)*(volatile s32 *)((char *)self->mgr + 0x18);`
//     With a plain `s32` load, cc1 narrows the RELOAD to the byte it needs and
//     emits `lbz r0, 0x1b(r9)` (byte 3 of the word!) instead of retail's
//     `lwz 0x18(r9)` + `stb`. A volatile load keeps the DECLARED width, so the
//     truncation happens on the store instead. 87.8 -> 88.55.
//  C. the float store run must be written vp[3], vp[2], vp[1] (NOT
//     vp[3],vp[1],vp[2]) for the 4 stfs to come out in retail's
//     0x30, 0x3C, 0x34, 0x38 order: 83.2 -> 84.0.
//  D. `st.a0C = ...` must be written BEFORE `st.a10 = arg2;` so the two
//     register-copy stores are not hoisted past each other: 84.0 -> 87.8.
//
// WHAT THE m2c BODY GOT WRONG (the four fixes worth ~78 points):
//  1. self+0x30..0x3C is a float[4] (a vec: 0.1f/30.0f/0.1f/1.0f, see
//     src/r2d_8029887C.c). The shared Unk_C7387A53 class types those slots
//     s32, so the s32 stores became fctiwz+stfd+stw conversion dances and a
//     phantom 8-byte stack slot. File-local SELF_t with f32 members fixes it.
//  2. The accumulator is `lbl_80303150 + Tmr_GetTime()` (0-arg global getter,
//     r3 = incoming arg0 left untouched). m2c invented 6 phantom call args.
//  3. fn_8021B55C's s32 RETURN must stay live into fn_8013DE78 (r3 is chained
//     through the tail call); declaring it void drops the chain.
//  4. fn_800B62EC is void 4-int/3-float. Its PROTOTYPE param order is written
//     interleaved (f32,s32,f32,s32,f32,s32,s32) — the register assignment is
//     byte-identical to the natural (s32 x4, f32 x3) order because PPC SysV
//     counts GPRs and FPRs in separate streams, but expand_call emits the arg
//     list in SOURCE order, and only the interleaved spelling reproduces
//     want's [r3][f1][r4][f2][r5][f3][r6][r7] setup. fn_800B62EC only reads
//     arg0 in its own body (see src/fn_800B62EC.c), so the callee's real
//     signature is unknowable and this is a per-caller decision (recipe 87 /
//     §7d-4). Worth +15.2 points on its own.
//  5. MSG_t carries a 0x1C tail pad so the object is 0x40 bytes: the args
//     block is 0x18 at sp+8, the message 0x40 at sp+0x20 and the shared
//     conversion temp lands at sp+0x60, giving the original 0x60-byte locals
//     area and therefore the original frame / save-block layout.
//     Worth +14.5 points; every other pad size (0x00..0x24) was tried and only
//     0x18/0x1C scored at all (tied; 0x1C used).
//
// LINK-SAFETY (re-audited 2026-09-29 with the §6bw branch-decode method;
// the compare masks relocations, so this has to be done by hand):
//  * All 10 bl sites match (Tmr_GetTime, fn_800B62EC x3, fn_8021D358,
//    fn_8022986C, fn_80137CB4, fn_8022A9D0, fn_8021B55C, fn_8013DE78), and all
//    5 intra-function R_PPC_REL14 addends (0xC4/0xF4/0x124/0x1EC/0x1EC) equal
//    retail's branch targets (0x800B6758/0x800B6788/0x800B67B8/0x800B6880 x2)
//    -> the control flow is byte-identical. (The addend is the target's
//    section offset, not target-minus-insn; tools/want_got.py renders the GOT
//    branch targets with the wrong base.)
//  * Every relocation is ADDR16_HA/LO, REL14 or REL24, i.e. all masked; the
//    @ha/@l pairs compute to retail's literals (0x802A0000 / -0x7720 etc.).
//  * All 15 undefined symbols already exist in symbols.txt: fn_800B62EC
//    (promoted src/), the fn_8013*/fn_8021*/fn_8022* callees, Tmr_GetTime
//    (scope:global), lbl_802988E0/E4/E8/EC/F0 (.rodata2, src/r2d_8029887C.c)
//    and lbl_80303150 / lbl_80305F9C (.data, src/dd_*.c).
//  * The object has a single .text section (0x20C = 524 B = symbols.txt
//    size:0x20C = the header marker's range) and NO .rodata/.data, so the
//    doc-14 pool-routing trap does not apply.
//  * 0 inline-asm instructions (no __asm__, no .long).
//
// RESIDUAL (15 words) -- one block: the constant-load / colouring preamble.
// The original sets up five float constants with page-address setups,
// interleaves two parameter home copies and the scale multiply among the
// loads, reuses one float register for the last constant, then runs four
// float stores plus a divide. This build has the same five constants, the
// same register colours (including the reuse) and the same four stores --
// but two loads come out in the opposite order, which swaps the page-register
// colours, and two loads sit above the multiply instead of below it, so the
// whole window is shifted by one to three slots. The remaining page-register
// difference follows from the same shift (shorter live ranges allow reuse).
//
// WHY THE LOAD ORDER CANNOT BE MOVED (verified, do not re-try these):
//  * cc1 -drtl/-dcombine shows the RTL order IS the source order, so the swap
//    is done by the SCHEDULER. Empirically the constant whose result has the
//    most USERS is pulled to the top of the block: E8 feeds two stfs and is
//    always emitted first no matter which statement order, declaration order
//    (incl. moving `temp_f1` before `vecY`), or which constants are volatile.
//  * `volatile` on the E0 / E8 / EC / E4 loads changes nothing (each stays in
//    its own statement slot but sched still orders them E8, E0, ...), and
//    marking all five volatile costs 2 words (17 vs 15).
//  * Every scheduler/optimisation flag is a no-op or a regression on this
//    body: -fno-schedule-insns 41.5%, -fno-schedule-insns2 71.8%, -Os 87.0%,
//    -fno-sched-spec / -fno-sched-interblock / -fno-gcse /
//    -fno-expensive-optimizations / -fno-crossjumping / -fno-thread-jumps /
//    -O3 all 88.55% (no change), -fno-rerun-cse-after-loop 9.1%.
//  * Statement-order / decl-order / inline-constant / single-expression
//    variants: 4-argument `secs = farg0*E0/E4` 8.7%, `vp[3],vp[2],vp[1]` run
//    (current) 88.55%, all six run permutations 84.7-88.55%, moving the
//    `self->v30` store to 3 different positions 70.2/85.5/88.55%, the
//    `vp = &self->v30` form 88.55%, inlining E0/E4/EC at their use sites
//    84.0-85.5%, `fr0`/`fr11`/`fr12`/`fr13` hard-reg pins on the five constant
//    locals 82.4-84.0% (the pins break the f0 REUSE that lever A bought).
//  * The one remaining 2-word item is the vp[1] (0x34) / vp[3] (0x3C) store
//    pair, which is emitted in the opposite order here; in all six run
//    permutations the LAST store of the run is hoisted to second position, so
//    no source order yields retail's order.
//  Next to try: an explicit dependency that keeps the E8 load from being
//  schedulable (e.g. routing vecY through a 1-bit bitfield or a struct copy
//  so its load is not a plain schedulable `lfs`), or a tiny volatile-asm
//  window around just the fmuls + first two lfs.
//
// ADDENDUM (2026-10-01) — the residual is PROVEN not source-reachable
// and the two "next to try" leads above are now closed as dead ends.
//  1. `cc1 -dr` (post-`reload` RTL) PROVES the front end already has retail's
//     load order when the 1000.0f multiply is written as the FIRST statement:
//     the `high:SI (symbol_ref:SI ...)` sequence reads lbl_802988E0, E8, EC, E4,
//     F0 — exactly retail's emission order. The object still emits them
//     E8, E0, E4, EC. So the swap is 100% `sched`, and the tie-break is the
//     AGENTS §6bg-recipe-8 priority = NUMBER OF USERS OF THE LOAD RESULT:
//     E8 (0.0f) feeds two `stfs` (self+0x30 and vp[2]/self+0x38) => priority 2
//     => always first; E0/E4/EC feed one each => follow in list order.
//     Consequently retail must have given E0 >= 2 users or E8 exactly 1, and
//     NEITHER is expressible without changing retail's instruction stream:
//     a second use of the 1000.0f adds an `lfs`/`fmuls`, and splitting the two
//     zero stores into two loads adds an `lfs`. The object is length-exact
//     (524 B == symbols.txt size:0x20C), so neither is available. This is the
//     real blocker; do NOT re-run statement-order / decl-order / flag ladders.
//  2. The FPR colours are ALREADY correct and are a pure function of the load
//     order: got has E8->f11 / E0->f0 / E4->f13 / EC->f12 / F0->f0(reuse) and
//     retail has E0->f0 / E8->f11 / EC->f12 / E4->f13 / F0->f0(reuse) — the
//     same five registers, the first two merely transposed. Fixing the load
//     order would fix the FPRs for free; there is nothing to fix there.
//  3. Constant-anchor hammer rejected with a mechanism: emitting all five
//     high-half constant setups as volatile asm with pinned page registers
//     plus volatile float loads reproduces the original anchor registers,
//     anchor positions, float colours and the last-constant reuse word for
//     word, but it destroys the parameter home copies: the original
//     interleaves two home copies among the schedulable loads, and a volatile
//     asm at the head of the block makes the prologue emit all six copies
//     first. Measured: unpinned anchors 74.05%, fully pinned 64.12%.
//  4. Volatile on the first-constant load plus that statement first is NOT
//     frame-neutral here (unlike lever A on the last constant): frame grows
//     one slot, save block grows one register, argument home rotates one step
//     => 3.23%. Do not retry.
//  5. Declaration-form levers inert this round: `extern const f32` for all
//     five (§6bt2) 77.86%; `extern char []` + `*(f32 *)` (§6ek) 88.55% (the
//     object is BYTE-IDENTICAL to base); `extern char []` + `*(s32 *)` for the
//     two `.data` globals (§6bc-1 L1) 88.55% (byte-identical). `vp` off
//     `self` instead of `arg0` 88.55%; `vp[1]/vp[2]` store swap 87.79%.
//  6. Statement order: putting the E0 multiply FIRST produces a
//     BYTE-IDENTICAL object to base (88.55%), which is the direct proof of (1).
//     `vecZ`/`timescale` order swaps 87.79%.
//  7. Flags independently re-confirmed inert: -fno-sched-spec,
//     -fno-sched-interblock, -fno-gcse, -fno-thread-jumps,
//     -fno-expensive-optimizations, -O3, -fconserve-space all exactly 88.55%;
//     -fno-schedule-insns 41.54%, -fno-schedule-insns2 71.76%, -Os 87.02%,
//     -mcpu=603 66.41%, -fno-rerun-cse-after-loop 9.92% are all WORSE.
//     `-fno-precompute-costs` and `-fno-crossjumping` do not exist in ProDG cc1.
//  UNLOCK HINT for a future attempt: the only remaining lever is to make E8's
//  load have ONE user without emitting an extra instruction — e.g. if the
//  second 0.0f store could be produced from a value already in a register
//  (it cannot in retail's own stream, f11 is the only 0.0f), or to make the
//  E0 load a 2-user priority-2 birth, which likewise needs an instruction
//  retail does not have. Treat this block as a `sched` user-count wall.
//
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "structs.h"

extern f32 lbl_802988E0;
extern f32 lbl_802988E4;
extern f32 lbl_802988E8;
extern f32 lbl_802988EC;
extern f32 lbl_802988F0;
extern s32 lbl_80303150;
extern s32 lbl_80305F9C;

extern s32 Tmr_GetTime(void);
/* interleaved param order: ABI-identical to (ptr,s32,s32,s32,s32,f32,f32,f32)
 * but reproduces retail's interleaved expand_call arg setup — see note 4. */
extern void fn_800B62EC(Unk_C7387A53 *, f32, s32, f32, s32, f32, s32, s32);
extern void *fn_8021D358(void *, u16);
extern s32 fn_8022986C(void *);
extern s32 fn_8022A9D0(void *);
extern s32 fn_8021B55C(void *, s32);
extern void fn_80137CB4(void *);
extern void fn_8013DE78(void *, void *);

/* self: mgr handle at +0xC, float[4] vector at +0x30 (NOT the shared
 * Unk_C7387A53 class, whose 0x30..0x3C are s32 by corpus majority vote). */
typedef struct {
    char pad0x0[0xC];
    s32 mgr;
    char pad0x10[0x20];
    f32 v30;
    f32 v34;
    f32 v38;
    f32 v3C;
} SELF_t;

/* 0x18-byte arg block handed to the script engine (msg.size == sizeof) */
typedef struct {
    s32 a00;
    s32 a04;
    s16 a08;
    s16 a0A;
    s8 a0C;
    char pad0xD[3];
    s32 a10;
    s8 a14;
    char pad0x15[3];
} ARGS_t;

/* script message header, fn_80137CB4's init shape; 0x1C tail pad for the
 * frame (see note 5) */
typedef struct {
    u8 cmd;
    u8 f01;
    u16 size;
    void *data;
    s32 f08;
    s32 f0C;
    u8 f10;
    char pad0x11[3];
    s32 f14;
    s32 f18;
    s32 f1C;
    u8 f20;
    char pad0x21[0x1C];
} MSG_t;

void fn_800B6694(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5,
                 f32 farg0, f32 farg1, f32 farg2) {
    SELF_t *self = (SELF_t *)arg0;
    f32 *vp;
    f32 vecY;
    f32 vecZ;
    f32 timescale;
    f32 temp_f1;
    f32 secs;
    f32 f_from;
    f32 f_to;
    s32 rsum;
    s32 node;
    s8 var_r25 = 0;
    ARGS_t st;
    MSG_t msg;

    vecY = lbl_802988E8;
    temp_f1 = farg0 * lbl_802988E0;
    vecZ = lbl_802988EC;
    timescale = lbl_802988E4;
    vp = (f32 *)((char *)arg0 + 0x30);
    self->v30 = vecY;
    secs = temp_f1 / timescale;
    vp[3] = *(volatile f32 *)&lbl_802988F0;
    vp[2] = vecY;
    vp[1] = vecZ;
    f_from = farg1;
    f_to = farg2;
    rsum = lbl_80303150 + Tmr_GetTime();
    if (arg3 != 0) {
        var_r25 = 1;
        fn_800B62EC((Unk_C7387A53 *)((char *)arg0 + 0x40), secs, rsum, f_from, arg1,
                    f_to - f_from, arg2, 0);
    }
    if (arg4 != 0) {
        var_r25 |= 2;
        fn_800B62EC((Unk_C7387A53 *)((char *)arg0 + 0xD4), secs, rsum, f_from, arg1,
                    f_to - f_from, arg2, 0);
    }
    if (arg5 != 0) {
        var_r25 |= 4;
        fn_800B62EC((Unk_C7387A53 *)((char *)arg0 + 0x168), secs, rsum, f_from, arg1,
                    f_to - f_from, arg2, 0);
    }
    node = lbl_80305F9C;
    rsum = (s32)fn_8021D358((void *)node, *(u16 *)((char *)self->mgr + 0x1A));
    if ((rsum != 0) && (fn_8022986C((void *)rsum) != 0)) {
        fn_80137CB4(&msg);
        node = fn_8021B55C((void *)node, fn_8022A9D0((void *)rsum));
        st.a00 = (s32)secs;
        st.a08 = (s16)f_from;
        st.a04 = arg1;
        st.a0A = (s16)(f_to - f_from);
        st.a0C = (s8)*(volatile s32 *)((char *)self->mgr + 0x18);
        st.a10 = arg2;
        st.a14 = var_r25;
        msg.data = &st;
        msg.size = 0x18;
        msg.cmd = 0x76;
        fn_8013DE78((void *)node, &msg);
    }
}
