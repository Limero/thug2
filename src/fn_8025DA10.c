// Carved from the 0x8025D010-0x8025DF74 gap.
// range 0x8025DA10-0x8025DA54 (68B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// Small sibling of fn_8025D988: clears DABR, zeroes 0xCC006008,
// sets 0xCC00601C = 1, sets DABR. ProDG-compiled (stock game flags).
#include "types.h"

void fn_8025D944(void);
void fn_8025D964(void);

void fn_8025DA10(void) {
    fn_8025D944();
    *(volatile u32 *)0xCC006008 = 0;
    *(volatile u32 *)0xCC00601C = 1;
    fn_8025D964();
}
