// WIP DRAFT (non-matching) — hand-refined from the m2c draft
// family=m2c range=0x8021ED5C-0x8021EEF4 size=408B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// UPDATED 2026-10-02: 15.5% -> 92.2% (NEAR). Semantics rebuilt, no
// flags, no casts, no barriers, no pins:
//  * the m2c "sp2C..sp58" scalars are ONE 0x44B record at r1+0x18 (the class
//    fn_8022AA50 constructs: it inits +0x1C/+0x24/+0x2C/+0x30/+0x38/+0x40,
//    name[16] at +1, s8 at +0x11 — Unk_A1F83658's layout, fn_8021C4FC's
//    `temp`).  Declared as separate scalars every store to it was DEAD
//    (nothing read them), ngccc deleted the whole block and the 408B length
//    was reached by accident.  As one struct whose address is taken the
//    frame is 0x88 with stmw r23,0x64 — exact.
//  * r1+0x08 is the 16B search_t record (cursor +4, name +8) — the same
//    typedef the matched siblings fn_8021D358/D758/D7F0/D888/DA20 use.
//  * callee arities/return types fixed from the call sites (the big one):
//    fn_8022AA50 is 1-arg (&rec, return unused), fn_8021C4FC is 3-arg
//    (arg0,&rec,counter), fn_8021D184 returns s8 (bare stb), fn_801A44E8
//    takes rec.unk0x1C + node->0x50, fn_8000F2F8/F320 take the lbl_802FFE98
//    pointer object.  All 15 callees declared -> the crclr cr1eq words are
//    gone.
//  * doc-36 SOLVED recipe (fn_80216C4C) for the search_t address split:
//    TWO distinct address webs — `q` for the two init stores + the first
//    walk call, a second pointer born as `s = &sp8` AT THE TAIL.  That
//    gives want's `addi r4,r1,8` birth + `mr r23,r4` home with the init
//    stores off r4 and only the re-arm store off the home, with NO pin.
//    A single shared pointer folds to `addi r25,r1,8` + `mr r4,r25` and
//    scores 78.4%; no pointer at all folds the stores to 0x10(r1) and
//    loses the home entirely; `s = q` (a copy of q's pseudo) is CSE-folded
//    back into q and also scores 78.4%.  The `volatile` qualifier is the
//    fn_80216C4C spelling but measured byte-identical without it here —
//    kept as insurance for the split, not load-bearing.
//  * two scheduling-order fixes (each worth 3.1%): the loop-invariant
//    `GLOBAL_T *g = lbl_802FFE98` named local puts the value load where
//    want has it (and makes the page anchor hoist into the preheader), and
//    `e.unk0x20 = 0x10` must be written AFTER `e.unk0x14 = node->unk0x1C`
//    (the scheduler then hoists the constant store back to the front of the
//    field run).  Field order otherwise = m2c's, with +0x38/+0x40 swapped.
//
// PARKED 2026-10-02 (w75/0x8021ED5C): 8 words left, one root cause — the
// loop-invariant zero pseudo and the counter pseudo swap callee-saved homes
// (want r26 = the 0 shared by the three `= 0` stores, r27 = the counter;
// got r26 = counter, r27 = 0), and with them the two-word shuffle at the
// head of the preheader: the want births sp+0x18 into r28, zeroes r26,
// loads the r25 high half, loads 0xa into r27 and 0x10 into r24, while
// this draft loads 0xa into r26 first, then births sp+0x18 into r28,
// loads the r25 high half, zeroes r27 and loads 0x10 into r24.
// ngccc allocates live-across-call pseudos in ascending pseudo (= source
// first-use) order here, and the counter is defined in the preheader, i.e.
// strictly before the body-hoisted zero — so pure C cannot put the zero
// first.  Tried (all 92.2% or worse, so the tie is insensitive to them):
// 2026-10-20: top-of-function shared `zero = 0` used by all three stores
// REVERTED (DIFF cascade: zero takes r27 early, counter displaced, preheader
// order breaks further). Sharing does not age the web; the entry-born
// counter still wins first pick. Restored 92.2%.
// counter init before the guard / at the top of the loop body (LICM does
// NOT hoist it: 400B), declaration order of every local, s32 vs u32,
// decimal vs hex constants, `s32 zero = 0` named local assigned in the entry
// block, plain `while` instead of `if`+`do/while` (87.2%).  Fixing only
// the r26/r27 swap would leave the ED9C/EDA0 order.
#include "types.h"
#include "structs.h"

extern char lbl_802A83F8[];
extern void *lbl_802FFE98;

void strcpy(void *, void *);
void *fn_8021D454(void *, void *, s32);
void *fn_8021D4E8(void *, void *, s32);
void *fn_8022AA50(void *);
s8 fn_8021D184(void *);
void fn_8000F2F8(void *, s32);
void fn_8000F320(void *);
void fn_801A44E8(s32, s32);
void fn_8021C7EC(void *, void *);
void fn_8021C4FC(void *, void *, s32);
void fn_8022AABC(void *, s32);
s32 fn_8022986C(void *);
void fn_80145058(s32);
void fn_80145008(s32);

/* r1+0x08: search_t, the 16B context record (same typedef as the matched
   siblings fn_8021D358/D758/D7F0/D888/DA20).  volatile + two address webs
   is what reproduces want's scratch/home split (docs/parkings/36, member
   fn_80216C4C) — do NOT "clean this up" into one pointer. */
typedef struct {
    s32 unk0;
    s32 cursor;
    const char *name;
    s32 unkC;
} search_t;

/* r1+0x18: the 0x44B record fn_8022AA50 constructs (layout == Unk_A1F83658,
   the `temp` of fn_8021C4FC). */
typedef struct {
    char pad0x1[0x11];
    s8 unk0x11;
    char pad0x12[0x2];
    s32 unk0x14;
    s32 unk0x18;
    s32 unk0x1C;
    s32 unk0x20;
    s32 unk0x24;
    s32 unk0x28;
    s32 unk0x2C;
    s32 unk0x30;
    s32 unk0x34;
    s32 unk0x38;
    s32 unk0x3C;
    s32 unk0x40;
} entry_t;

/* the list node walked by fn_8021D454/fn_8021D4E8 */
typedef struct {
    char pad0x0[0x18];
    s32 unk0x18;
    s32 unk0x1C;
    char pad0x20[0xC];
    s32 unk0x2C;
    s32 unk0x30;
    char pad0x34[0x8];
    char name[0x10];
    s32 unk0x4C;
    s32 unk0x50;
    char pad0x54[0x184];
    s32 unk0x1D8;
} node_t;

typedef struct {
    char pad0x0[0x5F8];
    s32 unk0x5F8;
} global_t;

void fn_8021ED5C(void *arg0) {
    volatile search_t sp8;
    search_t *q;
    search_t *s;
    entry_t e;
    node_t *node;
    node_t *temp_r29;
    node_t *node2;
    global_t *g;
    s32 var_r27;
    s32 var_r9;

    q = &sp8;
    q->name = (char *)lbl_802A83F8;
    q->cursor = 0;
    node = fn_8021D454(arg0, q, 1);
    if (node != NULL) {
        var_r27 = 0xA;
        do {
            temp_r29 = fn_8021D4E8(arg0, &sp8, 1);
            var_r9 = 1;
            if (!(node->unk0x1D8 & 8)) {
                var_r9 = 0;
            }
            if (var_r9 != 0) {
                fn_8022AA50(&e);
                var_r27 += 0xA;
                strcpy((char *)&e + 1, node->name);
                e.unk0x11 = fn_8021D184(arg0);
                g = lbl_802FFE98;
                e.unk0x14 = node->unk0x1C;
                e.unk0x20 = 0x10;
                e.unk0x2C = node->unk0x2C;
                e.unk0x30 = node->unk0x30;
                e.unk0x40 = node->unk0x4C;
                e.unk0x38 = 0;
                e.unk0x3C = 0;
                e.unk0x34 = 0;
                fn_8000F2F8(g, ((global_t *)g)->unk0x5F8);
                fn_801A44E8(e.unk0x1C, node->unk0x50);
                fn_8000F320(lbl_802FFE98);
                fn_8021C7EC(arg0, node);
                fn_8021C4FC(arg0, &e, var_r27);
                fn_8022AABC(&e, 2);
            }
            node = temp_r29;
        } while (node != NULL);
    }
    node2 = fn_8021D454(arg0, &sp8, 0);
    if (node2 != NULL) {
        do {
            if (fn_8022986C(node2) == 0) {
                fn_80145058(node2->unk0x18);
                fn_80145008(node2->unk0x18);
            }
            node2 = fn_8021D4E8(arg0, &sp8, 0);
        } while (node2 != NULL);
    }
    s = &sp8;
    s->name = (char *)lbl_802A83F8;
}
