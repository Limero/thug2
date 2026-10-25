// Promoted from src/wip 2026-10-09 (TRK accessor cluster, hand-decompiled).
// range 0x8025EA68-0x8025EA98 (48B). Byte-identical: tools/sda_verify.py LINK-SIM EXACT
// plus full-build `cmp` against the retail DOL.
// Arena-low bookkeeping: save OSGetArenaLo() into lbl_803CAB3C, then OSSetArenaLo(lo + lbl_803CAB38). The explicit `o` local before the store is load-bearing (puts the load ahead of the store).
// The r13-relative global accesses need the per-object -msdata=eabi -G4 override.
// extra_cflags: -msdata=eabi, -G4
#include "types.h"

extern u32 lbl_803CAB38;
extern u32 lbl_803CAB3C;
void *OSGetArenaLo(void);
void OSSetArenaLo(void *);

void fn_8025EA68(void) {
    volatile double _dummy; /* issue-01 +8 headroom: want frame 0x10 / LR 0x14 */
    void *t;
    u32 o;

    t = OSGetArenaLo();
    o = lbl_803CAB38;
    lbl_803CAB3C = (u32)t;
    OSSetArenaLo((char *)t + o);
}