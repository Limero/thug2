// PARKED 2026-10-30: 41.78% -> 97.3% (4 words).
//
// ScriptResizePark @ 0x80234588, 584B, 146 instructions. Object is LENGTH-EXACT
// (584B = symbols.txt size:0x248) and the only residual is ONE `sched` slot:
//
// The only residual is a four-word ordering tie at 0x8023469C-0x802346A8.
// The reference emits the r10 constant load first (the fourth instruction of
// the block) followed by the r26 byte store to 1(r11), the r11-to-r27 copy,
// and the r0 byte store to 8(r1). This build emits the identical four
// operations with the constant load last instead of first.
//
// The constant is the 4th of six `stb`s in source order (b1,b0,b2,b4,b3,b5) and
// want's `sched` hoists `movimm` 3 slots past its RTL slot; ngccc hoists it 0.
// Same instruction multiset, same order of every other insn, same registers.
//
// DIAGNOSIS (cc1 -dr, the §6bz/§6ek-3/§6bw method): the post-reload RTL already
// has the `movimm` born at its SOURCE slot (insn 187/195, mid-store-group), so
// the front end is NOT the problem and no source permutation can move the RTL
// position of the def. This is a `sched` hoist-distance tie, the same class as
// §6ep's "post-reload RTL already agrees -> sched2 cost tie" and §6do's
// COND_EXPR `li`-slot. NOT re-grindable by statement order or flags.
//
// EXHAUSTED on the final body (all measured, all byte-identical or worse):
//  * source: store order (b1,b0,b2,b4,b3,b5 = want's emission order, unique),
//    all four `lbz` staging positions, `p = q` at 4 positions in the then-block
//    and 4 in the else-block, `p` as scratch-vs-home, `q`-vs-`s8.` for the
//    word store, both copy blocks' value staging (4 shapes each)
//  * `volatile` on the b4 lvalue, via `q` and via `s8`; named `u8 one` constant
//    at 5 source positions, with and without a `"+r"` barrier
//  * 3 zero-emission `"+r"` barriers on v0/v1/v2/v3/p/q, and empty volatile /
//    memory-clobber / zero-byte fences immediately before the b4 store
//  * `register u8 one __asm__("r10")` pin, and a 1-insn opaque
//    `__asm__("li %0,1" : "=r"(one))` birth (no gain AND it breaks the
//    zero-asm budget — and note the FIRST measurement of it looked like EXACT
//    only because of a stale .o, the §6fj LEAF_TMPDIR hazard)
//  * 16 flags: -fno-schedule-insns (63%), -fno-schedule-insns2 (83%),
//    -Os (88%), -O1 (12%), -fno-expensive-optimizations (20%), and 11 neutral.
//
// THE THREE LEVERS THAT GOT HERE (each worth a double-figure jump — all
// standard, all worth re-reading §6* for before the next 90% draft):
//  1. §6db frame arithmetic: `locals = stwu_N - 16 - 4*nSavedGPRs` sized the two
//     6-byte `PK` objects + five s32 exactly; one `char` array beats `_dummy`.
//  2. §6dc/§6di/§6bf callee audit: `fn_80240B0C` returns `void *`,
//     `fn_802381E0` is 2-arg and its arg0 is the CHAINED `fn_80238964()`
//     (recipe 23), and 4 GetInteger sites are field-passes. Each undeclared or
//     mis-arity callee costs a spurious `crclr cr1eq`.
//  3. §6fs/§6fu: the DELAYED arm's `return 1` must be a SHARED tail, i.e. the
//     whole tail as if/else with ONE trailing `return 1` (a `goto block_12` is
//     byte-identical, 21 diffs vs 38 before). A separate `return 1` inside the
//     arm materialises a `li r3,1` in that block, +1 word, and cascades ~40
//     diffs through every following region.
//  4. §6cw/§6fg/§6s-1: ONE zero-code `"+r"` barrier on `p` right after `p = q;`
//     is worth 6 words — without it GCC coalesces the copy away and puts the
//     stores on the callee-saved home (r27) instead of retail's scratch (r11).
//  5. §6fs/§6fu staging: `wv`/`hv` temps in BOTH copy blocks make both loads
//     precede both stores (the second block needs the SAME shape as the first).
//  6. §6ds-2/§6df: a `register u16 hv __asm__("r11")` on the else-block halfword
//     fixes an r0<->r11 swap; pinning EITHER member of the pair works (it's an
//     OR, not an AND), and pinning the word to r0 works too.
//
// AUDIT of the 97.3% body: object `.text` 0x248 = 584B = symbols.txt size:0x248
// = header marker; only `.text` + `.rela.text` (no private `.rodata`, so
// masked-EXACT would also be promote-clean — no doc-14 pool caveat); ZERO
// emitted instructions (3 barriers + 1 register var); all 8 intra-function
// branch relocations verified by the §6bw method (4x R_PPC_REL14 addends
// 0x50/0x140/0x19c/0x1cc/0x218 -> 0x802345D8/0x802346C8/0x80234724/0x80234754/
// 0x802347A0, plus 2 local `b` at .text+0x168/.text+0x230/.text+0x234, all equal
// to want's decoded targets); `lbl_803A3158`/`lbl_803A3160` are real `.bss`
// symbols and want's `lis -0x7fc6` + `+0x3158`/`+0x3160` decode to them, so the
// hazard-277 masked-wrong-label case cannot apply; all 8 QB hashes hand-decoded
// from want's `lis`/`ori` pairs (0xB4F88771/0x7323E97C/0x9D2D8850/0xE39CF4ED/
// 0x69F93D01/0x937EB5C8/0x6F2C496C/0xA9967819) and they are plain immediates,
// so the 97.3% byte-verifies them. Compiles warning-free.
//
// NEXT LEVER, untried: a volatile-asm BRANCH WINDOW is not applicable (no
// branch here), so the only remaining route is a 1-insn opaque `li` birth
// *combined with* a source change that makes its RTL slot earlier — e.g. giving
// b4's value a data dependency on a web born in the preheader so `sched` must
// have it ready by slot 4. A bare opaque birth alone was measured inert.
//
// WHY SOURCE PLACEMENT CANNOT DO IT (re-derived from the emitted streams):
// retail's `li r10,1` sits after the three value loads and before the first
// store, i.e. it is hoisted three slots above the only store that reads it,
// while this build emits it immediately before that store. `flow` sinks a
// one-use constant definition down to its single use in both builds, so the
// def is at the same RTL slot; only the scheduler's hoist distance differs.
// Moving the def by hand therefore needs the value to have a SECOND RTL use
// (which would add an instruction and break the exact 584B size), not a
// different statement position — consistent with the inert named-local,
// pinned-register and barrier results listed above.
//
// family=m2c range=0x80234588-0x802347D0 size=584B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "qb_constants.h"
extern s32 lbl_803A3158;
extern bool lbl_803A3160;
s32 GetStructure_2(void *, s32, void *, s32);
s32 GetInteger(void *, s32, void *, s32);
s32 ContainsFlag(void *, s32);
void Script_RunScript(s32, s32, s32, s32, s32);
void *fn_80240B0C(void *, s32, s32, s32, s32, s32, s32);
void fn_802340AC(void *, void *);
s32 fn_80238964(void);
s32 fn_802381E0(s32, void *);
void fn_80234444(void *);

typedef struct { u8 b0; u8 b1; u8 b2; u8 b3; u8 b4; u8 b5; } PK_b;
typedef struct { u32 w; u16 h; } PK_w;
typedef union { PK_b b; PK_w w; } PK;
typedef struct { u32 w; u16 h; } GL;

bool ScriptResizePark(s32 arg0) {
    PK s8;
    PK s10;
    s32 sp18;
    s32 sp1C;
    s32 sp20;
    s32 sp24;
    s32 sp28;
    PK *p;
    PK *r10;
    u32 wv;
    u16 hv;

    if (lbl_803A3160 == 0) {
        fn_80240B0C(&lbl_803A3158, 0, 0, 0, 0, 0, 0);
        lbl_803A3160 = 1;
    }
    fn_80240B0C(&s8, 0, 0, 0, 0, 0, 0);
    sp18 = 0;
    if (GetStructure_2(arg0, QB_NEWBOUNDS, &sp18, 0) != 0) {
        GetInteger(sp18, QB_X, &sp1C, 0);
        GetInteger(sp18, QB_Z, &sp20, 0);
        GetInteger(sp18, QB_W, &sp24, 0);
        GetInteger(sp18, QB_L, &sp28, 0);
        {
        u8 v0, v1, v2, v3;
        PK *q;
        v0 = *(u8 *)((char *)&sp1C + 3);
        __asm__("" : "+r"(v0));
        v1 = *(u8 *)((char *)&sp20 + 3);
        q = &s8;
        q->b.b1 = 0;
        p = q;
        __asm__("" : "+r"(p));
        s8.b.b0 = v0;
        q->b.b2 = v1;
        v2 = *(u8 *)((char *)&sp24 + 3);
        v3 = *(u8 *)((char *)&sp28 + 3);
        q->b.b4 = 1;
        q->b.b3 = v2;
        q->b.b5 = v3;
        }
    } else {
        r10 = &s10;
        fn_802340AC(r10, arg0);
        {
        PK *q = &s8;
        register u16 hv __asm__("r11");
        hv = r10->w.h;
        q->w.h = hv;
        q->w.w = s10.w.w;
        p = q;
        }
    }
    if (ContainsFlag(arg0, QB_DELAYED) != 0) {
        ((GL *)&lbl_803A3158)->h = p->w.h;
        lbl_803A3158 = s8.w.w;
    } else {
        if (ContainsFlag(arg0, QB_USE_STORED) != 0) {
            s8.w.w = lbl_803A3158;
            p->w.h = ((GL *)&lbl_803A3158)->h;
        }
        r10 = &s10;
        wv = s8.w.w;
        hv = p->w.h;
        s10.w.w = wv;
        r10->w.h = hv;
        if (fn_802381E0(fn_80238964(), r10) == 1) {
            wv = s8.w.w;
            hv = p->w.h;
            s10.w.w = wv;
            r10->w.h = hv;
            fn_80234444(r10);
        } else {
            Script_RunScript(QB_PARKED_SHOW_OUT_OF_MEMORY_MESSAGE, 0, 0, 0, 0);
            return false;
        }
    }
    return true;
}
