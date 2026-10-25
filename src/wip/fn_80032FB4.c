// PARKED 2026-10-03 (b52): NEAR 75.2% (was DIFF 9.4%).
// LEAF_TMPDIR=<scratch> tools/venv/bin/python tools/test_wip_drafts.py --addr 0x80032FB4
// Length is now EXACT: .text == 484B == symbol size in symbols.txt, 121 vs 121
// instructions, and every out-param address (0x08/0x0c/0x10/0x14/0x18), the
// float->int scratch (0x38), frame 0x68, `stmw r27`@0x44, f30/f31 @0x58/0x60
// and the LR slot @0x6c all match. 43 real (non-reloc) words still differ,
// all of them REGISTER-CHOICE or a 2-word loop-exit idiom — see below.
//
// What got here (each measured):
//  1. DECLARE EVERY CALLEE (13 sites). m2c's implicit declarations made ngccc
//     emit `crclr cr1eq` before each `bl`; 13 junk words shifted the tail.
//  2. THE FOUR GUARD CALLS ARE CHAINED (b12's fn_80032388 finding, generalised):
//     each of GetChecksum_3 / fn_800cbe08 / GetStructure / GetArray receives
//     the PREVIOUS call's result as its arg0 — r3 is simply left holding it, so
//     the want shows no `mr r3` before the `bl`. m2c dropped arg0 on all four.
//     Ground truth: 0x8009fdd8 does `lwz r3,0x110(r3)`, 0x80125954 passes r3 to
//     0x80125480, 0x801285a4 does `mr r31,r3`. Also `fn_80033530` is a leaf
//     getter (`lwz r3,0x68(r3); blr`) and its RETURN is arg0 of GetChecksum_3.
//  3. Return type is VOID, not `void *`: the want has ONE shared epilogue with
//     no r3 materialisation, which is only possible if the return value is dead.
//     With `void *` ngccc needs a phi and emits four separate exits.
//  4. DISTINCT temp names per call result (recipe 106) — one shared temp makes
//     the 2nd..4th results get a saved-register home (`or. r30,r3,r3` + copy-back).
//  5. `lbl_802917E0` is stored by ADDRESS (`extern char []`), not by value —
//     m2c's `extern char []` assigned through a `s32` load produced `lwz`.
//  6. The second loop is a `for`, not do/while: the want carries BOTH the entry
//     test (`cmplw r28,r0 / bge exit`) and the latch test (`cmplw / blt body`).
//  7. ONE address-taken out-param block (recipe 113) instead of five scalars.
//     Frame arithmetic (recipes §"frame size is a closed-form tell"):
//     stwu 0x68 = 8 + locals + 4*5 GPRs + 8*2 FPRs  =>  locals region = 0x3c.
//     Want: out-params at 0x08..0x18, `stfd f13` scratch at 0x38, 4-byte tail.
//     ngccc leaves a fixed 12 bytes of slack after the last object, so
//     36 bytes must precede the scratch => a NINE-word block (`args[9]`).
//     Five separate scalars land them at 0x08 correctly but shrink the frame to
//     0x58; `volatile s32`/`volatile double` pads always steal slot 8
//     (recipe 105) and push sp8 to 0x18.
//  8. The element-ctor loop needs a `last = (ctr == 0)` temp between the two
//     stores (m2c had it): `while (ctr--)` inserts an extra `mr r0,ctr` copy
//     in the loop (7 words), and `while (ctr != 0)` with a trailing `ctr--`
//     gets converted by ivcanonize into `mtctr`/`bdnz`.
//
// REMAINING DIFF (43 words, all register colour or the exit idiom):
//  A. The redundant `if (n != 0)` at 0x80033050/54 is DELETED by ivcanonize
//     (trip count = ctr_init+1 = n is derivable from `ctr = n - 1`), and its
//     2 words come back as `subfic r7,r3,0; adde r0,r7,r3` (ngccc's
//     `ctr == 0` => `!(ctr u< 0)` rewrite feeding `cmpwi r0,0`). Tried and
//     failed to keep the guard: moving `ctr = n - 1` inside the guard,
////    `last = (ctr != 0)`, `last = !ctr`, `last = (ctr-1) != -1`, u32 ctr,
//     u8/registered `last` — all 484B/484B but the same 43 diffs.
//  B. Element ctor loop: want `cmpwi r10,0 / addi r10,r10,-1`; got compares
//     the canonicalised r0 and decrements r3. The array base also lands in
//     r10 (`addi r10,r3,8`) where the want keeps it in r3.
//  C. Loop counter / byte-offset registers are SWAPPED: want i=r28, off=r29;
//     got i=r29, off=r28. This is invariant under declaration order, source
//     assignment order, typeswap (s32/u32), role swap and hoisting `i = 0` /
//     `off = 0` earlier — it looks like a `global_register_alloc` ordering
//     coin-flip that is probably downstream of B.
//  D. The `0` stored to `p->unk0x10` is `li r0,0`+`stw r0` in the want and
//     `li r8,0`+`stw r8` here (same allocation family as B/C).
// UPDATE 2026-10-15: pins fix the colour directly (75.2% -> 76.9%):
// `register r28` on i + `register r29` on off restores want's i=r28/off=r29
// (the whole 0x800330A8+ loop/exit region is now byte-exact, including
// `add r3,r3,r29`, `addi r29,0x14`, `cmplw r28,r0`); `register r31` on n
// restores n's home (the pins stole it: n borrowed off's future r29).
// The `last` temp is load-bearing against a DIFFERENT failure: deleting it
// (plain do-while) lets ivcanonize take mtctr/bdnz AND drop the guard (DIFF).
// Remaining: A/B (guard-deletion + subfic/adde + mid-body CR0 test — needs a
// zero-insn CR0-resident temp, inexpressible in C; tried plain do-while =>
// mtctr DIFF), init-scheduling scatters, D (li r0 vs li r8, same family).
// MOST PROMISING NEXT IDEA: B and C are both register-colour; they likely flip
// together if A can be fixed. `subfic/adde` is `simplify_gen`/`find_equivalences`
// acting on a do-while whose exit test is at the TOP of the body; breaking the
// `ctr = n - 1` -> trip-count chain (e.g. initialising the counter through a
// path ivcanonize cannot see, or testing `p` against a precomputed end while
// still decrementing ctr) should restore both the `cmpwi r31,0 / beq` guard and
// the plain `cmpwi ctr,0`.
// WIP DRAFT (non-matching) — C body generated by tools/fill_wip_drafts.py
// family=m2c range=0x80032FB4-0x80033198 size=484B
// FLAG: -fno-schedule-insns
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

/* The element array: +0x8 is a vtable pointer, +0x10 is a flag word. */
extern char lbl_802917E0[];
extern f32 lbl_80291B50;
extern f32 lbl_80291B54;

/* Every callee must be DECLARED: an undeclared callee makes ngccc emit
   `crclr cr1eq` before each `bl`, which is one extra word and shifts the whole
   tail (recipes / finding 1). */
void *fn_80033530(void *);                 /* leaf getter: r3 = arg0->unk0x68 */
void *GetChecksum_3(void *, u32);         /* hash walk, arg0 = chained result */
void *fn_800cbe08(void *);                 /* arg0 = chained result */
void *GetStructure(void *, s32);           /* arg0 = chained result */
s32 GetArray(void *, CStruct *, void **, s32);
void *Mem_Alloc(s32);
void *fn_80129528(void *, s32);
s32 GetInteger(void *, u32, s32 *, s32);
s32 GetFloat(void *, u32, f32 *, s32);
s32 GetChecksum_2(void *, u32, s32 *, s32);
s32 GetStructure_2(void *, u32, s32 *, s32);
void fn_8002c43c(void *, s32, s32, s32);
void fn_8002ba5c(void *, s32);

void fn_80032FB4(CStruct *arg0, CStruct *arg1) {
    /* ONE address-taken out-param block (recipe 113) — see note 7 above.
       Nine words so the block ends at 0x2b and the float->int scratch lands
       at 0x38 with frame 0x68. */
    union {
        void *p;
        s32 i;
        f32 f;
    } args[9];
    s32 last;
    void *t0;
    void *t1;
    void *t2;
    void *t3;
    void *t4;
    register s32 n __asm__("r31");
    s32 ctr;
    register s32 off __asm__("r29");
    register u32 i __asm__("r28");
    void *v;
    void *p;
    f32 f30;
    f32 f31;

    /* The four guard calls are CHAINED: each one receives the previous
       result as its arg0 (r3 is simply left holding it), exactly like the
       allocator/ctor chaining in fn_80032388. */
    t0 = fn_80033530(arg0);
    t1 = GetChecksum_3(t0, QB_ANIMBLENDER);
    if (t1 != NULL) {
        t2 = fn_800cbe08(t1);
        if (t2 != NULL) {
            t3 = GetStructure(t2, 1);
            if (t3 != NULL) {
                t4 = GetArray(t3, arg1, &args[0].p, 0);
                if (t4 != NULL) {
                    n = ((CStruct *)args[0].p)->unk0x4;
                    arg0->unk0x70 = n;
                    if (n != 0) {
                        t4 = (void *)Mem_Alloc(n * 0x14 + 8) + 8;
                        ctr = n - 1;
                        *(s32 *)((char *)t4 - 8) = n;
                        p = t4;
                        /* Redundant test, but the want keeps it (see note A).
                           The `last` temp is load-bearing: a plain do-while
                           lets ivcanonize derive the trip count and emit
                           mtctr/bdnz (DIFF). */
                        if (n != 0) {
                            do {
                                ((CStruct *)p)->unk0x8 = (s32)lbl_802917E0;
                                last = ctr == 0;
                                ((CStruct *)p)->unk0x10 = 0;
                                ctr -= 1;
                                p = (char *)p + 0x14;
                            } while (last == 0);
                        }
                        f30 = lbl_80291B50;
                        f31 = lbl_80291B54;
                        i = 0;
                        off = 0;
                        arg0->unk0x6C = (s32)t4;
                        /* `for`, not do/while: the want carries BOTH the entry
                           test (cmplw r28,r0 / bge exit) and the latch test
                           (cmplw r28,r0 / blt body). */
                        for (; i < (u32)arg0->unk0x70; i++) {
                            v = fn_80129528(args[0].p, i);
                            args[1].i = 0;
                            if (GetInteger(v, QB_FRAME, &args[1].i, 0) == 0) {
                                args[2].f = f30;
                                GetFloat(v, QB_TIME, &args[2].f, 1);
                                args[1].i = (s32)(args[2].f * f31);
                            }
                            GetChecksum_2(v, QB_EVENT, &args[3].i, 1);
                            args[4].i = 0;
                            GetStructure_2(v, QB_PARAMS, &args[4].i, 0);
                            fn_8002c43c((void *)(arg0->unk0x6C + off), args[1].i, args[3].i, args[4].i);
                            fn_8002ba5c((void *)(arg0->unk0x6C + off), 1);
                            off += 0x14;
                        }
                    }
                }
            }
        }
    }
}