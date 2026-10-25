// Carved from the 0x8025D010-0x8025DF74 gap (promoted from src/wip).
// range 0x8025D944-0x8025D964 (32B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// Clears DABR (SPR 0x3F5; cf. src/fn_8025ACDC.c). MetroTRK debugger region;
// ProDG-compiled (verified with stock game flags, no relocs).
#include "types.h"

void fn_8025D944(void) {
    volatile u32 dabr = 0;
    __asm__ volatile("lwz 3,%0\n\tmtspr 0x3f5,3\n\tisync" :: "m"(dabr));
}
