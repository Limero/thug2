// PARKED 2026-09-28 (r5 re-audit): still 97.6% (80/82). RESIDUAL = exactly 2
// words, at 0x8003F25C and 0x8003F264: the want places the float copy into f2
// from f31 first and the integer copy into r5 from r26 last, with the pair
// store of f0 at 24(r1) identically placed between them, while this body
// emits the two independent copies transposed around that store.
// i.e. the two independent arg-setup copies of the FIRST call are transposed
// around the (identically-placed) v1[0] pair store. Everything else in all 82
// words matches, including the psq_l/psq_st chain (0x50/0x5C/0x64/...), the
// frame 0x70, all saved-register homes (r29=v0, r27=v1, r26=v2, r28=arg0,
// r30=arg1, f31=farg0, r25/r24/r23=arg2/3/4) and all three bl targets
// (readelf .rela.text REL24 at +0x84/+0xD8/+0x12C == want's 0x8003F28C /
// 0x8003F2E0 / 0x8003F334). Family: doc-15 (expand_call arg-setup order).
//
// STRUCTURAL ANALYSIS (why it is only these 2 words): the psq_l/psq_st chain
// is anchored at the SAME absolute offsets in both streams, so the scheduler
// leaves exactly two free slots (0x58 and 0x60) around the v1[0] store, and the
// only question is which of the two copies takes the earlier slot. Call 1 is
// the only one of the three whose f1 argument needs no copy (f1 still holds
// farg0 from entry, so it is coalesced), leaving a single float copy that lands
// in the SECOND free slot; calls 2 and 3 need `fmr f1,f31` as well and put the
// first copy in the first slot / the second copy in the second slot, which is
// why they match verbatim. No source spelling, proto shape, argument staging,
// register pin or scheduling flag moves the call-1 float copy into the first
// slot. An asm route would need the whole 15-insn call-1 window frozen (a
// 3-insn window cannot be placed between mr r4 and the psq_l at +0x5C, and the
// psq_st's f0/r1 operands cannot be expressed without inventing loads), i.e.
// the banned ASM_FUNC pattern — NOT recommended; keep this parked.
// SCAFFOLDING AUDIT (earlier lever 1) — the pin is NOT stale, it is
// load-bearing: deleting `register s32 pv0 __asm__("r29")` and using v0
// directly collapses the frame (0x70 -> 0x68, stmw r24) and scores 7.3%.
// There are no `// FLAG:` lines and no __asm__ barriers in the body. So the
// only asm here is the r29 register var (0 emitted instructions).
// CALLEE ARITY AUDIT (earlier lever 2): fn_8003EF58 reads r3,r4,r5,r6,r7,r8
// (r28=r3, r29=r4, r30=r5, r25=r7, r26=r8, cmpwi r6) plus f1 (fmr f23,f1)
// and f2 (fdivs f13,f2,f23) — the 8-arg proto here is right. It also does
// `mr r10,r11` but never uses r10, so r11 is a dead read, not a 9th arg
// (adding one would only cost a `li r9`).
// RETURN-TYPE FLIP (lever 3, re-verified): void 97.6% / s32 85.4% / f32 89.0%.
// EXHAUSTED, all at the SAME 2 words unless noted (≈60 variants total over
// three sessions; the 2026-09-27 list plus this round's):
//   sources: staged float local for arg4, explicit (s32 *) cast on arg4,
//     decl-order swap p1/p2/pv0, (p2 = v2, p2) comma staging, arg4 = &v2[0],
//     pv2 pinned r26, arg3/arg4 as (f32)farg0, pin+staged-pointer,
//     p2/p1 block-scoped and late-assigned, p1 pinned r27, p1+p2 both pinned,
//     arrays passed directly (decay) for args 1/4, stores through p1/p2,
//     (f32)fa local for the f2 slot, v0 used directly instead of pv0 (84.1%),
//     v1/v2 stores swapped (87.8%), all-four-loads-then-stores (30.5%),
//     temp-mediated v1[0] store, volatile v1[0] store, `"+f"` barrier on a
//     staged f2 copy (91.5%), `"+r"`/`"=r"` 0-tied wedges on the p2 value
//     (87.8%), memory-clobber barrier before the call (15.7%);
//   proto matrix: pointer args as s32* / void* / __ps_t* / all-void*, trailing
//     ints as u32, ints all cast to s32, floats-first (95.1%), floats-last
//     (89.0%), 3-float dead arg (29.4%);
//   arity/order: an extra dead float arg, dead 9th arg;
//   flags (22 tried): -fno-sched-spec and -fno-sched-interblock leave it
//     untouched, and EVERY other flag collapses the function
//     (-fno-schedule-insns 79.3%, -fno-schedule-insns2 42.7%, both 22.0%,
//     -fno-thread-jumps/-fno-caller-saves/-fno-delayed-branch/-fno-weak/
//     -fno-defer-pop/-fno-expensive-optimizations 3.4%, -fno-omit-frame-pointer
//     0.8%); flag PAIRS (-fno-sched-spec±-fno-sched-interblock±-fno-gcse±
//     -fno-expensive-optimizations, all 3.4%) are no better.
// WIP DRAFT (non-matching) — real paired-single reconstruction
// family=m2c range=0x8003F208-0x8003F350 size=328B  (0x148 == symbols.txt size)
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// extra_cflags: -mps-float
// RECONSTRUCTED 2026-09-26: 80/82 words (97.6%) with tools/ps_diff.py.
// The five-GPR/one-float target copies arg0.xy plus three arg1 points into
// three 16-byte endpoints, then calls fn_8003EF58 for the three triangle edges.
// Frame, saved-register homes, all PS loads/stores, the second and third calls,
// and the epilogue now match. The callee-side prototype is deliberately
// float-first: (s32 *, s32 *, f32, f32, s32 *, s32, s32, s32), which matches
// the retail r3/r4/f1/f2/r5/r6/r7/r8 setup.
// The 2nd and 3rd calls match exactly (their f1 reloads give the ready list a
// first AND a second float copy to place, which lands like retail); call 1 has
// only one float copy and it takes the wrong of the two free slots.
// Plain-C 97.6% body retained — no emitted inline-asm instructions.
#include "types.h"
void fn_8003EF58(s32 *, s32 *, f32, f32, s32 *, s32, s32, s32);
void fn_8003F208(const __ps_t *arg0, const __ps_t *arg1, s32 arg2, s32 arg3, s32 arg4, f32 farg0) {
    __ps_t v0[2];
    __ps_t v1[2];
    __ps_t v2[2];
    register s32 pv0 __asm__("r29") = (s32)v0;
    __ps_t *p1 = v1;
    __ps_t *p2 = v2;

    v0[0] = arg0[0];
    ((__ps_t *)pv0)[1] = arg0[1];
    v1[0] = arg1[0];
    v1[1] = arg1[1];
    v2[0] = arg1[2];
    v2[1] = arg1[3];
    fn_8003EF58((const __ps_t *)pv0, p1, farg0, farg0, p2, arg2, arg3, arg4);

    v0[0] = arg0[0];
    ((__ps_t *)pv0)[1] = arg0[1];
    v1[0] = arg1[2];
    v1[1] = arg1[3];
    v2[0] = arg1[4];
    v2[1] = arg1[5];
    fn_8003EF58((const __ps_t *)pv0, p1, farg0, farg0, p2, arg2, arg3, arg4);

    v0[0] = arg0[0];
    ((__ps_t *)pv0)[1] = arg0[1];
    v1[0] = arg1[0];
    v1[1] = arg1[1];
    v2[0] = arg1[4];
    v2[1] = arg1[5];
    fn_8003EF58((const __ps_t *)pv0, p1, farg0, farg0, p2, arg2, arg3, arg4);
}
