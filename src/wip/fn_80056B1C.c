// WIP DRAFT (non-matching) — C body reconstructed by hand from the retail bytes
// family=m2c range=0x80056B1C-0x80057298 size=1916B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// PARKED 2026-10-05 (w_80056B1C): full hand reconstruction of the 1916B body
// (semantics now correct: 27/27 `bl`, 5/5 `blrl`, 5/5 `lha 8(r9)`, 4/4 `andi.`,
// 1/1 `cmpw`, 6/6 `mtlr` — same call graph and same data flow as retail), but
// NOT byte-exact. Best measured: want_got 3.60% masked, object 1888B = 7 words
// short of 1916; instruction-sequence alignment 7.7%. Verdict DIFF.
// RESIDUAL: the prologue and register allocation. This body opens with a larger
// 0xb0 frame that additionally saves the condition-register field and starts its
// register save at r18 with the link-register slot at 0xb4 and the
// condition-register slot at 0x74, where the want opens with a smaller 0xa0 frame
// saving from r20 at 0x70 with the link slot at 0xa4 and immediately copies the
// first two arguments into r25 and r24 — i.e. this compiler needs fourteen
// callee-saved registers plus a spilled condition field where retail needs
// twelve, so every later instruction is shifted and re-numbered. This body also
// emits 2 dead `lis` (r18/r19) holding the CSE'd HI
// halves of lbl_80293290/lbl_80293260 that retail rematerialises (that is the
// 7-word shortfall; retail keeps only ONE such long-lived HI, r20 = 0x80290000).
// Structure that IS now right and should not be touched: the initialiser store
// ORDER matches retail instruction-for-instruction
// (A.4,A.8,A.14,A.C,A.10 | B.14=3260,B.4,B.8,B.C,B.10 | C.14=3260,B.14=3248,
// C.4,C.8,C.C,C.10 | D.14=3290,C.14=3248,D.4,D.8,D.14=3278,D.C,D.10) — this
// required declaring the four stack records as locals reached through local
// POINTER variables assigned lazily inside the guard; with direct `sp8.unk0x4=`
// access GCC's CSE dead-store-eliminates retail's three duplicate
// `unk0x14` stores and the object loses 3 words (tried: <scratch>).
// RULED OUT: -fno-schedule-insns / -fno-schedule-insns2 / both together
// (recipes 48/49; 1.68% -> 2.53% only); the `lbl_802FFE98` load must be written
// as `*(void **)&lbl_802FFE98` with arg2 chained off the loaded pointer — the
// bare `*(void**)0x802FFE98` literal form makes GCC emit 3 instructions
// (`lis/ori/lwz`) where retail emits 2 (`lis/lwz`) and it decodes arg2 as a
// load from 0x802FFFB0 instead of `->0x118`. NOT a scheduling-only park: at
// 479 instructions the whole allocation has to line up; per-`register`
// `asm()` pinning of the ~10 live values is the only untried lever and is a
// lottery, not a fix.
// NOTE the previous m2c body scored 9.47% but was 396B (99 words) SHORT with a
// 0x148 frame — it modelled the four stack records as FILE-SCOPE statics, i.e. a
// structurally different function; want_got flags that percentage as
// MEANINGLESS. This body is the honest reconstruction and keeps the length.
#include "types.h"
#include "structs.h"

extern char lbl_80293248[];
extern char lbl_80293260[];
extern char lbl_80293278[];
extern char lbl_80293290[];
extern s32 lbl_802FFE98;

/* method descriptor: +8 s16 this-relative offset, +0xC method pointer
   (call is mtlr/blrl, so it must be a real function-pointer type). */
typedef struct Desc {
    s32 unk0x0;
    s32 unk0x4;
    s16 unk0x8;
    s16 unk0xA;
    s32 (*unk0xC)(void *, s16);
} Desc;

/* script object: fn_80057C90 reads +0x0, fn_800582C0 reads +4 (flag bits),
   fn_800582B8 reads +0x14, teardown descriptor at +0x18. */
typedef struct Obj {
    s32 unk0x0;
    s32 unk0x4;
    char pad0x8[0x10];
    Desc *unk0x18;
} Obj;

/* 0x18-byte intrusive list node: -1 payload marks the circular sentinel. */
typedef struct Node {
    char pad0x0[0x4];
    s32 unk0x4;
    s32 unk0x8;
    struct Node *unk0xC;
    struct Node *unk0x10;
    Desc *unk0x14;
} Node;

void *Mem_NewZero(s32);
void fn_8000F2F8(void *, void *);
void fn_8000F320(void *);
s32 fn_800577B4(CStruct *, s32 *);
void fn_800577A0(CStruct *);
s32 fn_800582B8(CStruct *);
s32 fn_800582C0(CStruct *);
void fn_800583FC(CStruct *, s32);
void fn_8005840C(CStruct *, s32);
s32 fn_80057C90(CStruct *);
void fn_8000913C(CStruct *, s32 *);
void fn_80106AD4(s32, void *, void *, void *);

void fn_80056B1C(Unk_CFB386B2 *arg0, Unk_C7387A53 *arg1) {
    Node sp8;
    Node sp20;
    Node sp38;
    Node sp50;
    s32 sp68;
    s32 cnt;
    Node *a;
    Node *b;
    Node *c;
    Node *d;
    Node *n;
    Node *nx;
    Node *q;
    Node *nn;
    s32 f1;
    Obj *pay;
    Desc *vt;

    if (arg0->unk0xD4 != 0) {
        a = &sp8;
        a->unk0x4 = -1;
        a->unk0x8 = 0;
        a->unk0x14 = (Desc *)lbl_80293248;
        a->unk0xC = a;
        a->unk0x10 = a;
        b = &sp20;
        b->unk0x14 = (Desc *)lbl_80293260;
        b->unk0x4 = -1;
        b->unk0x8 = 0;
        b->unk0xC = b;
        b->unk0x10 = b;
        c = &sp38;
        c->unk0x14 = (Desc *)lbl_80293260;
        b->unk0x14 = (Desc *)lbl_80293248;
        c->unk0x4 = -1;
        c->unk0x8 = 0;
        c->unk0xC = c;
        c->unk0x10 = c;
        d = &sp50;
        d->unk0x14 = (Desc *)lbl_80293290;
        c->unk0x14 = (Desc *)lbl_80293248;
        d->unk0x4 = -1;
        d->unk0x8 = 0;
        d->unk0xC = d;
        d->unk0x10 = d;
        d->unk0x14 = (Desc *)lbl_80293278;
        fn_8000F2F8(*(void **)&lbl_802FFE98, *(void **)((char *)*(void **)&lbl_802FFE98 + 0x118));
        fn_800577A0(arg0->unk0xD0);
        if (arg1 != 0) {
            for (;;) {
                pay = (Obj *)fn_800577B4(arg0->unk0xD0, 0);
                if (pay == 0) {
                    break;
                }
                if (fn_800582C0(pay) & 4) {
                    n = (Node *)Mem_NewZero(0x18);
                    n->unk0x4 = fn_800582B8(pay);
                    n->unk0x14 = (Desc *)lbl_80293260;
                    n->unk0x8 = 0;
                    n->unk0xC = n;
                    n->unk0x10 = n;
                    n->unk0xC = a;
                    n->unk0x10 = a->unk0x10;
                    a->unk0x10->unk0xC = n;
                    a->unk0x10 = n;
                    fn_8005840C(pay, 4);
                    fn_800583FC(pay, 0x40);
                }
                if (fn_800582C0(pay) & 0x18) {
                    nn = (Node *)Mem_NewZero(0x18);
                    nn->unk0x4 = fn_800582B8(pay);
                    nn->unk0x8 = 0;
                    nn->unk0x14 = (Desc *)lbl_80293260;
                    nn->unk0xC = nn;
                    nn->unk0x10 = nn;
                    nn->unk0xC = b;
                    nn->unk0x10 = b->unk0x10;
                    b->unk0x10->unk0xC = nn;
                    b->unk0x10 = nn;
                    if (fn_800582C0(pay) & 8) {
                        n = (Node *)Mem_NewZero(0x18);
                        n->unk0xC = n;
                        n->unk0x10 = n;
                        n->unk0x8 = 0;
                        n->unk0x14 = (Desc *)lbl_80293290;
                        n->unk0x4 = (s32)pay;
                        n->unk0xC = d;
                        n->unk0x10 = d->unk0x10;
                        d->unk0x10->unk0xC = n;
                        d->unk0x10 = n;
                    } else {
                        fn_8005840C(pay, 0x10);
                    }
                }
                if (fn_800582C0(pay) & 0x20) {
                    n = (Node *)Mem_NewZero(0x18);
                    n->unk0x4 = fn_800582B8(pay);
                    n->unk0x14 = (Desc *)lbl_80293260;
                    n->unk0x8 = 0;
                    n->unk0xC = n;
                    n->unk0x10 = n;
                    n->unk0xC = c;
                    n->unk0x10 = c->unk0x10;
                    c->unk0x10->unk0xC = n;
                    c->unk0x10 = n;
                    fn_8005840C(pay, 0x20);
                }
            }
            q = arg1->unk0xC;
            if (q->unk0x4 == -1) {
                q = 0;
            }
            if (q != 0) {
                do {
                    nn = q->unk0xC;
                    if (nn->unk0x4 == -1) {
                        nn = 0;
                    }
                    f1 = 1;
                    pay = (Obj *)q->unk0x4;
                    cnt = 0;
                    n = b->unk0xC;
                    if (n->unk0x4 == -1) {
                        n = 0;
                    }
                    while (n != 0) {
                        n = n->unk0xC;
                        cnt += 1;
                        if (n->unk0x4 == -1) {
                            n = 0;
                        }
                    }
                    if (cnt != 0) {
                        nx = b->unk0xC;
                        if (nx->unk0x4 == -1) {
                            nx = 0;
                        }
                        while (nx != 0) {
                            n = nx->unk0xC;
                            if (n->unk0x4 == -1) {
                                n = 0;
                            }
                            if (nx->unk0x4 == fn_800582B8(pay)) {
                                f1 = 0;
                                break;
                            }
                            nx = n;
                        }
                    }
                    if (f1 != 0) {
                        n = (Node *)Mem_NewZero(0x18);
                        n->unk0x4 = fn_800582B8(pay);
                        n->unk0x14 = (Desc *)lbl_80293260;
                        n->unk0x8 = 0;
                        n->unk0xC = n;
                        n->unk0x10 = n;
                        n->unk0xC = b;
                        n->unk0x10 = b->unk0x10;
                        b->unk0x10->unk0xC = n;
                        b->unk0x10 = n;
                        fn_8005840C(pay, 0x10);
                    }
                    q = nn;
                } while (q != 0);
            }
        }
        fn_8000F320(*(void **)&lbl_802FFE98);
        fn_80106AD4(arg0->unk0xD4, a, b, c);
        cnt = 0;
        n = a->unk0xC;
        if (n->unk0x4 == -1) {
            n = 0;
        }
        while (n != 0) {
            n = n->unk0xC;
            if (n->unk0x4 == -1) {
                n = 0;
            }
            cnt += 1;
        }
        if (cnt != 0) {
            n = a->unk0xC;
            if (n->unk0x4 == -1) {
                n = 0;
            }
            if (n != 0) {
                do {
                    nn = n->unk0xC;
                    if (nn->unk0x4 == -1) {
                        nn = 0;
                    }
                    if (n != 0) {
                        vt = n->unk0x14;
                        vt->unk0xC((char *)n + vt->unk0x8, 3);
                    }
                    n = nn;
                } while (n != 0);
            }
        }
        cnt = 0;
        n = b->unk0xC;
        if (n->unk0x4 == -1) {
            n = 0;
        }
        while (n != 0) {
            n = n->unk0xC;
            if (n->unk0x4 == -1) {
                n = 0;
            }
            cnt += 1;
        }
        if (cnt != 0) {
            n = b->unk0xC;
            if (n->unk0x4 == -1) {
                n = 0;
            }
            if (n != 0) {
                do {
                    nn = n->unk0xC;
                    if (nn->unk0x4 == -1) {
                        nn = 0;
                    }
                    if (n != 0) {
                        vt = n->unk0x14;
                        vt->unk0xC((char *)n + vt->unk0x8, 3);
                    }
                    n = nn;
                } while (n != 0);
            }
        }
        cnt = 0;
        n = c->unk0xC;
        if (n->unk0x4 == -1) {
            n = 0;
        }
        while (n != 0) {
            n = n->unk0xC;
            if (n->unk0x4 == -1) {
                n = 0;
            }
            cnt += 1;
        }
        if (cnt != 0) {
            n = c->unk0xC;
            if (n->unk0x4 == -1) {
                n = 0;
            }
            if (n != 0) {
                do {
                    nn = n->unk0xC;
                    if (nn->unk0x4 == -1) {
                        nn = 0;
                    }
                    if (n != 0) {
                        vt = n->unk0x14;
                        vt->unk0xC((char *)n + vt->unk0x8, 3);
                    }
                    n = nn;
                } while (n != 0);
            }
        }
        cnt = 0;
        n = d->unk0xC;
        if (n->unk0x4 == -1) {
            n = 0;
        }
        while (n != 0) {
            n = n->unk0xC;
            if (n->unk0x4 == -1) {
                n = 0;
            }
            cnt += 1;
        }
        if (cnt != 0) {
            n = d->unk0xC;
            if (n->unk0x4 == -1) {
                n = 0;
            }
            if (n != 0) {
                do {
                    nn = n->unk0xC;
                    if (nn->unk0x4 == -1) {
                        nn = 0;
                    }
                    pay = (Obj *)n->unk0x4;
                    sp68 = fn_80057C90(pay);
                    fn_8000913C(arg0->unk0xD0, &sp68);
                    fn_8005840C(pay, 0x40);
                    if (pay != 0) {
                        vt = pay->unk0x18;
                        vt->unk0xC((char *)pay + vt->unk0x8, 3);
                    }
                    if (n != 0) {
                        vt = n->unk0x14;
                        vt->unk0xC((char *)n + vt->unk0x8, 3);
                    }
                    n = nn;
                } while (n != 0);
            }
        }
        d->unk0x14 = (Desc *)lbl_80293290;
        arg0->unk0x274 = 0;
        d->unk0x10->unk0xC = d->unk0xC;
        d->unk0xC->unk0x10 = d->unk0x10;
        d->unk0x10 = d;
        d->unk0xC = d;
        c->unk0x14 = (Desc *)lbl_80293260;
        c->unk0x10->unk0xC = c->unk0xC;
        c->unk0xC->unk0x10 = c->unk0x10;
        c->unk0x10 = c;
        c->unk0xC = c;
        b->unk0x14 = (Desc *)lbl_80293260;
        b->unk0x10->unk0xC = b->unk0xC;
        b->unk0xC->unk0x10 = b->unk0x10;
        b->unk0x10 = b;
        b->unk0xC = b;
        a->unk0x14 = (Desc *)lbl_80293260;
        a->unk0x10->unk0xC = a->unk0xC;
        a->unk0xC->unk0x10 = a->unk0x10;
        a->unk0x10 = a;
        a->unk0xC = a;
    }
}