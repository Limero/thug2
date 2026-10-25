// PARKED 2026-09-28 (b2_06): best 74.4% (was 74.4%). PS bone-accumulator. 34 diff words across
// 4 deep allocator/scheduler artifacts (GPR r27/r28 role swap, FPR colours, A-block schedule,
// reflink-cleanup addi-before-cmpwi). Prior agent swept all flags + source shapes; this
// session's named-local reflink cleanup is worse (46 words). Family: doc-15/regalloc + PS
// block placement. See the full residual analysis below.
// WIP DRAFT (non-matching) — FULL HAND-REBUILD 2026-09-27 from the want disasm.
// VERDICT: NEAR 74.4% (99/133 words), SIZE-EXACT 532B == retail 0x214.
//   (was 3.8% DIFF with an m2c husk of 8 dead `0;` stubs — that body is gone).
// Needs -mps-float: tools/test_wip_drafts.py --addr 0x800B6FCC (auto, __ps_t).
//
// WHAT THE REBUILD ESTABLISHED
// * The five opcode-4 words were hand-decoded, because capstone mislabels Gekko
//   paired-single and tools/ps_disasm.py prints them as `.word # op4`:
//   0x11206890 = ps_mr, 0x10000258/0x116B0258 = ps_muls0 (xo5=12),
//   0x118C002A/0x11AD582A = ps_add (xo5=21)  [AGENTS 6ai-152 / 6ax-218].
// * ps_muls0 is NOT reachable from plain `ps_t * f32` — ngccc emits ps_mul
//   (wrong opcode, and it also contracts the adds into ps_madd). Only
//   __builtin_ps_muls0 gives muls0. 99/133 -> this is the single biggest fix.
// * The muls0 SCALAR comes off a stack slot as a 16-BYTE pair load
//   (`psq_l f13, 408(r1)`) whose lane 0 is 0.001f, so the local must be read
//   through a __ps_t lvalue: `*(__ps_t *)&k[0]`. A plain `lfs` reads 4 bytes and
//   never matches. (Declaring the local as `__ps_t` and punning the *store*
//   ICEs cc1 — 6ai-154.)
// * Stack layout, all recovered from the frame: XForm A is 0xD0 at sp+0x08
//   (it has ps pairs at +0x88/+0x90 AND +0xC0/+0xC8), XForm B is 0xC0 at
//   sp+0xD8 (its +0xA8 reflink must land on sp+0x180 for fn_8010794C to
//   match), an 8-byte f32 k[2] at sp+0x198, and the two __ps_t product
//   temporaries reserve the two dead 8-byte slots at sp+0x1A0/0x1A8 — that
//   is exactly the 24 bytes needed to put stmw at sp+0x1B0 and give
//   frame 0x1D8 / f30@0x1C8 / f31@0x1D0 / LR@0x1DC.
// * 4800.0f has to be a NAMED local (`c4800`), otherwise ngccc reloads the
//   extern in both arms instead of homing it in the callee-saved f31 that
//   survives the three intervening calls.
// * The `goto have;` / label-inside-the-if shape is required: retail has TWO
//   fn_800B6578 call sites but only ONE fn_80107D7C site, and no `cmpwi sel`
//   guard — a shared `sel` pointer with a goto reproduces that exactly (a
//   plain `if (sel != NULL)` adds a test retail does not have).
// * The `r27 != 0` arm copies A+0x88 -> B+0x10 and A+0x90 -> B+0x18 (NOT
//   B+0x18 -> B+0x10, which is what the draft's first guess said).
//
// ONE DECLARATION-LEVEL REGISTER PIN (disclosed, per the task rules):
//   register char *ap __asm__("r29");
// Retail keeps &A live in r29 and uses `8(r29)` for every A+0x08 psq access
// while using fresh `addi rX,r1,8` for the A+0x00 call args. Without the pin
// ngccc rematerialises `addi r3,r1,8` at each of the four &A call sites, only
// 5 callee-saved GPRs survive (stmw r27,0x1B4), the frame collapses to
// 0x1D0, and every stack offset after sp+0x1B0 diverges. Adding the pin took
// 73.7% -> (with the __ps_t k read) 74.4% and fixed frame/save/LR offsets.
//
// PRECISE RESIDUAL (34 words, all allocator/scheduler, no semantic content):
//  1. GPR role swap, 7 words: want homes the s32 result in r27 and the second
//     &B web in r28; ngccc gives r28 to the result and r27 to &B
//     At 0x7034 retail copies r30 to r28 while the build copies it to r27,
//     and at 0x70A4 retail copies r3 to r27 while the build copies it to
//     r28. The zero compares at 0x70CC and 0x7160 therefore test r27 in
//     retail but r28 in the build, and the result moves at 0x7158 and 0x7184
//     read from r28 in retail but from r27 in the build.
//     Declaration-order permutations of r27/sel/t do not move it.
//  2. FPR colours, 4 words: 8.0f is f8 in want and f10 here; the k-pair copy
//     is f9 vs f11; the A+0x14 read-modify-write temp is f10 vs f0. Same
//     allocation-order family as (1) — one FPR-colouring shift cascades.
//  3. A-block schedule, ~14 words: want computes `lfs f10,0x1C(r1)` +
//     `fsubs f10,f10,f31` at 0x7058/0x7060 and only stores at 0x7094, and it
//     reloads A+0x08 at 0x7070 (before the A+0xC0 store) and sinks the
//     A+0xC8 store to 0x709C (last). ngccc does the reverse on all three:
//     the RMW lands at 0x70BC/0x70C4, the A+0x08 reload at 0x70AC, the
//     A+0xC8 store at 0x70B8. Source order already matches retail's store
//     order (A+0xC0, A+0x00, A+0x08, A+0x14, A+0x0C, A+0xC8), so this is
//     pure pre-REGALLOC block placement; -fno-schedule-insns2 / -fno-sched-spec
//     / -fno-gcse / -fno-schedule-insns / -fno-expensive-optimizations /
//     -fno-sched-interblock / -fno-thread-jumps all score WORSE (48.9% / 72.9%
//     / 39.1% / 11.4% / 60.9% / 72.9% / 72.9%) — do not re-run that ladder.
//  4. Reflink cleanup arg setup, 8 words: retail computes `addi r4,r1,0x180`
//     BEFORE `cmpwi r3,0` in both cleanup blocks; ngccc sinks it into the
//     branch body. A named `Link *pl` local did not change it.
//
// REMINDER for whoever finishes this: the masked compare hides every
// `lis`/`addi @ha/@l` address word (R_PPC_ADDR16_HA/LO), so a 100% masked
// score is NOT link-clean — re-check with `powerpc-eabi-readelf -r` and a
// full `tools/ninja build/G2TE52/main.dol` + `cmp` before promoting.
// family=m2c range=0x800B6FCC-0x800B71E0 size=532B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "structs.h"

extern f32 lbl_802989D0;   /* 0.001f  */
extern f32 lbl_802989D4;   /* 8.0f     */
extern f32 lbl_802989D8;   /* 4800.0f  */
extern f32 lbl_802989DC;   /* 48.0f    */
extern f32 lbl_802989E0;   /* 1.0f     */

/* 3-word reflink node at +0xA8 (fn_8010794C zeroes all three words). */
typedef struct {
    s32 a, b, c;
} Link;

/* Accumulatable XForm: 5 ps pairs, two u16 flags, reflink at +0xA8. */
typedef struct {
    __ps_t v00, v08, v10, v18, v20;
    char pad0x28[0x2C];
    u16 a54, a56;
    char pad0x58[0x30];
    __ps_t v88, v90;       /* 0x88, 0x90 */
    char pad0x98[0x10];
    Link link;            /* 0xA8 */
    char pad0xB4[0x0C];
    __ps_t vC0, vC8;       /* 0xC0, 0xC8  -> sizeof 0xD0 */
} XfA;

typedef struct {
    __ps_t v00, v08, v10, v18, v20;
    char pad0x28[0x2C];
    u16 a54, a56;
    char pad0x58[0x50];
    Link link;            /* 0xA8 */
    char pad0xB4[0x0C];
} XfB;                    /* sizeof 0xC0 */

/* arg0->0xC: the bone/target both accumulators are read from. */
typedef struct {
    char pad0x0[0x58];
    __ps_t v58, v60;
    char pad0x68[0x20];
    __ps_t v88, v90;
} Bone;

typedef struct {
    char pad0x0[0xC];
    void *u0C;             /* 0x0C */
    char pad0x10[0x18];
    f32 f28;               /* 0x28 */
    void *u2C;             /* 0x2C */
} Obj;

void fn_8010794C(XfA *);
void fn_80107A80(XfB *, s16, s16);
s32 fn_80107B20(void *, s32, void *);
f32 fn_80107D7C(void *);
void fn_800B6578(void *, void *, s32, f32);
void CObject_RemoveRefLink(CStruct *, CStruct *);

void fn_800B6FCC(Obj *arg0, s32 arg1, f32 farg0) {
    XfA A;
    XfB B;
    __ps_t p0;            /* dead frame slot, the sp+0x1A0 pair */
    __ps_t p1;            /* dead frame slot, the sp+0x1A8 pair */
    f32 c4800;            /* named so ngccc homes 4800.0f in f31 (callee-saved) */
    f32 k[2];
    s32 r27;
    void *sel;
    Bone *t;
    register char *ap __asm__("r29");

    fn_8010794C(&A);
    t = (Bone *)arg0->u0C;
    ap = (char *)&A;
    k[0] = lbl_802989D0;
    c4800 = lbl_802989D8;

    A.v00 = t->v58;
    *(__ps_t *)(ap + 8) = t->v60;
    A.v10 = t->v58;
    A.v18 = t->v60;
    p0 = __builtin_ps_muls0(t->v88, *(__ps_t *)&k[0]);
    p1 = __builtin_ps_muls0(t->v90, *(__ps_t *)&k[0]);
    A.vC0 = p0;
    A.v00 = A.v00 + p0;
    *(__ps_t *)(ap + 8) = *(__ps_t *)(ap + 8) + p1;
    ((f32 *)&A.v10)[1] -= c4800;
    ((f32 *)&A.v08)[1] += lbl_802989D4;
    A.vC8 = p1;

    r27 = fn_80107B20(ap, 0, 0);
    fn_8010794C(&B);
    fn_80107A80(&B, 0, 0x20);
    B.v00 = A.v00;
    B.v08 = *(__ps_t *)(ap + 8);
    ((f32 *)&B.v00)[1] += lbl_802989DC;
    if (r27 != 0) {
        B.v10 = A.v88;
        B.v18 = A.v90;
        ((f32 *)&B.v10)[1] -= lbl_802989E0;
    } else {
        B.v10 = A.v00;
        B.v18 = *(__ps_t *)(ap + 8);
        ((f32 *)&B.v10)[1] -= c4800;
    }

    if (fn_80107B20(&B, 0, 0) != 0) {
        fn_800B6578(arg0->u2C, &B, arg1, farg0);
        sel = &B;
        goto have;
    }
    if (r27 != 0) {
        fn_800B6578(arg0->u2C, &A, arg1, lbl_802989E0);
        sel = &A;
    have:
        arg0->f28 = fn_80107D7C(sel);
    }

    if (B.link.a != 0) {
        CObject_RemoveRefLink((CStruct *)B.link.a, (CStruct *)&B.link);
        B.link.a = 0;
    }
    if (A.link.a != 0) {
        CObject_RemoveRefLink((CStruct *)A.link.a, (CStruct *)&A.link);
        A.link.a = 0;
    }
}
