// WIP DRAFT (non-matching) — body reconstructed from the retail CFG by hand
// family=m2c range=0x8004B314-0x8004B798 size=1156B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// PARKED 2026-10-05 (w2_8004B314): **86.41% masked (score_wip, index-aligned),
// 287-word object vs the 289-word symbol**; verdict NEAR. Supersedes the 74.6%
// body that was in this file (same day, w_8004B314): the better body was
// sitting unreferenced in that round's <scratch>, so the
// commit step lost it. Lesson: score every /tmp variant of a draft, not just
// the one that got written back.
//
// WHAT MOVED THE SCORE (+11.9): the outer loop is now `for (;;)` + `break`
// instead of `goto loop_37` + a trailing `done:` block, AND the
// `register s32 found __asm__("r24")` pin is GONE. Both halves are load-bearing
// together, which is why the previous round measured the pin as "load-bearing
// (277 vs 268)" and the `for(;;)` form as "makes the frame -0x58": pin +
// for(;;) together cost 3 registers (stmw r19, 69.3%), for(;;) alone costs 2
// (stmw r19, 86.4%), goto + pin costs 0 (stmw r21, 74.6%).
//   * The `for(;;)` shape is what reproduces retail's TAIL exactly: want
//     0x8004B74C..0x8004B778 is ONE block -- `cmpwi r24,0 / bne <notify> /
//     lwzx r0,r29,r30 / cmpwi r0,0 / bne <loop_37> / b <exit>` -- with the
//     notify call out of line. Any goto/tail form leaves `found` tested TWICE
//     (`cmpwi r24,0 / beq <exit>`) because ngcc will not thread the earlier
//     test, and that costs the 2 missing words.
//   * Only a single found-test is reachable if every exit of the inner `while`
//     lands on one block, hence `break` + a post-loop `if (found) break; if
//     (flags[idx]==0) break;`.
//
// RESIDUAL (39 diffs), all one cause -- the callee-saved register budget.
// want needs 11 (stmw r21,0x24(r1), frame -0x50); this body needs 13 (stmw
// r19,0x24(r1), frame -0x58) because GCC hoists the loop-head constant 0 into
// a callee-saved reg (got 0x8004B680 `li r20,0 / stwx r20,r26,r30` where want
// has `li r0,0 / stwx r0,r9,r3`) and puts the idx*4 loop-header copy in r26.
// With 2 extra callee-saved regs the whole colouring shifts and nothing below
// can line up:
//   want  r21 busy  r22 mgr  r23 nodes r24 found r25 fbase r26 const1
//         r27 arg0  r28 arg1 r29 flags r30 idx*4 r31 node
//   got   r19 busy  r20 const0 r21 mgr  r22 nodes r23 found r24 fbase
//         r25 const1 r26 idxweb  r27 arg0 r28 arg1 r29 idx*4 r30 flags r31 node
// (arg0/arg1/r31 already agree; flags and idx*4 are swapped.) Everything after
// the prologue diff is that shift -- including the 2 words still missing at the
// loop head (0x8004B66C `slwi r3,r3,2` vs `slwi r0,r3,2`; want's extra
// `mr r9,r29`) and the 2 missing preheader copies on the back edge (want
// 0x8004B758/0x8004B75C `mr r3,r30 ; mr r9,r29`, absent here) -- because retail
// keeps those two webs in CALLER-saved r3/r9 (so it must re-copy them at the
// latch) and this body puts the idx web in callee-saved r26 (so it does not).
// This is the docs/parkings/15 register-allocation wall (needs pins/asm) plus
// the parked "indexed-store address-slot permutation" class (recipes 182).
//
// RULED OUT (all measured on this body, none beat 86.41%):
//   * doc-88 two-webs-for-one-frame-address: declaring a second `s32 *flags2`
//     and copying with an ordinary assignment statement coalesces back to one
//     register at EVERY placement -- copy as first statement of the `if (fn_
//     8004C414...)` body (86.41), copy before the fn_800A3BDC call (86.41),
//     copy inside the loop head (86.41), double redundant copy (86.41), and
//     the reverse split (stores use `flags`, loads use `flags2`) (86.41).
//     This is doc-88's own carve-out: the address is never passed to a callee,
//     so both spellings have fully overlapping ranges. The one placement that
//     is NOT a copy -- materialising `flags2 = arg0->unk0x5B4` at function
//     scope so the copy is genuinely first -- costs a 14th register
//     (`stmw r20`, addi r26 in the prologue) and collapses to 0.70%.
//   * register pins on this body: flags->r29 83.3%, flags->r9 9.1%, idx->r30
//     5.2%, found->r24 69.3%, node->r31 0.35%. All worse.
//   * tail shapes: goto+`done: if(found)` re-tests found (74.6%); `if/else if`
//     59.1%; `goto notify`/`goto exit` with an explicit recheck block 59.9% and
//     59.4% (both also steal r27 from arg0 -> the whole map shifts);
//     `done: if (found==0 && flags!=0) goto loop` 74.6%; rotated `continue`
//     form 83.3%; do-while inner loop 71.9%.
//   * flags: -O3/-fno-expensive-optimizations/-fno-cse-follow-jumps/
//     -fno-regmove/-fno-move-all-movables/-fno-reduce-all-givs/-fno-peephole/
//     -fno-rerun-loop-opt/-fno-branch-probabilities/-fno-unroll-loops/
//     -fno-caller-saves/-fno-float-store/-fno-sched-interblock/-fsched-spec/
//     -fno-inline/-finline all 86.41% (no-ops here);
//     -fno-schedule-insns 84.0%, -fno-schedule-insns2 81.5%, -fno-thread-jumps
//     86.1%, -fno-gcse 70.8% (size!), -fno-rerun-cse-after-loop 85.4%,
//     -fno-strength-reduce 67.6%, -Os 2.8%, -O1 49.5% (but the only body that
//     is exactly 1156B), -fno-omit-frame-pointer 12.1%. The `// FLAG:` line is
//     correctly absent -- the plain default flag set is the best one.
//   * loop-head store spelling: `flags[idx]=0`, `*(flags+idx)=0`,
//     `arg0->unk0x5B4[idx]=0` (68.4%), `= (s32)0`, and `node =
//     *(arg0->unk0x5A4+idx)` (85.0%). Swapping the two loop-head statements,
//     `while (1)` for `for (;;)`, `if (flags==0) break` before
//     `if (found) break` (85.4%), and `found!=0 || flags==0` as one break are
//     all 86.41%.
//
// NEXT LEVER: if this ever comes back, attack the register BUDGET, not the
// body -- the body is now right. Either find a way to keep the loop-head
// constant 0 and the idx*4 loop-header copy out of callee-saved registers
// (that alone would fix frame, map, and all three residual sites at once), or
// accept it as a pins/asm park.
#include "qb_constants.h"

extern char lbl_80292914[];
extern f32 lbl_80292924;
extern s32 lbl_8030191C;
extern s32 lbl_80301A78;

typedef struct ScriptEnt {
    char pad0x0[0x18];
    s32 unk0x18;
} ScriptEnt;

typedef struct ScriptNode {
    ScriptEnt *unk0x0;
    char pad0x4[0x8];
    s32 unk0xC;
    struct ScriptNode *unk0x10;
    s32 unk0x14;
    s32 unk0x18;
} ScriptNode;

typedef struct ScriptCtx {
    char pad0x0[0x5A4];
    ScriptNode *unk0x5A4[4];
    s32 unk0x5B4[4];
    char pad0x5C4[0xF4];
    s32 unk0x6B8[48];
    s32 unk0x778;
    s32 unk0x77C;
} ScriptCtx;

typedef struct ScriptMsg {
    s32 unk0x0;
    s32 unk0x4;
    s32 unk0x8;
    s32 unk0xC;
    void *unk0x10;
} ScriptMsg;

typedef struct RefLink {
    void *f0;
    s32 f4;
    s32 f8;
} RefLink;

s32 fn_8004C840(ScriptCtx *);
s32 fn_8004C414(ScriptCtx *, s32);
s32 GetInteger(void *, s32, s32 *, s32);
s32 fn_8009D364(void *, s32);
void *fn_80125A08(s32, s32);
s32 GetChecksum(void *, s32);
void GetElement_2(RefLink *, ScriptCtx *, s32, s32);
s32 fn_80042110(void *);
s32 fn_80042180(void *);
s32 fn_8004C858(ScriptCtx *, s32);
void fn_8004C410(ScriptCtx *, ScriptNode *);
void fn_8004BFE4(ScriptCtx *, RefLink *, s32);
void fn_8004C110(ScriptCtx *, RefLink *, s32, s32);
void fn_8004C2DC(ScriptCtx *, RefLink *);
s32 fn_800A3BDC(ScriptMsg *);
void fn_800A3B44(ScriptMsg *, s32, s32);
void fn_800A3B90(ScriptMsg *, s32, s32);
void CObject_RemoveRefLink(void *, RefLink *);
s32 fn_800A54AC(s32, s32, s32, s32, s32, s32, f32);

void fn_8004B314(ScriptCtx *arg0, ScriptMsg *arg1) {
    RefLink sp8;
    s32 sp18;
    s32 i;
    s32 busy;
    s32 mgr;
    ScriptNode *node;
    s32 found;
    s32 idx;
    s32 *flags;
    RefLink *p;

    if (arg0->unk0x778 == 0) {
        void *tbl = fn_80125A08(lbl_80292914, 1);
        arg0->unk0x778 = *(s32 *)((char *)tbl + 4);
        for (i = 0; i < arg0->unk0x778; i++) {
            arg0->unk0x6B8[i] = GetChecksum(tbl, i);
        }
    }
    busy = 0;
    if (fn_8004C840(arg0) != 0) {
        if (fn_8004C414(arg0, arg1->unk0x0) != 0) {
            busy = 1;
        }
    }
    if (arg0->unk0x77C == 0 || arg1->unk0x10 == 0 ||
        GetInteger(arg1->unk0x10, QB_DEVICE_NUM, &sp18, 0) == 0 ||
        fn_8009D364(lbl_8030191C, 0) == sp18) {
        mgr = lbl_80301A78;
        if (arg1->unk0x0 == QB_FOCUS && arg1->unk0x8 != QB_SYSTEM) {
            GetElement_2(&sp8, arg0, arg1->unk0x8, 0);
            p = &sp8;
            if (sp8.f0 != NULL && fn_80042110(sp8.f0) == 0) {
                fn_8004BFE4(arg0, p, fn_800A3BDC(arg1));
                fn_800A3B44(arg1, 1, 0);
            }
            if (sp8.f0 != NULL) {
                CObject_RemoveRefLink(sp8.f0, p);
                sp8.f0 = NULL;
            }
        }
        if (arg1->unk0x0 == QB_UNFOCUS && arg1->unk0x8 != QB_SYSTEM) {
            GetElement_2(&sp8, arg0, arg1->unk0x8, 0);
            p = &sp8;
            if (sp8.f0 != NULL && fn_80042110(sp8.f0) == 0) {
                fn_8004C110(arg0, p, 0, 0);
                fn_800A3B44(arg1, 1, 0);
            }
            if (sp8.f0 != NULL) {
                CObject_RemoveRefLink(sp8.f0, p);
                sp8.f0 = NULL;
            }
        }
        if (arg1->unk0x0 == QB_NOTIFY_CHILD_UNLOCK) {
            GetElement_2(&sp8, arg0, arg1->unk0x8, 0);
            fn_8004C110(arg0, &sp8, 1, 1);
            fn_800A3B44(arg1, 1, 0);
            if (sp8.f0 != NULL) {
                CObject_RemoveRefLink(sp8.f0, &sp8);
                sp8.f0 = NULL;
            }
        }
        if (arg1->unk0x0 == QB_NOTIFY_CHILD_LOCK) {
            GetElement_2(&sp8, arg0, arg1->unk0x8, 0);
            fn_8004C2DC(arg0, &sp8);
            fn_800A3B44(arg1, 1, 0);
            if (sp8.f0 != NULL) {
                CObject_RemoveRefLink(sp8.f0, &sp8);
                sp8.f0 = NULL;
            }
        }
        if (fn_8004C414(arg0, arg1->unk0x0) != 0 && arg1->unk0x8 == QB_SYSTEM) {
            found = 0;
            idx = fn_800A3BDC(arg1);
            flags = arg0->unk0x5B4;
            node = arg0->unk0x5A4[idx];
            while (node != NULL) {
                node->unk0x14 = 0;
                node = node->unk0x10;
            }
            flags[idx] = 1;
            for (;;) {
                flags[idx] = 0;
                node = arg0->unk0x5A4[idx];
                while (node != NULL) {
                    fn_8004C410(arg0, node);
                    if (node->unk0x14 == 0 && node->unk0x18 == 0 &&
                        fn_80042110(node->unk0x0) == 0) {
                        if (!busy || (fn_80042180(node->unk0x0) != 0 &&
                                      fn_8004C858(arg0, node->unk0xC) != 0)) {
                            if (fn_800A54AC(mgr, arg1->unk0x0, node->unk0x0->unk0x18,
                                            arg1->unk0x4, arg1->unk0x10, 0,
                                            lbl_80292924) != 0) {
                                found = 1;
                                break;
                            }
                            node->unk0x14 = 1;
                        }
                    }
                    if (flags[idx] != 0) {
                        break;
                    }
                    node = node->unk0x10;
                }
                if (found != 0) {
                    break;
                }
                if (flags[idx] == 0) {
                    break;
                }
            }
            if (found != 0) {
                fn_800A3B90(arg1, 1, 0);
            }
        }
    }
}