// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8025A9CC-0x8025AA6C (160B). Byte-identical.
#include "types.h"
#include "structs.h"
typedef s32 (*trk_send_t)(char *, s32);
register s32 trk_ctx __asm__("r31");
register s32 trk_lr __asm__("r30");
void __attribute__((naked)) Vtable0x80308A40_m11(void) {
    register s32 r3v __asm__("r3");
    register s32 r4v __asm__("r4");
    register s32 r5v __asm__("r5");
    register s32 r6v __asm__("r6");
    register s32 r7v __asm__("r7");
    register s32 r8v __asm__("r8");
    register s32 r9v __asm__("r9");
    register s32 r10v __asm__("r10");
    s32 fpv;
    s32 send_ret;
    __asm__ volatile("mflr %0" : "=r"(trk_lr));
    r4v = 0;
    r5v = (s32)((char *)trk_ctx + 0x70C);
    r6v = (s32)(char *)0x80000000;
    __asm__ volatile("" : "+r"(r6v));
    r6v = ((Unk_2ACC9031 *)r6v)->unk0x30C8;
    if (r6v == 0) {
        goto done;
    }
    r7v = 0;
    r8v = 4;
    r9v = 8;
    r10v = 0xC;
    for (;;) {
        r4v = r4v + 1;
        __asm__ volatile("stwbrx %0,%1,%2" : : "r"(r6v), "r"(r7v), "r"(r5v));
        r3v = ((Unk_2ACC9031 *)r6v)->unk0x0;
        __asm__ volatile("stwbrx %0,%1,%2" : : "r"(r3v), "r"(r8v), "r"(r5v));
        r3v = ((Unk_2ACC9031 *)r6v)->unk0x14;
        __asm__ volatile("stwbrx %0,%1,%2" : : "r"(r3v), "r"(r9v), "r"(r5v));
        r3v = ((Unk_2ACC9031 *)r6v)->unk0x18;
        __asm__ volatile("stwbrx %0,%1,%2" : : "r"(r3v), "r"(r10v), "r"(r5v));
        r5v = r5v + 0x10;
        if (r4v == 0x40) {
            goto done;
        }
        r6v = ((Unk_2ACC9031 *)r6v)->unk0x4;
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
    __asm__ volatile("stwbrx %0,%1,%2" : : "r"(r4v), "r"(r6v), "r"(trk_ctx));
    r4v = r4v + 8;
    __asm__ volatile("addi %0,%1,0x700" : "=r"(r3v) : "r"(trk_ctx));
    __asm__ volatile("lwz %0,0x6a4(%%r31)" : "=r"(fpv));
    __asm__ volatile("" : "+r"(fpv) : "r"(r3v), "r"(r4v));
    send_ret = ((trk_send_t)fpv)((char *)r3v, r4v);
    __asm__ volatile("cmpwi %0,0\n\tbne fn_8025A6FC" : : "r"(send_ret));
    __asm__ volatile("mtlr %0\n\tblr" : : "r"(trk_lr));
}
