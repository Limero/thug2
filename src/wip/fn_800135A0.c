// PARKED 2026-10-13: current best C remains size-exact at 192B and 66.7%.
// The else dispatch, prologue and return merge match; the remaining then-arm
// call setup differs in dataflow, not just order. Want stores and reloads
// arg0->unk0x0 across fn_8000DFA0 and keeps the dispatch record in its
// argument holder, while ngccc forwards the returned value and homes the
// record in a temp. A volatile
// field access restores the reload but disrupts allocation. Keep the semantic
// struct/prototype reconstruction below; no inline asm workaround.
//
// PARKED 2026-09-26 — 62.5% -> 66.7%, size-exact (192B). The whole
// prologue, the entire else-branch dispatch, the return-value merge and the
// epilogue now match byte-for-byte; the residual is ONE contiguous 19-word
// arg-setup block in the then-branch (a doc-15 class arg-setup / register-home
// coin flip). See "RESIDUAL" at the bottom for the exact 4-instruction
// statement of what differs and the search space already exhausted.
// family=m2c range=0x800135A0-0x80013660 size=192B
//
// SEMANTIC RECONSTRUCTION (all verified word-by-word against the DOL):
//
// Retail, in order:
//   arg0->unk0x14 = 6;
//   if (arg0->unk0x34 != 0) {
//       arg0->unk0x0 = fn_8000DFA0(arg0->unk0x34, 1);
//       lbl_802FFF10 += 1;
//       n = arg0->unk0x38 + 1;
//       arg0->unk0x38 = n;
//       d->unk0x14(arg0 + d->unk0x10, arg0->unk0x14, 0, arg0->unk0x0, 0, d, n);
//       ret = (arg0->unk0x0 != 0);
//   } else {
//       ret = d->unk0x2C(arg0 + d->unk0x28);  (falls into the shared epilogue)
//   }
//   return ret;
//
// FIX 1 — SEVEN-ARG dispatch, no phantom 8th (doc-52). m2c passed `0x80300000`
//   (the constant-setup half of the global's address) as an 8th argument. want
//   never writes the page anchor as an argument: the anchor only addresses
//   `lbl_802FFF10`. The call passes (this+off, this->0x14, 0, this->0x0, 0,
//   d, n) as its seven arguments.
//   Verified by score: 7-arg = 66.7%, 8-arg (counter) = 22.0%, 8-arg (0) = 28.6%.
// FIX 2 — the first call takes the ALREADY-LOADED field, not a bare literal:
//   the 0x34 field load is hoisted above the 0x14 store and feeds both the
//   branch test and the call.
// FIX 3 — mixed-width dispatch record (fn_8004CC88 lesson, and the same
//   `pad[0x10]/s16/s32` shape as the MATCHED sibling src/fn_80014AE8.c):
//   +0x10 and +0x28 are 16-bit signed, +0x14 and +0x2C are call targets.
// FIX 4 — explicit if/else with a SHARED `ret` (want's then-block falls
//   through into the true-value setup, the test goes to the else, both converge
//   on the epilogue). Early-return forms invert the block order (29.2%).
// FIX 5 (NEW 2026-09-26, the only one that changed bytes) — the dispatch
//   record local must be BLOCK-SCOPED, one per branch, not a single
//   function-top `d`. want homes the record in one holder in the then-branch
//   but in another in the else-branch, i.e. two disjoint variables; a shared
//   local merges the live ranges and GCC 2.95 colours both the same, which
//   costs 5 words in the else branch. `Wip135A0Disp *d` / `*d2` declared inside
//   their own blocks makes the else branch match EXACTLY: 62.5% -> 66.7%.
// FIX 6 — the counter is a NAMED local (`n = arg0->unk0x38 + 1; arg0->unk0x38
//   = n;`) so the call's 7th argument is the held register value retail keeps,
//   not a re-read of memory.
//
// RESIDUAL (16 words, all inside the then-branch's 19-word call-arg block;
// the 10-word prologue and the 17-word tail are exact):
//   (a) want emits the store of the call result IMMEDIATELY after the call,
//       because the result dies there. ngccc keeps the result live for the
//       call's 4th argument and sinks the store to after the global increment.
//       Root cause is (b).
//   (b) want RELOADS the dispatch's 4th argument instead of forwarding the
//       stored value (register copy in the build). GCC 2.95's delayed_store
//       folds the store/reload pair into a register copy. This is the SAME
//       just-stored-field-reread idiom the MATCHED sibling src/fn_8001347C.c
//       had to defeat, and its proven mechanism is volatile-qualified access
//       on BOTH the store and the re-read. Applying that here DOES emit both
//       target operations (store adjacent to the call plus reload), but it
//       then steers the dispatch record into the second-arg holder and the
//       score drops to 32.7%.
//   (c) consequently the record `d` is homed in a temp and copied to the 6th
//       argument holder, where want has it BORN in the 6th-arg holder and read
//       three times straight out of it (fn slot, offset slot, passed as the
//       holder). The temp home is forced by the page anchor for `lbl_802FFF10`,
//       which the build allocates to an argument holder — the anchor/record
//       home collision. want's split anchor/record allocation is the one where
//       the anchor pseudo is allocated AFTER the two argument pseudos; the
//       build's order is the reverse.
//   (d) want has a dead re-read of the counter between the counter store and
//       the fn-pointer load; ngccc emits no second read of the counter. This
//       is the same non-forwarding as (b) and is presumably a GCC 2.95
//       reload-pass artifact that only appears once (b) is reproduced.
//
// SEARCH SPACE ALREADY EXHAUSTED (every one scored <= 66.7%; the only thing
// that ever moved the number was FIX 5):
//   * counter shape: `x = x+1` / `x++` / `x = ++x` / local `n` / re-read at the
//     call site — ALL FOUR compile to the identical instruction stream (ngccc
//     CSEs them before allocation), so the counter is not a lever;
//   * global-vs-counter statement order: global first = 66.7%, counter first
//     = 27.1% (so global-first is right and is what is committed);
//   * record placement: before the call / after the call / after the counter /
//     function-top / read inline at each use site — best 62.5%, i.e. all worse
//     than block-scoped-after-the-call;
//   * dispatch fn-pointer prototype: 7 return/param type permutations
//     (s32/void return, pointer-typed zero args, pointer-typed 4th arg, all
//     pointer args) — all 66.7%;
//   * `fn_8000DFA0` signature: (s32,s32) / (void*,s32) / (s32,void*) /
//     (void*,void*) / u32 return / old-style — all 66.7%, old-style 26.5%
//     (so the 2-arg prototyped form is right);
//   * `arg0` typed `void *` with casts — 66.7%;
//   * parameter copied to a local, `(s32)0` zero args, `parmlocal` — 66.7%;
//   * 24 `-fno-*` singles + the 3 documented pairs (incl. the
//     `-fno-schedule-insns -fno-schedule-insns2` "source order" pair) — best
//     66.7% (`-fno-schedule-insns` actively drops to 31.2%), so this is an
//     ALLOCATION difference, not a scheduler one;
//   * hard-register pin on the record as a diagnostic — the pin is
//     dropped/mis-homed and the body drops to 64.6%, so the record cannot be
//     forced into its want holder without breaking the counter;
//   * volatile store only / volatile read only / volatile on the 0x14 pair /
//     volatile on the 0x34 test — 32.7% / 28.6% / 66.7% / 20.4%.
//
// REMAINING BLOCKER: doc-15 / doc-10 class. It needs GCC 2.95 to skip the
// store->reload forwarding of `arg0->unk0x0` (feature (b)) WITHOUT letting the
// volatile route perturb the register allocation (which is what the proven
// sibling mechanism does here). Retry if a per-object flag combination or a
// new source shape appears that reproduces the store+reload pair while keeping
// the record in its want holder and the page anchor split.
//
// WIP DRAFT (non-matching, best body) — parked 2026-09-26.
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
typedef struct Wip135A0Disp {
    char pad0x0[0x10];
    s16 unk0x10;
    s16 unk0x12;
    s32 (*unk0x14)(void *, s32, s32, s32, s32, void *, s32);
    char pad0x18[0x10];
    s16 unk0x28;
    s16 unk0x2A;
    s32 (*unk0x2C)(void *);
} Wip135A0Disp;
typedef struct Wip135A0Obj {
    s32 unk0x0;
    char pad0x4[0x10];
    s32 unk0x14;
    char pad0x18[0x1C];
    s32 unk0x34;
    s32 unk0x38;
    Wip135A0Disp *unk0x3C;
} Wip135A0Obj;
s32 fn_8000DFA0(s32, s32);
extern s32 lbl_802FFF10;

s32 fn_800135A0(Wip135A0Obj *arg0) {
    s32 ret;
    arg0->unk0x14 = 6;
    if (arg0->unk0x34 != 0) {
        Wip135A0Disp *d;
        s32 n;
        arg0->unk0x0 = fn_8000DFA0(arg0->unk0x34, 1);
        d = arg0->unk0x3C;
        lbl_802FFF10 += 1;
        n = arg0->unk0x38 + 1;
        arg0->unk0x38 = n;
        d->unk0x14((char *)arg0 + d->unk0x10, arg0->unk0x14, 0, arg0->unk0x0, 0, d, n);
        ret = 1;
        if (arg0->unk0x0 == 0) {
            ret = 0;
        }
    } else {
        Wip135A0Disp *d2;
        d2 = arg0->unk0x3C;
        ret = d2->unk0x2C((char *)arg0 + d2->unk0x28);
    }
    return ret;
}
