// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8025AA6C-0x8025AB94 (296B). Byte-identical.
#include "types.h"
#include "structs.h"
typedef s32 (*trk_send_t)(char *, s32);
register s32 trk_ctx __asm__("r31");
register s32 trk_lr __asm__("r30");
void __attribute__((naked)) Vtable0x80308A40_m12(void) {
    register s32 r3v __asm__("r3");
    register s32 r4v __asm__("r4");
    register s32 r5v __asm__("r5");
    register s32 r6v __asm__("r6");
    register s32 r7v __asm__("r7");
    register s32 r8v __asm__("r8");
    register s32 r9v __asm__("r9");
    register s32 r10v __asm__("r10");
    register s32 r11v __asm__("r11");
    register s32 r12v __asm__("r12");
    register s32 r14v __asm__("r14");
    register s32 r15v __asm__("r15");
    register s32 r16v __asm__("r16");
    register s32 r17v __asm__("r17");
    register u32 r18v __asm__("r18");
    s32 fpv;
    s32 send_ret;
    __asm__ volatile("mflr %0" : "=r"(trk_lr));
    r4v = 0;
    r5v = (s32)((char *)trk_ctx + 0x70C);
    r6v = (s32)(char *)0x80000000;
    __asm__ volatile("" : "+r"(r6v));
    r6v = ((Unk_7535F8AF *)r6v)->unk0xDC;
    if (r6v == 0) {
        goto done;
    }
    r7v = 0;
    r8v = 4;
    r9v = 8;
    r10v = 0xC;
    r11v = 0x10;
    r12v = 0x14;
    r14v = 0x18;
    r15v = 0x1C;
    r16v = 0x20;
    for (;;) {
        r4v = r4v + 1;
        __asm__ volatile("stwbrx %0,%1,%2" : : "r"(r6v), "r"(r7v), "r"(r5v));
        r3v = ((Unk_7535F8AF *)r6v)->unk0x2C8;
        __asm__ volatile("stwbrx %0,%1,%2" : : "r"(r3v), "r"(r8v), "r"(r5v));
        r3v = ((Unk_7535F8AF *)r6v)->unk0x2CC;
        __asm__ volatile("stwbrx %0,%1,%2" : : "r"(r3v), "r"(r9v), "r"(r5v));
        r3v = ((Unk_7535F8AF *)r6v)->unk0x2D0;
        __asm__ volatile("stwbrx %0,%1,%2" : : "r"(r3v), "r"(r10v), "r"(r5v));
        r3v = ((Unk_7535F8AF *)r6v)->unk0x2D4;
        __asm__ volatile("stwbrx %0,%1,%2" : : "r"(r3v), "r"(r11v), "r"(r5v));
        r3v = ((Unk_7535F8AF *)r6v)->unk0x2D8;
        __asm__ volatile("stwbrx %0,%1,%2" : : "r"(r3v), "r"(r12v), "r"(r5v));
        r3v = ((Unk_7535F8AF *)r6v)->unk0x2F0;
        __asm__ volatile("stwbrx %0,%1,%2" : : "r"(r3v), "r"(r14v), "r"(r5v));
        /* nested list 1: node->0x2E8 chain via ->0x2E0 */
        r18v = 0;
        __asm__ volatile("" : "+r"(r18v));
        r3v = ((Unk_7535F8AF *)r6v)->unk0x2E8;
        r17v = r5v + 0x24;
    nl1:
        if (r3v == 0) {
            goto nl1done;
        }
        __asm__ volatile("stwbrx %0,%1,%2" : : "r"(r3v), "r"(r18v), "r"(r17v));
        r18v = r18v + 4;
        r3v = ((Unk_75645628 *)r3v)->unk0x2E0;
        goto nl1;
nl1done:
        r17v = r17v + r18v;
        r18v = r18v >> 2;
        __asm__ volatile("stwbrx %0,%1,%2" : : "r"(r18v), "r"(r15v), "r"(r5v));
        /* nested list 2: node->0x2F4 chain via ->0x10 */
        r18v = 0;
        __asm__ volatile("" : "+r"(r18v));
        r3v = ((Unk_7535F8AF *)r6v)->unk0x2F4;
    nl2:
        if (r3v == 0) {
            goto nl2done;
        }
        __asm__ volatile("stwbrx %0,%1,%2" : : "r"(r3v), "r"(r18v), "r"(r17v));
        r18v = r18v + 4;
        r3v = ((Unk_75645628 *)r3v)->unk0x10;
        goto nl2;
nl2done:
        r17v = r17v + r18v;
        r18v = r18v >> 2;
        __asm__ volatile("stwbrx %0,%1,%2" : : "r"(r18v), "r"(r16v), "r"(r5v));
        r5v = r17v;
        {
            register s32 t40 __asm__("r4");
            __asm__ volatile("" : "+r"(t40) : "r"(r17v), "r"(r5v));
            if (t40 == 0x40) {
                goto done;
            }
        }
        r6v = ((Unk_7535F8AF *)r6v)->unk0x2FC;
        if (r6v == 0) {
            goto done;
        }
    }
done:
    __asm__ volatile("addi %0,%1,0x708" : "=r"(r3v) : "r"(trk_ctx));
    r6v = 0;
    __asm__ volatile("" : "+r"(r6v));
    __asm__ volatile("stwbrx %0,%1,%2" : : "r"(r4v), "r"(r6v), "r"(r3v));
    r6v = 0x702;
    __asm__ volatile("" : "+r"(r6v));
    r4v = r5v - r3v;
    __asm__ volatile("sthbrx %0,%1,%2" : : "r"(r4v), "r"(r6v), "r"(trk_ctx));
    r4v = r4v + 8;
    __asm__ volatile("addi %0,%1,0x700" : "=r"(r3v) : "r"(trk_ctx));
    __asm__ volatile("lwz %0,0x6a4(%%r31)" : "=r"(fpv));
    __asm__ volatile("" : "+r"(fpv) : "r"(r3v), "r"(r4v));
    send_ret = ((trk_send_t)fpv)((char *)r3v, r4v);
    __asm__ volatile("cmpwi %0,0\n\tbne fn_8025A6FC" : : "r"(send_ret));
    __asm__ volatile("mtlr %0\n\tblr" : : "r"(trk_lr));
}
