// WIP DRAFT (non-matching) — hand rebuild from the original's control flow.
// family=m2c range=0x80219B18-0x80219C60 size=328B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// STRUCTURE: two walks over a linked list plus a count of nodes matching arg1.
//   `a` and `b` are two 0x10-byte iterator locals of the same type (frame
//   slots r1+8 and r1+0x18): +4 is the cursor, +8 the descriptor it is reset
//   to (lbl_802A83F8 for `a`, lbl_802A8030 for `b`). Both descriptors are
//   written in the prologue and again before the return; the second write goes
//   through the same pointer that the prologue used for `a`, which is why the
//   original keeps it in a callee-saved register for the whole function.
//   walk 1 starts at fn_8021D454(arg0, &a, 0), advances with
//   fn_8021D4E8(arg0, &a, 0), and counts nodes whose +0x34 equals arg1 — this
//   walk is byte-identical to the original.
//   walk 2 seeds b's cursor at arg0+0x148, then repeatedly loads
//   `*(cursor+0xC)` as the next cursor; a -1 in that cursor's +0x4 means end
//   of chain and becomes NULL, and the cursor's +0x4 is the new node (the same
//   idiom as the promoted sibling src/fn_8021D454.c). Each node whose
//   (+0x20 & 0x1C) != 4 and +0x28 == arg1 counts.
//   tail: a's descriptor = lbl_802A83F8, b's = lbl_802A8030, return the count.
//
// CURRENT STATE: 316B compiled against the original's 328B — every block,
// constant and branch is present, but three instructions are missing, so the
// object is 3 words short of the symbol and cannot be promoted yet. The
// index-aligned sweep score (7.3%) is meaningless at this length: the tail is
// displaced, so only the first words line up.
// RESIDUAL, in the two places where the shapes differ:
//   * walk 2's entry computes the first node and then jumps into the loop's
//     bottom test; the original emits a separate entry test (a move-plus-record
//     into the loop variable) and falls into the body. The same ?: is
//     if-converted at the entry and emitted as a branch diamond at the bottom
//     in the original, so the difference is where GCC 2.95 placed the loop
//     test, not what the source says.
//   * the prologue builds &a and copies it to the callee-saved register the
//     tail uses, and stores b's cursor through a freshly materialised &b while
//     b's descriptor store stays r1-relative; here both b stores go through
//     the pointer.
// Levers measured and rejected (object size against the 328B original):
// writing the advance block out twice instead of inlining a helper (272B, and
// the loop rotates to the do/while form);
// `while ((node = next(&b)) != 0)` (268B); an if/else instead of the ?: inside
// the helper (272B); returning the cursor and testing it in the caller (304B);
// a separate loop variable for walk 2 (316B, identical); `register Node *node
// asm("r11")` (316B, identical); a `for` loop instead of `while` (identical);
// and -fno-schedule-insns / -insns2 / -gcse / -optimize-register-move /
// -cse-follow-jumps / -strength-reduce / -delayed-branch (all byte-identical
// to the default build).
#include "types.h"
#include "structs.h"

extern char lbl_802A8030[];
extern char lbl_802A83F8[];
s32 fn_8021D454(s32, CStruct *, s32);
s32 fn_8021D4E8(s32, CStruct *, s32);

typedef struct Iter {
    s32 unk0x0;
    s32 unk0x4;
    void *unk0x8;
    s32 unk0xC;
} Iter;

typedef struct Node {
    s32 unk0x0;
    s32 unk0x4;
    s32 unk0x8;
    s32 unk0xC;
    s32 unk0x10;
    char pad0x14[0xC];
    s32 unk0x20;
    s32 unk0x24;
    s32 unk0x28;
    s32 unk0x2C;
    s32 unk0x30;
    s32 unk0x34;
} Node;

static __inline__ void iter_init(Iter *it, void *vt) {
    it->unk0x8 = vt;
    it->unk0x4 = 0;
}

static __inline__ Node *next_node(Iter *it) {
    Node *p;

    p = (Node *)((Node *)it->unk0x4)->unk0xC;
    if (p->unk0x4 == -1) {
        p = 0;
    }
    it->unk0x4 = (s32)p;
    return (p != 0) ? (Node *)p->unk0x4 : 0;
}

s32 fn_80219B18(s32 arg0, s32 arg1) {
    Iter a;
    Iter b;
    Iter *pa;
    Node *node;
    s32 count;

    pa = &a;
    iter_init(pa, lbl_802A83F8);
    iter_init(&b, lbl_802A8030);
    count = 0;
    node = (Node *)fn_8021D454(arg0, (CStruct *)pa, 0);
    while (node != 0) {
        if (node->unk0x34 == arg1) {
            count += 1;
        }
        node = (Node *)fn_8021D4E8(arg0, (CStruct *)&a, 0);
    }

    b.unk0x4 = arg0 + 0x148;
    node = next_node(&b);
    while (node != 0) {
        if (((node->unk0x20 & 0x1C) != 4) && (node->unk0x28 == arg1)) {
            count += 1;
        }
        node = next_node(&b);
    }

    pa->unk0x8 = lbl_802A83F8;
    b.unk0x8 = lbl_802A8030;
    return count;
}
