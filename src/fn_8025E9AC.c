// Matched 2026-10-17 (mwcc region, GC/1.3.2 + cflags_dolphin).
// range 0x8025E9AC-0x8025EA48 size=0x9C (156B).
// One-shot ARAM uploader setup under an interrupt guard. If the CAB4C
// flag is clear: level = OSDisableInterrupts(); set the flag; stash
// arg1/arg2/arg0/arg0>>12 into the CA368/CAB40/CAB38/CAB44 slots; run
// F3E0 on fn_8025EA98's address (its lis feeds the base addi while r4
// itself stays 0x80260000 stale into the call, as do the r5 page shift
// and the r6 flag constant), then F298, F340, EA68, and
// OSRestoreInterrupts(level). Byte-identical: verified with full
// SDA/ADDR16 reloc resolution against the retail DOL.
#include "types.h"

extern s32 lbl_803CAB4C;
extern u32 lbl_803CA368;
extern u32 lbl_803CAB38;
extern u32 lbl_803CAB40;
extern u32 lbl_803CAB44;
extern void fn_8025EA98(u32 arg0);
extern void fn_8025F3E0(s32 arg0);
extern void fn_8025F298(void);
extern void fn_8025F340(void);
extern void fn_8025EA68(void);
s32 OSDisableInterrupts(void);
void OSRestoreInterrupts(s32 level);

void fn_8025E9AC(u32 arg0, u32 arg1, u32 arg2) {
    s32 level;

    if (lbl_803CAB4C == 0) {
        level = OSDisableInterrupts();
        lbl_803CAB4C = 1;
        lbl_803CA368 = arg1;
        lbl_803CAB40 = arg2;
        lbl_803CAB38 = arg0;
        lbl_803CAB44 = arg0 >> 12;
        fn_8025F3E0((s32)fn_8025EA98);
        fn_8025F298();
        fn_8025F340();
        fn_8025EA68();
        OSRestoreInterrupts(level);
    }
}
