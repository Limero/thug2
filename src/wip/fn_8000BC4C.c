// PARKED 2026-10-21 at 43.5%. The residual is the entry ternary only: WANT
// keeps the payload-carrying block far, materialises the zero in the node
// register and jumps over the load, while ngccc materialises the zero in a
// fresh r0 and branches to it. Reversing the test polarity makes the loop
// rotator fold the entry computation into the back edge, so the current
// polarity is the closest shape. The loop tail differs only the same way
// (WANT keeps the loop value in r3, this body uses r0 plus a copy).
// PARKED 2026-10-20 at 40.0% (45/46 words; reloc-aware alignment: everything
// byte-identical except the 5-word prologue ternary). WANT (bne-form):
// cmpwi r11,0; bne->lwz-far; li r11,0; b->join; lwz r11,4(r11); join: or.+beq.
// GOT (beq hoisted-form): cmpwi r11,0; li r0,0; beq->join; lwz r0,4(r11).
// Findings (all verified via cc1 -da RTL dumps + reloc-aware objdump -r):
// - cc1 EXPANSION emits want's shape (with the b); jump1 deletes the b and
//   hoists w=0 to a fresh reg (r0). Fires for ternary/if-else/goto forms and
//   survives -fno-thread-jumps and `return v` (r3-liveness) alike.
// - want's `li r11,0` cannot be plain w=0 with w==r11 (r11==0 is proven on the
//   else path, so it deletes); it also cannot be hoisted (would kill node).
// - volatile asm barriers change layout but never produce li+b together:
//   asm-in-else -> then-fallthrough/else-far; asm-in-then -> li deleted;
//   both-asms -> b kept but li deleted; dup-stw into branches -> 46 words
//   but stores can't merge (different values) and layout diverges.
// - RED HERRING (do not re-chase): objdump -d WITHOUT -r shows branch
//   targets that look retargeted/threaded by ngcas. ngcas is correct; local
//   branches carry R_PPC_REL14 relocs resolved at link. Always read with -r.
// - Sibling fn_8000B6F8 matched with ternary+middle-calls (middle blocks the
//   hoist); this function has no middle, so the same source shape merges.
// Next ideas (untried): keep w pinned to a fresh reg (li survives) AND force
// bne layout with a cold-then marker that doesn't coalesce w into r11.
// WIP DRAFT — sibling-idiom clone of promoted fn_8000B6F8 (same It/Nd pattern).
// family=hand range=0x8000BC4C-0x8000BD04 size=184B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "structs.h"
void fn_8000C79C(s32);
extern char lbl_802901D8[];

/* linked-list node: f04 is the payload (== -1 is the "no entry" sentinel),
   f0C is the next node */
typedef struct Nd {
    s32 f00;
    s32 f04;
    s32 f08;
    struct Nd *f0C;
} Nd;

/* 12-byte stack iterator at r1+8: f04 = cursor, f08 = lbl_802901D8 */
typedef struct It {
    s32 f00;
    Nd *f04;
    s32 f08;
} It;

/* arg0: node embedded at +0x4 (cursor starts as its address, not a load) */
typedef struct Holder {
    char pad0x00[0x4];
    Nd f04;
} Holder;

void fn_8000BC4C(Holder *arg0) {
    s32 scratch;
    s32 pad1;
    s32 pad2;
    register Nd *node __asm__("r11");
    register s32 w __asm__("r0");
    s32 v;

    ((It *)&scratch)->f08 = (s32)lbl_802901D8;
    ((It *)&scratch)->f04 = &arg0->f04;
    node = ((It *)&scratch)->f04->f0C;
    if (node->f04 == -1) {
        node = NULL;
    }
    ((It *)&scratch)->f04 = node;
    if (node != 0) {
        w = node->f04;
        __asm__ volatile ("");
    } else {
        w = 0;
    }
    v = w;

    while (v != 0) {
        register Nd *lnode __asm__("r11");
        fn_8000C79C(v);
        lnode = ((It *)&scratch)->f04->f0C;
        if (lnode->f04 == -1) {
            lnode = NULL;
        }
        ((It *)&scratch)->f04 = lnode;
        v = (lnode != 0) ? lnode->f04 : 0;
    }
    /* keeps pad1/pad2 live with zero emitted instructions so the iterator
       occupies r1+8 (same WALL as fn_8000B6F8) */
    __asm__("" : : "m"(pad1), "m"(pad2));
    ((It *)&scratch)->f08 = (s32)lbl_802901D8;
}
