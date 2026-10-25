// __check_pad3: CodeWarrior crt helper — reset iff all 0x0EEF Pad3 reset bits set.
// range=0x800032C0-0x80003300 size=64B
// Retail is MWCC-compiled (mflr-first prologue, pop-before-mtlr epilogue);
// ProDG/ngccc can never emit that shape. Build with mw_version="GC/1.2.5n"
// + cflags_gqr_mwcc + "-schedule off" (see configure.py). The -schedule off
// keeps the lis/lhz/andi/cmpwi chain above the li/bl block. mwcc always
// emits code to .text, so rename_section=".text=.init" routes it to the
// split's section (mwcc 1.2.5n has no section pragma). Byte-identical.
#include "types.h"

extern void OSResetSystem(s32, s32, s32);

void fn_800032C0(void) {
    if ((*(volatile u16 *)0x800030E4 & 0x0EEF) == 0x0EEF) {
        OSResetSystem(0, 0, 0);
    }
}
