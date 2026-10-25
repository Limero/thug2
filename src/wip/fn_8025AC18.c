// WIP DRAFT — hand-written from disassembly (PARKED)
// family=hand range=0x8025AC18-0x8025ACDC size=196B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "qb_constants.h"
/*
PARK ANALYSIS (isolated audit 2026-09-25):
VERIFIED ENTRY/ABI:
  - The range is exactly 49 instructions / 196 bytes. Its literal entry is
    `mflr r30`; there is no stwu, no stack frame, and no write/save of r31.
    r31 is first consumed at +0x60 (`addi r3,r31,0x708`).
  - The table dispatcher at 0x8025A6D4..0x8025A6E8 already uses incoming r31,
    loads lbl_80308A40[command], and reaches slot 18 with `mtlr/blrl`. Thus the
    context pointer is genuinely caller-established; r31 is not a compiler
    prologue artifact.
BOUNDED C ATTEMPT:
  - `naked` plus SCALAR file-scope r31/r30 register variables expresses the
    nonstandard entry without inventing a frame. The body below remains mostly
    C (9 emitted asm instructions / 49 = 18.4%, not whole-body asm).
  - Short asm windows cover only the ABI-critical idioms: callee-CR0
    consumption after fn_8025ABEC, fn_8025AC04's r4-preserving return, the
    byte-reversed halfword store, and the shared error branch / explicit LR
    return. The indirect send call is plain C.
  - Project ProDG compile verification succeeds: diff_near.py reports 19/51 aligned
    masked words (37.3%), with GOT=204B versus WANT=196B.
EXACT TECHNICAL BLOCKER:
  - WANT's copy is two updating pairs, `lwzu/stwu` x2. Both plain and volatile
    pre-increment C collapse the source pointer into rematerialized addresses
    0x80000028/0x8000002C plus `lwz`, while ngccc also hoists the
    fn_8025A1D0 address/size constants between the second load and store. This
    changes the sequence by one instruction and shifts the otherwise matching
    sthbrx/indirect-call/error tail by four bytes.
  - The GX FIFO block is structurally exact but still has three scheduler/
    materialization differences: two li/ori completion swaps and want's
    `lis r4,0x1200` versus ngccc's `li r4,0x1200`.
  - The CR-across-call, incoming-r31, and external-branch features are therefore
    NOT standalone blockers once handled by the short sanctioned asm windows.
    Link-level identity was not attempted because this isolated draft remains
    unregistered and the task forbids build/split/promotion changes.
*/
typedef s32 (*trk_send_t)(char *, s32);
register s32 trk_ctx __asm__("r31");
register s32 trk_lr __asm__("r30");

extern void DCInvalidateRange(void *addr, unsigned int n);
extern void fn_8025ABEC(void);
extern void fn_8025AC04(s32 *status);
extern s32 fn_8025A1D0(void *dst, const void *src, s32 len);

void __attribute__((naked)) Vtable0x80308A40_m18(void) {
    register s32 r3v __asm__("r3");
    register s32 r4v __asm__("r4");
    register s32 r5v __asm__("r5");
    volatile u32 *dst;
    volatile u32 *src;
    s32 fpv;
    s32 send_ret;

    __asm__ volatile("mflr %0" : "=r"(trk_lr));
    __asm__ volatile("bl fn_8025ABEC\n\tbne 8f" ::: "memory");

    r4v = 0x20;
    DCInvalidateRange((void *)0x803ACCC0, r4v);
    r3v = QB_UNKNOWN_0xCC006000;
    r4v = 0x14;
    *(volatile u32 *)(r3v + 0x00) = r4v;
    r4v = 0x1200;
    *(volatile u32 *)(r3v + 0x08) = r4v;
    r4v = 0;
    *(volatile u32 *)(r3v + 0x0C) = r4v;
    *(volatile u32 *)(r3v + 0x10) = r4v;
    r4v = 0x803ACCC0;
    *(volatile u32 *)(r3v + 0x14) = r4v;
    r4v = 0x20;
    *(volatile u32 *)(r3v + 0x18) = r4v;
    r4v = 3;
    *(volatile u32 *)(r3v + 0x1C) = r4v;
    r4v = 3;
    __asm__ volatile("bl fn_8025AC04" ::: "memory");
    __asm__ volatile("8:");
    dst = (volatile u32 *)((s32)trk_ctx + 0x708);
    *dst = r4v;
    src = (volatile u32 *)0x80000024;
    r5v = *++src;
    *++dst = r5v;
    r5v = *++src;
    *++dst = r5v;
    r3v = (s32)dst + 4;
    r4v = 0x803ACCC0;
    r5v = 0x20;
    fn_8025A1D0((void *)r3v, (const void *)r4v, r5v);
    r4v = 0x2C;
    r5v = 0x702;
    __asm__ volatile("sthbrx %0,%1,%2" : : "r"(r4v), "r"(r5v), "r"(trk_ctx));
    r3v = (s32)trk_ctx + 0x700;
    r4v = r4v + 8;
    fpv = *(s32 *)((s32)trk_ctx + 0x6A4);
    __asm__ volatile("" : "+r"(fpv) : "r"(r3v), "r"(r4v));
    send_ret = ((trk_send_t)fpv)((char *)r3v, r4v);
    __asm__ volatile("cmpwi %0,0\n\tbne fn_8025A6FC" : : "r"(send_ret));
    __asm__ volatile("mtlr %0\n\tblr" : : "r"(trk_lr));
}
