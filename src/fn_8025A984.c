// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8025A984-0x8025A9CC (72B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
// IDENTIFIED (2026-09-01): named Vtable0x80308A40_m8 (vtable slot 8 of the
// 0x80308A40 object) — MetroTRK send-path vtable method. Writes a byte-reversed
// header (stwbrx r5,0x704 / sthbrx 4,0x702) into the r31 context buffer, then
// calls the send function pointer at ctx+0x6A4; on nonzero return tails to
// fn_8025A6FC (shared error path), else returns. Match notes: mwcc codegen —
// naked attr + file-scope register pins r31/r30; tail must be the promoted
// sibling idiom (cmpwi %0,0\n\tbne fn_8025A6FC then mtlr/blr), not an if-form
// (which emits an extra trailing b and overshoots the 72B symbol).
#include "types.h"
#include "structs.h"
typedef s32 (*trk_send_t)(char *, s32);
register s32 trk_ctx __asm__("r31");
register s32 trk_lr __asm__("r30");
void __attribute__((naked)) Vtable0x80308A40_m8(void) {
    register s32 r3v __asm__("r3");
    register s32 r4v __asm__("r4");
    register s32 r6v __asm__("r6");
    s32 fpv;
    s32 send_ret;
    __asm__ volatile("mflr %0" : "=r"(trk_lr));
    r3v = ((Unk_B31C2A27 *)trk_ctx)->unk0x6BC;
    ((Unk_B31C2A27 *)trk_ctx)->unk0x708 = r3v;
    __asm__ volatile("" ::: "memory");
    {
        register s32 r5v __asm__("r5");
        r5v = ((Unk_B31C2A27 *)trk_ctx)->unk0x6D4;
        __asm__ volatile("" : "+r"(r5v));
        r6v = 0x704;
        __asm__ volatile("" : "+r"(r6v) : "r"(r5v));
        __asm__ volatile("stwbrx %0,%1,%2" : : "r"(r5v), "r"(r6v), "r"(trk_ctx));
    }
    r4v = 4;
    r6v = 0x702;
    __asm__ volatile("sthbrx %0,%1,%2" : : "r"(r4v), "r"(r6v), "r"(trk_ctx));
    __asm__ volatile("" : "+r"(r4v));
    r3v = (s32)((char *)trk_ctx + 0x700);
    r4v = r4v + 8;
    fpv = ((Unk_B31C2A27 *)trk_ctx)->unk0x6A4;
    __asm__ volatile("" : "+r"(fpv) : "r"(r3v), "r"(r4v));
    send_ret = ((trk_send_t)fpv)((char *)r3v, r4v);
    __asm__ volatile("cmpwi %0,0\n\tbne fn_8025A6FC" : : "r"(send_ret));
    __asm__ volatile("mtlr %0\n\tblr" : : "r"(trk_lr));
}
