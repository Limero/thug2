// WIP DRAFT — rewritten 2026-10-15 from want (was parked m2c 23.3% DIFF).
// Bone-hierarchy iterator: bone manager from fn_801259C8, outer for over
// children (NULL slot => inner for over manager bones, checksum match =>
// alloc 0x30 node, init, store, read QB_RADIUS into bone+0x28). The m2c
// draft failed on 9 temps (frame 0x58 vs 0x50), immediate compares, and a
// rotated loop; this rewrite uses u32 counters (cmplw), for/for with entry
// and latch tests, sp8 == call (cmpw r0,r3), and dead-slot + top-lblp fill.
// PARKED 2026-10-15: frame 0x50 + stmw r20 + slots (sp8@8/spC@0xC) + all
// calls/loops/RA-RB roles match; residual is 3 compiler-choice words: (1)
// lbl lis+addi hoists to function top into saved regs (want keeps it at
// the inner pre-header in temp r9: `lis r9 / addi r21`), immune to
// assignment position (top/pre-inner/in-arm all hoist), loop forms
// (while/for outer/inner), and explicit-lbplp variants; (2) the child
// shift fuses into bo's home (`slwi r28`, want `slwi r11 + mr r27,r11`),
// immune to bo typing (s32/char*), block scope, and declaration order;
// (3) driven mgr/bo home swap (r27/r28). got 324B, want 328B.
// WALL-LEVERS that WORKED here, reusable elsewhere: `char *bo` byte-offset
// + `u32 cb` base flips stwx/lwzx to offset-in-RA (pointer-first
// canonicalization: `cb+bo` and `bo+cb` compile identically, only the
// TYPES decide RA/RB); all-volatile stack locals (`volatile s32/f32` +
// `volatile s32 _pad[2]`) pack slots in declaration order (plain sp8/spC +
// volatile-double pad misplaces the pad low and shifts slots to 0x10/0x14).
// family=m2c range=0x80050720-0x80050868 size=328B
// family=m2c range=0x80050720-0x80050868 size=328B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "qb_constants.h"
#include "structs.h"

typedef struct BoneH {
    void *child;
    s32 count;
} BoneH;

extern char lbl_80292EE0[];
extern f32 lbl_80292EC4;

void *fn_801259C8(s32 arg0, s32 arg1);
void *fn_80129528(void *arg0, s32 arg1);
s32 fn_801286D0(void *arg0, s32 arg1, void *arg2, s32 arg3);
s32 fn_8003A324(s32 arg0, s32 arg1);
void *Mem_Alloc2(s32 arg0);
void fn_80006F6C(void *arg0);
s32 GetFloat(void *arg0, s32 arg1, f32 *arg2, s32 arg3);

void fn_80050720(BoneH *arg0, s32 arg1) {
    volatile s32 sp8;
    volatile f32 spC;
    BoneH *mgr;
    u32 var;
    u32 next;
    char *bo;
    u32 j;
    void *v;
    void *node;
    void *entry;
    u32 cb;
    volatile s32 _pad[2];
    char *lblp;
    f32 rad;

    mgr = fn_801259C8(0xE785E, 1);
    lblp = lbl_80292EE0;
    for (var = 1; var < arg0->count; var = next) {
        next = var + 1;
        if (((s32 *)arg0->child)[var] == 0) {
            bo = (char *)(var * 4);
            rad = lbl_80292EC4;
            for (j = 0; j < mgr->count; j++) {
                sp8 = 0;
                v = fn_80129528(mgr, j);
                fn_801286D0(v, 0xCAB84088, (s32 *)&sp8, 1);
                if (sp8 == fn_8003A324(arg1, var)) {
                    cb = (u32)arg0->child;
                    spC = rad;
                    node = Mem_Alloc2(0x30);
                    ((s32 *)node)[1] = (s32)lblp;
                    fn_80006F6C((char *)node + 8);
                    *(void **)(cb + bo) = node;
                    v = fn_80129528(mgr, j);
                    GetFloat(v, QB_RADIUS, (f32 *)&spC, 1);
                    entry = *(void **)(bo + (u32)arg0->child);
                    *(f32 *)((char *)entry + 0x28) = spC;
                }
            }
        }
    }
}
