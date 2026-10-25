// PARKED 2026-10-21: 94.3% (34/34 words, size-exact 136B); 2 words differ, both
// in the then-branch store pair, which is emitted in the opposite order.
// The then-branch keeps the two MMIO reads and both address adjustments in one
// run (load CD04, load CD08, +0x400, -1) and parks the results in locals before
// storing, so the stores are what remains: the body below emits the CD08 store
// before the CD04 store, retail emits CD04 first.
// MEASURED (all on the body below, size-exact every time): writing the two
// stores in the other order drops to 82.9% (the loads stop being hoisted above
// them); assigning +0x400 / -1 at read time, folding the constants into the
// stores, a temp per store, chained/compound forms, and both declaration
// orders all stay at 82.9-94.3% with this same last pair swapped. So the wall
// is the scheduler's tie-break between two volatile stores with equal
// priority, not the source spelling. Frame, anchors (r31 for CD04, r10 for
// CD08), the call sequence, the else arm and the argument setup are exact.
// WIP DRAFT (non-matching) — hand decode.
// family=hand range=0x8025D1FC-0x8025D284 size=136B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// STRUCTURE: EXI poll/select one-shot. Snapshots CD04 (r29, kept across the
// calls), writes 0x1000 to the PI/EXI selector, calls the poll helper, then
// branches on the CD08 countdown:
//   CD08 != 0 : CD04 += 0x400, CD08--, usw = 0x400
//   CD08 == 0 : usw = CD0C, CD0C = 0 (the zero is CD08's value)
// then CCAC and CCFV(cd04, usw).
//
// The three bss words behave as VOLATILE hardware/command state: retail
// re-reads CD04 and CD08 for the read-modify-write (it does not reuse the
// snapshot or the tested value), and the CD0C store reuses the register that
// held the tested CD08 value.  That is exactly the codegen a volatile
// `s32 v = CDxx;` followed by `CDxx = v +/- k;` produces, so the body below
// qualifies every CD access volatile and keeps CD08 in a local.
//
// The 0x1000 selector is a named local assigned before the CD04 snapshot:
// retail births its constant before the snapshot load and stores it after
// both page anchors, which a local declaration reproduces.
//
// Helpers need lbl_ entries at promote time (no size needed).
#include "types.h"

extern u8 lbl_803ACEE8[];
extern u8 lbl_803ADEE0[];
extern u8 gap_05_803AD0E0_bss[];
void fn_8025D1A0(void);
void fn_8025CCAC(void);
void fn_8025CCFC(s32, s32);

#define CD04 (*(volatile s32 *)(lbl_803ACEE8 - 0x1E4))
#define CD08 (*(volatile s32 *)(lbl_803ADEE0 - 0x11D8))
#define CD0C (*(volatile s32 *)(gap_05_803AD0E0_bss - 0x3D4))

void fn_8025D1FC(void) {
    u32 ctrl = 0x1000;
    s32 cd04 = CD04;
    s32 cd08;
    s32 usw;
    s32 cur;
    s32 cnt;

    *(volatile u32 *)0xCC003000 = ctrl;
    fn_8025D1A0();
    cd08 = CD08;
    if (cd08 != 0) {
        cur = CD04 + 0x400;
        cnt = CD08;
        CD08 = cnt - 1;
        CD04 = cur;
        usw = 0x400;
    } else {
        usw = CD0C;
        CD0C = cd08;
    }
    fn_8025CCAC();
    fn_8025CCFC(cd04, usw);
}
