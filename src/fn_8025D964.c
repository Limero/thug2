// Carved from the 0x8025D010-0x8025DF74 gap (promoted from src/wip).
// range 0x8025D964-0x8025D988 (36B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// Sets DABR (SPR 0x3F5) to 0xCC00601E. Sibling of fn_8025D944 (clear).
// ProDG-compiled (verified with stock game flags, no relocs).
#include "types.h"

void fn_8025D964(void) {
    volatile u32 dabr = 0xCC00601E;
    __asm__ volatile("lwz 3,%0\n\tmtspr 0x3f5,3\n\tisync" :: "m"(dabr));
}
