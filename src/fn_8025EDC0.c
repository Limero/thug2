// Promoted from src/wip 2026-10-09 (TRK accessor cluster, hand-decompiled).
// range 0x8025EDC0-0x8025EE04 (68B). Byte-identical: tools/sda_verify.py LINK-SIM EXACT
// plus full-build `cmp` against the retail DOL.
// TRK state dispatcher: switch (lbl_803CA368[3]) { 0: fn_8025EE04; 1: fn_8025EFD4; default: fn_8025F068; }.
// The r13-relative global accesses need the per-object -msdata=eabi -G4 override.
// extra_cflags: -msdata=eabi, -G4
#include "types.h"

extern s32 lbl_803CA368;
void fn_8025EE04(void);
void fn_8025EFD4(void);
void fn_8025F068(void);

void fn_8025EDC0(void) {
    volatile double _dummy; /* issue-01 +8 headroom: want frame 0x10 / LR 0x14 */
    if (((s32 *)&lbl_803CA368)[3] == 0) {
        fn_8025EE04();
    } else if (((s32 *)&lbl_803CA368)[3] == 1) {
        fn_8025EFD4();
    } else {
        fn_8025F068();
    }
}