// Promoted from src/wip 2026-10-15 (mwcc region).
// range 0x8025EC94-0x8025ED48 size=0xB4 (180B).
// Byte-identical: verified with full SDA/ADDR16 reloc resolution
// against the retail DOL (mwcc GC/1.3.2 + cflags_dolphin).
//
// ARAM download helper: w = F6E4(arg); level = OSDisableInterrupts(); spin
// on ARGetDMAStatus; latch IRQ status; DCFlushRange(w, 0x1000);
// ARStartDMA(0, w, F1D4(arg), 0x1000); spin; if IRQ was 0,
// __ARClearInterrupt(); OSRestoreInterrupts(level); return F26C(arg).
// (F26C returns void; the trailing call takes arg0, so this function
// itself returns void.)
// Load-bearing details: s32 (not u32) arg0 with no cast at the call sites,
// and declaration order w/irq/level (callee-saved colouring: arg0 -> r28,
// level -> r29, irq -> r30, w -> r31).
#include "types.h"

extern u32 fn_8025F6E4(u32 arg0);
extern u32 fn_8025F1D4(s32 arg0);
extern void fn_8025F26C(s32 arg0);
extern s32 OSDisableInterrupts(void);
extern void OSRestoreInterrupts(s32 level);
extern u32 ARGetDMAStatus(void);
extern u16 __ARGetInterruptStatus(void);
extern void __ARClearInterrupt(void);
extern void ARStartDMA(u32 type, u32 mainmem_addr, u32 aram_addr, u32 length);
extern void DCFlushRange(void *addr, u32 len);

void fn_8025EC94(s32 arg0) {
    u32 w;
    s32 irq;
    s32 level;

    w = fn_8025F6E4(arg0);
    level = OSDisableInterrupts();
    while (ARGetDMAStatus() != 0) {
    }
    irq = __ARGetInterruptStatus();
    DCFlushRange((void *)w, 0x1000);
    ARStartDMA(0, w, fn_8025F1D4(arg0), 0x1000);
    while (ARGetDMAStatus() != 0) {
    }
    if (irq == 0) {
        __ARClearInterrupt();
    }
    OSRestoreInterrupts(level);
    fn_8025F26C(arg0);
}
