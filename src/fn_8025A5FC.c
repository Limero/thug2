// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8025A5FC-0x8025A610 (20B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
#include "structs.h"
void fn_8025A5FC(void) {
    register char *base __asm__("r3");
    register s32 val __asm__("r4");
    base = (char *)0x803A44A0;
    __asm__ volatile("" : "+r"(base));
    val = 1;
    ((Unk_9829ABF8 *)base)->unk0x6D4 = val;
}
// EXACT 100% (verified tools/test_wip_drafts.py --addr 0x8025A5FC).
// Recipe (new, portable): absolute-base+offset store that WANT keeps UNFOLDED
// (lis/ori of base, member offset on the store). Plain C folds the sum into
// one constant -> wrong split. Fix: pin base/value to their regs
// (register .. __asm__("rN")), put a volatile empty-asm "+r" barrier AFTER
// the base def so the offset cannot fold, and assign the value AFTER the
// barrier so li schedules below ori (want order: lis/ori/li/stw).
// Zone context: this whole cluster touches the TRK-style ctx block at
// .bss lbl_803A44A0 (size 0x8820); WANT materializes the base with lis+ORI
// (literal form, NOT symbol/addi form) everywhere.
