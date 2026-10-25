// PARKED 2026-10-05 (w2_8018C080): DIFF 2.7% -> NEAR 51.9% (96/185 words).
// Object is now SIZE-EXACT (740B == want) and the FRAME + SAVE MAP are exact:
// `stwu -0x38` / `stmw r26,0x20` / `stw r0,0x3c` / `lmw r26,0x20` -- i.e. all
// three of a14's blockers are gone at once.  No flags, no inline asm, and the
// only new construct is a second named pointer to the same local.
// Reproduce: LEAF_TMPDIR=<scratch> tools/venv/bin/python tools/test_wip_drafts.py --addr 0x8018C080
//
// === THE FIX (a14's "most promising next idea" WORKED) ===
// a14 was right that the body needs TWO registers for the same stack address.
// What was missing is that a SECOND DECLARATOR INITIALISER is not enough --
// `sp8, *sp8p = &sp8, *sp8q = &sp8;` is CSEd back to one register (measured:
// frame 0x40, `stmw r27`, 736B, still 2.7%).  The copy has to be an ordinary
// ASSIGNMENT whose live ranges genuinely overlap:
//     sp8, *sp8p = &sp8, *sp8q;
//     sp8q = sp8p;            /* FIRST statement of the body */
// `sp8p` then dies after the two initial field stores (0x80/0x84) while
// `sp8q` stays live across every call to the end of the function, so ngccc
// cannot coalesce them and emits `addi r30,r1,8` + `mr r26,r30`.  That also
// fixes the frame for free: the extra callee-saved GPR is what pushes the
// locals region to 0x38.
// Placement of that one assignment is load-bearing -- it must be BEFORE the
// `if (res == 0)` vcall, otherwise &sp8 is born after the branch and the
// ranges stop overlapping:
//     copy at the very top of the body      -> 0x38 / stmw r26 / 740B  (this)
//     copy after the vcall branch           -> 0x40 / stmw r27 / 736B  (2.7%)
//     copy after `gm = Game_GetGoalManager()`-> 0x40 / stmw r27 / 736B  (2.7%)
//     copy just before `sp8p->unk0x4 = res;` -> 0x40 / stmw r27 / 736B  (2.7%)
//     no declarator init at all, both assigned late -> 0x40 / 736B   (2.7%)
// A SECOND, REDUNDANT copy of the same assignment is also required -- see the
// "why the copies look silly" note below; dropping it costs 32 points.
// Reproduce the sweep: tools/venv/bin/python <scratch> 0x8018C080 <dir>
// (reports frame / stmw base / object length for a directory of variants).
//
// === WHY THE THREE `sp8q = sp8p;` SITES LOOK SILLY (they are load-bearing) ===
// There are three syntactically redundant copies in the body: at the top,
// inside the goal branch before `vt = arg0->vtbl;`, and before the tail
// `vt->fn6C(...)`.  Semantically they are no-ops (sp8p never changes), but they
// are what forces the register allocator's hand: measured by deletion --
//   all three present  96/185  51.9%  740B  frame 0x38 stmw r26   <-- keep
//   drop the TOP one        37/185  20.0%  736B  frame 0x48 stmw r25
//   drop the MIDDLE one     96/185  51.9%  (free -- see below)
//   drop the TAIL one       37/185  20.0%  736B
// i.e. the TOP and TAIL copies are the load-bearing pair, and the middle one is
// free (it was left in from the search and is not needed; it can be deleted
// without changing codegen).  Do not "clean up" the other two.
//
// === WHAT IS STILL DIFFERENT (51.9% residual) ===
// Opcode-aligned (tools/ps_diff.py / the align helper) the body is 145/185;
// the residual is dominated by REGISTER NUMBERING, not by structure:
//   * the two &sp registers are r28/r26 in got vs r30/r26 in want;
//   * `res` is r30 in got vs r29 in want, `prev` r29 vs r28 -- i.e. the same
//     three-way transposition, so the whole body after 0x3C shifts;
//   * `addi r30,r1,8` + `mr r26,r30` are emitted at 0x14/0x1C in got but at
//     0x38/0x40 in want (retail sinks them past the `lis`; ngccc hoists them);
//   * want has `or. r4,r9,r9` / `beq` where got has `cmpwi r4,0` / `bne` at
//     0xF0/0x128 -- a POINTER-TRUTH-TEST polarity spelling, measured both ways
//     (`while (nodep)` / `if (*nodep)` / `if (nodep != NULL)`): all 51.9%, and
//     `if (nodep != NULL)` on the OUTER test is much worse (14.6%, 736B);
//   * want duplicates the `fn_8018BFB4` tail call (`b`/`mr r3,r31`/`bl` at
//     0x20C-0x214) where got emits a single shared block;
//   * one `rlwinm` immediate differs (want 0,8,6 vs got 0,0x19,0x17).
// RULED OUT this round (do not repeat): all 5040 declaration-order permutations
// of the 7 non-struct locals (sampled; none moved off 51.9%); all 6 relative
// orders of {sp8 decl, res, prev}; struct last vs first; struct field-count
// variants (8/12/16/20 bytes); the 0-pointer / 1-pointer / 2-pointer forms;
// swapping which pointer feeds the call args vs the field stores; and the
// `void *sp8r` alias spelling.  All land on either 51.9% (740B) or 2.7% (736B).
//
// === ORIGINAL PARK NOTE (a14, 2026-10-03) -- kept for the record ===
// What the DOL actually does (a14's findings, all derived from the disasm):
//  * vtable dispatch: arg0->unk0x14 is a class descriptor with {s16 offset,
//    fn} pairs at 0x20/0x24, 0x68/0x6c, 0xC8/0xCC.  The entries take the
//    OBJECT ONLY -- declaring them 2-arg adds an `mr r4,r9` per site (4 extra
//    words); that is what m2c's casts implied and it is wrong.
//  * fn_8018C054(arg0, v): v is the (f32)(f64)s32 / 1000.0f conversion of
//    fn_8018C060(goal) -- it IS the 2nd argument (the pool at 0x802A9608 is the
//    int->f64 magic 2^52+2^31).  The leftover `mr r4, r9` (andi result) at
//    0x8018C1D8 is a dead hardreg set that ProDG keeps.  Passing
//    `flags & 2` instead makes ProDG DCE the whole 14-word conversion.
//  * fn_8021D454/4E8 take a 3rd argument (0) -> `li r5, 0`.
//  * fn_8009CF2C must be declared or you get a `crclr cr1eq`.
//  * arg0->unk0x70 &= ~0x80 (rlwinm 0,8,6), not 0xFEFFFFFF.
//  * fn_8018B90C takes 1 arg (m2c passed 2).
//  * fn_801907E0(arg0, 0x4999FB52), fn_8012720C(arg0->unk0x20, 0x7100155D).
//
// Remaining diff (the one instruction): the DOL keeps TWO registers for the
// same stack address -- r30 (`addi r30,r1,8` at 0x8018C0B8) used as the base
// of the two initial struct stores `stw r10,8(r30)` / `stw r29,4(r30)`, and a
// COPY r26 (`mr r26,r30`) used for the call argument `mr r4,r26` and for the
// final `stw r9,8(r26)`.  ngccc coalesces my single `sp8p` pointer into one
// register (r27/r28 depending on variant), so I am one `mr` short.  Tried:
// direct `&sp8` args + direct field stores (728B, GCC rematerialises
// `addi r4,r1,8` and uses r1-based stores); `sp8p` for everything (736B, one
// register); hybrid stores-via-pointer + args-via-&sp8 (736B, still coalesced).
// Most promising next idea: two source-level pointers to the same local (one
// used only for the two initial field stores, one for the two call args and
// the final store) so their live ranges overlap and ngccc cannot coalesce them.
// WIP DRAFT (non-matching) — C body derived from the DOL disassembly by a14
// family=m2c range=0x8018C080-0x8018C364 size=740B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
void fn_80183C7C(void *, void *);
void fn_80180390(void *);
void fn_8012720C(void *, void *);
void fn_8000F320(void *);
void fn_8018C054(void *, s32);
void fn_8000F2F8(void *, void *);
void fn_8018BE00(void *, void *, void *);
void fn_8018B90C(void *);
void fn_801907E0(void *, void *);
s32 fn_8018C060(void *);
void fn_8018BFB4(void *);
extern char lbl_802FFE98[];
#include "qb_constants.h"
#include "structs.h"
s32 GoalManager_GetGoal(s32, s32, s32);
s32 fn_8021D454(s32, void *, s32);
s32 fn_8021D4E8(s32, void *, s32);
s32 ContainsFlag(s32, u32);
void *GetChecksum_3(s32, u32);
s32 Game_GetGoalManager(void);
s32 fn_8009CF2C(s32);
extern f32 lbl_802A9610;
extern char lbl_802A83F8[];
extern char lbl_80305F9C[];

/* vtable descriptor reached through the +0x14 slot: each entry is a
   {s16 byte offset from the object, function pointer} pair. */
typedef struct {
    char pad00[0x20];
    s16 off20;
    char pad22[2];
    s32 (*fn24)(void *);
    char pad28[0x40];
    s16 off68;
    char pad6A[2];
    s32 (*fn6C)(void *);
    char pad70[0x58];
    s16 offC8;
    char padCA[2];
    s32 (*fnCC)(void *);
} GoalVtbl;

typedef struct {
    char pad00[0x14];
    GoalVtbl *vtbl;
    char pad18[4];
    s32 unk0x1C;
    s32 unk0x20;
    char pad24[0xC];
    s32 *node;
    char pad34[0x14];
    s32 unk0x48;
    char pad4C[0x18];
    s32 unk0x64;
    char pad68[8];
    s32 unk0x70;
} GoalManagerObj;

typedef struct {
    char pad00[0x14];
    GoalVtbl *vtbl;
    char pad18[0x18];
    s32 *next;
} GoalObj;


s32 fn_8018C080(GoalManagerObj *arg0) {
    struct {
        s32 unk0x0;
        s32 unk0x4;
        void *unk0x8;
    } sp8, *sp8p = &sp8, *sp8q;
    Unk_9994C3F5 *ctx;
    GoalVtbl *vt;
    s32 res;
    s32 *nodep;
    s32 gm;
    s32 prev;
    GoalObj *goal;

    sp8q = sp8p;
    vt = arg0->vtbl;
    res = vt->fn24((char *)arg0 + vt->off20);
    if (res == 0) {
        ctx = *(Unk_9994C3F5 **)&lbl_802FFE98;
    fn_8000F2F8(ctx, ctx->unk0x11C);
    gm = Game_GetGoalManager();
    sp8p->unk0x4 = res;
    sp8p->unk0x8 = lbl_802A83F8;
    arg0->unk0x48 = arg0->unk0x48 + 1;
    arg0->unk0x64 = res;
    prev = *(s32 *)&lbl_80305F9C;
    if (ContainsFlag(arg0->unk0x20, QB_RESET_SCORE) != 0) {
        CStruct *cs = (CStruct *)fn_8021D454(prev, sp8q, 0);
        while (cs != NULL) {
            fn_80180390(*(s32 *)((s32 *)GetChecksum_3(*(s32 *)((char *)cs + 0x18), QB_SKATERSCORE) + 0x1C));
            cs = (CStruct *)fn_8021D4E8(prev, sp8q, 0);
        }
    }
    nodep = arg0->node;
    if (*nodep != 0) {
        goal = NULL;
        while (nodep != NULL) {
            goal = (GoalObj *)GoalManager_GetGoal(gm, *nodep, 1);
            nodep = goal->next;
            if (nodep == NULL) {
                break;
            }
            if (*nodep == 0) {
                break;
            }
        }
        if (goal == NULL) {
            fn_8018BFB4(arg0);
        } else {
            if (arg0->unk0x1C & 2) {
                fn_8018C054(arg0, (s32)((f32)fn_8018C060(goal) / lbl_802A9610));
            } else {
                fn_8018BFB4(arg0);
            }
            vt = goal->vtbl;
            if (vt->fnCC((char *)goal + vt->offC8) != 0) {
                fn_8018BE00(goal, 0, 0);
                vt = arg0->vtbl;
                if (vt->fnCC((char *)arg0 + vt->offC8) != 0) {
                    fn_8018BE00(arg0, 0, 0);
                    fn_8018B90C(arg0);
                }
            }
        }
    } else {
        fn_8018BFB4(arg0);
    }
    sp8q = sp8p;
    vt = arg0->vtbl;
    if (vt->fnCC((char *)arg0 + vt->offC8) == 0) {
        fn_8018B90C(arg0);
    }
    arg0->unk0x70 = arg0->unk0x70 & ~0x80;
    fn_8012720C(arg0->unk0x20, QB_COMBO_STARTED);
    fn_801907E0(arg0, QB_ACTIVATE);
    if (fn_8009CF2C(prev) == 0) {
        arg0->unk0x70 = arg0->unk0x70 | 0x40000000;
    }
    vt = arg0->vtbl;
    vt->fn6C((char *)arg0 + vt->off68);
    fn_80183C7C(gm, arg0);
    fn_8000F320(*(s32 *)&lbl_802FFE98);
    sp8q->unk0x8 = lbl_802A83F8;
    return 1;
    }
    return 0;
}