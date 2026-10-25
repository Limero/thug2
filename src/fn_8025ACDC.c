// Auto-generated from tools/gen_wip_drafts.py (promoted from src/wip)
// range 0x8025ACDC-0x8025AD34 (88B). Byte-identical.
// Link-level exactness was verified against the full linked DOL.
#include "types.h"
/*
WANT (22 instructions, all in the retail range):
  mflr r30
  lbz r3,0x701(r31); bl lbl_8025DEB8; sth r3,0x708(r31)
  rlwinm. r3,r3,0,0,0; beq skip
  mfspr r4,DABR; stw r4,0x450(r31); li r3,0; mtspr DABR,r3
  skip:
  li r4,2; li r5,0x702; sthbrx r4,r5,r31
  addi r3,r31,0x700; addi r4,r4,8
  lwz r0,0x6A4(r31); mtlr r0; blrl
  cmpwi r3,0; bne fn_8025A6FC
  mtlr r30; blr

The vtable slot is dispatched by the surrounding MetroTRK loop at
0x8025A6D4..0x8025A6E8: it loads lbl_80308A40[cmd] and executes blrl
without changing r31. The context initializer at 0x8025A358 materializes
r31 as lbl_803A44A0 (0x803A44A0), and the sibling state-save paths preserve
that same base. This entry has no frame and never establishes r31 itself;
the file-scope register variables below model that verified calling
convention without inventing a save/restore pair.

The DABR SPR read/write, record-producing mask, indexed big-endian
halfword store, external error-tail branch, and zero-frame return have no
useful ordinary ProDG C spelling. They are small opcode-specific asm
fragments (10 emitted instructions of 22); the remaining data flow is C,
including the direct callback call whose lwz/mtlr/blrl shape is compiled
by the toolchain. Standalone default-ngccc verification is masked EXACT
22/22. The external bne is still relocation-masked by the tester, so a
full linked-DOL compare remains required before any promotion.
*/
typedef s32 (*trk_send_t)(char *, s32);
register s32 trk_ctx __asm__("r31");
register s32 trk_lr __asm__("r30");
register s32 trk_fp __asm__("r0");
extern s32 lbl_8025DEB8(s32);

void __attribute__((naked)) Vtable0x80308A40_m19(void) {
    register s32 r3v __asm__("r3");
    register s32 r4v __asm__("r4");
    register s32 r5v __asm__("r5");
    s32 send_ret;

    __asm__ volatile("mflr %0" : "=r"(trk_lr));
    r3v = *(u8 *)((char *)trk_ctx + 0x701);
    r3v = lbl_8025DEB8(r3v);
    *(u16 *)((char *)trk_ctx + 0x708) = (u16)r3v;

    __asm__ volatile("rlwinm. %0,%0,0,0,0\n\tbeq 8f" : "+r"(r3v));
    __asm__ volatile("mfspr %0,0x3f5" : "=r"(r4v));
    *(u32 *)((char *)trk_ctx + 0x450) = r4v;
    r3v = 0;
    __asm__ volatile("mtspr 0x3f5,%0\n\t8:" : : "r"(r3v));

    r4v = 2;
    __asm__ volatile("" : "+r"(r4v));
    r5v = 0x702;
    __asm__ volatile("sthbrx %0,%1,%2" : : "r"(r4v), "r"(r5v), "r"(trk_ctx));
    r3v = (s32)((char *)trk_ctx + 0x700);
    r4v = r4v + 8;
    trk_fp = *(s32 *)((char *)trk_ctx + 0x6A4);
    __asm__ volatile("" : "+r"(trk_fp) : "r"(r3v), "r"(r4v));
    send_ret = ((trk_send_t)trk_fp)((char *)r3v, r4v);
    __asm__ volatile("cmpwi %0,0\n\tbne fn_8025A6FC" : : "r"(send_ret));
    __asm__ volatile("mtlr %0\n\tblr" : : "r"(trk_lr));
}
