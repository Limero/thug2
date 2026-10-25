// WIP DRAFT (non-matching) — hand rebuild.
// family=hand range=0x8021D2C4-0x8021D358 size=148B
// INERT: not registered in splits.txt/configure.py — never compiled,
// not counted in objdiff progress. activate via tools/wip.py.
//
// Walks the manager's enumerator: fills a 16-byte record on the frame (word 4
// = 0, word 8 = the label sentinel), opens the enumeration with fn_8021D454,
// then advances with fn_8021D4E8 until an entry whose +0x1C id matches arg1
// shows up. The record is re-armed before every return path.
//
// PARKED 2026-10-22: 91.89% (34/37 words), object size exact. Residual is a
// 3-word SCHEDULING rotation in the entry block. The record address is born in
// the argument register and copied into the callee-saved home, exactly as the
// promoted twin fn_80216C4C does it: a short-lived alias pinned to r4
// (q = &sp8, stores through q) plus the long-lived home (p) taken from it after
// the stores. That reproduces the whole prologue (`addi r4,r1,8` birth,
// `mr r30,r4` home, stores addressed off r4, stmw r28 frame 0x28) and the
// arg1/label colouring (r29/r28, forced by pinning arg1 to r29).
//
// The residual: retail emits `mr r30,r4`, then the word-4 zero store, then the
// word-8 sentinel store; sched2 hoists the sentinel store above the copy and
// leaves the zero store below it. Source statement order, `p = q` placement,
// a volatile record, and -fno-schedule-insns(2) were each measured and all
// miss (volatile keeps the store order but sinks both stores below the
// argument copies and loses arg1's r29 colouring). Both stores are plain word
// stores through the same base, so the reorder is not alienable from C by
// ordering alone, and the object is already the exact size.
#include "types.h"
#include "structs.h"

extern char lbl_802A83F8[];
void *fn_8021D454(s32 arg0, void *out, s32 flag);
void *fn_8021D4E8(s32 arg0, void *out, s32 flag);

typedef struct Rec {
    s32 f0;
    s32 f4;
    char *f8;
    s32 fC;
} Rec;

typedef struct Entry {
    s32 pad[7];
    s32 id;
} Entry;

void *fn_8021D2C4(s32 arg0, s32 arg1_) {
    register s32 arg1 __asm__("r29") = arg1_;
    Rec sp8;
    register Rec *q __asm__("r4");
    Rec *p;
    Entry *entry;

    q = &sp8;
    q->f8 = lbl_802A83F8;
    q->f4 = 0;
    p = q;
    entry = fn_8021D454(arg0, q, 1);
    if (entry != NULL) {
        do {
            if (entry->id == arg1) {
                p->f8 = lbl_802A83F8;
                return entry;
            }
            entry = fn_8021D4E8(arg0, &sp8, 1);
        } while (entry != NULL);
    }
    p->f8 = lbl_802A83F8;
    return NULL;
}
