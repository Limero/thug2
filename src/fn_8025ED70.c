// Promoted from src/wip 2026-10-09 (TRK accessor cluster, hand-decompiled).
// range 0x8025ED70-0x8025EDA0 (48B). Byte-identical: tools/sda_verify.py LINK-SIM EXACT
// plus full-build `cmp` against the retail DOL.
// TRK dispatch shim: fn_8025F808(); fn_8025EDB8(1); fn_8025EDB0(0).
// The r13-relative global accesses need the per-object -msdata=eabi -G4 override.
// extra_cflags: -msdata=eabi, -G4
#include "types.h"

extern void fn_8025F808(void);
void fn_8025EDB8(s32);
void fn_8025EDB0(s32);

void fn_8025ED70(void) {
    volatile double _dummy; /* issue-01 +8 headroom: want frame 0x10 / LR 0x14 */
    fn_8025F808();
    fn_8025EDB8(1);
    fn_8025EDB0(0);
}