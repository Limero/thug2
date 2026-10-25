// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8025A7A8-0x8025A7F8 (80B). Byte-identical.
#include "types.h"
#include "structs.h"
typedef s32 (*trk_send_t)(char *, s32);
extern s32 fn_8025A1D0(char *, char *, s32);
register s32 trk_ctx __asm__("r31");
register s32 trk_lr __asm__("r30");
void __attribute__((naked)) Vtable0x80308A40_m2(void) {
    register s32 r3v __asm__("r3");
    register s32 r4v __asm__("r4");
    register s32 r5v __asm__("r5");
    register s32 r6v __asm__("r6");
    register s32 r29v __asm__("r29");
    s32 fpv;
    s32 send_ret;
    __asm__ volatile("mflr %0" : "=r"(trk_lr));
    r6v = 0x704;
    __asm__ volatile("" : "+r"(r6v));
    __asm__ volatile("lwbrx %0,%1,%2" : "=r"(r4v) : "r"(r6v), "r"(trk_ctx));
    __asm__ volatile("addi %0,%1,0" : "=r"(r5v) : "r"(trk_ctx));
    r4v = r4v + r5v;
    r3v = (s32)((char *)trk_ctx + 0x708);
    r6v = 0x702;
    __asm__ volatile("lhbrx %0,%1,%2" : "=r"(r5v) : "r"(r6v), "r"(trk_ctx));
    r29v = r5v;
    fn_8025A1D0((char *)r3v, (char *)r4v, r5v);
    r3v = (s32)((char *)trk_ctx + 0x700);
    __asm__ volatile("" : "+r"(r3v));
    r4v = r29v;
    __asm__ volatile("" : "+r"(r4v) : "r"(r3v));
    r4v = r4v + 8;
    __asm__ volatile("" : "+r"(r4v));
    fpv = ((Unk_B31C2A27 *)trk_ctx)->unk0x6A4;
    __asm__ volatile("" : "+r"(fpv) : "r"(r3v), "r"(r4v));
    send_ret = ((trk_send_t)fpv)((char *)r3v, r4v);
    __asm__ volatile("cmpwi %0,0\n\tbne fn_8025A6FC" : : "r"(send_ret));
    __asm__ volatile("mtlr %0\n\tblr" : : "r"(trk_lr));
}
