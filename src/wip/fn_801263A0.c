// WIP DRAFT (non-matching) — hand-rebuilt from disasm, best known 76.0% (38/50, size-exact 200B)
// family=m2c range=0x801263A0-0x80126468 size=200B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// PARKED 2026-09-26 at 76.0% (38/50 words, size-exact 200B).
// Up from the stale m2c baseline of 38.0%.
//
// SEMANTICS (all of 0x801263A0..0x8012640C is byte-identical to want):
//   guarded string-table intern. If the global at 0x8030FE54 is non-zero,
//   hash arg0 to a 0x50-stride bucket in the table at 0x80303258, walk the
//   8-byte-stride collision chain calling strcasecmp() on each candidate
//   (early-out on the first match), then append arg1's bytes plus a NUL to
//   the bump pointer at 0x80303260 and record the entry.
//
// LEVERS FOUND (each measured, kept in the body):
//  1. `idx = arg0 & 0xFFFF;` MUST be computed INSIDE the `if (lbl_802FFE54)`
//     guard.  Hoisting it above the guard makes ngccc materialise want's
//     `clrlwi r0,r3,0x10` / `mulli` before the global load instead of after
//     the `beq`.  38.0% -> 65.3% on its own -- the single biggest lever here.
//  2. A named `u8 *cur` cursor for the tail.  65.3% -> 70.0%.
//  3. ALIAS-SYMBOL ANCHOR LEAK (recipe 6b-144).  want re-materialises a page
//     anchor TWICE more than ngccc does: `lis r11` at 0x80126420 (loop) and
//     again at 0x80126440 (NUL-terminate tail), on top of the r9 anchor from
//     the guard load and the r11 anchor from the bucket-base load.  ngccc
//     GCSEs all four into ONE r9 anchor.  Routing ONLY the copy loop's
//     read+write through the neighbour symbol `lbl_8030325C` with a
//     compensating `+ 4` (same 0x8030 page, same cell address) makes the loop
//     expression syntactically distinct so it cannot CSE, forcing a fresh
//     `lis`.  70.0% -> 76.0%.  `lbl_80303264 - 4` scores identically (76.0%).
//
// RESIDUAL (12 words, all in the NUL-terminate tail + register colouring). At
// 0x80126440 the original loads a fresh page high half into r11, reads the
// bump pointer at displacement 0x3260 into r9, stores the zero byte, then does
// the address add and the entry store, while this draft reuses the
// already-loaded value from r8 into r11, stores through it, and only then
// materialises a fresh page anchor into r9 before the same add/store tail.
// i.e. the tail still consumes the register holding site A's already-loaded
// `lbl_80303260` value (r8) instead of re-loading through a fresh anchor.
// The loop half of the same alias trick drops the tail back to 70% (two
// distinct aliases over-constrain the page allocation), so the fix has to
// land on the tail alone -- and every spelling tried for that regresses.
//
// DEAD ENDS MEASURED (all worse than 76.0%; none are worth re-grinding):
//  * volatile cursor / volatile store-back / volatile site-A read -- forces
//    re-loads but drops the body to 48-49 words: 56-64%.
//  * aliasing site A (node->f_04) or `cur`'s init to free the real symbol for
//    the tail: 56-70%, and it costs 1-2 words.
//  * two DIFFERENT aliases (loop 5C+4 + tail 64-4, either order): 70%.
//  * inverting `if (c != 0)` so the tail inlines and the loop goes out-of-line:
//    28-36%.  Also `if/else` with the tail in the else: 34%.
//  * loop shapes: `while(c!=0)`, `for(;;)+break`, `*b++`, post-increment
//    cursor -- all 58-66%, none size-exact.
//  * `lbl_80303258` as `s32*` + `arr[idx*0x14]`: 14.9%.  `u16 arg0`: 14.6%.
//  * flags on the 76% body: -fno-expensive-optimizations, -fno-cse-follow-jumps
//    and -fno-sched-interblock are all exact no-ops (76.0%); -fno-gcse 56.9%
//    (and 51 words); -fno-schedule-insns 68.0%; -fno-tree-pre does not exist
//    in ProDG cc1; -fno-ipa-cse errors out.
//
// ROOT CAUSE: want re-materialises a page anchor per basic block where ngccc
// runs a single GCSE'd anchor.  The alias trick buys back ONE of the three
// rematerialisations; getting the tail's is blocked because the tail's value
// is CSE'd against the `node->f_04` store, and separating the two costs more
// words than it saves.  This is the doc-15/§6b-144 anchor class (same family
// as 0x801B6EB8's parked GCSE anchor split), not a semantic or type error --
// do NOT re-try the loop-shape or flag ladders.
#include "types.h"
s32 strcasecmp(s32);
extern s32 lbl_802FFE54;
extern void *lbl_80303258;
extern u8 *lbl_80303260;
extern u8 *lbl_8030325C;
typedef struct { s32 f_00; void *f_04; } Node;
void fn_801263A0(s32 arg0, u8 *arg1) {
    u8 *p;
    void *nxt;
    u8 *b;
    u8 c;
    s32 idx;
    Node *node;
    u8 *cur;
    if (lbl_802FFE54 != 0) {
        idx = arg0 & 0xFFFF;
        node = (Node *)((char *)lbl_80303258 + idx * 0x50);
        if (node->f_04 != 0) {
            do {
                if (node->f_00 == arg0) {
                    strcasecmp((s32)node->f_04);
                    return;
                }
                node = (Node *)((char *)node + 8);
                nxt = node->f_04;
            } while (nxt != 0);
        }
        node->f_00 = arg0;
        node->f_04 = lbl_80303260;
        p = arg1;
        cur = lbl_80303260;
        c = *p;
        if (c != 0) {
            do {
                b = ((u8 *)&lbl_8030325C + 4);
                *b = c;
                (*(u8 **)((char *)&lbl_8030325C + 4)) = b + 1;
                c = *++p;
            } while (c != 0);
        }
        b = cur;
        *b = 0;
        lbl_80303260 = b + 1;
    }
}
