// WIP DRAFT (non-matching) — semantic C reconstruction
// family=m2c range=0x801F21A8-0x801F2320 size=376B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// FLAG: -mps-float
//
// PARKED 2026-10-02 (w75/0x801F21A8): the ONE residual is the way retail
// rematerialises the waypoint address. Want computes the entry pointer with
// TWO instructions at each of its THREE use sites —
//   At the top site the want shifts arg1 left by 5 into r29 at 0x1BC,
//   copies arg0 into r30 at 0x1C0, adds them into r9 at 0x1C4, and adds
//   0x120 at 0x1CC (r9 there is also the seventh argument of the first
//   call). The `if` write-back adds the same two registers into r9 at
//   0xC0 and adds 0x120 at 0xC4, and the `else` write-back repeats that
//   pair at 0x134/0x138.
// so `arg1<<5` (r29) and `arg0` (r30) are the two long-lived callee-saved
// operands and the FULL pointer (0x120 included) is a *rematerialisable*
// pseudo that reload re-emits per site (hence disp 0/8, not 288/296). Every C
// spelling instead CSEs `arg0 + (arg1<<5)` into ONE callee-saved pseudo and
// folds 0x120 into the psq displacement: `slwi r0,r4,5 | add r30,r3,r0` +
// `288(r30)` / `296(r30)` + one `addi r9,r30,0x120` for the call arg. That is
// 5 instructions shorter (348B vs 376B object) and it is the sole length gap;
// everything downstream of 0x14 shifts, which is why the positional score
// cannot move (12/94). The stmw/lmw span (want r26..r31 = 6, got r27..r31 = 5)
// and the `or. r26,r3,r3` colour of `result` are consequences of the same
// decision, not independent defects.
// Tried (each measured, none > 12.8%): raw per-site deref with no ENTRY macro;
// `((char*)arg0 + 0x120) + arg1`; `((GoalPoint*)((char*)arg0+(arg1<<5)))[9]`;
// `&((GoalPoint*)arg0)[9 + arg1]`; `sizeof`-multiply; `long`/u32 arithmetic;
// block-local pointers (separate `e`/`f` in each arm); staged `base`/`off`/
// `p120` locals before the call (recipes 123); struct-member array at 0x120
// (-> indexed `psq_lx`, frame 0x128, much worse). All 20 collapse to the same
// single callee-saved sum pseudo. A minimal probe (same 8-arg call shape,
// address used at 3 sites straddling 4 calls) confirms it is not a
// whole-function-pressure artefact.
// KNOWN-GOOD EXPERIMENT, NOT KEPT (recorded so nobody re-derives it): retail
// does NOT CSE the four `point -> upper/lower` copies — it re-loads the pair
// twice (`psq_l f0,8(r1)` before both `psq_st 24(r1)` and `40(r1)`, and
// `psq_l ..,8(r10)` before both `32(r1)` and `48(r1)`), 8 words total, while
// plain C emits 6 (one load feeding two stores). Declaring the copy source
// `volatile __ps_t point[2]` reproduces want's 8-word block VERBATIM
// (order too: load,store,load,store,load,store,load,store with the `lfs/stfs`
// margin fixups interleaved between them), but costs 2 extra words overall and
// drops the official score 12.8% -> 5.3%, so it is left out per house rule
// (never leave load-bearing scaffolding that does not buy a match).
// Confirmed-correct and worth keeping: frame 0x120 / stfd f31 @0x118 / LR
// @0x124; query at r1+0x38 with result[2] at +0x88 and link at +0xA8; waypoint
// record stride 0x20, 0x20-byte array at arg0+0x120, only its first 16 bytes
// (one `__ps_t[2]`) are read/written; `upper` at r1+0x18, `lower` at r1+0x28,
// `point` at r1+0x8; margin = lbl_802AE2B4 loaded once into f31 and re-added
// to upper[0].y in the retry arm; `result` kept callee-saved because the second
// fn_80107B20 return would clobber r3 and `query.link = result` happens at the
// very end; fn_8010794C takes all 8 args (r4-r8 = arg1..arg5, r9 = entry,
// r10 = &point).
#include "types.h"
#include "structs.h"

typedef struct {
    __ps_t position[2];
    char pad0x10[0x10];
} GoalPoint;

typedef struct {
    char pad0x00[0x88];
    __ps_t result[2];
    char pad0x98[0x10];
    CStruct *link;
    char pad0xAC[0x14];
} GoalQuery;

extern f32 lbl_802AE2B4;
extern void fn_8010794C(void *, s32, s32, s32, s32, s32, void *, void *);
extern void fn_80107A8C(__ps_t *, __ps_t *);
extern void fn_80107AA0(__ps_t *, __ps_t *);
extern s32 fn_80107B20(Unk_E9DCA07D *, s32, void *);
extern void CObject_RemoveRefLink(void *, void *);

void fn_801F21A8(Unk_7258DEBD *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    GoalPoint *entry;
    __ps_t point[2];
    __ps_t upper[2];
    __ps_t lower[2];
    GoalQuery query;
    f32 margin;
    s32 result;

    entry = (GoalPoint *)((char *)arg0 + (arg1 << 5) + 0x120);
    point[0] = entry->position[0];
    point[1] = entry->position[1];
    upper[0] = point[0];
    lower[0] = point[0];
    upper[1] = point[1];
    lower[1] = point[1];
    margin = lbl_802AE2B4;
    ((f32 *)upper)[1] += margin;
    ((f32 *)lower)[1] -= margin;
    fn_8010794C(&query, arg1, arg2, arg3, arg4, arg5, entry, point);
    fn_80107A8C((__ps_t *)&query, upper);
    fn_80107AA0((__ps_t *)&query, lower);
    result = fn_80107B20((Unk_E9DCA07D *)&query, 1, 0);
    if (result != 0) {
        entry->position[0] = query.result[0];
        entry->position[1] = query.result[1];
        if (query.link != 0) {
            CObject_RemoveRefLink(query.link, &query.link);
            query.link = 0;
        }
    } else {
        ((f32 *)upper)[1] += margin;
        fn_80107A8C((__ps_t *)&query, upper);
        fn_80107AA0((__ps_t *)&query, lower);
        if (fn_80107B20((Unk_E9DCA07D *)&query, 1, 0) != 0) {
            entry->position[0] = query.result[0];
            entry->position[1] = query.result[1];
        }
        if (query.link != 0) {
            CObject_RemoveRefLink(query.link, &query.link);
            query.link = result;
        }
    }
}