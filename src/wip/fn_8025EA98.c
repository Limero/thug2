// WIP DRAFT (non-matching) — hand-written from disasm 2026-10-09.
// family=hand range=0x8025EA98-0x8025EC94 size=508B
// INERT: not wired in configure.py — never compiled.
// ARAM DMA upload + debugger-hook dispatch. t0 = tb_conv() below; run the
// EDC0 dispatcher; idx = its r3 result (EE04/EFD4/F068 return it);
// base = CAB3C + (idx << 12); spin on ARGetDMAStatus; latch the IRQ status;
// if F710(idx) is nonzero and F61C(entry) is nonzero, run the F26C +
// DCFlushRange + F1D4 + ARStartDMA(0) upload (flag = 1); then F540(entry,
// idx). F284(aligned) path downloads the other way (F1D4 + ARStartDMA(1) +
// DCInvalidateRange + ICInvalidateRange), else F214/F234. Then F4AC,
// OSRestoreInterrupts, and if the CAB48 hook is set: t1 = tb_conv() and
// hook(arg, base, idx, delta = t1 - t0 in r6, flag in r7) via bctrl.
// The tb_conv() op sequence (slwi/rlwimi/mulhwu/__div2i) and the exact
// idx-from-r3 pickup are promotion work; only the call structure is
// transcribed here.
// BASELINE 2026-10-11 (first measurement; tools/mwcc_cmp.py +
// manual masked compare): GC/1.3.2 = 512B (+1 word), 8% masked (116/127
// diffs); GC/1.2.5n = 644B (wrong family). So 1.3.2 is confirmed as the
// region compiler (matches the E9AC-cluster note) and the call-structure
// transcription is nearly size-correct, but content needs the full mwcc
// rebuild (tb_conv inline shape, idx pickup, call arg order). PARKED for a
// dedicated mwcc session — not a quick win.
#include "types.h"

extern u32 lbl_803CAB3C;
extern u32 lbl_803CAB48;
extern s32 fn_8025EA50(void);
extern void fn_8025EDC0(void);
extern u32 fn_8025F710(s32 arg0);
extern u32 fn_8025F61C(u32 arg0);
extern void fn_8025F26C(s32 arg0);
extern u32 fn_8025F1D4(s32 arg0);
extern u32 fn_8025F214(s32 arg0);
extern void fn_8025F234(s32 arg0);
extern u32 fn_8025F284(s32 arg0);
extern void fn_8025F4AC(u32 arg0, u32 arg1, u32 arg2);
extern void fn_8025F540(s32 arg0, u32 arg1);
extern s32 OSDisableInterrupts(void);
extern void OSRestoreInterrupts(s32 level);
extern u64 OSGetTime(void);
extern u32 ARGetDMAStatus(void);
extern u16 __ARGetInterruptStatus(void);
extern void __ARClearInterrupt(void);
extern void ARStartDMA(u32 type, u32 mainmem_addr, u32 aram_addr, u32 length);
extern void DCFlushRange(void *addr, u32 len);
extern void DCInvalidateRange(void *addr, u32 len);
extern void ICInvalidateRange(void *addr, u32 len);
extern u64 __div2i(u32 hi, u32 lo, u32 x, u32 den);

static u32 tb_conv(void) {
    u64 t = (u64)OSGetTime() << 3;
    u32 m = *(volatile u32 *)0x800000F8 >> 2;
    u32 h = (u32)(((u64)0x431BDE83 * m >> 32) >> 15);

    return (u32)__div2i((u32)(t >> 32), (u32)t, 0, h);
}

void fn_8025EA98(u32 arg0) {
    u32 t0;
    u32 idx;
    u32 base;
    u32 entry;
    u32 aligned;
    u32 flag;
    s32 level;
    u16 irq;

    t0 = tb_conv();
    fn_8025EDC0();
    idx = 0; /* promotion: pick up EDC0's r3 result */
    base = lbl_803CAB3C + (idx << 12);
    entry = fn_8025F710((s32)idx);
    level = OSDisableInterrupts();
    while (ARGetDMAStatus() != 0) {
    }
    irq = __ARGetInterruptStatus();
    flag = 0;
    if (entry != 0 && fn_8025F61C(entry) != 0) {
        fn_8025F26C((s32)entry);
        flag = 1;
        DCFlushRange((void *)base, 0x1000);
        ARStartDMA(0, base, fn_8025F1D4((s32)entry), 0x1000);
        while (ARGetDMAStatus() != 0) {
        }
    }
    if (entry != 0) {
        fn_8025F540((s32)entry, idx);
    }
    aligned = arg0 & 0xFFFFF000;
    if (fn_8025F284((s32)aligned) != 0) {
        ARStartDMA(1, base, fn_8025F1D4((s32)aligned), 0x1000);
        while (ARGetDMAStatus() != 0) {
        }
        DCInvalidateRange((void *)base, 0x1000);
        ICInvalidateRange((void *)base, 0x1000);
    } else if (fn_8025F214((s32)aligned) == 0) {
        fn_8025F234((s32)aligned);
    }
    if (irq == 0) {
        __ARClearInterrupt();
    }
    fn_8025F4AC(aligned, base, idx);
    OSRestoreInterrupts(level);
    if (lbl_803CAB48 != 0) {
        /* hook(arg0, base, idx, tb_conv() - t0, flag) via bctrl */
    }
}
