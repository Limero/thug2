// 0x80044614 - walk a ref-counted node chain (obj+0x64 -> obj+0x70 -> ...),
// NEAR 9.6% (per-object flags: -fno-thread-jumps -fno-schedule-insns). The
// last gain came from re-emitting a node-name store run in the order the
// original emits it.
// appending each node's name (obj+0x190) plus a separator to the caller's
// buffer until the accumulated strlen reaches the caller's limit.
// Decoded 2026-10-03 from the want + the sibling walk
// 0x800447B4, which shares the cell protocol:
//   * 16-byte ref-cell {node, link, obj, pad} passed BY ADDRESS as
//     CObject_AddRefLink(node, &cell) / CObject_RemoveRefLink(node, &cell)
//     (0x8009dfa0 / 0x8009dfc0 keep obj->unk0x4 as the head of a list of
//     these cells).  Two cells live at +8 and +0x18(r1) => 16-byte cells.
//   * `node = next` is a MOVE-assign: release(node); node = next.node;
//     addref(node); release(next); next = 0.
//   * return 0 (length limit hit) / 1 (chain exhausted).
// family=m2c range=0x80044614-0x800447B4 size=416B
// FLAG: -fno-schedule-insns
//   release cell that jump-threading otherwise deletes; see PARKED note)
void strcat(char *, char *);
void CObject_AddRefLink(void *, void *);
void CObject_RemoveRefLink(void *, void *);
extern char lbl_802924C4[];
extern char lbl_80292518[];

typedef struct {
    void *f0;
    s32 f4;
    s32 f8;
    s32 fC;
} RefCell;

s32 fn_80044614(void *arg0, char *arg1, s32 arg2) {
    RefCell a;
    RefCell b;
    RefCell *pa;
    RefCell *pb;
    s32 total = 0;
    char *name;
    s32 nxt;
    s32 *cur;

    pa = &a;
    *arg1 = lbl_802924C4[0];
    pa->f4 = 0;
    pa->f8 = 0;
    a.f0 = *(void **)((char *)arg0 + 0x64);
    if (a.f0) {
        CObject_AddRefLink(a.f0, pa);
    }
    cur = a.f0;
    while (a.f0) {
        pb = &b;
        nxt = *(s32 *)((char *)a.f0 + 0x70);
        b.f0 = (void *)nxt;
        pb->f8 = 0;
        pb->f4 = 0;
        if (b.f0) {
            CObject_AddRefLink(b.f0, pb);
        }
        name = *(char **)((char *)a.f0 + 0x190);
        total += strlen(name);
        if (b.f0) {
            total++;
        }
        if (total < arg2) {
            strcat(arg1, name);
            if (b.f0) {
                strcat(arg1, lbl_80292518);
            }
        } else {
            if (b.f0) {
                CObject_RemoveRefLink(b.f0, pb);
                b.f0 = 0;
            }
            if (a.f0) {
                CObject_RemoveRefLink(a.f0, pa);
                a.f0 = 0;
            }
            return 0;
        }
        if (a.f0) {
            CObject_RemoveRefLink(a.f0, pa);
            a.f0 = 0;
        }
        a.f0 = b.f0;
        if (b.f0) {
            CObject_AddRefLink(b.f0, pa);
        }
        if (b.f0) {
            CObject_RemoveRefLink(b.f0, pb);
            b.f0 = 0;
        }
        cur = a.f0;
    }
    if (cur) {
        CObject_RemoveRefLink(cur, pa);
        a.f0 = 0;
    }
    return 1;
}
// PARKED 2026-10-03: 6.9% masked, object 404B vs symbol 416B
// (3 insns short).  The body is now a per-instruction structural match of the
// want from 0x8004464C through 0x80044740 plus the whole post-loop tail; the
// residual is EXACTLY three missing instructions, all callee-saved-register
// allocation artifacts, and each one is proven to need a source shape I could
// not reach in C:
//   1+2. A register copy at 0x80044668 and 0x80044778.  The want keeps the
//      post-loop `if (cur)` release as a 2-pred PHI whose incoming loads sit
//      at 0x80044664 and 0x80044774 (each loading a word from frame offset 8
//      into a scratch), followed at each site by a copy of that scratch into
//      the argument register, a null compare of the scratch, and a branch to
//      the exit at the first site and back to the loop at the second; the exit
//      block then tests the phi (address 0x80044784), not the load.
//     i.e. the load pseudo (r0) and the phi pseudo (r3) must stay DISTINCT.
//     Proved: with the flag this draft emits `lwz r3,8(r1); cmpwi r3,0` at both
//     preds - ngccc coalesces the phi input with the phi result, so no copy is
//     needed.  Every C formulation that keeps the block alive (plain `if (a.f0)`
//     after the loop, a `cur` temp assigned before the loop and at the latch, a
//     `cur` assigned only at the latch) collapses to that same shape; the house
//     solution for the identical want at 0x800447B4 and at the MATCHED
//     src/fn_80044C64.c is an asm pin (`register s32 *copy __asm__("r3")` +
//     `__asm__("" : "+r"(copy))`), which makes the value opaque.  I did not use
//     asm (task rule).  `-fthread-jumps` (the default) DELETES the block
//     outright (380B -> phi known-zero on both edges); `-fno-thread-jumps`
//     keeps it, which is why the flag is set.
//   3.   `mr r26,r11` at 0x80044638.  The want homes `&a` in a callee-saved reg
//     (r26, all five call args) while the two cell-zero stores use a SHORT-LIVED
//     scratch copy born at 0x80044630 (`addi r11,r1,8`) - a reload-pass live-
//     range split.  Proved unattainable: `pa = &a` + `pa->f4/f8` (1 pseudo) gives
//     one register; `&a` written directly rematerialises `addi r4,r1,8` at every
//     call site and r1-relative stores (loses the frame); `qa = &a` as a second
//     variable is CSE'd/coalesced back to one register; and `((RefCell*)&a)->f4`
//     is canonicalised to MEM[0xc(r1)].  Note the two MEM-base stores DO use the
//     register base while the node store `a.f0=` uses 8(r1) - that mixed-base
//     signature is already reproduced here.
// Also unsolved: the global saved-register role rotation (want arg2=r25,
// &a=r26, arg1=r27, zero=r28/29, &b=r30, name=r31; got arg2=r25, arg1=r26,
// zero=r27/28, &a=r29, &b=r30, name=r31).  Relative priority order of the two
// zeros vs `&a` is what differs, and it is the same wall as recipes
// "global saved-register role rotation".  A variant with `&a` in the right slot
// (arg1=r27, zero=r28) exists but then rematerialises `&a` per call site and the
// frame drops to 0x40 / stmw r26.
// The previous m2c husk scored 17.3% (20.0% official) only because its second
// cell was allocated at +0xC, a 2-insn offset that resynchronised the positional
// compare for 12 instructions; it is semantically broken (cell overlap, the
// `total += 1` separator dropped as `if (0)`, `>=` split as `!= arg2`) and can
// never match.  Do not "restore" it.
