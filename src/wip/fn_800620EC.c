// WIP DRAFT (non-matching) — C body hand-written for the fn_800620EC list teardown
// family=m2c range=0x800620EC-0x80062250 size=356B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// Identification: registry destructor. Walks the doubly-linked node list at
// arg0+0x10 twice (destroy-then-unlink, then unlink-and-free), then clears the
// u16 counters at arg0+0x4A/0x4C/0x4E. Same node as fn_80062250 /
// fn_8006230C / fn_80061F9C (see the matched fn_8006230C.c for the slot idiom).
//
// PARKED 2026-10-02 (w75/0x800620EC): 85.4% NEAR (13 of 89 words differ), all
// of it ngccc register-allocation coin-flips that pure C cannot reach.
// Tried and REJECTED as hypotheses (each scored worse or restructured the frame):
//   - plain-C rewrite with no stack-slot struct            1.1% (frame 0x20)
//   - m2c draft as-is                                     10.1%
//   - 10 padded volatile slot fields (house idiom)       64.0%  <-- the big win
//   - + explicit loop-terminator temps (want mem-op order)67.4%
//   - + one variable per live-range role (r0/r11/r10 split)74.2%
//   - + split loop-1 preheader/tail cursors               83.1%  <-- big win
//   - + temp for the 2nd `c->next` reload                 85.4%  <-- best
//   - `-fno-schedule-insns` 18.0%, `-fno-schedule-insns2` 55.1%, `-fno-gcse` 71.9%
// 2026-10-12: a0=r29 HARD PIN (register Reg *a0 __asm__("r29"), all arg0 uses
// via a0) FIXES Residual A wholesale (11 words) -- homes + all r29/r31 refs
// exact. Cost: loop2 latch reschedules (12w rotation) + tail rotates; tail
// recovered to 2w via [slot18=slot20][f4E][f4A][f4C] order (load-use gap
// deterministically fills li+sth4e; other rotations worse). lp->r31 pin alone
// explodes (frame 0x60, 77%). Net 85.4% -> 82.0% (pin) -> 82.02% (tail).
// Residual A (11 words, the whole r29/r31 class): WANT homes `arg0` in r29 and
//   `&arg0->list` in r31 (`mr r29,r3` / `addi r31,r29,0x10`); every C form
//   homes them the other way round (`mr r31,r3` / `addi r29,r31,0x10`). Tried:
//   dropping the `lp` variable (v20 -> 10.1%, frame collapses to 0x60 and the
//   head reload becomes `0x10(r31)`), `register List *lp`, `lp` declared first /
//   last, `lp = &arg0->list` hoisted to the first statement, a local copy of
//   the parameter, raising arg0's reference count (extra `arg0->list.head`
//   reads in the guard and the slot08 store), and rebalancing refs into/out of
//   loop2 via `arg0->list.count--` / `arg0->list.head` (rtl-cse folds all of
//   them back onto the `lp` pseudo, so arg0 gains no in-loop refs and can never
//   out-rank `lp`). This is the §6a-6 / §6q-133 "saved-reg allocation
//   coin-flip" family, documented as reachable only via a hard register pin
//   (`register s32 a0 __asm__("r29"); a0 = arg0;`), which this pass may not use.
// Residual B (2 words): in the loop-1 `pay->unk0xC` arm WANT emits
//   `lwz r30,4(r9); mr r3,r9` and GOT emits `mr r3,r9; lwz r30,4(r9)` — the
//   pre-RA scheduler hoists the call's r3 arg-copy over the `owner` load.
//   Tried: `owner` at block/function scope, `owner` volatile, `Sub *q = sub`
//   copy, comma-expression call pair, `pay`/`sub` at function scope, `s32 owner`
//   with a void-returning proto, `(s32)1` arg, per-parameter proto types.
typedef struct Node Node;
typedef struct Sub Sub;
typedef struct Pay Pay;
typedef struct List List;
typedef struct Reg Reg;

struct Sub {
    char pad0x0[0x4];
    void *owner;
};

struct Pay {
    void *unk0x0;
    char pad0x4[0x8];
    Sub *unk0xC;
};

struct Node {
    Pay *pay;
    Node *next;
    Node *prev;
    char pad0xC[0x4];
};

struct List {
    Node *head;
    s32 count;
};

struct Reg {
    char pad0x0[0x10];
    List list;
    char pad0x18[0x32];
    u16 f4A;
    u16 f4C;
    u16 f4E;
};

void Mem_Free(void *);
void fn_80055228(void *);
s32 fn_8005546C(void *, s32);
s32 fn_8005D734(void *);

void fn_800620EC(Reg *arg0) {
    /* Ten 8-byte-strided volatile slots: WANT keeps every list cursor, every
       loop terminator and four write-only copies of the walker in memory, which
       is what produces the 0x68 frame and the per-iteration reloads. */
    struct {
        Node *volatile slot08;
        s32 pad0C;
        Node *volatile slot10;
        s32 pad14;
        Node *volatile slot18;
        s32 pad1C;
        Node *volatile slot20;
        s32 pad24;
        Node *volatile slot28;
        s32 pad2C;
        Node *volatile slot30;
        s32 pad34;
        Node *volatile slot38;
        s32 pad3C;
        Node *volatile slot40;
        s32 pad44;
        Node *volatile slot50;
        s32 pad4C;
        Node *volatile slot48;
        s32 pad54;
    } s;
    Node *h1;
    Node *w1;
    Node *wt;
    Node *ht;
    Node *nt;
    Node *h2;
    Node *w2;
    Node *c;
    Node *hb;
    Node *nb;
    Node *nx2;
    List *lp;
    register Reg *a0 __asm__("r29");

    /* pass 1: run the per-node destructor, then free the payload */
    a0 = arg0;
    h1 = a0->list.head;
    s.slot08 = h1;
    w1 = NULL;
    if (h1 != NULL) {
        w1 = h1->next;
    }
    s.slot10 = w1;
    lp = &a0->list;
    if (w1 == h1) {
        goto part2;
    }
loop1:
    fn_80055228(s.slot10->pay->unk0x0);
    {
        Sub *sub = s.slot10->pay->unk0xC;
        if (sub != NULL) {
            void *owner = sub->owner;
            fn_8005546C(sub, 1);
            fn_8005D734(owner);
        }
    }
    Mem_Free(s.slot10->pay);
    /* WANT reloads slot10 then slot08 then derefs: separate tail variables. */
    wt = s.slot10;
    ht = s.slot08;
    nt = wt->next;
    s.slot10 = nt;
    if (nt != ht) {
        goto loop1;
    }

    /* pass 2: unlink and free every node */
part2:
    h2 = a0->list.head;
    w2 = NULL;
    if (h2 != NULL) {
        w2 = h2->next;
    }
    hb = lp->head;
    s.slot20 = w2;
    s.slot28 = hb;
    if (w2 == hb) {
        goto tail;
    }
loop2:
    c = s.slot20;
    nb = c->next;
    s.slot40 = c;
    s.slot38 = c;
    s.slot20 = nb;
    s.slot50 = c;
    nx2 = c->next;
    s.slot48 = c;
    s.slot38 = nx2;
    if (c != lp->head) {
        c->prev->next = c->next;
        c->next->prev = c->prev;
        Mem_Free(c);
        lp->count--;
    }
    {
        Node *n38 = s.slot38;
        Node *n20 = s.slot20;
        Node *n28 = s.slot28;
        s.slot30 = n38;
        if (n20 != n28) {
            goto loop2;
        }
    }

tail:
    s.slot18 = s.slot20;
    a0->f4A = 0;
    a0->f4E = 0;
    a0->f4C = 0;
}
// 2026-10-22: 87.6% (was 84.3%): `slot50`/`pad4C` declared before `slot48`; `nb = c->next` above `s.slot40 = c`.
