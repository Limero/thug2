// WIP DRAFT — hand rewrite from the retail disassembly (2026-10-18).
// Replaces the m2c fill (8.1% -> NEAR 80.4%, size-exact 368B). Prologue
// through the main enumerator loop is byte-exact; the two doloop tail
// fills match instruction-for-instruction except temp-reg colours.
// family=m2c range=0x8019D00C-0x8019D17C size=368B
//
// LEVERS THAT MOVED IT (reusable):
// - Callee audit FIRST: fn_8009C838 is 1-arg (Unk_C8FEE62D*) per its matched
//   file (src/fn_8009C838.c), not void; r3 already holds arg0 so no setup
//   changes, but the arity moves prologue scheduling (+8.7%). Same class as
//   the fn_800AF938 note in WIP.md (prototype shape moves prologue).
// - fn_80009B04 is 2-arg (matched src/fn_80009B04.c); r3 already holds the
//   Mem_NewZero result so no mr is emitted. Mem_NewZero symbol (not fn_).
// - 0x8019D9E4/0x8019DA3C/0x8019D7FC are FUNCTIONS (fn_ symbols): use
//   (s32)fn_... not int literals (symbol_ref vs CONST_INT schedules + encodes
//   differently: addi-borrow form vs ori form).
// - The pre-call callback values must be NAMED temps assigned between
//   Mem_NewZero and fn_80009B04 (cb1/cb2: +38% global-colour snap). A store-
//   position expression sinks below the bl; the want keeps lis/addi above.
//   Same for the loop consts (cbD/cbA born pre-loop, D7FC-first: fixes the
//   r28/r29 home swap; the stores must stay unk0x18-first in source).
// - Loop-2 pointer is two-step (q = arg0+0x38 early, q += 3 late) to repro
//   want's addi r8 + addi r9 pair.
// - Tail loops are plain do-while with separate decrement (doloop emits the
//   mtctr/bdnz pair, no asm needed).
// PARKED 80.4%: residual 18 words, ALL in the tail scalar setup (0xD0F8-):
// want coalesces each single-use const temp with one loop value (1/n1->r10,
// 0x12c/p->r9, 0x32/fill->r11; qbase solo r8) while ngccc pairs 1/qbase->r9
// and leaves n1 solo r8. Tried: n1-early/late birth, n1=1-then-0x20 shared
// var (splits webs instead of merging), fill0 local (contaminates to r7),
// r10 pin on n1 (global cascade to 76%). Per §6es finding 2 (post-reload
// RTL matches, only hard-reg colours differ) this is a local-alloc wall;
// needs a birth-order/processing-order lever, not more source shapes.
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "structs.h"

extern char lbl_802AAE90[];
extern char lbl_802AAEB8[];
extern char lbl_802AAEE0[];

void *fn_8009C838(Unk_C8FEE62D *);
void *Mem_NewZero(s32);
void *fn_80009B04(Unk_5EF41E38 *, void *);
void fn_8019D7FC(void);
void fn_8019D9E4(void);
void fn_8019DA3C(void);

void *fn_8019D00C(Unk_C3BA7E00 *arg0) {
    s32 idx;
    s32 zero;
    s32 one;
    CScript *t1;
    CScript *t2;
    CScript *t;
    s32 cb1;
    s32 cb2;
    s32 cbD;
    s32 cbA;
    char *p26;
    char *p27;
    s32 n1;
    s32 *p;
    s32 n2;
    s32 *q;
    s32 v;

    idx = 0;
    zero = 0;
    fn_8009C838((Unk_C8FEE62D *)arg0);
    one = 1;
    p27 = (char *)arg0 + 0x64;
    p26 = (char *)arg0 + 0x28;
    arg0->unk0x14 = (s32)lbl_802AAE90;
    t1 = Mem_NewZero(0x24);
    cb1 = (s32)fn_8019D9E4;
    fn_80009B04((Unk_5EF41E38 *)t1, (void *)-0x7D0);
    t1->unk0x1C = cb1;
    t1->unk0x20 = (s32)arg0;
    t1->unk0x18 = (s32)lbl_802AAEE0;
    arg0->unk0x18 = (s32)t1;
    t2 = Mem_NewZero(0x24);
    cb2 = (s32)fn_8019DA3C;
    fn_80009B04((Unk_5EF41E38 *)t2, (void *)-0x3E8);
    t2->unk0x18 = (s32)lbl_802AAEE0;
    t2->unk0x1C = cb2;
    t2->unk0x20 = (s32)arg0;
    arg0->unk0x1C = (s32)t2;
    cbD = (s32)fn_8019D7FC;
    cbA = (s32)lbl_802AAEB8;
    do {
        t = Mem_NewZero(0x30);
        fn_80009B04((Unk_5EF41E38 *)t, (void *)-0x3E8);
        t->unk0x24 = idx;
        t->unk0x18 = cbA;
        idx += 1;
        t->unk0x28 = cbD;
        t->unk0x2C = (s32)arg0;
        *(CScript **)p26 = t;
        *(s32 *)(p27 - 8) = zero;
        p26 += 4;
        *(s32 *)p27 = one;
        p27 += 0xC;
    } while (idx <= 3);
    arg0->unk0x190 = 1;
    arg0->unk0x50 = 0x12C;
    n1 = 0x20;
    arg0->unk0x54 = 0x32;
    q = (s32 *)((char *)arg0 + 0x38);
    arg0->unk0x198 = 0;
    arg0->unk0x48 = 0;
    p = (s32 *)((char *)arg0 + 0x18C);
    arg0->unk0x8C = 0;
    arg0->unk0x194 = 0;
    do {
        *p = 0;
        p -= 2;
        n1 -= 1;
    } while (n1 != 0);
    n2 = 4;
    q += 3;
    v = 3;
    do {
        *q = v;
        q -= 1;
        v -= 1;
        n2 -= 1;
    } while (n2 != 0);
    return arg0;
}
