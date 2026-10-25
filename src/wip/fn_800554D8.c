// PARKED 2026-09-27 (ag10): best 47.8% (was 47.8%). DIFF-tier, 48 diffs.
// REVIEWED 2026-10-18 (random triage): 4 blockers stand (FPR hoist set +
// doc-15 arg order + owner-copy live-set + NaN-safe 6th-test shape); each has
// a tried-and-neutral list. Needs allocator-level levers. Body untouched.
// family=m2c range=0x800554D8-0x8005564C size=372B
//
// Residual: 48 diffs across arg-setup order (doc-15), FPR load offsets,
// node-walk register roles, overlap-test block structure, and a missing
// `mtlr r0` in the epilogue (got loads LR to r0 but never restores it —
// a compiler artifact from complex return-path merging). Too many
// independent issues for a quick win; needs a full multi-session rebuild.
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// WHAT THE FUNCTION IS (derived from the DOL disasm, no guessing):
//   Build the world AABB spanning arg0..arg0+0x10 on the stack: fn_8000723C
//   seeds it, fn_8000728C expands it by the second box.  Then walk the node
//   list hanging off lbl_80364C28; each node's +4 field is both the payload
//   pointer AND the end-of-list marker (-1 => stop).  For every node whose
//   payload's +0xD4 AABB overlaps the query AABB, append (payload, aabb) to
//   the two 16-entry output arrays lbl_803C9BF8 / lbl_803C9BB8, max 15 hits.
//   Returns the lbl_803C9BB8 array (NULL-terminated) or 0 if nothing matched.
//   `Bounds` is {f32 lo[4]; f32 hi[4]}: a 6-float AABB with a dead 4th
//   float in each half (offset 0xC is never read — confirmed by both
//   fn_8000728C's disasm and this function's).
//
// SCORE HISTORY (tools/test_wip_drafts.py --addr 0x800554D8, masked %):
//   2026-08-29  8.6%   m2c draft after moving the statics into locals
//   2026-09-20 23.7%   22/93 — best m2c-lineage body (global scratch
//                      register rotation, doc-15 family)
//   2026-09-26 47.8%   48/92 — this body (see below)
//
// WHAT THIS REWRITE FIXED (all real bugs in the m2c lineage, not cosmetics):
//   1. 4th overlap test read sp.f0 instead of sp.f8 — the old body compared
//      the same field twice and never read the z-min, so it loaded only FIVE
//      query floats and every FPR came out one register high (f9..f13 vs the
//      wanted f8..f13).  Fixing the field fixed the FPR set outright.
//   2. `Bounds` is now a real 6-float AABB type instead of a 7-float guess
//      plus *(f32*)&->unkN puns; the +0xC hole matches the callees.
//   3. Three-variable head/next/tag shape, so the `mr r8,r9` head copy and
//      the `mr r7,r9` next copy survive (m2c's single-variable form lets
//      cc1 elide both copies).
//   4. count must be u32 — want uses `cmplwi r10,0xe` (unsigned) for the
//      `> 14` cap, m2c produced `cmpwi`.
//   5. Output-array writes use a BYTE offset (`(char*)lbl + off`, off += 4).
//      The element-index form scaled by 4 again and emitted `slwi ..,4`.
//   6. Store order: arrA, count++, arrB, off += 4, then the cap test — the
//      m2c order let cc1 hoist the count increment to the front of the block.
//   7. Real two-array + null-terminate tail (`return lbl_803C9BB8`), which
//      is where the `mr r3,r11` return-value materialisation comes from.
//
// STILL PARKED — precise remaining blocker:
//   1. THE PREHEADER FPR HOIST SET (costs the whole rest of the stream).
//      want hoists only FIVE query floats and re-materialises the stack address
//      inside the loop for the sixth: the hoisted loads place the floats from
//      0x18, 8, 0x20, 0x1c and 0xc of the stack frame into f8 through f12, and
//      the sixth value is loaded inside the loop through a freshly computed base
//      (r1 plus 8 into r8) into f13.
//      i.e. f8=hi[0] f9=lo[0] f10=hi[2] f11=hi[1] f12=lo[1] f13=lo[2], and
//      sp.lo[2] (the 4th test) is the one value NOT hoisted — its load is
//      split-web'd onto a fresh base register computed in the loop.  EVERY
//      plain C form hoists all six in first-use order
//      (f8=hi0 f9=lo0 f10=hi2 f11=lo2 f12=hi1 f13=lo1), which costs one
//      instruction and shifts every following word by one — hence 48 diffs
//      for a body that is otherwise right instruction-for-instruction.
//      Tried and neutral: 0x1C (lo[3]+w+hi[3]) vs 0x20 (lo[4]/hi[4]) struct
//      size, scalar member names instead of lo[]/hi[] indices, a
//      `*(f32*)((char*)&sp + 8)` spelling for the 4th access, and a named
//      `f32 *` alias.  This is a loop-invariant-address / web-split artifact
//      of the SN global allocator, not a source-reachable shape.
//   2. First call's arg-move order: want `mr r4,r30; addi r3,r1,8`, this body
//      `addi r3,r1,8; mr r4,r30` (doc-15; survives every callee-proto shape
//      swept — 9 return/param-type variants of fn_8000723C x 7 of
//      fn_8000728C, including the M8.31 s32-return flip, old-style, f32).
//   3. `mr r5,r9` (owner copy) is absent: cc1 loads `node->f4` straight into
//      the pinned r5 instead of into a scratch r9 and copying, because our
//      live set has one GPR fewer than want's (want keeps node in r8 AND
//      aabb in r9 simultaneously; here aabb takes over node's dead register).
//   4. The 6th test: want gets a bare `fcmpu + ble -> accept`; the
//      if/else-if spelling makes cc2.95 emit the NaN-safe
//      `fcmpu + cror cr0un,cr0eq,cr0lt + bns` instead (§6ai-156: that shape
//      is only reachable from a NEGATED <=).  9 boolean spellings swept
//      (||-chain, &&-of-negations, 6-way ||, goto, pre-initialised, F-first,
//      `ok = (F)`, …); none produces the plain `ble` with the shared reject
//      block that want has.
//
// The four `register ... __asm__("rN")` declarations are the only
// non-semantic part of this body: they pin count->r10, next->r7, the
// node->next temp->r9 and owner->r5 to want's homes.  They are pure
// declarations (no code) and are what lifts the score from 31.2% (identical
// body, no pins) to 47.8%.  Unpinned subsets measured: none 64/93, count 59,
// count+next 57, count+next+tmp 54, all four 48.  Pinning `node`, `aabb` or
// `head` as well makes things WORSE (61-71) and changes the object size.
#include "types.h"

typedef struct BS { f32 lo[4]; f32 hi[4]; } Bounds;
typedef struct Node {
    s32 f0;
    s32 f4;
    s32 f8;
    struct Node *next;
} Node;
typedef struct Obj { char pad[0xD4]; Bounds *aabb; } Obj;

void fn_8000723C(Bounds *, void *);
void fn_8000728C(Bounds *, void *);
extern s32 lbl_80364C28;
extern char lbl_803C9BF8[];
extern char lbl_803C9BB8[];

s32 fn_800554D8(void *arg0) {
    Bounds sp;
    register u32 count __asm__("r10");
    s32 off;
    register s32 next __asm__("r7");
    register s32 tmp __asm__("r9");
    register s32 owner __asm__("r5");
    Bounds *aabb;
    s32 ok;
    s32 tag;
    Node *head;
    Node *node;

    fn_8000723C(&sp, arg0);
    fn_8000728C(&sp, (char *)arg0 + 0x10);

    count = 0;
    head = *(Node **)&lbl_80364C28;
    tag = head->f4;
    node = head;
    if (tag == -1) {
        node = NULL;
    }
    if (node != NULL) {
        off = 0;
        do {
            tmp = (s32)node->next;
            tag = ((Node *)tmp)->f4;
            next = (s32)tmp;
            if (tag == -1) {
                next = 0;
            }
            owner = node->f4;
            aabb = ((Obj *)owner)->aabb;
            if (aabb != NULL) {
                if (aabb->lo[0] > sp.hi[0] || sp.lo[0] > aabb->hi[0] ||
                    aabb->lo[2] > sp.hi[2] || sp.lo[2] > aabb->hi[2] ||
                    aabb->lo[1] > sp.hi[1]) {
                    ok = 0;
                } else if (sp.lo[1] <= aabb->hi[1]) {
                    ok = 1;
                } else {
                    ok = 0;
                }
                if (ok != 0) {
                    *(void **)((char *)lbl_803C9BF8 + off) = (void *)owner;
                    count += 1;
                    *(void **)((char *)lbl_803C9BB8 + off) = aabb;
                    off += 4;
                    if (count > 0xE) {
                        break;
                    }
                }
            }
            node = (Node *)next;
        } while (node != 0);
    }
    if (count == 0) {
        return 0;
    }
    count *= 4;
    *(void **)((char *)lbl_803C9BF8 + count) = NULL;
    {
        void *base = lbl_803C9BB8;
        *(void **)((char *)lbl_803C9BB8 + count) = NULL;
        return base;
    }
}
