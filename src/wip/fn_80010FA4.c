// WIP DRAFT (non-matching) — hand reconstruction from the WANT disassembly.
// family=m2c range=0x80010FA4-0x800113E4 size=1088B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// PARKED 2026-10-06. Best body below; not
// re-measured (no compiler in the slice).
//
// WHAT THIS IS: the heap free-list coalescing / block-release routine of the
// Neversoft allocator family that also contains the matched callees
// fn_80011DE0 (0x80011DE0, 32B) and fn_80011E00 (0x80011E00, 20B), and the
// parked realloc sibling fn_80011454 (src/wip/fn_80011454.c).  arg0 is the
// heap/manager, arg1 is the block being released back into the +0x40 list.
//
// SEMANTIC FIXES MADE vs the old m2c husk (which had `0;` statements and read
// the uninitialised `var_r31` before assigning it):
//   1. fn_80011DE0 is a TWO-argument call (`(CStruct *, s32)`; body is
//      `arg0->unk0x4 += arg1; if (...) arg0->unk0x8 = ...`).  The WANT only
//      sets r3/r4 before the bl; the old 5-arg prototype forced three dead
//      argument copies.  fn_80011E00 is likewise `(CStruct *, s32)`.
//   2. The block size is a BITFIELD: +0x08 is `{ u32 hi:24; u32 lo:8; }` with
//      `lo` == byte +0x0B (confirmed by the matched-callee family note in
//      src/wip/fn_800119B4.c and by fn_80011454).  `hi` reads as `lwz;srwi 8`,
//      `lo` reads as `lbz 0xB`, and `w.hi = ...` emits the single
//      `rlwimi rD,rS,8,0,0x17` the WANT has.  The old body's
//      `(x & 0xFF) | (v << 8)` spelling cannot produce that.
//   3. `lbl_80290628` is declared `extern s32` (folded `lis`+disp), not
//      `*(s32 *)0x80290628`, and `lbl_802FFE98` is `extern void *`.
//   4. The three accounting counters are typed struct members (tr28.b/tr28.c
//      = "current"/"peak" at +0x2C/+0x30, tr1C.b at +0x20), not raw offsets.
//   5. Control flow is the real list walk + double coalesce + the
//      `mode == 1 && head == 0` / `mode == -1 && prev == 0` two-case tail.
//
// KNOWN RESIDUAL / UNVERIFIED (the reason this is parked, not promoted):
//   * GCC 2.95 stages the `tr10`/`tr04` tracker structs through six stack
//     slots (sp+0x18..0x20 before each call, sp+0x08..0x10 after) that this
//     body does not reproduce.  They look like a macro-expanded
//     save/restore of a 3-word temporary; without the compiler I could not
//     pin the exact source shape, and folding them away is the main risk.
//   * `node->size` is re-read after the coalesce branches in the tail, so a
//     named size temp is required there (kept as `sz`).
//   * Register colouring of the r25/r27/r28 walk triples and the r26/r30
//     aliases of tr1C/tr28 is unverified.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

/* Free-list block: +0x00 next, +0x08 { size:24, lo:8 } (lo == byte +0x0B). */
typedef struct HNode HNode;
struct HNode {
    HNode *next;
    s32    unk0x4;
    u32    size : 24;
    u32    lo   :  8;
};

/* The +0x40 object; its +0x1C is the list head. */
typedef struct {
    char   pad0x00[0x1C];
    HNode *head;
} HList;

/* One accounting tracker: a@+0, b@+4, c@+8 (0x0C bytes). */
typedef struct {
    s32 a;
    s32 b;
    s32 c;
} Tracker;

typedef struct {
    s32      unk0x00;
    Tracker  tr04;   /* 0x04 */
    Tracker  tr10;   /* 0x10 */
    Tracker  tr1C;   /* 0x1C */
    Tracker  tr28;   /* 0x28 */
    s32      unk0x34;
    s32      mode;   /* 0x38 */
    void    *top;    /* 0x3C */
    HList   *list;   /* 0x40 */
} Heap;

extern s32   lbl_80290628;
extern void *lbl_802FFE98;
void  fn_80011DE0(CStruct *, s32);
void *fn_80011E00(CStruct *, s32);
void  fn_80010400(void *, s32, s32);

void fn_80010FA4(Heap *arg0, HNode *arg1) {
    HNode *head;
    HNode *prev;
    HNode *prev2;
    s32    off;
    s32    sz;

    /* Fold the pending low byte into the 24-bit size, then clear it. */
    arg1->size = arg1->size + arg1->lo;
    arg1->lo = 0;

    fn_80011DE0((CStruct *)&arg0->tr10, 1);
    arg0->tr28.b = arg0->tr28.b + arg1->size;
    if (arg0->tr28.b > arg0->tr28.c) {
        arg0->tr28.c = arg0->tr28.b;
    }
    fn_80011E00((CStruct *)&arg0->tr04, 1);
    arg0->tr1C.b = arg0->tr1C.b - arg1->size;
    fn_80010400(lbl_802FFE98, QB_TEAMMATEPRO, 0);

    /* Walk the block list to the first block with a higher address. */
    prev  = 0;
    prev2 = 0;
    head  = arg0->list->head;
    for (;;) {
        if (head == 0) {
            break;
        }
        if ((u32)head >= (u32)arg1) {
            break;
        }
        prev2 = prev;
        prev  = head;
        head  = head->next;
    }
    arg1->next = head;

    /* Coalesce with the successor block if it is physically adjacent. */
    if (head != 0) {
        off = lbl_80290628;
        sz  = arg1->size;
        if ((HNode *)((char *)arg1 + off + sz) == head) {
            arg1->next = *(HNode **)((char *)arg1 + off + sz);
            arg1->size = sz + off + head->size;
            fn_80011E00((CStruct *)&arg0->tr10, 1);
            off = lbl_80290628;
            arg0->tr28.b = arg0->tr28.b + off;
            if (arg0->tr28.b > arg0->tr28.c) {
                arg0->tr28.c = arg0->tr28.b;
            }
            arg0->tr1C.b = arg0->tr1C.b - off;
        }
    }

    /* Coalesce with the predecessor block if it is physically adjacent. */
    if (prev != 0) {
        off = lbl_80290628;
        sz  = prev->size;
        if ((HNode *)((char *)prev + off + sz) == arg1) {
            prev->size = sz + off + arg1->size;
            prev->next = *(HNode **)((char *)prev + off + sz);
            fn_80011E00((CStruct *)&arg0->tr10, 1);
            off = lbl_80290628;
            arg0->tr28.b = arg0->tr28.b + off;
            if (arg0->tr28.b > arg0->tr28.c) {
                arg0->tr28.c = arg0->tr28.b;
            }
            arg0->tr1C.b = arg0->tr1C.b - off;
            arg1 = prev;
            prev = prev2;
        } else {
            prev->next = arg1;
        }
    } else {
        arg0->list->head = arg1;
    }

    if (arg0->mode == 1 && head == 0) {
        off = lbl_80290628;
        if (arg0->top == (void *)((char *)arg1 + arg1->size + off)) {
            if (prev != 0) {
                prev->next = head;
            } else {
                arg0->list->head = prev;
            }
            arg0->top = (char *)arg0->top - (arg1->size + off) * arg0->mode;
            goto tail;
        }
        return;
    }
    if (arg0->mode != -1) {
        return;
    }
    if (prev != 0) {
        return;
    }
    if (arg0->top != (void *)arg1) {
        return;
    }
    off = lbl_80290628;
    arg0->top = (char *)arg1 + arg1->size + off;
    arg0->list->head = arg1->next;
tail:
    fn_80011E00((CStruct *)&arg0->tr10, 1);
    off = lbl_80290628;
    arg0->tr28.b = arg0->tr28.b - arg1->size;
    arg0->tr1C.b = arg0->tr1C.b - off;
}
