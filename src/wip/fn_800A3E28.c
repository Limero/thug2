// PARKED 2026-10-03 (b11): DIFF 17.57% masked (26/148 words); got 576B vs
//   want 592B (148 words). Baseline was DIFF 17.6% — UNCHANGED, the body below
//   is already instruction-for-instruction correct apart from two hard-reg
//   coin flips. Reproduce:
// LEAF_TMPDIR=<scratch> tools/venv/bin/python tools/test_wip_drafts.py --addr 0x800A3E28
//   tools/venv/bin/python tools/want_vs_got.py 0x800A3E28
//
// EXACT RESIDUAL: the entire function matches insn-for-insn, instruction
// SEQUENCE included, except 7 hard-register numbers and 4 missing `mr`s that
// are a direct consequence of ONE of them. Every branch, compare, shift,
// crclr-free call site, load/store displacement, block order and the whole
// 0x800A3FFC..0x800A405C tail are byte-identical.
//
// (1) `arg0->unk0x0` (the entry array) is coloured r10 by retail, r3 by the
//     build. RELOAD COALESCING: in the build the `e = base` / `hit = base`
//     init copies fold away because base's home reg IS r3, so loop A's two
//     cursors are `e`=r3, `hit`=r9. Retail keeps base in its own home r8
//     (call-clobbered, reloaded after the CStruct_delete call — see below),
//     which forces 3 extra `mr`s and 4 extra words:
//     Retail emits five register copies the build lacks: at 0x800A3E98 it
//     copies r10 to r8, at 0x800A3EA4 r0 to r10, at 0x800A3EBC r8 to r3, at
//     0x800A3F28 r8 to r9, and at 0x800A3F38 r10 to r8. The build emits none
//     of these (its e cursor simply lives in r3 as base, and at 0x800A3F28
//     it reloads r9 from 0(r31) instead of copying r8).
//     Because of the 4-word deficit everything from +1f0 on is laid out one
//     word early, so the (identical) tail is reported as differing too.
//     The base-reg choice is a GCC-2.95 reload/local-alloc preference tie
//     between r3 and r8 for two call-clobbered pseudos of equal priority.
//     Same class of wall as a04's parked fn_800A4C28 (see its PARKED block:
//     "GCC 2.95 local-alloc/pref-order coin flip, not a semantics bug").
// (2) In the grow/copy block retail keeps `old` in r30 (reusing the dead
//     `res` home — the only callee-saved reg left that dies before the
//     Mem_Alloc call) and the copy offset in the call-clobbered r4. The build
//     gives `old` r29 (the dead `key` home) and the offset r30. Same tie-break.
//
// RULED OUT (with reasons, don't re-try blindly):
//  (a) `base` as a real local (e.g. `Ent *base = arg0->unk0x0;`) — DEAD ON
//      ARRIVAL, provably. Retail homes base in r8, a CALL-CLOBBERED reg, and
//      re-reads it from memory after the call at 0x800A3EE8
//      (`lwz r9,0(r31); add r9,r28,r9`). A local would have to be callee-saved
//      or spilled (all 11 callee-saved regs are already taken by the 7 args +
//      res/flag/off/key). So base is a per-expression read of the field, which
//      is what the body does. (fn_800A49EC, matched, does keep its cursor in a
//      callee-saved reg — but that function has no call under the cursor.)
//  (b) Real `s32 n = 0` + `if (n != 0) { do {...} while (i < n); }` instead
//      of the `i = 0; if (i < n)` alias — tried (b11): got LONGER and worse,
//      564B, 141 words, 136 diffs. ngccc then spills `i` and re-emits the
//      zero-init; the `i = 0`/`cmpw r30,r0` register-sharing trick below is
//      load-bearing, exactly as the note at the bottom says.
//  (c) Inline `arg0->unk0x4` in the pre-tests to force the want's
//      `lwz r0,4(r31)` + `cmpw r30,r0` + `mr r10,r0` shape — not even worth
//      building: ngccc's CSE unifies the field read with the `n` local, so it
//      degenerates to the single `lwz r10, 4(r31)` the build already emits.
//      Any spelling that genuinely splits the two reads (e.g. re-reading
//      through a second pointer) is a semantics bug in this function.
//
// NEXT IDEA (orchestrator's call): both residuals are pure local-alloc coin
// flips and are only reachable with `register ... __asm__("rN")` pins on `e`
// (r3) plus a pinned copy of the array (r8), and on the copy-loop offset
// (r4). That is effectively hand-assigning the allocator, so b11 did not do
// it (brief rule 2). Everything else about this function is solved.
//
// WIP DRAFT (non-matching) — hand reconstruction from the retail disassembly.
// family=m2c range=0x800A3E28-0x800A4078 size=592B  (0x250 == symbols.txt
// size:0x250, so the marker is self-consistent)
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// SCORE: 17.57% masked (26/148 words), 576B built vs 592B retail (4 words
// short; see the PARKED block at the top for where they go).
// Was 2.7% (m2c draft) before this rewrite. The whole function TAIL,
// 0x800A3FFC..0x800A4058 (24 insns), is byte-identical instruction-for-
// instruction, and every callee-saved register (r21..r31) matches.
//
// BEST SCORE INSTRUCTION: ProDG cc1 allocates bitfields LSB-FIRST, and for a
// 1-bit field at bit 0 it folds the value's shift into the rlwimi ROTATE:
//   f->b0 = arg5;        ->  rlwimi rA, arg5, 0x1f, 0, 0
//   f->b1 = 0;           ->  rlwinm rA, rA, 0, 2, 0
// which is the retail pair verbatim. Writing the "obvious" `(arg5>>1)&1`
// instead makes cc1 materialise `srawi` into an extra callee-saved reg
// (-3.2% and a whole-register shift). Struct order must be {b0:1;b1:1;hi:30};
// MSB-first order puts the fields at bits 31/30 and cannot match.
// Second lever (from the byte-exact sibling fn_800A3D8C, same 0x14-stride
// family): guarded do-while with `i = 0; if (i < n) { do {...} while (i < n); }`
// plus a RAW byte-offset IV used offset-first (`*(s32 *)(off + arg0->unk0x0 +
// 4)`) reproduces the preheader-guard + latch double test and keeps `off`
// uns Strength-reduced. Loop A's loop-invariant hash must be a hoisted local
// (`s32 key = QB_NULL_SCRIPT;`) so it takes a saved reg — letting cc2
// rematerialise it drops one hard-reg candidate and shifts the whole
// allocation by one slot (-7%).
//
// PRECISE RESIDUAL (all one root cause, plus knock-on block offsets):
// 1. `arg0->unk0x0` (the array) is coloured r4 by the build but r10 by
//    retail. Retail's reload split then has to free r10 before the count can
//    live there, which is what produces the two extra copies retail has and
//    the build lacks:  `mr r8, r10`  (array copied into r8 for the loop-init
//    uses) and `mr r10, r0` (count loaded into r0, then copied into r10). The
//    build has no conflict (array r4, count r10) so it emits a bare
//    `lwz r10, 4(r31)`. This is a local-regalloc tie-break on two call-clobbered
//    pseudos of equal priority; it is not reachable from a source shape — four
//    variants were tried (s32-typed array local, extra `base = ...` alias,
//    assignment-in-condition, direct field use). The best of them is in the
//    body; the other three all regressed.
// 2. Knock-on effect of (1): the loop-A preheader is 4 words short and the
//    loop-B preheader lacks retail's `mr r8, r10`, so everything from
//    0x800A3F1C onward is laid out one word earlier than retail and the
//    byte-compare reports the (otherwise identical) tail as differing.
// 3. Inside the grow/copy block, retail keeps `old` in r30 (reusing the dead
//    `res` home) and the copy-loop offset in r4; the build uses r29 and r30.
//    That is the same tie-break, not a different bug.
// Everything else — the 4 induction variables of loop A and their increment
// order, loop B's dual cursor, the copy loop's batched loads + indexed first
// store + named `d` pointer, the subfic/adde fold, the cr4 call-preserved
// compare with mfcr/mtcrf, and the full tail — already matches.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern char lbl_80301A78[];

s32 Mem_Alloc(s32);
void Mem_Free2(void *);
void CStruct_delete(CStruct *, s32);
s32 CStruct_new(s32);
s32 fn_80126EDC(CStruct *, CStruct *);
void fn_800A5B64(CStruct *, s32, s32);

/* 0x14-stride array entry */
typedef struct {
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fC;
    s32 f10;
} Ent;

/* entry->0x10 low two bits (ProDG allocates bitfields LSB-first) */
typedef struct {
    u32 b0 : 1;
    u32 b1 : 1;
    u32 hi : 30;
} EntF10;

void fn_800A3E28(CStruct *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4,
                 s32 arg5, CStruct *arg6) {
    Ent *res = 0;
    Ent *e;
    Ent *hit;
    s32 flag = 1;
    s32 i;
    s32 n;
    s32 off;

    if (arg0->unk0x0 == 0) {
        arg0->unk0x4 = 1;
        arg0->unk0x0 = Mem_Alloc(0x14);
        res = (Ent *)arg0->unk0x0;
    } else {
        n = arg0->unk0x4;
        i = 0;
        if (i < n) {
            s32 key = QB_NULL_SCRIPT;
            off = 0;
            e = (Ent *)arg0->unk0x0;
            hit = (Ent *)arg0->unk0x0;
            do {
                if (e->f0 == arg2) {
                    s32 v = e->fC;
                    res = hit;
                    if (v != 0) {
                        CStruct_delete((CStruct *)v, 3);
                    }
                    flag = ((*(s32 *)(off + arg0->unk0x0 + 4) ^ key) == 0);
                    goto tail;
                }
                i++;
                hit = (Ent *)((char *)hit + 0x14);
                e = (Ent *)((char *)e + 0x14);
                off += 0x14;
            } while (i < n);
        }
        i = 0;
        if (i < n) {
            char *fp = (char *)arg0->unk0x0 + 4;
            e = (Ent *)arg0->unk0x0;
            do {
                if (*(s32 *)fp == QB_NULL_SCRIPT) {
                    res = e;
                    goto tail;
                }
                i++;
                fp += 0x14;
                e = (Ent *)((char *)e + 0x14);
            } while (i < n);
        }
        {
            Ent *old = (Ent *)arg0->unk0x0;
            Ent *src;
            s32 coff = 0;
            arg0->unk0x0 = Mem_Alloc((n + 1) * 0x14);
            i = 0;
            if (i < (s32)arg0->unk0x4) {
                Ent *d;
                src = old;
                do {
                    s32 a0 = src->f0;
                    s32 a4 = src->f4;
                    s32 a8 = src->f8;
                    s32 ac = src->fC;
                    d = (Ent *)(coff + arg0->unk0x0);
                    *(s32 *)(coff + arg0->unk0x0) = a0;
                    d->f4 = a4;
                    d->f8 = a8;
                    d->fC = ac;
                    d->f10 = src->f10;
                    i++;
                    coff += 0x14;
                    src = (Ent *)((char *)src + 0x14);
                } while (i < (s32)arg0->unk0x4);
            }
            if (old != 0) {
                Mem_Free2(old);
            }
            n = arg0->unk0x4;
            res = (Ent *)((char *)arg0->unk0x0 + n * 0x14);
            arg0->unk0x4 = n + 1;
        }
    }
tail:
    {
        EntF10 *f = (EntF10 *)&res->f10;
        res->f8 = arg4;
        f->b0 = arg5;
        f->b1 = 0;
    }
    if (arg6 != 0) {
        res->fC = fn_80126EDC((CStruct *)CStruct_new(8), arg6);
    } else {
        res->fC = (s32)arg6;
    }
    res->f4 = arg3;
    res->f0 = arg2;
    arg0->unk0xC = 1;
    if (flag != 0) {
        fn_800A5B64((CStruct *)*(s32 *)&lbl_80301A78, arg2, arg1);
    }
}
