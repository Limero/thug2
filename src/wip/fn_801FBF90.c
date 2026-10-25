// WIP DRAFT (non-matching) — hand-fixed from m2c: CStruct_new(8) is 1-arg
// chained into CStruct_ctor (recipe 23/§7a); fn_80129068 is 3-arg
// (handle, count, 0xA) with count field-passed in r4 (recipe 18); count
// tested via fused or. r31 (assign-in-condition).
//
// PARKED at 97.6% (82/84 words). Remaining diff = prologue save-order pair
// ONLY: want [mr r28,r3][mr r26,r4], got [mr r26,r4][mr r28,r3] (doc-15
// family, prologue param-home-copy emission order). Everything else EXACT.
// Structural analysis: arg0→r28 (pin), arg1→r26, idx→r27, handle→r29,
// temp→r30, count→r31 (or.-fused) recycled by walker→r31. The r30/r31
// temp↔walker swap was cracked by SPLITTING the alloc-result into TWO
// variables (btemp branch-site / ltemp loop-site) — merged single var gave
// got temp→r31/walker→r30 inverted. Tried: pins on a0 (decl-init + plain +
// both-pinned + decl-order swap + "+r" barrier), flags -fno-schedule-insns
// / -fno-schedule-insns2 / -fno-sched-spec / pairs / -fno-gcse (insns and
// insns2 fix or keep the prologue but scramble the loop-tail arg-setup
// rotations; sched-spec/gcse no-ops).
// Probe evidence (synthetic p1-p4 in /tmp, 3.9.3): param home copies emit
// in ASCENDING target-regno order (also seen in EXACT fn_801FB394:
// [r21][r23][r27]); want's [r28][r26] violates that, so one of the two
// copies must be a non-home insn — and cc1 always expands explicit pin
// copies AFTER the expand_used_vars home-copy group, so [r28-first] looks
// unreachable from standalone C. Declaring `S idx = 0;` as a top decl-init
// (inner assignment removed) shifts colors to idx→r26/mgr→r27/obj→r28 but
// keeps [mgr-copy][obj-copy]. Retry only if a new doc-15 lever lands.
// 2026-10: explicit-assign quadrant closed: plain pin decls + `a0=arg0;a1=arg1`
// (both assign orders, both decl orders) all emit [r26][r28] — same-cycle
// emission is ascending-regno regardless of program/pseudo order. Sched1 viz
// for the explicit form shows r26-copy on iu, r28-copy on iu2 with ready
// [13,16] (decl-init form has ready [16,13] yet emits the same [r26][r28]),
// so neither ready order nor unit assignment selects it; different-cycles is
// impossible for entry copies of incoming args (both ready t=1). Descending
// [r28][r26] stands unreachable from standalone C.
// family=m2c range=0x801FBF90-0x801FC0E0 size=336B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
// PROBED 2026-09-03: first-diff artifact = mr r28,r3 /
// mr r26,r4 prologue copy swap at 0x10/0x14 (doc-15 class).
#include "types.h"
#include "qb_constants.h"
#include "structs.h"
extern void AddInteger(CStruct *, s32, s32);
extern s32 fn_801FBE18(void);
extern s32 fn_801FBE3C(s32);
extern s32 CStruct_new(s32);
extern s32 CStruct_ctor(s32);
extern void fn_801FA068(s32, s32);
extern void fn_80127CD4(CStruct *, s32, s32);
extern void AddChecksum(CStruct *, s32, s32);
extern s32 fn_801FB334(Unk_C7387A53 *);
extern s32 fn_8003E7CC(s32);
extern s32 fn_80128F94(Unk_9D4ED6AF *);
extern void fn_80129068(Unk_5AA7B5D7 *, s32, s32);
extern void fn_80129314(CStruct *, s32, s32);
extern void AddArrayPointer(CStruct *, s32, s32);
extern void fn_8009F674(s32, s32);

void fn_801FBF90(void *arg0, s32 arg1) {
    s32 count;
    s32 handle;
    s32 btemp;
    s32 ltemp;
    s32 idx;
    CStruct *walker;
    register s32 a1 __asm__("r26") = arg1;
    register Unk_C7387A53 *a0 __asm__("r28") = arg0;

    AddInteger(a1, QB_NUMFREERAILPOINTS, fn_801FBE18());
    AddInteger(a1, QB_NUMFREERAILS, fn_801FBE3C(a0));
    if (a0->unk0x28 != NULL) {
        btemp = CStruct_ctor(CStruct_new(8));
        fn_801FA068(a0->unk0x28, btemp);
        fn_80127CD4(a1, QB_CURRENTRAIL, btemp);
    } else {
        AddChecksum(a1, QB_CURRENTRAIL, QB_NULL);
    }
    if ((count = fn_801FB334(a0)) != 0) {
        idx = 0;
        handle = fn_80128F94(fn_8003E7CC(0xC));
        fn_80129068(handle, count, 0xA);
        walker = a0->unk0x24;
        if (walker != NULL) {
            do {
                ltemp = CStruct_ctor(CStruct_new(8));
                fn_801FA068(walker, ltemp);
                fn_80129314(handle, idx++, ltemp);
                walker = walker->unk0x4;
            } while (walker != NULL);
        }
        AddArrayPointer(a1, QB_RAILS, handle);
    }
    fn_8009F674(a0, a1);
}
