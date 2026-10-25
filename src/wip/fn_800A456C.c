// PARKED 2026-10-03: NEAR 55.2% masked; got 464B == want 464B (116 words),
//   object .text == symbol size, no private .rodata, no asm. Baseline was
//   DIFF 13.8% — UP 41 points, and the body is now instruction-for-instruction
//   identical to the want apart from the residuals listed below. Reproduce:
// LEAF_TMPDIR=<scratch> tools/venv/bin/python tools/test_wip_drafts.py --addr 0x800A456C
// LEAF_TMPDIR=<scratch> tools/venv/bin/python tools/want_vs_got.py 0x800A456C
//
// WHAT WENT IN (all four are semantic, all four are load-bearing — do not
// revert them, they take the body from 13.8% to 55%):
//   (1) NO local `n`: read `self->n` at each use site (the `if`, the count
//       loop's `i = self->n`, `m = self->n - cnt`, `m < self->n`).  m2c's
//       `s32 n` local deletes one word: retail has
//         0x800A458C lwz r0,4(r31) / 0x800A4594 mr r3,r0
//       i.e. one CSE load into a *temp* + a copy into the long-lived home, and
//       the loop's own reload dest is r0 so the temp dies in the loop.  With a
//       real `n` local ngccc folds the load straight into n's reg and emits no
//       `mr` (body goes 1 word short = 460B = DIFF again).
//   (2) Branch polarity in the copy loop.  `if (sp->unk4 == h) {delete} else
//       {copy}` makes ngccc emit `bne .Lcopy` + the DELETE block INLINE and put
//       the copy block out of line.  Retail is `beq .Ldelete` + the COPY block
//       inline (0x800A46AC/0x800A46B0), so write
//       `if (h != QB_NULL_SCRIPT) {copy} else {delete}`.
//   (3) The copy block reads unk8/unkC into locals BEFORE the stores:
//         lwzx r0,r28,r9 / lwz r9,8(r3) / lwz r11,0xc(r3) / stw x5 / lwz r0,0x10(r3) / stw
//       Five independent `dp->f = sp->f;` statements compile to a load/store
//       interleave (11 words, one word too many).  With `v8`/`vC` temps and
//       `h` holding unk4 the block becomes byte-exact 0x800A46B4..0x800A46D8.
//       unk0 keeps its `*(s32 *)((char *)self->arr + off)` spelling (m2c is
//       right) — that is what yields the indexed `lwzx r0, r28, r9`.
//   (4) TWO byte cursors, not one: retail's destroy-all loop uses r30 and its
//       copy loop r28, so `off2` (destroy) and `off` (copy) are separate
//       variables.  One shared `off` puts the destroy loop's cursor in r28 and
//       loses 0x800A45EC..0x800A462C.
//
// WHAT IS LEFT (the exact residual):
//   (A) HARD-REG TRANSPOSITION — `self` and `i` are swapped and this alone
//       accounts for ~45 of the 52 mismatched words:
//         retail: self=r31  i=r29      build: self=r29  i=r31
//       Everything else is identical: dp+off2=r30, off3+zero2=r28, hash=r27,
//       m=r26, np=r25, zero3=r24, n=r3.
//       RULED OUT: declaration order is irrelevant here — moving `i` before
//       the pointers, moving it last, and +12 dummy locals all leave the
//       transposition untouched; `Cont *s = self;` (making it a plain local
//       instead of a PARM_DECL) also does not move it.  Splitting the count
//       loop's counter into a second variable DOES free `self` to r31, but the
//       new counter then goes to CTR (`mtctr`/`bdnz` instead of the want's
//       `addic. r29,r29,-1`/`bne`) and the body drops to 460B.  So the
//       counter must be the same variable as the two later loop indices
//       (retail's r29 is one variable across all three loops) and the
//       transposition survives that.
//   (B) count-loop copy order (0x800A4594/0x800A45AC): retail materialises
//       the long-lived `n` home BEFORE the `ble` and copies n->i after it; the
//       build emits both copies inside the guarded block in the other order.
//       Assigning `n = self->n;` outside the `if` does produce the want's
//       shape but then GCC folds the load into n's reg and the `mr` vanishes
//       (460B, DIFF).
//   (C) loop-3 preheader order (0x800A46A0..0x800A46AC): retail
//       `li r24,0 / ori r27,r27 / li r28,0 / mr r30,r25`, the build emits the
//       exact reverse `li r28,0 / mr r30,r25 / ori r27,r27 / li r24,0`.
//       Swapping `off = 0;` / `dp = np;` in the source moves `dp` but not the
//       hash/zero pair, so it is the hoisted-invariant order, not the statement
//       order.
//   NOTE for the next agent: b11's "base pointer in a call-clobbered home"
//   trick does NOT apply here — retail never holds `self->arr` in a register
//   across the `CStruct_delete` calls, it re-reads `lwz rX,0(r31)` every time,
//   and there is no base local to kill.
// family=m2c range=0x800A456C-0x800A473C size=464B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"
#include "qb_constants.h"

// 0x14-byte array element.
typedef struct {
    s32 unk0;
    s32 unk4;   /* QB_NULL_SCRIPT hash */
    s32 unk8;
    s32 unkC;   /* CStruct* cleared here */
    s32 unk10;
} Entry;

// this: { Entry *arr; s32 n; s32 pad8; s32 flag; }
typedef struct {
    Entry *arr;
    s32 n;
    s32 pad8;
    s32 flag;
} Cont;

void CStruct_delete(void *, s32);
s32 Mem_Alloc(s32);
void Mem_Free2(void *);
void fn_8000F2F8(void *, s32);
s32 fn_8000F320(void *);
extern s32 lbl_802FFE98;

void fn_800A456C(Cont *self) {
    Entry *np;
    Entry *dp;
    Entry *sp;
    s32 cnt, m, n, i, off, off2, h, v8, vC;
    s32 *q;

    if (self->arr == NULL) {
        return;
    }
    cnt = 0;
    if (self->n > 0) {
        /* only read below when the loop above ran at least once */
        n = self->n;
        i = n;
        q = (s32 *)((char *)self->arr + 4);
        do {
            h = *q;
            q = (s32 *)((char *)q + 0x14);
            if (h == QB_NULL_SCRIPT) {
                cnt++;
            }
        } while (--i != 0);
    }
    if (cnt == 0) {
        return;
    }
    self->flag = 1;
    m = n - cnt;
    if (m == 0) {
        if (m < n) {
            i = 0;
            off2 = 0;
            do {
                sp = (Entry *)((char *)self->arr + off2);
                if (sp->unkC != 0) {
                    CStruct_delete((void *)sp->unkC, 3);
                    ((Entry *)((char *)self->arr + off2))->unkC = 0;
                }
                i++;
                off2 += 0x14;
            } while (i < self->n);
        }
        if (self->arr != NULL) {
            Mem_Free2(self->arr);
        }
        self->arr = NULL;
        self->n = 0;
        return;
    }
    i = 0;
    fn_8000F2F8((void *)lbl_802FFE98, *(s32 *)((char *)lbl_802FFE98 + 0x124));
    np = (Entry *)Mem_Alloc(m * 0x14);
    fn_8000F320((void *)lbl_802FFE98);
    if (i < self->n) {
        off = 0;
        dp = np;
        do {
            sp = (Entry *)((char *)self->arr + off);
            h = sp->unk4;
            if (h != QB_NULL_SCRIPT) {
                v8 = sp->unk8;
                vC = sp->unkC;
                dp->unk0 = *(s32 *)((char *)self->arr + off);
                dp->unk4 = h;
                dp->unk8 = v8;
                dp->unkC = vC;
                dp->unk10 = sp->unk10;
                dp = (Entry *)((char *)dp + 0x14);
            } else if (sp->unkC != 0) {
                CStruct_delete((void *)sp->unkC, 3);
                ((Entry *)((char *)self->arr + off))->unkC = 0;
            }
            i++;
            off += 0x14;
        } while (i < self->n);
    }
    if (self->arr != NULL) {
        Mem_Free2(self->arr);
    }
    self->arr = np;
    self->n = m;
}