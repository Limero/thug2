// Carved from the 0x8025D010-0x8025DF74 gap.
// range 0x8025D988-0x8025DA10 (136B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// EXI-debugger MMIO init: clears DABR, programs 0xCC006008-0xCC00601C,
// sets DABR. ProDG-compiled (stock game flags, store order as written).
#include "types.h"

void fn_8025D944(void);
void fn_8025D964(void);

void fn_8025D988(void *arg0) {
    fn_8025D944();
    *(volatile u32 *)0xCC006008 = 0x12000000;
    *(volatile u32 *)0xCC00600C = 0;
    *(volatile u32 *)0xCC006010 = 0x20;
    *(volatile u32 *)0xCC006018 = 0x20;
    *(volatile u32 *)0xCC006014 = (u32)arg0;
    *(volatile u32 *)0xCC00601C = 3;
    fn_8025D964();
}
