// REBUILD 2026-10-17 from full want decode (2026-10-13 draft was 4.6% DIFF).
// CORRECTED SHAPE (verified against want, all load/store/call targets check
// out): THREE args (middle s32 unused — want never touches r4/r6),
// saved=r5->r7 early, link=NULL or node->link homed via *volatile local*
// (`Node3698 *volatile mem` — NOT `volatile Node3698 *mem`, which leaves the
// local itself non-volatile and emits nothing), base=&arg0->f_1C (r9),
// cur=base (r8), count=base->link-as-int, AddInteger(saved->f_18, idx+1,
// 0x8FD8B4C3), return 1. Volatile sinks wA(slot10)/wB(slot18) confirmed
// emitting (got frame -0x18 with all three homes; want -0x20).
// PARKED 2026-10-17 at ~40% DIFF, SIZE 172B vs want 200B. Residual: ngccc
// coalesces base/cur (no `mr r8,r9`), keeps idx in r4 instead of r5 (no
// early `mr r7,r5`; saved scheduled late), and restructures the
// idx>=count guard. Needs coloring pressure work (extra live local or
// register pins) — do not re-grind the shape, it is right.
// Shape: node=arg0->f_1C; saved=arg1 (r7); link=NULL or node->link (r10,
// homed to slot8 via volatile mem: plain link is clobbered by t=cur so the
// value must reload from mem each iter); base=&arg0->f_1C (r9),
// cur=base (r8); idx=0; count=base->link-as-int; count==0 -> exit,
// idx>=count -> chk; straight-line first-link check -> chk; do-loop with
// write-only volatile sinks wA(slot10)/wB(slot18); chk: idx!=curval ->
// exit else idx--; exit: AddInteger(saved->f_18, idx+1, magic); return 1.
// family=hand range=0x80203698-0x80203760 size=200B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
#include "types.h"

typedef struct Node3698 {
    void *unk0x0;
    struct Node3698 *unk0x4;
} Node3698;

typedef struct {
    char pad0x0[0x1C];
    Node3698 *unk0x1C;
} Arg0_3698;

typedef struct {
    char pad0x0[0x18];
    s32 unk0x18;
} Arg1_3698;

void AddInteger(s32, s32, s32);

s32 fn_80203698(Arg0_3698 *arg0, s32 arg1, Arg1_3698 *arg2) {
    Node3698 *node;
    Arg1_3698 *saved;
    Node3698 *link;
    Node3698 *volatile mem;
    Node3698 *volatile wA;
    Node3698 *volatile wB;
    Node3698 *base;
    Node3698 *cur;
    Node3698 *t;
    Node3698 *q;
    Node3698 *lv;
    Node3698 *p;
    s32 count;
    s32 idx = 0;

    (void)arg1;
    node = arg0->unk0x1C;
    saved = arg2;
    link = NULL;
    if (node != NULL) {
        link = node->unk0x4;
    }
    mem = link;
    base = (Node3698 *)&arg0->unk0x1C;
    cur = base;
    count = (s32)base->unk0x4;
    if (count == 0) {
        goto exit;
    }
    if (idx >= count) {
        goto chk;
    }
    p = (Node3698 *)link->unk0x0;
    if (p->unk0x4 == NULL) {
        goto chk;
    }
loop:
    t = cur;
    q = (Node3698 *)mem;
    idx += 1;
    wB = q;
    lv = q->unk0x4;
    wA = q;
    mem = lv;
    if (idx >= (s32)t->unk0x4) {
        goto chk;
    }
    p = (Node3698 *)lv->unk0x0;
    if (p->unk0x4 != NULL) {
        goto loop;
    }
chk:
    if (idx != (s32)cur->unk0x4) {
        goto exit;
    }
    idx -= 1;
exit:
    AddInteger(saved->unk0x18, idx + 1, 0x8FD8B4C3);
    return 1;
}
