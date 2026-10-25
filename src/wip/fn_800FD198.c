// WIP draft - PARKED. See notes below.
// extra_cflags: -mps-float
// family=m2c range=0x800FD198-0x800FD264 size=204B
// PARKED: PS stack-spill/regalloc class (docs/parkings/06-paired-single-ops.md
//   M5.0j), same root as fn_800FD074. Semantically complete reconstruction of
//   the game's bytes (verified by hand against PS disassembly):
//   - copies 4 pairs arg1 -> arg2, keeping pair0/pair1 live in FPRs and a
//     ps_mr duplicate of pair2 (f13 = f12 idiom)
//   - subtracts position pairs arg0+0x10/arg0+0x18 from pairs 1..4 with mixed
//     stale-register vs reload sources (pair0/pair1 use stale regs, pair3/pair4
//     reload from arg2) - no single C shape produces that mix in 3.9.3
//   - two fn_8008757C(&sp8, arg0+0x60, ...) transforms; second call's r5 is
//     arg2+0x10 staged BEFORE call 1 returns (r28 saved reg)
//   - results stored back SWAPPED: sp8/spC -> arg2+0x10, sp10/sp14 -> arg2+0x18
//   - want saves r28/r29/r30 (arg2+0x10, arg0+0x60, arg2); ngccc folds the
//     derived pointers and saves fewer regs; ps_sub dead-store gap may also
//     apply (doc06 M5.0j). Needs the game's exact ProDG build.
// SEARCHED 2026-09-11 (tools/store_order_search.py): store/assignment block(s) re-ordered (reversed / ascending / descending); score now 17.6% ([2]rev->15.7% [1]rev->17.6%).
#include "types.h"
#include "structs.h"
extern void fn_8008757C(void *, Unk_DB0E2BAB *, CStruct *);

void fn_800FD198(Unk_BE223D5D *arg0, Unk_EA529D06 *arg1, Unk_EA529D06 *arg2) {
    __ps_t sp8[2];
    __ps_t p0;
    __ps_t p1;
    __ps_t p1b;
    __ps_t p2;
    __ps_t p3;

    p0 = arg1->unk0x0;
    arg2->unk0x0 = p0;
    p1 = arg1->unk0x8;
    arg2->unk0x8 = p1;
    p2 = arg1->unk0x10;
    arg2->unk0x10 = p2;
    p1b = p1;
    p3 = arg1->unk0x18;
    arg2->unk0x18 = p3;
    arg2->unk0x10 = arg2->unk0x10;
    p0 = p0 - arg0->unk0x10;
    arg2->unk0x0 = p0;
    p1b = p1b - arg0->unk0x18;
    arg2->unk0x8 = p1b;
    p2 = arg2->unk0x10 - arg0->unk0x10;
    arg2->unk0x10 = p2;
    p3 = arg2->unk0x18 - arg0->unk0x18;
    arg2->unk0x18 = p3;
    fn_8008757C((void *)sp8, (char *)arg0 + 0x60, (char *)arg2 + 0);
    arg2->unk0x8 = sp8[1];
    arg2->unk0x0 = sp8[0];
    fn_8008757C((void *)sp8, (char *)arg0 + 0x60, (char *)arg2 + 0x10);
    arg2->unk0x18 = sp8[1];
    arg2->unk0x10 = sp8[0];
}
