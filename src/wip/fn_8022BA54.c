// PARKED 2026-10-01: 83.3% -> 95.83% (46/48). ONE register-declaration pin
// family=hand range=0x8022BA54-0x8022BB14 size=192B
// fixed most of residual (b)+(c) (docs/parkings/75 lever):
//
//      register void *pv9 __asm__("r9");
//
// on the SECOND `sub->unk0x10` reload (the one whose result is stored
// through).  The residual window needs THREE distinct registers -- r10 for the
// lbl_802FFE98 page anchor, r0 for the first reload, r9 for the second -- and
// unpinned ngccc only ever uses two, collapsing the reloads onto r10 and
// pushing the anchor into r9.  Pinning the second reload to r9 splits them.
// Same mechanism as fn_80191E8C/fn_8016D52C: the pin reserves the register
// that a DIFFERENT value wanted, and the allocator re-flows around it.
//
// Measured here: pin r9 -> 95.83% (best); pin the anchor to r10 -> 79.17%;
// to r11 -> 75.00%; pin the first reload to r0 -> 77.08%; move the `pg =
// lbl_802FFE98` assignment earlier in source -> 93.75% both ways (worse).
//
// REMAINING RESIDUAL (2 words, doc-73 class): want anchors lbl_802FFE98 in
// r10, got still uses r9.  ngccc's HI16 symbol-reload set is {r9, r11}
// (docs/parkings/73), and r9 is now pinned, so r11 is the documented fallback
// -- r10 is not reachable from C.  Pinning the anchor variable directly makes
// it worse (79%/75%, the pin forces the address through a register instead of
// a symbol_ref MEM).  Do NOT re-run the pin matrix above; this is a doc-73
// wall, not a scheduling one.
// PREVIOUS PARK NOTE (residual (a)) CLOSED 2026-10-12: the strncpy call-site
// arg-move now matches; dstp@r3 / srcp@r4 / both-pins variants all score
// 95.83% byte-identical to this body (same 2 doc-73 words). Remaining is ONLY
// the doc-73 anchor (r10 unreachable); no open lever left.
//
// MEASURED AND REJECTED (do not promote): splitting the page anchor from its
// load into two asm blocks -- `lis 10, lbl_802FFE98@ha` (r10 clobbered) ahead
// of the previous statement's load, `lwz %0, lbl_802FFE98@l(10)` at the use --
// reproduces the function exactly (2 of 48 words hand-written). That is a byte
// match, not a decompilation, so this draft stays parked. A combined
// two-instruction block anchors at the use and drags the neighbouring load off
// r0 (91.7%).
//#include "types.h"
#include "structs.h"
extern s32 lbl_80305F9C;
extern void *lbl_802FFE98;

s32 fn_80219680(CStruct *);
void fn_8000F2F8(Unk_9F352E7C *, s32);
void *Mem_NewZero(s32);
void *fn_80229404(void *, s32);
s32 strncpy(void *, void *, s32);
void fn_8000F320(Unk_F12C5E01 *);

void fn_8022BA54(void *arg0, void *arg1, s32 arg2) {
    Unk_27A1786C *item;
    void *prev;
    void *pg;
    register char *sub __asm__("r11");
    register void *pv9 __asm__("r9");

    if (fn_80219680((void *)lbl_80305F9C) != 0) {
        fn_8000F2F8(lbl_802FFE98, ((Unk_B0F19D72 *)lbl_802FFE98)->unk0x148);
    } else {
        fn_8000F2F8(lbl_802FFE98, ((Unk_B0F19D72 *)lbl_802FFE98)->unk0x134);
    }

    item = fn_80229404(Mem_NewZero(0x1F8), 0);
    item->unk0x30 = arg2;
    strncpy((char *)item + 0x3C, arg1, 0xF);

    sub = (char *)arg0 + 0xAC;
    item->unk0x4B = 0;
    prev = *((void * *)&((Unk_42076946 *)sub)->unk0x10);
    item->unk0xC = sub;
    item->unk0x10 = prev;
    pg = lbl_802FFE98;
    pv9 = *((void *volatile *)&((Unk_42076946 *)sub)->unk0x10);
    ((Unk_E266FB50_2 *)pv9)->unk0xC = item;
    *((void * *)&((Unk_42076946 *)sub)->unk0x10) = item;
    fn_8000F320(pg);
}
