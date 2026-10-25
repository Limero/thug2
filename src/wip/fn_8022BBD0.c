// WIP DRAFT (non-matching) — hand-rebuilt from the want disassembly
// family=m2c range=0x8022BBD0-0x8022BC98 size=200B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// PARKED at 42.0% (SIZE-EXACT 200B, was 24.0% / 196B at hand-off).
// Semantics (fully recovered, no longer m2c garbage):
//   this is an INLINED `search_t` iterator walk (the same local type as the
//   promoted twins src/fn_8021D358.c / fn_8021D7F0.c / fn_8021D888.c /
//   fn_8021D758.c: { s32 unk0; s32 cursor; const char *name; s32 unkC; }).
//   sp.name is set to the lbl_802A83F8 sentinel object on all three exits,
//   sp.cursor walks a child list, and the result is
//   *(s32 *)((char *)lbl_802A83F8 + 0x30) when `count` steps succeed.
//   ProDG zone (stwu-first prologue), no calls, so no `-G`/FPR quirks.
// Frame: 0x18 (16-byte search_t) and the lbl's HI16/LO16 pair hoisted to the
// entry block in r11 — both now exact.  Also exact: the `addi r3,r3,0xac`
// param reassignment (§6av-215), the `mr r8,r9` split web, the `mr r10,r8`
// loop base, the do-while latch (want's back edge targets the `cmpwi r4,0`
// HEAD, not the body), the entry guard, and the whole fail block.
//
// RESIDUAL (29 of 50 words), two independent items:
//
// (1) THE 5-WORD SELECT — want emits, TWICE, the shape
//        cmpwi rX,0 | bne L | li rX,0 | b M | L: lwz rX,4(rX) | M:
//     i.e. the 5-instruction COND_EXPR expansion with the branch JUMPING TO
//     THE `else` ARM (polarity `bne` = jump-if-true to the load) and the
//     `li` block falling through and ending in a real `b` to the join.
//     VERIFIED ROOT CAUSE with `cc1 -dr` on a minimal probe: the POST-RELOAD
//     RTL for `x = (m == 0) ? 0 : m->b;` is *already* this 5-word shape
//     ([cmp][beq→li-block][li][b][li-block]) — i.e. the shape exists — but
//     (a) `fold_cond_expr` rewrites the test from `m == 0` to `m != 0` with
//     the arms swapped, which FLIPS the branch polarity (want is `bne`), and
//     (b) the `jump` pass then hoists the arm's pure `SET x,0` above the
//     branch and deletes the now-redundant `b`, collapsing 5 words to 3-4.
//     (b) was measured to be un-defeatable: `-fno-thread-jumps`,
//     `-fno-gcse`, `-fno-schedule-insns{,2}`, `-fno-sched-spec`,
//     `-fno-sched-interblock`, `-fno-expensive-optimizations`, `-O1/-Os/-O3`,
//     zero-code `"+r"` barriers before/after the select, and 14 different
//     source spellings (ternary both polarities, if/else both polarities,
//     `m ? .. : ..`, statement-first, goto-form with a join label) all
//     collapse identically.  A 13-form × 13-form spelling sweep (1.7 µs) over
//     the two diamonds jointly: every combination gives 192-196B, none 200B.
//     The one C construct that DOES survive the hoist is a **store**
//     destination — a minimal probe `if (m==0) *pp=0; else *pp=m->b;` emits
//     `cmpwi|bne|stw|b|lwz|stw` in ALL FIVE in-tree ProDG versions, because
//     a store is not hoistable.  Using that shape for the ENTRY diamond
//     (a scratch struct field + read-back) is what brought the object to
//     the exact 200B length; the read-back is not forwarded (2 extra insns),
//     so it trades want's `b`+`or.` for `stw`+`lwz` and still misses.
//     Using it for the LOOP diamond instead makes the loop 1 word short
//     (184B total).  Using it for both is the 42.0% body below.
//
// (2) BLOCK ORDER — want's `ret` block (lis/lwz r3,0x30(r11)/addi/stw/b)
//     sits PHYSICALLY IN THE MIDDLE, in the fall-through slot of the select's
//     true-arm block, at 0x8022BC18 — between the select's two arms and the
//     loop preheader.  GCC always emits it after the loop.  The label ORDER
//     in the source matters a lot here: `fail:` before `ret:` puts the ret
//     block last (36.0%); `ret:` before `fail:` lands the FAIL block at
//     want's exact 0x8022BC80 slot and is worth +6 points.  (Per §6be: where
//     a `goto` target's basic block is created decides its physical slot, and
//     block-creation order is what `maybe_reorder_blocks` sorts on.)
//
// (3) LBL ADDRESS WEBS — want uses the entry-block anchor r11 for both the
//     first `sp.name = lbl` store AND the ret path's `lwz r3,0x30(r11)`, but
//     a FRESH r9 pair for each of the two exit-path `sp.name = lbl` stores
//     (and the ret block's `lis` is hoisted to its block top while its `addi`
//     stays put).  No spelling tried (a named `const char *nm` used for the
//     entry store + ret load with the bare symbol in the exit stores, or vice
//     versa, with/without an explicit cast) splits the two webs; GCC's reload
//     either reuses one anchor everywhere or a fresh one everywhere.  This is
//     the same "L5: one pseudo per symbol per function" anchor situation as
//     doc 73 / §6bg, without a hard-reg pin route (pins bind pseudos, not
//     reloads — §6cx).
//
// EXPERIMENT LOG (change -> %):
//   24.0%  inherited m2c draft (196B, frame 0x10, wrong loop kind, 4 calls
//          it does not make, `lwz 0xb8` offset bug, m2c's M2C statics)
//   14.3%  file-local 16B search_t + Node_t typedefs, `s` pinned to r8,
//          two address webs (p + s), v2: one variable reused for the node
//          AND the "next" role
//   16.7%  loop kind: guarded `while` -> do-while + peeled entry guard, so
//          the latch back-edge targets the `cmpwi r4,0` HEAD (want), not a
//          rotated body
//   28.0%  `while (arg1 != 0)` + `goto ret`/`goto fail` — tail blocks right,
//          but GCC rotates the loop
//   31.25% do-while + `arg0 += 0xAC` param reassignment (want's
//          `addi r3,r3,0xac; stw r3,4(r9); lwz r,0xc(r3)`) + `w = s` in the
//          preheader; 13x13 diamond-spelling sweep, all 192-196B
//   29.2%  distinct `nx` destination variable (want's `or. r11,r9,r9` copy
//          appears) — still 192B
//   32.0%  STORE-destination select (`if (m != 0) *t = 0; else *t = m->unk4;`
//          into a scratch struct field, read back) — 200B
//   36.0%  ... with `fail:` before `ret:`
//   42.0%  ... with `ret:` before `fail:` (this file) — 200B, 29/50 diffs
//   +6.0%  ret-before-fail label order          -6.0% reverting that order
//   flags:  all 12 tested flags are 42.0% no-ops except
//           -fno-schedule-insns2 (32.0%), -fno-rerun-cse-after-loop (20.4%),
//           -fno-schedule-insns (4.1%), -O1 (10.0%) — none is load-bearing.
// AUDIT (park hygiene, §6bw method + §6bg hazards):
//   object = `.text` 0xC8 ONLY (200B) + `.rela.text` — no `.rodata`/`.data`,
//   so no doc-14 promote caveat; `size=200B` == symbols.txt `size:0xC8` ==
//   header `range` end 0x8022BC98; 0 EMITTED inline instructions (the single
//   `__asm__` in the file is the `register search_t *s __asm__("r8")`
//   attribute, which emits nothing).  lbl_802A83F8 hand-decoded from want's
//   `lis -0x7fd5` (= page 0x802B) + `addi -0x7c08` = 0x802B0000-0x7C08 =
//   0x802A83F8, which IS a symbols.txt .rodata2 object (size 0x44) — the
//   masked-score wrong-label hazard (277) does not apply.  REL14/REL24 audit:
//   got has 8 branch relocations vs want's 10 (the two missing `b`s) and only
//   4 of the targets agree (0x8022BC04 / BC18 / BC80 / BC90), so the CFG still
//   differs — as expected, the branch graph is part of the residual.
// BEST THEORY: this is very likely the "larger-function-split origin" §6an
// suspected.  The 5-word select is provably reachable (post-reload RTL) but
// every GCC 2.95 transformation that can reach C destroys it, and the ret
// block's mid-function physical slot is likewise not something any label
// order produces.  Closest sibling: fn_8022BB14 (0x8022BB14, 188B) shares
// the first 16 instructions EXACTLY and its own entry diamond DOES have the
// 5-word shape while its loop diamond has the collapsed 4-word shape — i.e.
// retail itself emits both forms of the same idiom two instructions apart,
// which is only explicable by a split/inline boundary.
#include "types.h"
extern char lbl_802A83F8[];

/* retail local: the `search_t` iterator scratch of the promoted twins
   (src/fn_8021D358.c etc.).  unk0/unkC are never written here; they exist
   to give the 16-byte frame retail's stwu r1,-0x18 implies. */
typedef struct {
    s32 unk0;
    s32 cursor;
    const char *name;
    s32 unkC;
} search_t;

/* the walked node: child at +0xC, next/terminal flag at +0x4 (-1 == end) */
typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
} Node_t;

s32 fn_8022BBD0(s32 arg0, s32 arg1) {
    search_t sp8;
    search_t *p = &sp8;
    register search_t *s __asm__("r8");
    search_t *w;
    Node_t *n;
    Node_t *m;
    Node_t *nx;

    p->name = (char *)lbl_802A83F8;
    arg0 = (s32)((char *)arg0 + 0xAC);
    p->cursor = arg0;
    s = p;
    n = (Node_t *)(*(s32 *)((char *)arg0 + 0xC));
    if (n->unk4 == -1) {
        n = 0;
    }
    s->cursor = (s32)n;

    /* NX = (m == 0) ? 0 : m->unk4.  Written as a store-conditional into a
       scratch field because that is the ONLY plain-C form that stops the
       `jump` pass hoisting the arm's `li` above the branch (see the
       RESIDUAL (1) note); the read-back is not forwarded. */
    m = n;
    {
        s32 *t = &s->unk0;
        if (m != 0) {
            *t = 0;
        } else {
            *t = m->unk4;
        }
    }
    nx = s->unk0;
    if (nx == 0) {
        goto fail;
    }
    w = s;
    do {
        if (arg1 == 0) {
            goto ret;
        }
        n = (Node_t *)w->cursor;
        arg1 -= 1;
        m = (Node_t *)n->unkC;
        if (m->unk4 == -1) {
            m = 0;
        }
        s->cursor = (s32)m;
        nx = (m == 0) ? 0 : m->unk4;
    } while (nx != 0);

ret:
    s->name = (char *)lbl_802A83F8;
    return *(s32 *)((char *)lbl_802A83F8 + 0x30);
fail:
    s->name = (char *)lbl_802A83F8;
    return 0;
}
